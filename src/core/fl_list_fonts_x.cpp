//
// "$Id$"
//
// Copyright 1998-2000 by Bill Spitzak and others.
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

// This horrible mess is to to provide fltk with a friendly font-naming
// interface, despite the incredible stupidity in the X font mechanism.

// The "X font name" is a long string that looks something like this:

// -foundry-family-weight-slant-width1-style-8-180-75-75-p-104-iso8859-1

// Fltk ignores the "foundry" and everything after the "style".  All X
// fonts where the remainder matches are part of an fltk "family" of
// fonts where the only differences are the size and encoding.

// The fltk interface, and much of the innards of this, uses "nice"
// names.  This is a straght-forward translation of the X name of some
// font in a family to compress it to a readable family name.  There is
// no guarantee that all nice names are unique, and there is no reverse
// translation other than to list all the fonts and find a match.

#include <efltk/x.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <config.h>

// return dash number N, or pointer to ending null if none:
static const char* font_word(const char* p, int n)
{
    //  while (*p) {if (*p=='-') {if (!--n) break;} p++;}
                                 // simpler to follow logic?
    for (; *p; p++) if (*p == '-' && !--n) break;

    return p;
}


// turn word N of a X font name into either some attribute bits
// (right now 0, FL_BOLD, or FL_ITALIC), or into -1 indicating that
// the word should be put into the name:

static int attribute(int n, const char *p)
{
    // don't put blank things into name:
    if (!*p || *p=='-' || *p=='*') return 0;
    if (n == 3 || n == 5)        // weight or sWidth
    {
        if (!strncmp(p,"normal",6) ||
            !strncmp(p,"light",5) ||
            !strncmp(p,"medium",6) ||
            !strncmp(p,"book",4) ||
            !strncmp(p,"regular",7)) return 0;
        if (!strncmp(p,"bold",4) ||
            !strncmp(p+4,"bold",4) ||
            !strncmp(p+5,"bold",4)) return FL_BOLD;
    }                            // slant
    else if (n == 4)
    {
        if (*p == 'r') return 0;
        if (*p == 'i' || *p == 'o') return FL_ITALIC;
    }
    return -1;
}


// turn the system name into a nice name, write it to output buffer,
// and return the accumulated attribute, and possibly the size:

static int to_nice(char* o, const char* p)
{

    int type = 0;

    // get the family:
    const char *x = font_word(p,2); if (*x) x++; if (*x=='*') x++;
    const char *e = font_word(x,1);
    strncpy(o,x,e-x); o += e-x;

    // collect all the attribute words:
    for (int n = 3; n <= 5; n++)
    {
        // get the next word:
        if (*e) e++; x = e; e = font_word(x,1);
        int t = attribute(n,x);
        if (t < 0) {*o++ = ' '; strncpy(o,x,e-x); o += e-x;}
        else type |= t;
    }
    *o = 0;

    return type;
}


// public function that calls the converter.  If ap is null it will also
// add bold/italic words to the end of the nice name.
const char* Fl_Font_::name(int* ap) const
{
    static char buffer[128];
    int type = to_nice(buffer, name_);
    if (ap) *ap = type;
    else
    {
        if (type & FL_BOLD) strcat(buffer," bold");
        if (type & FL_ITALIC) strcat(buffer, " italic");
    }
    return buffer;
}


////////////////////////////////////////////////////////////////
// Generate a list of every font known by X server:

// Sort X font names in alphabetical order of their "nice" names:
// This is horrendously slow, but only needs to be done once....
extern "C"
{
    static int sort_function(const void *aa, const void *bb)
    {
        char aname[128]; int aattrib = to_nice(aname, *(char**)aa);
        char bname[128]; int battrib = to_nice(bname, *(char**)bb);
        int ret = strcasecmp(aname, bname); if (ret) return ret;
        return (aattrib-battrib);
    }
}

