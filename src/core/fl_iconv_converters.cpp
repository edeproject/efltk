/* Our own notion of wide character, as UCS-4, according to ISO-10646-1. */
typedef unsigned int ucs4_t;

#define RET_ILSEQ      -1
#define RET_TOOFEW(n)  (-2-(n))
#define RET_TOOSMALL   -2
#define RET_ILUNI      -1

#if HAVE_ICONV

#include <iconv.h>

/* State used by a conversion. 0 denotes the initial state. */
typedef unsigned int state_t;
/* iconv_t is an opaque type. This is the real iconv_t type. */
typedef struct conv_struct * conv_t;

// Data type for conversion multibyte -> unicode
struct mbtowc_funcs {
	int (*xxx_mbtowc) (conv_t conv, ucs4_t *pwc, unsigned char const *s, int n);
    /*
     * int xxx_mbtowc (conv_t conv, ucs4_t *pwc, unsigned char const *s, int n)
     * converts the byte sequence starting at s to a wide character. Up to n bytes
     * are available at s. n is >= 1.
     * Result is number of bytes consumed (if a wide character was read),
     * or -1 if invalid, or -2 if n too small, or -2-(number of bytes consumed)
     * if only a shift sequence was read.
     */
	int (*xxx_flushwc) (conv_t conv, ucs4_t *pwc);
    /*
     * int xxx_flushwc (conv_t conv, ucs4_t *pwc)
     * returns to the initial state and stores the pending wide character, if any.
     * Result is 1 (if a wide character was read) or 0 if none was pending.
     */
};

// Data type for conversion unicode -> multibyte
struct wctomb_funcs {
	int (*xxx_wctomb) (conv_t conv, unsigned char *r, ucs4_t wc, int n);
    /*
     * int xxx_wctomb (conv_t conv, unsigned char *r, ucs4_t wc, int n)
     * converts the wide character wc to the character set xxx, and stores the
     * result beginning at r. Up to n bytes may be written at r. n is >= 1.
     * Result is number of bytes written, or -1 if invalid, or -2 if n too small.
     */
	int (*xxx_reset) (conv_t conv, unsigned char *r, int n);
    /*
     * int xxx_reset (conv_t conv, unsigned char *r, int n)
     * stores a shift sequences returning to the initial state beginning at r.
     * Up to n bytes may be written at r. n is >= 0.
     * Result is number of bytes written, or -2 if n too small.
     */
};

// Data type for general conversion loop.
struct loop_funcs {
	size_t (*loop_convert) (iconv_t icd,
		const char* * inbuf, size_t *inbytesleft,
		char* * outbuf, size_t *outbytesleft);
	size_t (*loop_reset) (iconv_t icd,
		char* * outbuf, size_t *outbytesleft);
};

// Contents of a conversion descriptor.
struct conv_struct {
	struct loop_funcs lfuncs;
    /* Input (conversion multibyte -> unicode) */
	int iindex;
	struct mbtowc_funcs ifuncs;
	state_t istate;
    /* Output (conversion unicode -> multibyte) */
	int oindex;
	struct wctomb_funcs ofuncs;
	int oflags;
	state_t ostate;
    /* Operation flags */
	int transliterate;
	int discard_ilseq;
};

/////////////////////////////////

typedef struct {
	const char *iconv_enc;
	const char *enc;
} charset_map_entry;

static charset_map_entry charsets_map[] = {
	{ "TIS-620",      "tis620.2529-1",   },
	{ "GB2312",       "gb2312.1980-0",   },
	{ "KSC_5601",     "ksc5601.1987-0",  },
	{ "JIS_X0201",    "jisx0201.1976-0", },
	{ "JIS_X0208",    "jisx0208.1983-0", },
	{ "JIS_X0212",    "jisx0212.1990-0", },
	{ "BIG5",	      "big5-1",	 },
	{ "BIG5",	      "big5-0",	 },
	{ "GB18030",      "gb18030.2000-0",  },
	{ "GB18030",      "gb18030.2000-1",  },
	{ "BIG5-HKSCS",   "hkscs-1",	 },
	{ "EUC-TW",       "cns11643-1",	 },
	{ "EUC-TW",       "cns11643-2",	 },
	{ "EUC-TW",       "cns11643-3",	 },
	{ "GBK",          "gbk-0",           }
};
static int charsets_map_size = sizeof(charsets_map)/sizeof(charsets_map[0]);

static const char *xlfd_to_iconv(const char *enc)
{
	for(int n=0; n<charsets_map_size; n++) {
		if(!strcasecmp(enc, charsets_map[n].enc))
			return charsets_map[n].iconv_enc;
	}
	return enc;
}

#define CACHE_START 100
#define CACHE_SIZE  128

typedef struct {
	int id;
	char *name;
	conv_t conv;
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
				free(c->name);
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

	int add(conv_t cd, const char *name) {
		int key = next_cache_id;
		int index = int_hash(key, CACHE_SIZE);
		Converters *cached = &cache[index];
		cached->convs[cached->cnt].id = next_cache_id;
		cached->convs[cached->cnt].name = strdup(name);
		cached->convs[cached->cnt].conv = cd;
		cached->cnt++;
		next_cache_id += 24;
		return key;
	}

	int find(const char *name)
	{
		for(int n=0; n<CACHE_SIZE; n++) {
			for(int n2=0; n2<cache[n].cnt; n2++) {
				if(!strcasecmp(cache[n].convs[n2].name, name)) {
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
		int len=0;
		Converter *cached = find(enc);
		if(cached) {
			if((len=cached->conv->ofuncs.xxx_wctomb(cached->conv, (unsigned char*)s, ucs, 2)) > 0)
				return len;
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
					(const char**)&inbuf, inbytesleft,
					(char **)&obuf, &outbytesleft);
			if(err == (size_t)-1) {
				return -1;
			}
			return obuf - outbuf;
		}
		return -1;
	}
};

Iconv_UcsCache ucs_cache;
Iconv_UTF8Cache utf8_cache;

#else

typedef void* conv_t;
typedef void* iconv_t;

#endif /* HAVE_ICONV */
