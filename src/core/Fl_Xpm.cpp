#include <efltk/Fl_Image.h>

/* This is an XPM image file loading framework */

#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static uint8 *read_ptr = 0;
static int    readed   = 0;
static int    read_size= 0;

static int Read(void *buf, int len)
{
    memcpy(buf, read_ptr, len);
    read_ptr+=len;
    return len;
}

bool xpm_is_valid_xpm(void **stream)
{
    if(stream) {
        // The header string of an XPMv3 image has the format
        // <width> <height> <ncolors> <cpp> [ <hotspot_x> <hotspot_y> ]
        char *ptr = ((char **)stream)[0];
        if(!ptr) return false;

        int w, h, ncol, cpp;
        if(sscanf(ptr, "%d %d %d %d", &w, &h, &ncol, &cpp) != 4)
            return false;
        return true;
    }
    return false;
}

/* See if an image is contained in a data source */
bool xpm_is_valid(void *stream, bool file)
{
    if(stream && file) {
        uint8 type[10];
        memcpy(type, stream, 10);
        if(memcmp(type, "/* XPM */", 9) == 0) {
            return true;
        }
    }
    return false;
}

static char *xpm_gets(char *string, int maxlen)
{
    int i;

    for ( i=0; i<(maxlen-1); ++i ) {
        if(Read(&string[i], 1) <= 0 )
        {
            /* EOF or error */
            if(i == 0) {
                /* Hmm, EOF on initial read, return NULL */
                return 0;
            }
            break;
        }
        /* In this case it's okay to use either '\r' or '\n'
         as line separators because blank lines are just
         ignored by the XPM format.
         */
        if( (string[i] == '\n') || (string[i] == '\r') ) {
            break;
        }
    }
    string[i] = '\0';
    return string;
}

/* Hash table to look up colors from pixel strings */
#define STARTING_HASH_SIZE 256

struct hash_entry {
    char *key;
    uint32 color;
    struct hash_entry *next;
};

struct color_hash {
    struct hash_entry **table;
    struct hash_entry *entries; /* array of all entries */
    struct hash_entry *next_free;
    int size;
    int maxnum;
};

static int hash_key(const char *key, int cpp, int size)
{
    int hash;

    hash = 0;
    while ( cpp-- > 0 ) {
        hash = hash * 33 + *key++;
    }
    return hash & (size - 1);
}

static struct color_hash *create_colorhash(int maxnum)
{
    int bytes, s;
    struct color_hash *hash;

    /* we know how many entries we need, so we can allocate
     everything here */
    hash = (color_hash *)malloc(sizeof *hash);
    if(!hash)
        return NULL;

    /* use power-of-2 sized hash table for decoding speed */
    for(s = STARTING_HASH_SIZE; s < maxnum; s <<= 1)
        ;
    hash->size = s;
    hash->maxnum = maxnum;
    bytes = hash->size * sizeof(struct hash_entry **);
    hash->entries = NULL;	/* in case malloc fails */
    hash->table = (hash_entry **)malloc(bytes);
    if(!hash->table)
        return NULL;
    memset(hash->table, 0, bytes);
    hash->entries = (hash_entry *)malloc(maxnum * sizeof(struct hash_entry));
    if(!hash->entries)
        return NULL;
    hash->next_free = hash->entries;
    return hash;
}

static int add_colorhash(struct color_hash *hash,
                         char *key, int cpp, uint32 color)
{
    int index = hash_key(key, cpp, hash->size);
    struct hash_entry *e = hash->next_free++;
    e->color = color;
    e->key = key;
    e->next = hash->table[index];
    hash->table[index] = e;
    return 1;
}

/* fast lookup that works if cpp == 1 */
/* Or maybe not... */
#define QUICK_COLORHASH(hash, key) ((hash)->table[*(uint8 *)(key)]->color)

static uint32 get_colorhash(struct color_hash *hash, const char *key, int cpp)
{
    struct hash_entry *entry = hash->table[hash_key(key, cpp, hash->size)];
    while(entry) {
        if(memcmp(key, entry->key, cpp) == 0)
            return entry->color;
        entry = entry->next;
    }
    return 0;		/* garbage in - garbage out */
}

static void free_colorhash(struct color_hash *hash)
{
    if(hash && hash->table) {
        free(hash->table);
        free(hash->entries);
        free(hash);
    }
}

#define ARRAYSIZE(a) (int)(sizeof(a) / sizeof((a)[0]))

/*
 * convert colour spec to RGB (in 0xrrggbb format).
 * return 1 if successful. may scribble on the colorspec buffer.
 */
