#include <config.h>

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <efltk/fl_utf8.h>

////////////////////////////////////////

#include "fl_iconv_converters.cpp"

#include "headers/iso8859_1.h"
#include "headers/iso8859_2.h"
#include "headers/iso8859_3.h"
#include "headers/iso8859_4.h"
#include "headers/iso8859_5.h"
#include "headers/iso8859_6.h"
#include "headers/iso8859_7.h"
#include "headers/iso8859_8.h"
#include "headers/iso8859_9.h"
#include "headers/iso8859_9e.h"
#include "headers/iso8859_10.h"
#include "headers/iso8859_11.h"
#include "headers/iso8859_13.h"
#include "headers/iso8859_14.h"
#include "headers/iso8859_15.h"
#include "headers/iso8859_16.h"

#include "headers/koi8_r.h"
#include "headers/koi8_u.h"

#include "headers/symbol_.h"
#include "headers/dingbats_.h"

const int fl_ucs2fontmap(char *s, unsigned int ucs, int enc)
{
    int ret = -1;
    int len = 0;

    switch(enc) {
    case 0:	/* iso10646-1 */
        s[0] = (char) ((ucs & 0xFF00) >> 8);
        s[1] = (char) (ucs & 0xFF);
        len = 2;
        ret = enc;
        break;

    case 1:	/* iso8859-1 */
        if ((len=iso8859_1_wctomb(NULL, (unsigned char*)s, ucs, 2)) > 0) {
            ret = enc;
        }
        break;

    case 2:	/* iso8859-2 */
        if ((len=iso8859_2_wctomb(NULL, (unsigned char*)s, ucs, 2)) > 0) {
            ret = enc;
        }
        break;

    case 3:	/* iso8859-3 */
        if ((len=iso8859_3_wctomb(NULL, (unsigned char*)s, ucs, 2)) > 0) {
            ret = enc;
        }
        break;

    case 4:	/* iso8859-4 */
        if ((len=iso8859_4_wctomb(NULL, (unsigned char*)s, ucs, 2)) > 0) {
            ret = enc;
        }
        break;

    case 5:	/* iso8859-5 */
        if ((len=iso8859_5_wctomb(NULL, (unsigned char*)s, ucs, 2)) > 0) {
            ret = enc;
        }
        break;

    case 6:	/* iso8859-6 */
        if ((len=iso8859_6_wctomb(NULL, (unsigned char*)s, ucs, 2)) > 0) {
            ret = enc;
        }
        break;

    case 7:	/* iso8859-7 */
        if ((len=iso8859_7_wctomb(NULL, (unsigned char*)s, ucs, 2)) > 0) {
            ret = enc;
        }
        break;

    case 8:	/* iso8859-8 */
        if ((len=iso8859_8_wctomb(NULL, (unsigned char*)s, ucs, 2)) > 0) {
            ret = enc;
        }
        break;

    case 9:	/* iso8859-9 */
        if ((len=iso8859_9_wctomb(NULL, (unsigned char*)s, ucs, 2)) > 0) {
            ret = enc;
        }
        break;

    case 10:	/* iso8859-9e */
        if ((len=iso8859_9e_wctomb(NULL, (unsigned char*)s, ucs, 2)) > 0) {
            ret = enc;
        }
        break;

    case 11:	/* iso8859-10 */
        if ((len=iso8859_10_wctomb(NULL, (unsigned char*)s, ucs, 2)) > 0) {
            ret = enc;
        }
        break;

    case 12:	/* iso8859-11 */
        if ((len=iso8859_11_wctomb(NULL, (unsigned char*)s, ucs, 2)) > 0) {
            ret = enc;
        }
        break;

    case 13:	/* iso8859-13 */
        if ((len=iso8859_13_wctomb(NULL, (unsigned char*)s, ucs, 2)) > 0) {
            ret = enc;
        }
        break;

    case 14:	/* iso8859-14 */
        if ((len=iso8859_14_wctomb(NULL, (unsigned char*)s, ucs, 2)) > 0) {
            ret = enc;
        }
        break;

    case 15:	/* iso8859-15 */
        if ((len=iso8859_15_wctomb(NULL, (unsigned char*)s, ucs, 2)) > 0) {
            ret = enc;
        }
        break;

    case 16:	/* iso8859-16 */
        if ((len=iso8859_16_wctomb(NULL, (unsigned char*)s, ucs, 2)) > 0) {
            ret = enc;
        }
        break;

    case 17:	/* koi8-r */
        if ((len=koi8_r_wctomb(NULL, (unsigned char*)s, ucs, 2)) > 0) {
            ret = enc;
        }
        break;

    case 18:	/* koi8-u */
        if ((len=koi8_u_wctomb(NULL, (unsigned char*)s, ucs, 2)) > 0) {
            ret = enc;
        }
        break;

    case 19:	/* symbol */
        if (ucs <= 0x00F7) {
            if (ucs >= 0x0020) {
                s[0] = 0;
                s[1] = unicode_to_symbol_1b_0020[ucs - 0x0020];
                if (s[1]) {
                    len = 1;
                    ret = enc;
                }
            }
        } else if (ucs <= 0x0192) {
            if (ucs >= 0x0192) {
                s[0] = 0;
                s[1] = unicode_to_symbol_1b_0192[ucs - 0x0192];
                if (s[1]) {
                    len = 1;
                    ret = enc;
                }
            }
        } else if (ucs <= 0x03D6) {
            if (ucs >= 0x0391) {
                s[0] = 0;
                s[1] = unicode_to_symbol_1b_0391[ucs - 0x0391];
                if (s[1]) {
                    len = 1;
                    ret = enc;
                }
            }
        } else if (ucs <= 0x232A) {
            if (ucs >= 0x2022) {
                s[0] = 0;
                s[1] = unicode_to_symbol_1b_2022[ucs - 0x2022];
                if (s[1]) {
                    len = 1;
                    ret = enc;
                }
            }
        } else if (ucs <= 0x25CA) {
            if (ucs >= 0x25CA) {
                s[0] = 0;
                s[1] = unicode_to_symbol_1b_25CA[ucs - 0x25CA];
                if (s[1]) {
                    len = 1;
                    ret = enc;
                }
            }
        } else if (ucs <= 0x2666) {
            if (ucs >= 0x2660) {
                s[0] = 0;
                s[1] = unicode_to_symbol_1b_2660[ucs - 0x2660];
                if (s[1]) {
                    len = 1;
                    ret = enc;
                }
            }
        } else if (ucs <= 0xF6DB) {
            if (ucs >= 0xF6D9) {
                s[0] = 0;
                s[1] = unicode_to_symbol_1b_F6D9[ucs - 0xF6D9];
                if (s[1]) {
                    len = 1;
                    ret = enc;
                }
            }
        } else if (ucs <= 0xF8FE) {
            if (ucs >= 0xF8E5) {
                s[0] = 0;
                s[1] = unicode_to_symbol_1b_F8E5[ucs - 0xF8E5];
                if (s[1]) {
                    len = 1;
                    ret = enc;
                }
            }
        }
        break;

    case 20:	/* dingbats */
        if (ucs <= 0x00A0) {
            if (ucs >= 0x0020) {
                s[0] = 0;
                s[1] = unicode_to_dingbats_1b_0020[ucs - 0x0020];
                if (s[1]) {
                    len=1;
                    ret = enc;
                }
            }
        } else if (ucs <= 0x2195) {
            if (ucs >= 0x2192) {
                s[0] = 0;
                s[1] = unicode_to_dingbats_1b_2192[ucs - 0x2192];
                if (s[1]) {
                    len = 1;
                    ret = enc;
                }
            }
        } else if (ucs <= 0x2469) {
            if (ucs >= 0x2460) {
                s[0] = 0;
                s[1] = unicode_to_dingbats_1b_2460[ucs - 0x2460];
                if (s[1]) {
                    len = 1;
                    ret = enc;
                }
            }
        } else if (ucs <= 0x2666) {
            if (ucs >= 0x25A0) {
                s[0] = 0;
                s[1] = unicode_to_dingbats_1b_25A0[ucs - 0x25A0];
                if (s[1]) {
                    len = 1;
                    ret = enc;
                }
            }
        } else if (ucs <= 0x27BE) {
            if (ucs >= 0x2701) {
                s[0] = 0;
                s[1] = unicode_to_dingbats_1b_2701[ucs - 0x2701];
                if (s[1]) {
                    len = 1;
                    ret = enc;
                }
            }
        } else if (ucs <= 0xF8E4) {
            if (ucs >= 0xF8D7) {
                s[0] = 0;
                s[1] = unicode_to_dingbats_1b_F8D7[ucs - 0xF8D7];
                if (s[1]) {
                    len = 1;
                    ret = enc;
                }
            }
        }
        break;

    default:
        break;
    }

#if HAVE_ICONV
    if(ret==-1) {
        if( (len = ucs_cache.convert(s, ucs, enc)) > 0) {
            ret = enc;
        }
    }
#endif

    if(len==1 && s[0]!=0) {
        s[1] = s[0];
        s[0] = 0;
    }

    return ret;
}

