/**
  * Implementation of Fl_Base64 class
  * 
  * The source below is under LGPL license.
  * Copyright (c) EDE Team. More information: http://ede.sf.net .
  * Authors (sorted by time they worked on this source file):
  *     Dejan Lekic <dejan§nu6.org>
  * Contributors (ie. people that have sent patches, ideas, suggestions):
  *     None
  **/

#include <efltk/net/Fl_Base64.h>

/**
 * Following structures are originally from mutt
 * Best regards to mutt developers!
 */
static int Index_64[128] = {
    -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1,
    -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,62, 63,-1,-1,-1,
    52,53,54,55, 56,57,58,59, 60,61,-1,-1, -1,-1,-1,-1,
    -1, 0, 1, 2,  3, 4, 5, 6,  7, 8, 9,10, 11,12,13,14,
    15,16,17,18, 19,20,21,22, 23,24,25,-1, -1,-1,-1,-1,
    -1,26,27,28, 29,30,31,32, 33,34,35,36, 37,38,39,40,
    41,42,43,44, 45,46,47,48, 49,50,51,-1, -1,-1,-1,-1
}; /* Index_64 */

static char B64Chars[64] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
    'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
    'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
    't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', '+', ','
};

#define base64val(c) Index_64[(unsigned int)(c)]
#define base64chars(c) B64Chars[(unsigned int)(c & 0x3F)]

/* ------------------------------------------------------------------------- */
/* ENCODE INTERFACE															 */
/* ------------------------------------------------------------------------- */

/**
  * encode() method encodes (base64) given buffer bufSource
  * to given destination buffer bufDest.
  *
  * @param bufDest Fl_Buffer Destination buffer
  * @param bufSource Fl_Buffer Source buffer
  * @see encode(Fl_Buffer bufSource)
  * @author Dejan Lekic, http://dejan.nu6.org
  */
void Fl_Base64::encode(Fl_Buffer& bufDest, const Fl_Buffer& bufSource)
{
    char c;
    char *current = bufSource.data();
    unsigned len = bufSource.bytes();

    while (len >= 3)
    {
        c = base64chars((current[0] & 0xFC) >> 2);
        bufDest.append(c);

        c = base64chars(((current[0] & 0x03) << 4) | ((current[1] & 0xF0) >> 4));
        bufDest.append(c);

        c = base64chars(((current[1] & 0x0F) << 2) | ((current[2] & 0xC0) >> 6));
        bufDest.append(c);

        c = base64chars(current[2] & 0x3F);
        bufDest.append(c);

        len     -= 3;
        current += 3;   /* move pointer 3 characters forward */
    } /* while */

    /* Now we should clean up remainder */
    if (len > 0)
    {
        c = base64chars(current[0] >> 2);
        bufDest.append(&c, 1);      
        if (len > 1)
        {
            c = base64chars(((current[0] & 0x03) << 4) | (current[1] >> 4));
            bufDest.append(&c, 1);
            c = base64chars((current[1] & 0x0f) << 2);
            bufDest.append(&c, 1);
            c = '=';
            bufDest.append(&c, 1);
        } /* if */
        else
        {
            c = base64chars((current[0] & 0x03) << 4);
            bufDest.append(&c, 1);
            c = '=';
            bufDest.append(&c, 1);
            c = '=';
            bufDest.append(&c, 1);
        } /* else */
    } /* if */
} /* encode(Fl_Buffer& bufDest, const Fl_Buffer& bufSource) */

/* ------------------------------------------------------------------------- */

/**
 * This encode() method encodes (base64) given buffer bufSource
 * and returns Fl_String object.
 *
 * @param bufSource Fl_Buffer* Source buffer
 * @returns Fl_String
 * @see encode(Fl_Buffer* bufDest, Fl_Buffer* bufSource)
 * @author Dejan Lekic, http://dejan.nu6.org
 */
void Fl_Base64::encode(Fl_String& strDest, const Fl_Buffer& bufSource)
{
    Fl_Buffer bufOut;
    encode(bufOut, bufSource);
    
	if(!strDest.empty()) strDest.clear();
    strDest.append(bufOut.data(), bufOut.bytes());
} /* encode(Fl_String& strDest, const Fl_Buffer& bufSource) */



/* ------------------------------------------------------------------------- */
/* DECODE INTERFACE															 */
/* ------------------------------------------------------------------------- */

static int internal_decode(Fl_Buffer &bufDest, const uchar *src, unsigned src_len)
{
    const unsigned char *current = src;
    unsigned char c;
    int ch, j=0;

    if (src_len <= 0)
        return -1;            /* If source buffer is empty return -1  */
    
	if ((src_len % 4) != 0)   /* Source buffer MUST be dividable by 4 */		
		return -1;            /* (no reminders)                       */    
	
	bufDest.reset();

    for (unsigned i=0; i < src_len; i++)
    {
        ch = current[i];

        if (ch == '=') 
            break;
        if (ch == ' ') 
            ch = '+';
        ch = Index_64[ch];
        if (ch < 0) 
        {
            continue;
        } /* if */
        switch (i % 4)
        {
            case 0:
                c = (unsigned char)((ch << 2) & 0xFF);
                bufDest.append((char *)&c, 1);
                break;
            case 1:
                bufDest.data()[j] |= ((ch >> 4) & 0xFF);
                j++;
                if (current[i+1] != '=')
                {
                    c = (unsigned char)((ch << 4) & 0xFF);
                    bufDest.append((char *)&c, 1);
                } /* if */
                break;
            case 2:
                bufDest.data()[j] |= ((ch >> 2) & 0x0f);
                j++;
                if (current[i+1] != '=')
                {
                    c = (unsigned char)((ch << 6) & 0xFF);
                    bufDest.append((char *)&c, 1);
                } /* if */
                break;
            case 3:
                bufDest.data()[j] |= ch;
                j++;
                break;
        } /* switch */
    } /* for */
    return j;
} /* decode(Fl_Buffer &bufDest, const Fl_Buffer &bufSource) */


int Fl_Base64::decode(Fl_Buffer &bufDest, const Fl_Buffer& bufSource)
{
	return internal_decode(bufDest, (const uchar *)bufSource.data(), bufSource.bytes());
} /* decode(Fl_Buffer &bufDest, const Fl_Buffer &bufSource) */

/* ------------------------------------------------------------------------- */

int Fl_Base64::decode(Fl_Buffer &bufDest, const Fl_String& strSource)
{
    return internal_decode(bufDest, (const uchar *)strSource, strSource.length());
} /* decode(Fl_Buffer &bufDest, const Fl_String &strSource) */

/* ------------------------------------------------------------------------- */



/***** $Id$
 *     Project: eFLTK
 ***   This source code is released under GNU LGPL License
 *     Copyright (c) EDE Team, 2000-DWYRT  (DWYRT = Date When You Read This)
 ***** Equinox Desktop Environment, http://ede.sf.net */