int fl_list_fonts(Fl_Font*& arrayp)
{
    static Fl_Font* font_array = 0;
    static int num_fonts = 0;
    if (font_array) {
        arrayp = font_array;
        return num_fonts;
    }

    fl_open_display();
    int xlistsize;
    char **xlist = XListFonts(fl_display, "-*", 10000, &xlistsize);
    if (!xlist) return 0;        // ???
    qsort(xlist, xlistsize, sizeof(*xlist), sort_function);

    Fl_Font_* family = 0;        // current family
    char family_name[128] = "";  // nice name of current family

    int array_size = 0;
    for (int i=0; i<xlistsize;)
    {
        char newname[128];
        int attribute = to_nice(newname, xlist[i]);

        // find all the matching fonts:
        int n = 1;
        for (; i+n < xlistsize; n++) {
            char nextname[128];
            int nextattribute = to_nice(nextname, xlist[i+n]);
            if (nextattribute != attribute || strcmp(nextname, newname))
                break;
        }

        Fl_Font_* newfont;
        // See if it is one of our built-in fonts:
        const char* skip_foundry = font_word(xlist[i], 2);
        int length = font_word(skip_foundry, 6)-skip_foundry;
        for (int j = 0; ; j++) {
            // no, create a new font
            if (j >= 16) {
                newfont = new Fl_Font_;
                newfont->name_ = xlist[i];
                newfont->bold_ = newfont;
                newfont->italic_ = newfont;
                newfont->first = 0;
                newfont->xlist_ = xlist+i;
                newfont->xlist_n_ = -n;
                break;
            }
            // see if it is one of our built-in fonts:
            // if so, set the list of x fonts, since we have it anyway
            if (!strncmp(skip_foundry, fl_fonts[j].name_+2, length))
            {
                newfont = fl_fonts+j;
                if(!newfont->xlist_) {
                    newfont->xlist_ = xlist+i;
                    newfont->xlist_n_ = -n;
                }
                break;
            }
        }

        if (attribute && !strcmp(newname, family_name))
        {
            switch (attribute)
            {
            case FL_BOLD: family->bold_ = newfont; break;
            case FL_ITALIC: family->italic_ = newfont; break;
            case FL_BOLD|FL_ITALIC:
                family->bold_->italic_ = family->italic_->bold_ = newfont;
                break;
            }

        } else {

            family = newfont;
            strcpy(family_name, newname);
            if (num_fonts >= array_size) {
                array_size = 2*array_size+128;
                font_array = (Fl_Font*)realloc(font_array, array_size*sizeof(Fl_Font));
            }
            font_array[num_fonts++] = newfont;
        }

        i += n;
    }
    arrayp = font_array;
    return num_fonts;
}


////////////////////////////////////////////////////////////////
// Return all the encodings for this font:
int Fl_Font_::encodings(const char**& arrayp) const
{
    if(((Fl_Font_*)this)->cache_xlist()==0)
        return 0;
    int listsize = xlist_n_;
    if(listsize<0) listsize = -listsize;
    static const char* array[128];
    int count = 0;
    for (int i = 0; i < listsize; i++) {
        const char *q = xlist_[i];
        const char *c = font_word(q,13);
        if (!*c++ || !*c) continue;
        // insert-sort the new encoding into list:
        int n;
        int m;
        for (n = count; n > 0; n--) {
            int cmp = strcasecmp(array[n-1], c);
            if (cmp < 0) break;
            if (cmp == 0) goto CONTINUE;
        }
        for (m = count; m > n; m--) array[m] = array[m-1];
        array[n] = c;
        count++;
        if (count >= 128) break;
    CONTINUE:;
    }
    arrayp = array;
    return count;
}

////////////////////////////////////////////////////////////////

// Return all the point sizes supported by this font:
int Fl_Font_::sizes(int*& sizep) const
{
    if(((Fl_Font_*)this)->cache_xlist()==0) return 0;
    int listsize = xlist_n_;
    if(listsize<0) listsize = -listsize;

    static int array[128];
    int count = 0;
    for (int i = 0; i < listsize; i++) {
        const char *q = xlist_[i];
        const char* d = font_word(q,7);
        if (!*d++) continue;
        int s = strtol(d,0,10);
        // insert-sort the new size into list:
        int m;
        int n;
        for (n = count; n > 0; n--) {
            int cmp = array[n-1]-s;
            if (cmp < 0) break;
            if (cmp == 0) goto CONTINUE;
        }
        for (m = count; m > n; m--) array[m] = array[m-1];
        array[n] = s;
        count++;
        if (count >= 128) break;
    CONTINUE:;
    }
    sizep = array;
    return count;
}


//
// End of "$Id$"
//
