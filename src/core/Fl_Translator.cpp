#include <efltk/Fl.h>
#include <efltk/Fl_Renderer.h>
#include <efltk/Fl_Exception.h>
#include <efltk/Fl_Translator.h>
#include <efltk/Fl_String_Hash.h>
#include <efltk/filename.h>
#include <efltk/vsnprintf.h>
#include <efltk/fl_utf8.h>

#include <ctype.h>
#include <errno.h>
#include <stdlib.h>

class MessageHash : public Fl_String_Hash
{
public:
    MessageHash() { }
    bool load_etb(FILE *fp);
    bool load_mo(FILE *fp);
};

typedef struct {
    Fl_String fullstring; //fi_FI@euro
    Fl_String lang;       //fi
    Fl_String territory;  //_FI
    Fl_String codeset;    //.8859
    Fl_String modifier;   //@euro
    Fl_String norm_codeset; //.iso8859
} locale;

typedef struct {
    Fl_String domain;
    Fl_String path;
    MessageHash hash;
    locale *loc;
} catalog;

////////////////////////////
////////////////////////////

Fl_Translator Fl_Translator::translator;
Fl_CString_List Fl_Translator::search_paths_;
Fl_Ptr_List Fl_Translator::catalogs_;

Fl_Translator::Fl_Translator()
{
    search_paths_.append(".");
    search_paths_.append("./locale");
#ifndef _WIN32
    search_paths_.append("/usr/locale");
    search_paths_.append("/usr/share/locale");
#endif
}

Fl_Translator::~Fl_Translator()
{
    for(uint n=0; n<catalogs_.size(); n++) {
        catalog *cat = (catalog*)catalogs_[n];
        delete cat->loc;
        delete cat;
    }
}

char *Fl_Translator::tr(const char *string)
{
    Fl_String *ret;
    for(uint n=0; n<catalogs_.size(); n++) {
        catalog *cat = (catalog*)catalogs_[n];
        ret = cat->hash.find(string);
        if(ret) return (char*)ret->c_str();
    }
    return (char*)string;
}

char *Fl_Translator::dtr(const char *domain, const char *string)
{
    Fl_String *ret;
    for(uint n=0; n<catalogs_.size(); n++) {
        catalog *cat = (catalog*)catalogs_[n];
        if(cat->domain==domain) {
            ret = cat->hash.find(string);
            if(ret) return (char*)ret->c_str();
        }
    }
    return (char*)string;
}

bool Fl_Translator::has_search_path(const char *path)
{
    for(uint n=0; n<search_paths_.size(); n++) {
        if(search_paths_[n] == path)
            return true;
    }
    return false;
}

void Fl_Translator::add_search_path(const char *path)
{
    search_paths_.prepend(path);
}

void Fl_Translator::remove_search_path(const char *path)
{
    search_paths_.remove(path);
}

enum {
    LOAD_NONE = 0,
    LOAD_ETB,
    LOAD_MO
};

catalog *load_binary_file(const char *domain, const char *full_path, locale *loc)
{
    int load=LOAD_NONE;
    if(strstr(full_path, ".etb")) load=LOAD_ETB;
    else if(strstr(full_path, ".mo")) load=LOAD_MO;

    if(load==LOAD_NONE || !fl_file_exists(full_path)) {
        return 0;
    }

    catalog *cat = new catalog;

    FILE *fp = fopen(full_path, "r");
    if(!fp) {
        delete cat;
        return 0;
    }

    bool ret;
    if(load==LOAD_ETB)
        ret = cat->hash.load_etb(fp);
    else
        ret = cat->hash.load_mo(fp);

    if(!ret) {
        delete cat;
        fclose(fp);
        return 0;
    }

    fclose(fp);
    cat->domain = domain;
    cat->path = full_path;
    cat->loc = loc;
    return cat;
}

////////////////////////////
////////////////////////////

