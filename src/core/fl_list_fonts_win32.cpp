//
// "$Id$"
//
// _WIN32 font utilities for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-1999 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//

#include <efltk/Fl.h>
#include <efltk/win32.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <config.h>
#include <efltk/fl_utf8.h>
#include <stdio.h>

// turn a stored font name into a pretty name:
const char* Fl_Font_::name(int* ap) const
{
    int type;
    switch (name_[0])
    {
        case 'B': type = FL_BOLD; break;
        case 'I': type = FL_ITALIC; break;
        case 'P': type = FL_BOLD | FL_ITALIC; break;
        default:  type = 0; break;
    }
	int skip=1; if(name_[1]=='@') skip++;
    if (ap) { *ap = type; return name_+skip; }
    if (!type) { return name_+skip; }
    static char buffer[128];
    strncpy(buffer, name_+skip, sizeof(buffer)-1);
    if (type & FL_BOLD) strcat(buffer, " bold");
    if (type & FL_ITALIC) strcat(buffer, " italic");	

    return buffer;
}

static const char *charset_to_str(DWORD ch)
{
	switch(ch) {
		case ANSI_CHARSET:			return "Ansi";
		case BALTIC_CHARSET:		return "Baltic";
		case CHINESEBIG5_CHARSET:	return "Chinese Big5";
		case EASTEUROPE_CHARSET:	return "Eastern Europe";
		case GB2312_CHARSET:		return "Gb2312";
		case GREEK_CHARSET:			return "Greek";
#ifndef _WIN32_WCE
		case HANGUL_CHARSET:		return "Hangul";
#endif
		case MAC_CHARSET:			return "MAC";
		case OEM_CHARSET:			return "OEM";
		case RUSSIAN_CHARSET:		return "Russian";
		case SHIFTJIS_CHARSET:		return "Shift Jis";
		case SYMBOL_CHARSET:		return "Symbol";
		case TURKISH_CHARSET:		return "Turkish";
		case VIETNAMESE_CHARSET:	return "Vietnamese";
		case JOHAB_CHARSET:			return "Johab";
		case ARABIC_CHARSET:		return "Arabic";
		case HEBREW_CHARSET:		return "Hebrew";
		case THAI_CHARSET:			return "Thai";

		case DEFAULT_CHARSET:
		default:
			break;
	}
	return "Unknown";
}

static Fl_Font_ *enc_font=0;
static int CALLBACK encoding_enumcb(CONST LOGFONT* lplf,
			CONST TEXTMETRIC* lpntm,
			DWORD fontType,
			LPARAM p)
{
	const char *c = charset_to_str(lplf->lfCharSet);
	for(uint n=0; n<enc_font->charsets_->size(); n++)
		if(!strcmp(enc_font->charsets_->item(n), c))
			return 0;		

	enc_font->charsets_->append(c);
	return 1;
}

extern char *fl_utf82locale(const char *s, UINT codepage = 0);

int Fl_Font_::encodings(const char**& arrayp) const
{
	if(charsets_) {
		// Cached..
		arrayp=(const char**)charsets_->data();
		return charsets_->size();
	}

	((Fl_Font_*)this)->charsets_ = new Fl_CString_List;
	enc_font = (Fl_Font_*)this;

    HDC dc = fl_getDC();
    LOGFONT lf;
    memset(&lf, 0, sizeof(lf));
	
	const char *name = name_+1;
	TCHAR *family_name;
#ifdef UNICODE
	int len = fl_utf_nb_char((unsigned char*)name, strlen(name));
	family_name = (TCHAR*)malloc((len + 1) * sizeof(TCHAR));
	fl_utf2unicode((unsigned char*)name, len, (unsigned short*)family_name);
	family_name[len] = 0;
	wcsncpy(lf.lfFaceName, family_name, LF_FACESIZE);
#else
	family_name = fl_utf82locale(name);
	strncpy(lf.lfFaceName, family_name, LF_FACESIZE);
#endif  
	
	lf.lfCharSet = DEFAULT_CHARSET;

#ifndef _WIN32_WCE
    EnumFontFamiliesEx(dc, &lf, (FONTENUMPROC)encoding_enumcb, 0, 0);
#else
	EnumFontFamilies(dc, NULL, (FONTENUMPROC)encoding_enumcb, 0);
#endif

	if(charsets_->size()==0) charsets_->append("Unknown");
	else charsets_->sort();
	
    // This is a poor simulation:
    //static const char* simulation[] = {"iso8859-1", 0};
    //arrayp = simulation;
    //return 1;
	
	arrayp=(const char**)charsets_->data();
	return charsets_->size();
}


////////////////////////////////////////////////////////////////
// List sizes:

static Fl_Font_ *size_font=0;
static int CALLBACK size_enumcb(
	CONST LOGFONT* lpelf,
	CONST TEXTMETRIC* lpntm,
	DWORD fontType,
	LPARAM p)
{
    if ((fontType & RASTER_FONTTYPE) == 0) {
        // Scalable font
        return 0;
    }
    int add = lpntm->tmHeight - lpntm->tmInternalLeading;
	size_font->sizes_->append(add);
    return 1;
}