const int fl_encoding_number(const char *enc)
{
    if (!enc || !strncasecmp(enc, "iso10646-1", 10)) {
        return 0;
    } else if (!strcasecmp(enc, "iso8859-1")) {
        return 1;
    } else if (!strcasecmp(enc, "iso8859-2")) {
        return 2;
    } else if (!strcasecmp(enc, "iso8859-3")) {
        return 3;
    } else if (!strcasecmp(enc, "iso8859-4")) {
        return 4;
    } else if (!strcasecmp(enc, "iso8859-5")) {
        return 5;
    } else if (!strcasecmp(enc, "iso8859-6")) {
        return 6;
    } else if (!strcasecmp(enc, "iso8859-7")) {
        return 7;
    } else if (!strcasecmp(enc, "iso8859-8")) {
        return 8;
    } else if (!strcasecmp(enc, "iso8859-9")) {
        return 9;
    } else if (!strcasecmp(enc, "iso8859-9e")) {
        return 10;
    } else if (!strcasecmp(enc, "iso8859-10")) {
        return 11;
    } else if (!strcasecmp(enc, "iso8859-11")) {
        return 12;
    } else if (!strcasecmp(enc, "iso8859-13")) {
        return 13;
    } else if (!strcasecmp(enc, "iso8859-14")) {
        return 14;
    } else if (!strcasecmp(enc, "iso8859-15")) {
        return 15;
    } else if (!strcasecmp(enc, "iso8859-16")) {
        return 16;
    } else if (!strcasecmp(enc, "koi8-r")) {
        return 17;
    } else if (!strcasecmp(enc, "koi8-u")) {
        return 18;
    } else if (!strcasecmp(enc, "symbol")) {
        return 19;
    } else if (!strcasecmp(enc, "dingbats") || !strcasecmp(enc, "zapfdingbats") ||
               !strcasecmp(enc, "zapf dingbats") || !strcasecmp(enc, "itc zapf dingbats")) {
        return 20;
    }

#if HAVE_ICONV
    int cached_index;
    iconv_t iconv;
    /* Try to find correct converter name for iconv */
    enc = xlfd_to_iconv(enc);

    /* Search cache */
    cached_index = ucs_cache.find(enc);
    if(cached_index>=0) return cached_index;

    /* Create new */
    iconv = iconv_open(enc, "UCS-4");
    if(iconv!=NULL && iconv!=(iconv_t*)-1) {
        //printf("iconv: %s\n", enc);
        return ucs_cache.add((conv_t)iconv, enc);
    }
#endif /* HAVE_ICONV */

    //printf("NO ENCODING: (%s)\n", enc);
    return -1;
}

