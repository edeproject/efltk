/* Our own notion of wide character, as UCS-4, according to ISO-10646-1. */
typedef unsigned int ucs4_t;
typedef void* conv_t;

#define RET_ILSEQ      -1
#define RET_TOOFEW(n)  (-2-(n))
#define RET_TOOSMALL   -2
#define RET_ILUNI      -1

#if HAVE_ICONV

#include <iconv.h>

typedef struct {
    const char *iconv_enc;
    const char *enc;
} charset_map_entry;

static charset_map_entry charsets_map[] = {
   { "TIS-620",      "TIS620.2529-1",   },
   { "GB2312",       "GB2312.1980-0",   },
   { "KSC_5601",     "KSC5601.1987-0",  },
   { "JIS_X0201",    "JISX0201.1976-0", },
   { "JIS_X0208",    "JISX0208.1983-0", },
   { "JIS_X0212",    "JISX0212.1990-0", },
   { "BIG5",	     "BIG5-1",	 },
   { "BIG5",	     "BIG5-0",	 },
   { "GB18030",      "GB18030.2000-0",  },
   { "GB18030",      "GB18030.2000-1",  },
   { "BIG5-HKSCS",   "HKSCS-1",	 },
   { "EUC-TW",       "CNS11643-1",	 },
   { "EUC-TW",       "CNS11643-2",	 },
   { "EUC-TW",       "CNS11643-3",	 },
   { "GBK",          "GBK-0",           }
};
static int charsets_map_size = sizeof(charsets_map)/sizeof(charsets_map[0]);

static const char *xlfd_to_iconv(const char *enc)
{
    for(int n=0; n<charsets_map_size; n++) {
        if(!strcmp(enc, charsets_map[n].enc))
            return charsets_map[n].iconv_enc;
    }
    return enc;
}

#define CACHE_START 100
#define CACHE_SIZE  128

typedef struct {
    int id;
    Fl_String name;
    iconv_t conv;
} Converter;

typedef struct {
    int cnt;
    Converter convs[64];
} Converters;

class Iconv_Cache {
public:
    int next_cache_id;
    Converters cache[CACHE_SIZE];

    Iconv_Cache() {
        next_cache_id = CACHE_START;
        memset(cache, 0, sizeof(cache));
    }
    ~Iconv_Cache() {
        for(int n=0; n<CACHE_SIZE; n++) {
            for(int n2=0; n2<cache[n].cnt; n2++) {
                Converter *c = &cache[n].convs[n2];
                iconv_close((iconv_t)c->conv);
            }
        }
    }

    int int_hash(int key, int table_size) {
        if( key < 0 ) key = -key;
        return key % table_size;
    }

    Converter *find(int key) {
        int index = int_hash(key, CACHE_SIZE);
        Converters *cached = &cache[index];
        for(int n=0; n<cached->cnt; n++)
            if(cached->convs[n].id == key)
                return &cached->convs[n];
        return 0;
    }

    int add(iconv_t cd, const Fl_String &name) {
        int key = next_cache_id;
        int index = int_hash(key, CACHE_SIZE);
        Converters *cached = &cache[index];
        cached->convs[cached->cnt].id = next_cache_id;
        cached->convs[cached->cnt].name = name;
        cached->convs[cached->cnt].conv = cd;
        cached->cnt++;
        next_cache_id += 24;
        return key;
    }

    int find(const Fl_String &name)
    {
        for(int n=0; n<CACHE_SIZE; n++) {
            for(int n2=0; n2<cache[n].cnt; n2++) {
                if(name == cache[n].convs[n2].name) {
                    return n;
                }
            }
        }
        return -1;
    }
};

class Iconv_UcsCache : public Iconv_Cache
{
public:
    int convert(char *s, unsigned int ucs, int enc) {
        Converter *cached = find(enc);
        if(cached) {
            size_t inlen = 4, outlen = 2;
            size_t *inbytesleft = (size_t *)&inlen;
            size_t outbytesleft = outlen+1; // + 1, for null len == 1
            char *inbuf = (char*)&ucs, *outbuf = s;;

           size_t err = iconv((iconv_t)cached->conv,
                              (ICONV_CONST char **)&inbuf, inbytesleft,
                              (char **)&outbuf, &outbytesleft);
           if(err == (size_t)-1) return -1;
           return (outbuf - s);
        }
        return -1;
    }
};

class Iconv_UTF8Cache : public Iconv_Cache
{
public:
    int convert(int index,
                const unsigned char *inbuf, int &inlen,
                char *outbuf, int outlen)
    {
        Converter *cached = find(index);
        if(cached) {
            size_t *inbytesleft = (size_t *)&inlen;
            size_t outbytesleft = outlen+1; // + 1, for null len == 1
            char *obuf = outbuf;
            size_t err = iconv((iconv_t)cached->conv,
                               (ICONV_CONST char **)&inbuf, inbytesleft,
                               (char **)&obuf, &outbytesleft);
            if(err == (size_t)-1) return -1;
            return obuf - outbuf;
        }
        return -1;
    }
};

Iconv_UcsCache ucs_cache;
Iconv_UTF8Cache utf8_cache;

#else

typedef void* iconv_t;

#endif /* HAVE_ICONV */