static Fl_String get_filename(const char *domainname, const char *dirname, const char *ext, locale &l, bool is_mo)
{
    //language[_territory[.codeset]][@modifier]
    char file[FL_PATH_MAX];

    // Full locale string
    snprintf(file, sizeof(file)-1, "%s/%s/%s%s.%s", dirname, l.fullstring.c_str(), is_mo?"LC_MESSAGES/":"", domainname, ext);
    if(fl_file_exists(file)) return file;

    if(l.territory.length()>0 && l.codeset.length()>0 && l.modifier.length()>0) {
        // Lang + territory + codeset + modifier
        snprintf(file, sizeof(file)-1, "%s/%s%s%s%s/%s%s.%s", dirname, l.lang.c_str(), l.territory.c_str(), l.codeset.c_str(), l.modifier.c_str(), is_mo?"LC_MESSAGES/":"", domainname, ext);
        if(fl_file_exists(file)) return file;
        // Lang + territory + normalized codeset + modifier
        snprintf(file, sizeof(file)-1, "%s/%s%s%s%s/%s%s.%s", dirname, l.lang.c_str(), l.territory.c_str(), l.norm_codeset.c_str(), l.modifier.c_str(), is_mo?"LC_MESSAGES/":"", domainname, ext);
        if(fl_file_exists(file)) return file;
    }

    if(l.territory.length()>0 && l.modifier.length()>0) {
        // Lang + territory + modifier
        snprintf(file, sizeof(file)-1, "%s/%s%s%s/%s%s.%s", dirname, l.lang.c_str(), l.territory.c_str(), l.modifier.c_str(), is_mo?"LC_MESSAGES/":"", domainname, ext);
        if(fl_file_exists(file)) return file;
    }

    if(l.territory.length()>0) {
        // Lang + territory
        snprintf(file, sizeof(file)-1, "%s/%s%s/%s%s.%s", dirname, l.lang.c_str(), l.territory.c_str(), is_mo?"LC_MESSAGES/":"", domainname, ext);
        if(fl_file_exists(file)) return file;
    }

    if(l.modifier.length()>0) {
        // Lang + modifier
        snprintf(file, sizeof(file)-1, "%s/%s%s/%s%s.%s", dirname, l.lang.c_str(), l.modifier.c_str(), is_mo?"LC_MESSAGES/":"", domainname, ext);
        if(fl_file_exists(file)) return file;
    }

    if(l.lang.length()>0) {
        // Lang
        snprintf(file, sizeof(file)-1, "%s/%s/%s%s.%s", dirname, l.lang.c_str(), is_mo?"LC_MESSAGES/":"", domainname, ext);
        if(fl_file_exists(file)) return file;
    }

    return "";
}

/*
 * Normalize codeset name.  There is no standard for the codeset
 * names.  Normalization allows the user to use any of the common names.
 */
static Fl_String normalize_codeset(Fl_String codeset)
{
    bool only_digit = true;
    Fl_String ret;
    int n;

    for(n=1; n<codeset.length(); n++) {
        if(isalnum(codeset[n])) {
            if(isalpha(codeset[n]))
                only_digit = false;
        }
    }
    if(only_digit) ret = ".iso";
    else ret=".";

    for(n=1; n<codeset.length(); n++) {
        if(isalpha(codeset[n]))
            ret += tolower(codeset[n]);
        else if(isdigit(codeset[n]))
            ret += codeset[n];
    }
    return ret;
}

/*
 * Locale can consist of up to four recognized parts for the XPG syntax:
 * language[_territory[.codeset]][@modifier]
 */
static void parse_locale(const char *locale, locale &loc)
{
    char *start=0, *pos=0;
    loc.fullstring = locale;

    //territory
    start = strchr(locale, '_');
    if(start) {
        loc.lang = Fl_String(locale, start-locale);
        pos = start;
        while(*pos != '\0' && *pos != '.' && *pos != '@') pos++;
        loc.territory = Fl_String(start, pos-start);
    }

    //codeset
    start = strchr(locale, '.');
    if(start) {
        if(loc.lang.length()==0) loc.lang = Fl_String(locale, start-locale);
        pos = start;
        while(*pos != '\0' && *pos != '@') pos++;
        loc.codeset = Fl_String(start, pos-start);
        loc.norm_codeset = normalize_codeset(loc.codeset);
    }

    //modifier
    start = strchr(locale, '@');
    if(start) {
        if(loc.lang.length()==0) loc.lang = Fl_String(locale, start-locale);
        pos = start;
        while(*pos != '\0') pos++;
        loc.modifier = Fl_String(start, pos-start);
    }
}