///////////////////////////////////////////////
///////////////////////////////////////////////

typedef struct builtin_converter {
    int (*xxx_mbtowc)(conv_t conv, ucs4_t *pwc, unsigned char const *s, int n);
    const char *name[2];
};

static builtin_converter converters[] = {
    { iso8859_1_mbtowc, { "iso8859-1", "iso-8859-1" } },
    { iso8859_2_mbtowc, { "iso8859-2", "iso-8859-2" } },
    { iso8859_3_mbtowc, { "iso8859-3", "iso-8859-3" } },
    { iso8859_4_mbtowc, { "iso8859-4", "iso-8859-4" } },
    { iso8859_5_mbtowc, { "iso8859-5", "iso-8859-5" } },
    { iso8859_6_mbtowc, { "iso8859-6", "iso-8859-6" } },
    { iso8859_7_mbtowc, { "iso8859-7", "iso-8859-7" } },
    { iso8859_8_mbtowc, { "iso8859-8", "iso-8859-8" } },
    { iso8859_9_mbtowc, { "iso8859-9", "iso-8859-9" } },
    { iso8859_9e_mbtowc, { "iso8859-9e", "iso-8859-9e" } },
    { iso8859_10_mbtowc, { "iso8859-10", "iso-8859-10" } },
    { iso8859_11_mbtowc, { "iso8859-11", "iso-8859-11" } },
    { iso8859_13_mbtowc, { "iso8859-13", "iso-8859-13" } },
    { iso8859_14_mbtowc, { "iso8859-14", "iso-8859-14" } },
    { iso8859_15_mbtowc, { "iso8859-15", "iso-8859-15" } },
    { iso8859_16_mbtowc, { "iso8859-16", "iso-8859-16" } },

    { koi8_r_mbtowc, { "koi8-r", 0 } },
    { koi8_u_mbtowc, { "koi8-u", 0 } }
};
static int converters_size = sizeof(converters)/sizeof(converters[0]);

