// Fl_Config.cpp: implementation of the Fl_Config class.
//
//////////////////////////////////////////////////////////////////////

#include <efltk/vsnprintf.h>
#include <efltk/Fl_Config.h>

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

#ifdef _WIN32
# include <io.h>
# define access(a,b) _access(a,b)
# define R_OK 4
#else
# include <unistd.h>
#endif /* _WIN32 */

int conf_is_path_rooted(const char *fn)
{
    /* see if an absolute name was given: */
#ifdef _WIN32
    if (fn[0] == '/' || fn[0] == '.' || fn[0] == '\\' || fn[1]==':')
#else
    if (fn[0] == '/' || fn[0] == '.')
#endif
        return 1;
    return 0;
}

#define CONFIGDIR "ede"
// This should stay public so that programs can locate their config files easily.
const char* fl_find_config_file(const char* fn, bool cflag)
{
    static char path[4096];

    if(conf_is_path_rooted(fn)) {
        strcpy(path, fn);
        return (cflag || !access(path, R_OK)) ? path : 0;
    }
    char *cptr = fl_get_homedir();
    if(cptr) {
        snprintf(path, sizeof(path)-1, "%s%s%s", cptr, "/.ede/", fn);
        if(cflag || !access(path, R_OK)) {
            delete []cptr;
            return path;
        }
        delete []cptr;
    }

    snprintf(path, sizeof(path), CONFIGDIR "/%s", fn);
    return (cflag || !access(path, R_OK)) ? path : 0;
}

#ifdef BACKWARD_COMPATIBLE
Fl_Config *current_config=0;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Fl_Config::Fl_Config(const char *_filename, bool read, bool create)
{
    _error = 0;
    filename = _filename?strdup(_filename):0;
    cur_sec = 0;
    changed=false;

    if(read) read_file(create);
}

Fl_Config::~Fl_Config()
{
    flush();

    Section *s;
    for(s = sections.first(); s != 0; s = sections.next() )
        if(s) delete s;

    if(filename) delete []filename;

#ifdef BACKWARD_COMPATIBLE
    if(current_config==this) current_config=0;
#endif
}

/* get error string associated with error number */
const char *Fl_Config::strerror(int error)
{
    switch(error)
    {
    case CONF_SUCCESS: return "successful completion";
    case CONF_ERR_FILE: return "could not access config file";
    case CONF_ERR_SECTION: return "config file section not found";
    case CONF_ERR_KEY: return "key not found in section";
    case CONF_ERR_MEMORY: return "could not allocate memory";
    case CONF_ERR_NOVALUE: return "invalid value associated with key";

#ifdef BACKWARD_COMPATIBLE
    case CONF_ERR_AGAIN: return "try operation again (lockfile exists?)";
    case CONF_ERR_ARGUMENT: return "invalid argument";
    case CONF_ERR_DEPTH: return "section or include nesting too deep";
#endif

    default: return "unknown error";
    }
}

bool Fl_Config::read_file(bool create)
{
    bool error = false;
    if(filename)
    {
        if(create && !fl_file_exists(filename))
        {
            FILE *f = fopen(filename, "w+");
            if(f) {
                fputs("\n",f);
                fclose(f);
            } else error=true;
        }
    } else error=true;

    if(error) {
        _error = CONF_ERR_FILE;
        return false;
    }

    // If somebody calls this function two times, we
    // need to clean earlier section list...
    Section *s;
    for(s = sections.first(); s != 0; s = sections.next() )
        delete s;

    sections.clear();

    /////
    FILE *fp = fopen(filename, "rw+");
    if(!fp) {
        //fprintf(stderr, "fp == 0: %s\n", filename);
        _error = CONF_ERR_FILE;
        return false;
    }

    struct stat fileStat;
    stat(filename, &fileStat);
    unsigned int size = fileStat.st_size;
    if(size == 0) {
        _error = 0;
        return true;
    }

    char *buffer, *lines, *tmp;
    if( (buffer = new char[size]) == 0) {
        _error = CONF_ERR_MEMORY;
        return false;
    }

    unsigned int readed = fread(buffer, 1, size, fp);
    if(readed <= 0)
    {
        fclose(fp);
        _error = CONF_ERR_FILE;
        return false;
    }
    fclose(fp);

    Section *section = 0;
    char *ptr = buffer;
    lines = strtok(ptr, "\n");
    while(lines != 0)
    {
        if(lines)
        {
            while(*lines && (*lines==' '||*lines=='\t')) lines++;

            if (lines[0] == '[')
            {
                if ((tmp = strchr(lines, ']')))
                {
                    *tmp = '\0';
                    section = create_section(&lines[1]);
                }
            }
            else if (lines[0] != '#' && section)
            {
                tmp = strchr(lines, '=');
                if(!tmp) tmp = strchr(lines, ':');
                if(tmp)
                {
                    *tmp = '\0';
                    tmp++;
                    create_string(section, lines, tmp);
                }
            }
        }

        lines = strtok(NULL,"\n");
    }

    if(buffer)
        delete []buffer;

    _error = 0;
    changed=false;
    return true;
}