char *Fl_Translator::textdomain(const char *domainname)
{
    static char *domain = 0;
    for(uint n=0; n<catalogs_.size(); n++) {
        catalog *cat = (catalog*)catalogs_[n];
        if(cat->domain==domainname) {
            domain = (char*)cat->domain.c_str();
            catalogs_.remove(n);
            catalogs_.prepend(cat);
            break;
        }
    }
    return domain;
}

char *Fl_Translator::bindtextdomain(const char *domainname, const char *dirname)
{
    extern char *last_locale;
    if(!last_locale) return 0;
    locale *loc = new locale;
    parse_locale(last_locale, *loc);

    Fl_String file;
    file = get_filename(domainname, dirname, "etb", *loc, true);
    if(file.length()==0) file = get_filename(domainname, dirname, "mo", *loc, true);

    catalog *cat=0;
    if(file.length()>0) {
        cat = load_binary_file(domainname, file.c_str(), loc);
    } 
    if(!cat) {
        delete loc;
        return 0;
    }
    catalogs_.prepend(cat);
    return (char*)cat->path.c_str();
}

const char *Fl_Translator::load_translation(const char *domainname)
{
    extern char *last_locale;
    if(!last_locale) return 0;
    locale *loc = new locale;
    parse_locale(last_locale, *loc);

    Fl_String file;
    catalog *cat=0;

    for(uint n=0; n<search_paths_.size(); n++) {
        const char *dirname = search_paths_[n];
        file = get_filename(domainname, dirname, "etb", *loc, false);
        if(file.length()==0) file = get_filename(domainname, dirname, "mo", *loc, false);
        if(file.length()==0) continue;

        cat = load_binary_file(domainname, file.c_str(), loc);
        break;
    }
    if(!cat) {
        delete loc;
        return 0;
    }
    catalogs_.prepend(cat);
    return cat->path.c_str();
}

const char *Fl_Translator::load_translation_file(const char *desired_domain, const char *path)
{
    extern char *last_locale;
    if(!last_locale) return 0;
    locale *loc = new locale;
    parse_locale(last_locale, *loc);

    catalog *cat=0;
    cat = load_binary_file(desired_domain, path, loc);
    if(!cat) {
        delete loc;
        return 0;
    }
    catalogs_.prepend(cat);
    return path;
}

///////////////////////////////////////
// EFltk .etb file loading interface //
///////////////////////////////////////

#define SWAP(b) (swap ? fl_swap_32(b) : b)

typedef struct {
    uint32 magic;
    uint32 version;
    uint32 hashsize;
    uint32 numstrings;
} etb_header;

static const uint32 etb_magic      = 0xF4382150;
static const uint32 etb_magic_swap = 0x502138F4;
static const uint32 etb_version    = 0x10000001;

bool MessageHash::load_etb(FILE *fp)
{
    clear();

    long size;
    if(fseek(fp, 0, SEEK_END)!=0) { fl_throw(strerror(errno)); return false; }
    if( (size = ftell(fp)) == -1) { fl_throw(strerror(errno)); return false; }
    if(fseek(fp, 0, SEEK_SET)!=0) { fl_throw(strerror(errno)); return false; }

    char *data = (char *) malloc(size);
    if(fread(data, size, 1, fp)==0 && errno!=0) {
        free(data);
        fl_throw(strerror(errno));
        return false;
    }

    etb_header *head = (etb_header*)data;
    uint32 magic = head->magic;

    if(magic!=etb_magic && magic!=etb_magic_swap) {
        free(data);
        Fl::warning("ETB translation file, magic number failure");
        return false;
    }
    if(head->version!=etb_version) {
        free(data);
        Fl::warning("ETB translation file, incorrect version");
        return false;
    }

    bool swap = (magic!=etb_magic);

    size_ = SWAP(head->hashsize);
    if(lists_) delete []lists_;
    lists_ = new Fl_Ptr_List[size_];

    uint numstrings = SWAP(head->numstrings);

    int *lengths = (int*)(data+sizeof(etb_header));
    int *indexes = (int*)(data+sizeof(etb_header) + (numstrings*2*sizeof(uint32)));
    char *dataptr = (char*)(data+sizeof(etb_header) + (numstrings*2*sizeof(uint32)) + (numstrings*sizeof(uint32)));

    Fl_String orig, *tr;
    int lenpos=0;
    for(uint n=0; n<numstrings; n++)
    {
        orig = Fl_String(dataptr, SWAP(lengths[lenpos]));
        dataptr += lengths[lenpos++];

        tr   = new Fl_String(dataptr, SWAP(lengths[lenpos]));
        dataptr += lengths[lenpos++];

        HashEntry *entry = new HashEntry;
        entry->key = orig;
        entry->val = tr;
        lists_[SWAP(indexes[n])].append(entry);
    }

    free(data);
    return true;
}