static int converter_loop(builtin_converter *converter,
                          const unsigned char *inbuf, int &inlen,
                          char *outbuf, int outlen)
{
    int inpos=0;
    int outpos=0;
    ucs4_t wc;
    while(inpos < inlen) {
        if(converter->xxx_mbtowc(NULL, &wc, inbuf+inpos, 1)<=0)
            break;
        outpos += fl_ucs2utf(wc, outbuf+outpos);
        inpos++;
    }
    inlen = inpos;
    return outpos;
}

int fl_find_converter(const char *from_codeset)
{
    for(int n=0; n<converters_size; n++) {
        if(converters[n].name[1] && !strcasecmp(from_codeset, converters[n].name[1])) {
            return n;
            break;
        }
        if(converters[n].name[0] && !strcasecmp(from_codeset, converters[n].name[0])) {
            return n;
            break;
        }
    }
#if HAVE_ICONV
    int cached_index;
    iconv_t iconv;

    /* Try to find correct converter name for iconv */
    from_codeset = xlfd_to_iconv(from_codeset);

    /* Search cache */
    cached_index = utf8_cache.find(from_codeset);
    if(cached_index>=0) return cached_index;

    /* Create new */
    iconv = iconv_open("UTF-8", from_codeset);
    if(iconv!=NULL && iconv!=(iconv_t*)-1) {
        return utf8_cache.add((conv_t)iconv, from_codeset);
    }
#endif /* HAVE_ICONV */

    return -1;
}

int fl_convert2utf(int index,
                   const unsigned char *inbuf, int &inlen,
                   char *outbuf, int outlen)
{
    if(index>=0 && index<converters_size) {
        builtin_converter *converter = &converters[index];
        return converter_loop(converter, inbuf, inlen, outbuf, outlen);
    }
#if HAVE_ICONV
    return utf8_cache.convert(index, inbuf, inlen, outbuf, outlen);
#else
    return -1;
#endif /* HAVE_ICONV */
}

int fl_convert2utf(const char *from_codeset,
                   const unsigned char *inbuf, int &inlen,
                   char *outbuf, int outlen)
{
    return fl_convert2utf(fl_find_converter(from_codeset), inbuf, inlen, outbuf, outlen);
}