void Fl_Config::write_section(int indent, FILE *fp, Section *sec)
{
    Section *child;
    for(int a=0; a<indent; a++) fprintf(fp, " ");

    fprintf(fp, "[%s%s]\n", sec->path, sec->name);

    for(Line *l = sec->lines.first(); l!=0; l = sec->lines.next() )
        if(l && l->key) {
            for(int a=0; a<indent; a++) fprintf(fp, " ");
            fprintf(fp, "  %s=%s\n", l->key, l->value?l->value:"");
        }

    fprintf(fp, "\n");

    for(child = sec->sections.first(); child!=0; child=sec->sections.next()) {
        write_section(indent+2, fp, child);
    }
}

bool Fl_Config::flush()
{
    if(!changed) return true;

    FILE *file;
    if(!filename || !(file = fopen(filename, "w"))) {
        _error = CONF_ERR_FILE;
        return false;
    }

    Section *s;
    for(s = sections.first(); s != 0; s = sections.next() )
        if(s)
        {
            write_section(0, file, s);
        }

    fclose(file);
    _error = 0;

    changed=false;

    return true;
}

Line *Fl_Config::create_string(Section *section, const char * key, const char * value)
{
    Line *line = new Line(key, value);

    line->key = fl_trim(line->key);
    if(line->value) {
        line->value = fl_trim(line->value);
    }

    section->lines.append(line);
    return line;
}

Section *Fl_Config::create_section(const char *name)
{
    Section *section = find_section(name, true);
    if(section) return section;

    Section *parent=0;
    char secpath[1024]={0}, secname[256]={0};
    int namelen=strlen(name);
    const char *ptr=name+namelen-1;
    char ch;
    bool gotname=false;
    int namebegin=namelen;
    while((ch=*ptr--)) {
        namebegin--;
        if(ch=='/') {
            if(!gotname) {
                strncpy(secname, name+(namebegin+1), namelen-namebegin-1);
                gotname = true;
                break;
            }
        }
    }

    if(!gotname) strncpy(secname, name, sizeof(secname)-1);
    if(gotname) strncpy(secpath, name, namebegin+1);

    Fl_PtrList <Section> *list;

    if(*secpath) {
        parent = find_section(secpath, false);

        if(!parent) {
            // Add all parent sections!

            char tmp[256]={0}, *tmpptr = tmp;
            char tmppath[1024]={0};
            char *ptr = secpath; int pos=0;
            while( (ch=*ptr++) ) {
                if(ch=='/') {
                    if(parent) list = &parent->sections;
                    else list = &sections;

                    parent = new Section(tmp, tmppath, parent);
                    list->append(parent);

                    memset(tmp, 0, sizeof(tmp));
                    tmpptr = tmp;

                    strncpy(tmppath+pos, tmpptr, strlen(tmpptr));
                    pos+=strlen(tmpptr);
                    strncpy(tmppath+pos, "/", 1);
                    pos++;

                    continue;
                }
                *tmpptr++ = ch;
            }
        }

    }

    if(parent) list = &parent->sections;
    else list = &sections;

    section = new Section(secname, secpath, parent);
    list->append(section);

    return section;
}