int Fl_Font_::sizes(int*& sizep) const
{
	if(sizes_) {
		// Cached..
		sizep=(int*)sizes_->data();
		return sizes_->size();
	}

	((Fl_Font_*)this)->sizes_ = new Fl_Int_List;
	size_font = (Fl_Font_*)this;

    HDC dc = fl_getDC();
	LOGFONT lf;
	memset(&lf, 0, sizeof(lf));

	const char *name = name_+1;
	TCHAR *family_name;
#ifdef UNICODE
	int len = fl_utf_nb_char((unsigned char*)name, strlen(name));
	family_name = (TCHAR*)malloc((len + 1) * sizeof(TCHAR));
	fl_utf2unicode((unsigned char*)name, len, (unsigned short*)family_name);
	family_name[len] = 0;
	wcsncpy(lf.lfFaceName, family_name, LF_FACESIZE);
#else
	family_name = fl_utf82locale(name);
	strncpy(lf.lfFaceName, family_name, LF_FACESIZE);
#endif  

	lf.lfCharSet = DEFAULT_CHARSET;

#ifndef _WIN32_WCE	
	EnumFontFamiliesEx(dc, &lf, (FONTENUMPROC)size_enumcb, 0, 0);    
#else
	EnumFontFamilies(dc, lf.lfFaceName, (FONTENUMPROC)size_enumcb,0);    
#endif
	if(sizes_->size()==0) sizes_->append(0);
	else sizes_->sort();

	sizep=(int*)sizes_->data();
	return sizes_->size();
}


////////////////////////////////////////////////////////////////
// list fonts:

static char *attr_letters = "PPIB ";

static Fl_Font_* make_a_font(char attrib, const char* name, CONST LOGFONT *lfont)
{
    // see if it is one of our built-in fonts and return it:
    for (int j = 0; j < 16; j++)
    {
        if(fl_fonts[j].name_[0] == attrib && !fl_utf_strcasecmp(fl_fonts[j].name_+1, name)) 
			return fl_fonts+j;
    }

    // no, lets create a font:
    Fl_Font_* newfont = new Fl_Font_;
	newfont->charsets_ = 0;
	newfont->sizes_ = 0;
    char *n = new char[strlen(name)+2];
    n[0] = attrib;
    strcpy(n+1, name);

    // if this is something like "Arial Bold", strip the "Bold" part if not using it
	// This doesnt work, if different locale than en_US
	// Windows converts also font names to current locale...
    /*char *pEnd = n + strlen(n);
    for(int i = 0; attr_names[i]; i++)
    {
        char *pTemp = strstr(n, attr_names[i]);
        if(pTemp == pEnd - strlen(attr_names[i]))
            *pTemp = '\0';
    }
	*/
	
	// This is better, locale independ way:
	if(lfont->lfWeight>FW_NORMAL || lfont->lfItalic) {
		char *pTemp = strrchr(n, ' ');
		if(pTemp) *pTemp = '\0';
	}
    
    newfont->name_ = n;
    newfont->bold_ = newfont;
    newfont->italic_ = newfont;
    newfont->first = 0;
    return newfont;
}

static Fl_Font* font_array = 0;
static int num_fonts = 0;
static int array_size = 0;

static int CALLBACK enumcb(
	CONST LOGFONT *lplf,
	CONST TEXTMETRIC *lpntm,
	DWORD fontType,
	LPARAM p)
{
    // we need to do something about different encodings of the same font
    // in order to match X!  I can't tell if each different encoding is
    // returned sepeartely or not.  This is what fltk 1.0 did:
    if(lplf->lfCharSet != ANSI_CHARSET) return 1;	

	static char utf8buf[LF_FULLFACESIZE*6];
	utf8buf[fl_unicode2utf((unsigned short*)((ENUMLOGFONT*)lplf)->elfFullName, LF_FULLFACESIZE, utf8buf)];
	const char *name = utf8buf;	

    bool bNeedBold = (lplf->lfWeight <= FW_NORMAL);

    Fl_Font_* base = make_a_font(' ', name, lplf);
    base->italic_ = make_a_font('I', name, lplf);
    if (bNeedBold) {
        base->bold_ = make_a_font('B', name, lplf);
        base->italic_->bold_ = base->bold_->italic_ = make_a_font('P', name, lplf);
    }

    if (num_fonts >= array_size) {
        array_size = 2*array_size+128;
        font_array = (Fl_Font*)realloc(font_array, array_size*sizeof(Fl_Font));
    }
    font_array[num_fonts++] = base;

    return 1;
}

// Sort fonts by their "nice" name (it is possible Win32 always returns
// them in this order, but I'm not sure):
static int sort_function(const void *aa, const void *bb)
{
    const char* name_a = (*(Fl_Font_**)aa)->name_;
    const char* name_b = (*(Fl_Font_**)bb)->name_;
    int ret = fl_utf_strcasecmp(name_a+1, name_b+1); 
	if (ret) return ret;
    return name_a[0]-name_b[0];  // sort by attribute
}

int fl_list_fonts(Fl_Font*& arrayp)
{
    if (font_array) {
		arrayp = font_array; 
		return num_fonts;
	}
    HDC dc = fl_getDC();
    LOGFONT lf;
    memset(&lf, 0, sizeof(lf));
	
	// According to MSDN:
	// to enumerate all styles and charsets of all fonts:
	lf.lfFaceName[0] = 0;
	lf.lfCharSet = DEFAULT_CHARSET;

#ifndef _WIN32_WCE
    EnumFontFamiliesEx(dc, &lf, (FONTENUMPROC)enumcb, 0, 0);
#else
    EnumFontFamilies(dc, NULL, (FONTENUMPROC)enumcb, 0);
#endif
    
    qsort(font_array, num_fonts, sizeof(Fl_Font), sort_function);
    arrayp = font_array;
    return num_fonts;
}


//
// End of "$Id$"
//