static int color_to_rgb(char *spec, uint32 *rgb)
{
	if(!strcasecmp("none", spec) || !strcasecmp("#background", spec)) {
        *rgb = 0xffffffff;
        return 1;
    }
#ifndef _WIN32    
    XColor x;
    fl_open_display();
    if(!XParseColor(fl_display, fl_colormap, spec, &x)) {
        *rgb = 0xffffffff;
        return 1;
    }
    RGB888_FROM_RGB((*rgb), x.red>>8, x.green>>8, x.blue>>8);
    return 1;
#else
    /* poor man's rgb.txt */
    static struct { char *name; uint32 rgb; } known[] = {
        {"none",  0xffffffff},
        {"background",  0xffffffff},
        {"black", 0x00000000},
        {"white", 0x00ffffff},
        {"red",   0x00ff0000},
        {"green", 0x0000ff00},
        {"blue",  0x000000ff}
    };

    if(spec[0] == '#') {
        char buf[7];
        ++spec;
        switch(strlen(spec)) {
        case 3:
            buf[0] = buf[1] = spec[0];
            buf[2] = buf[3] = spec[1];
            buf[4] = buf[5] = spec[2];
            break;
        case 6:
            memcpy(buf, spec, 6);
            break;
        case 12:
            buf[0] = spec[0];
            buf[1] = spec[1];
            buf[2] = spec[4];
            buf[3] = spec[5];
            buf[4] = spec[8];
            buf[5] = spec[9];
            break;
        }
        buf[6] = '\0';
        *rgb = strtol(buf, NULL, 16);
        return 1;
    } else {
        int i;
        for(i = 0; i < ARRAYSIZE(known); i++)
            if(strcmp(known[i].name, spec)) {
                *rgb = known[i].rgb;
                return 1;
            }
        return 0;
    }
#endif
}

static char *skipspace(char *p)
{
    while(isspace((unsigned char)*p))
        ++p;
    return p;
}

static char *skipnonspace(char *p)
{
    while(!isspace((unsigned char)*p) && *p)
        ++p;
    return p;
}

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

// This is somewhat STUPID :)) but i do this anyway,
// Convert static xpm array to char buffer what looks like a file :)
static char *build_xpm(char **stream)
{
	// <width> <height> <ncolors> <cpp> [ <hotspot_x> <hotspot_y> ]
	char *check = (char *)stream[0];
	int w, h, ncol, cpp;	
    if(sscanf(check, "%d %d %d %d", &w, &h, &ncol, &cpp) != 4) {
		return 0;
	}
	int lines=ncol+h;

    char head[] = "{\n";
    int size=sizeof(head)-1;
    char *buf=new char[size+3];	
    memcpy(buf, head, size);
	
	int curline=0;
    char *line=0;
    while(curline++<=lines) {
		line=*stream++;
        int pos=size;
        int linesize = strlen(line);
        size+=linesize+4;
        buf=(char *)realloc(buf, sizeof(char*)*size);

        char *ptr = buf+pos;
        *ptr++ = '\"';
        int c=0;
        while((c=*line++)) {
            *ptr++ = c;
        }
        strncpy(ptr, "\",\n", 3);		
    }
    strncpy(buf+size-2, "\n}\0", 3);

    return buf;
}