////////////////////////////////////////////
// GNU gettext .mo file loading interface //
////////////////////////////////////////////

struct mo_file_header {
    uint32 magic;            /* The magic number.  */
    uint32 revision;         /* The revision number of the file format.  */
    uint32 nstrings;         /* The number of strings pairs.  */
    uint32 orig_tab_offset;  /* Offset of table with start offsets of original strings.  */
    uint32 trans_tab_offset; /* Offset of table with start offsets of translation strings.  */
    uint32 hash_tab_size;    /* Size of hashing table.  */
    uint32 hash_tab_offset;  /* Offset of first hashing entry.  */
};

struct string_desc {
    uint32 length; /* Length of addressed string.  */
    uint32 offset; /* Offset of string in file.  */
};

/* The magic number of the GNU message catalog format.  */
#define MO_MAGIC 0x950412de
#define MO_MAGIC_SWAPPED 0xde120495
bool MessageHash::load_mo(FILE *fp)
{
    clear();

    long size;
    if(fseek(fp, 0, SEEK_END)!=0) { fl_throw(strerror(errno)); return false; }
    if( (size = ftell(fp)) == -1) { fl_throw(strerror(errno)); return false; }
    if(fseek(fp, 0, SEEK_SET)!=0) { fl_throw(strerror(errno)); return false; }

    struct mo_file_header *data = (struct mo_file_header *) malloc (size);
    if(fread(data, size, 1, fp)==0 && errno!=0) {
        free(data);
        fl_throw(strerror(errno));
        return false;
    }

    if(data->magic!=MO_MAGIC && data->magic != MO_MAGIC_SWAPPED) {
        free(data);
        Fl::warning("MO translation file, magic number failure");
        return false;
    }
    if(data->revision!=0) {
        free(data);
        Fl::warning("MO translation file, incorrect revision");
        return false;
    }

    bool swap = (data->magic!=MO_MAGIC);

    struct string_desc *orig_tab = (struct string_desc *)((char *) data + SWAP(data->orig_tab_offset));
    struct string_desc *trans_tab = (struct string_desc *)((char *) data + SWAP(data->trans_tab_offset));

    uint numstrings = SWAP(data->nstrings);
    size_ = numstrings;
    if(size_<100) size_=100;
    if(lists_) delete []lists_;
    lists_ = new Fl_Ptr_List[size_];

    // Get charset information
    int info_pos = SWAP(orig_tab[numstrings-1].offset) + SWAP(orig_tab[numstrings-1].length) + 1;
    char *start = (char*)data+info_pos;
    char *end = start;
    while(*end++) { if((char*)data-end >= size) break; }
    Fl_String codeset(start, start-end);
    int converter_index=-1;
    info_pos = codeset.pos("charset");
    if(info_pos>0) {
        info_pos+=8;
        int end_pos = codeset.pos('\n', info_pos);
        if(end_pos>info_pos) {
            codeset = codeset.sub_str(info_pos, end_pos-info_pos);
            converter_index = fl_find_converter(codeset.c_str());
        }
    }

    Fl_String orig, tr;
    for(uint n=0; n<numstrings; n++) {
        if(converter_index>0) {
            orig = Fl_String::from_codeset( converter_index, ((char*)data+SWAP(orig_tab[n].offset)), SWAP(orig_tab[n].length));
            tr   = Fl_String::from_codeset( converter_index, ((char*)data+SWAP(trans_tab[n].offset)), SWAP(trans_tab[n].length));
        } else {
            orig = Fl_String( ((char*)data+SWAP(orig_tab[n].offset)), SWAP(orig_tab[n].length));
            tr   = Fl_String( ((char*)data+SWAP(trans_tab[n].offset)), SWAP(trans_tab[n].length));
        }
        if(orig.length()>0 && tr.length()>0)
            insert(orig, tr);
    }

    free(data);
    return true;
}