Section *Fl_Config::find_section(const char *path, bool perfect_match)
{
    if(!path || !*path) return 0;

    int last_slash = -1, pos=0;

    Section *section=0;
    char sec[256]={0};
    const char *pathptr = path;
    char *secptr = sec;
    char ch;
    while((ch=*pathptr++)) {
        pos++;
        if(ch=='/')
        {
            last_slash=pos;
            Section *tmp = find_section(section, sec, false);
            if(!tmp) if(perfect_match) return 0; else break;
            section = tmp;

            memset(sec, 0, sizeof(sec));
            secptr = sec;
        } else
            *secptr++ = ch;
    }

    if(last_slash==-1) {
        return find_section(0, path, false);
    } else
    if(last_slash<pos) {
        Section *tmp = find_section(section, sec, false);
        if(!tmp&&perfect_match) return 0;
        else if(tmp) section = tmp;
    }

    return section;
}

Section *Fl_Config::find_section(Section *sec, const char *name, bool recursive)
{
    Fl_PtrList<Section> *list = sec?&sec->sections:&sections;
    Section *s;
    for(s = list->first(); s != 0; s = list->next() )
        if(s)
        {
            if(!strcmp(s->name, name)) {
                _error = 0;
                return s;
            }
            if(recursive) {
                s = find_section(s, name, recursive);
                if(s) return s;
            }
        }

    _error = CONF_ERR_SECTION;
    return 0;
}

Line *Fl_Config::find_string(Section *section, const char *key)
{
    if(key) {
        Line *line;
        for(line = section->lines.first(); line != 0; line = section->lines.next() ) {
            if(line) {
                if( line->key && !strcmp(line->key, key) ) {
                    _error = 0;
                    return line;
                }
            }
        }
    }

    _error = CONF_ERR_KEY;
    return 0;
}

void Fl_Config::remove_key(const char *section, const char *key)
{
    if(key) {
        Section *sect;
        Line *line;

        if((sect = find_section(section, true)) != 0) {
            if ((line = find_string(sect, key)) != 0) {
                sect->lines.remove(line);
                delete line;
                _error = 0;
                changed = true;
#ifdef BACKWARD_COMPATIBLE
                current_config=this;
#endif
                return;
            }
        }
    }
    _error = CONF_ERR_KEY;
}

void Fl_Config::remove_sec(const char *section)
{
    if(section) {
        Section *sect;
        if((sect = find_section(section, true)) != 0) {
            if(sect->parent) {
                sect->parent->sections.remove(sect);
            } else {
                sections.remove(sect);
            }
            delete sect;
            _error = 0;
            changed = true;
#ifdef BACKWARD_COMPATIBLE
            current_config=this;
#endif
            return;
        }
    }

    _error = CONF_ERR_SECTION;
}

/*
 *  Read functions
 */

char *Fl_Config::read_string(Section *s, const char *key)
{
    if(!key) {
        _error = CONF_ERR_KEY;
        return 0;
    }
    if(!s) {
        _error = CONF_ERR_SECTION;
        return 0;
    }

    Line *l = find_string(s, key);
    if(l&&l->value)
    {
        char *tmp = strchr(l->value, '#');
        if(tmp) *tmp = '\0';
        _error = 0;
        return strdup(l->value);
    }

    _error = CONF_ERR_KEY;
    return 0;
}

long Fl_Config::read_long(Section *s, const char *key)
{
    char *k = read_string(s, key);
    if(!k) return 0;
    long ret = atol(k);
    delete []k;
    return ret;
}

int Fl_Config::read_int(Section *s, const char *key)
{
    char *k = read_string(s, key);
    if(!k) return 0;
    int ret = atoi(k);
    delete []k;
    return ret;
}

float Fl_Config::read_float(Section *s, const char *key)
{
    char *k = read_string(s, key);
    if(!k) return 0;
    float ret = (float)atof(k);
    delete []k;
    return ret;
}