/* Load a XPM type image from stream */
static Fl_Image *xpm_create(void *stream, bool file)
{
    char *file_buffer=0;

    if(!file) {
        file_buffer = build_xpm((char **)stream);
        if(!file_buffer) return 0;
        read_ptr = (uint8 *)file_buffer;        

    } else {
        read_ptr = (uint8 *)stream;                
    }

    Fl_Image *image;
    char line[1024];
    char *here;
    int index;
    int x, y;
    int w, h, ncolors, cpp;
    int pixels_len;
    char *pixels = NULL;
    int indexed;
    uint8 *dst;
    struct color_hash *colors;
    Fl_Colormap_Color *im_colors = NULL;
    char *keystrings, *nextkey;
    char *error = NULL;

    /* Skip to the first string, which describes the image */
    do {
        here = xpm_gets(line, sizeof(line));
        if ( !here ) {
            printf("Premature end of data 1\n");
            return 0;
        }
        here = skipspace(here);
    } while(*here != '"');
    /*
     * The header string of an XPMv3 image has the format
     *
     * <width> <height> <ncolors> <cpp> [ <hotspot_x> <hotspot_y> ]
     *
     * where the hotspot coords are intended for mouse cursors.
     * Right now we don't use the hotspots but it should be handled
     * one day.
     */
    if(sscanf(here + 1, "%d %d %d %d", &w, &h, &ncolors, &cpp) != 4
       || w <= 0 || h <= 0 || ncolors <= 0 || cpp <= 0) {
        printf("Invalid format description\n");
        return 0;
    }

    keystrings = (char *)malloc(ncolors * cpp);
    if(!keystrings) {
        printf("Out of memory\n");
        free(pixels);
        return 0;
    }
    nextkey = keystrings;

    /* Create the new surface */
    if(ncolors <= 256) {
        indexed = 1;
        image = new Fl_Image(w, h, 8,0,0,0,0,0,0);
        im_colors = image->format()->palette->colors;
        image->format()->palette->ncolors = ncolors;
    } else {
        indexed = 0;
        image = new Fl_Image(w, h, 32, 0,
                              0xff0000, 0x00ff00, 0x0000ff, 0, 0);
    }
    if(!image) {
        /* Hmm, some SDL error (out of memory?) */
        free(pixels);
        return 0;
    }

    /* Read the colors */
    colors = create_colorhash(ncolors);
    if ( ! colors ) {
        error = "Out of memory";
        goto done;
    }
    for(index = 0; index < ncolors; ++index ) {
        char *key;
        int len;

        do {
            here = xpm_gets(line, sizeof(line));
            if(!here) {
                error = "Premature end of data 2";
                goto done;
            }
            here = skipspace(here);
        } while(*here != '"');

        ++here;
        len = strlen(here);
        if(len < cpp + 7)
            continue;	/* cannot be a valid line */

        key = here;
        key[cpp] = '\0';
        here += cpp + 1;

        /* parse a colour definition */
        for(;;) {
            char nametype;
            char *colname;
            char delim;
            uint32 rgb;

            here = skipspace(here);
            nametype = *here;
            here = skipnonspace(here);
            here = skipspace(here);
            colname = here;
            while(*here && !isspace((unsigned char)*here)
                  && *here != '"')
                here++;
            if(!*here) {
                error = "color parse error";
                goto done;
            }
            if(nametype == 's')
                continue;      /* skip symbolic colour names */

            delim = *here;
            *here = '\0';
            if(delim)
                here++;

            if(!color_to_rgb(colname, &rgb)) {
                continue;
            }

            memcpy(nextkey, key, cpp);
            if(indexed) {
                Fl_Colormap_Color *c = im_colors + index;
                c->r = rgb >> 16;
                c->g = rgb >> 8;
                c->b = rgb;
                c->a = 0;
                if(rgb == 0xffffffff) c->a = 1;
                add_colorhash(colors, nextkey, cpp, index);
            } else
                add_colorhash(colors, nextkey, cpp, rgb);
            nextkey += cpp;
            if(rgb == 0xffffffff) {
                image->mask_type(MASK_COLORKEY);
                image->colorkey(rgb);
            }
            break;
        }
    }

    /* Read the pixels */
    pixels_len = w * cpp;
    pixels = (char *)malloc(MAX(pixels_len + 5, 20));
    if(!pixels) {
        error = "Out of memory";
        goto done;
    }
    dst = image->data();
    for (y = 0; y < h; ) {
        char *s;
        char c;
        do {
            if(Read(&c, 1) <= 0)
            {
                error = "Premature end of data 3";
                goto done;
            }
        } while(c == ' ');
        if(c != '"') {
            /* comment or empty line, skip it */
            while(c != '\n' && c != '\r') {
                if(Read(&c, 1) <= 0) {
                    error = "Premature end of data 4";
                    goto done;
                }
            }
            continue;
        }
        if(Read(pixels, pixels_len + 3) <= 0) {
            error = "Premature end of data 5";
            goto done;
        }
        s = pixels;
        if(indexed) {
            /* optimization for some common cases */
            /*if(cpp == 1)
                for(x = 0; x < w; x++)
                    dst[x] = QUICK_COLORHASH(colors,
                                             s + x);
            else*/
                for(x = 0; x < w; x++)
                    dst[x] = get_colorhash(colors,
                                           s + x * cpp,
                                           cpp);
        } else {
            for (x = 0; x < w; x++)
                ((uint32*)dst)[x] = get_colorhash(colors,
                                                  s + x * cpp,
                                                  cpp);
        }
        dst += image->pitch();
        y++;
    }

done:
    if(error) {
        if(image)
            delete image;
        image = NULL;
        printf("%s\n", error);
    }
    free(pixels);
    free(keystrings);
    free_colorhash(colors);
    if(file_buffer) free(file_buffer);

    return image;
}

ImageReader xpm_reader =
{
    xpm_is_valid,
    xpm_is_valid_xpm,
    xpm_create
};