bool Fl_Config::read_bool(Section *s, const char *key)
{
    bool ret = false;
    char *k = read_string(s, key);
    if(!k) return false;

    if( !strcasecmp(k, "TRUE") ||
       !strcasecmp(k, "YES") ||
       !strcasecmp(k, "ON") ||
       !strcasecmp(k, "1") ) {

        ret = true;

    } else
    if( !strcasecmp(k, "FALSE") ||
       !strcasecmp(k, "NO") ||
       !strcasecmp(k, "OFF") ||
       !strcasecmp(k, "0") ) {

        ret = false;

    } else {

        _error = CONF_ERR_NOVALUE;
        return false;

    }

    delete []k;
    _error = 0;
    return ret;
}

Fl_Color Fl_Config::read_color(Section *s, const char *key)
{
    char *k = read_string(s, key);
    if(!k) return FL_BLACK;

    int r=0,g=0,b=0;
    if(sscanf(k, "RGB(%d,%d,%d)", &r, &g, &b)!=3) {
        _error = CONF_ERR_NOVALUE;
        return FL_BLACK;
    }
    delete []k;
    _error = 0;
    return fl_rgb(r,g,b);
}

/*
 *  Write functions
 */

void Fl_Config::write_string(Section *s, const char *key, const char *value)
{
    if(!key) {
        _error = CONF_ERR_KEY;
        return;
    }
    if(!s) {
        _error = CONF_ERR_SECTION;
        return;
    }
    Line *line;
    if((line = find_string(s, key)))
    {
        if(line->value) delete []line->value;
        line->value = value?strdup(value):0;
    }
    else
        create_string(s, key, value);

    changed=true;

#ifdef BACKWARD_COMPATIBLE
    current_config=this;
#endif
}

void Fl_Config::write_long(Section *s, const char *key, const long value)
{
    char tmp[128];
    sprintf(tmp, "%ld", value);
    write_string(s, key, tmp);
}

void Fl_Config::write_int(Section *s, const char *key, const int value)
{
    char tmp[128];
    sprintf(tmp, "%d", value);
    write_string(s, key, tmp);
}

void Fl_Config::write_float(Section *s, const char *key, const float value)
{
    char tmp[256];
    sprintf(tmp, "%f", value);
    write_string(s, key, tmp);
}

void Fl_Config::write_bool(Section *s, const char *key, const bool value)
{
    if(value)
        write_string(s, key, "1");
    else
        write_string(s, key, "0");
}

void Fl_Config::write_color(Section *s, const char *key, const Fl_Color value)
{
    uint8 r,g,b;
    fl_get_color(value, r,g,b);
    char tmp[32];
    sprintf(tmp, "RGB(%d,%d,%d)", r,g,b);
    write_string(s, key, tmp);
}

void Fl_Config::write_string(const char *sect, const char *key, const char *value)
{
    Section *sec = find_section(sect, true);
    if(!sec) sec = create_section(sect);

    write_string(sec, key, value);
}

void Fl_Config::write_long(const char *sect, const char *key, const long value)
{
    Section *sec = find_section(sect, true);
    if(!sec) sec = create_section(sect);
    write_long(sec, key, value);
}

void Fl_Config::write_int(const char *sect, const char *key, const int value)
{
    Section *sec = find_section(sect, true);
    if(!sec) sec = create_section(sect);
    write_int(sec, key, value);
}

void Fl_Config::write_float(const char *sect, const char *key, const float value)
{
    Section *sec = find_section(sect, true);
    if(!sec) sec = create_section(sect);
    write_float(sec, key, value);
}

void Fl_Config::write_bool(const char *sect, const char *key, const bool value)
{
    Section *sec = find_section(sect, true);
    if(!sec) sec = create_section(sect);
    write_bool(sec, key, value);
}

void Fl_Config::write_color(const char *sect, const char *key, const Fl_Color value)
{
    Section *sec = find_section(sect, true);
    if(!sec) sec = create_section(sect);
    write_color(sec, key, value);
}

