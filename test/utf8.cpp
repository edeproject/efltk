// UTF-8 test program for the Extended Fast Light Tool Kit (EFLTK).
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
// Please report all bugs and problems to "fltk-bugs@fltk.org".
//

#include <efltk/math.h>
#include <config.h>

#include <efltk/Fl.h>
#include <efltk/Fl_Double_Window.h>
#include <efltk/Fl_Toggle_Button.h>
#include <efltk/Fl_Choice.h>
#include <efltk/Fl_Input.h>
#include <efltk/Fl_Box.h>
#include <efltk/Fl_Scroll.h>
#include <efltk/Fl_ListView.h>
#include <efltk/fl_draw.h>
#include <efltk/fl_utf8.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#if HAVE_XUTF8

class My_Input : public Fl_Input
{
public:
    My_Input (int x, int y, int w, int h) : Fl_Input(x, y, w, h) {};
    void draw() {
        fl_push_clip(0,0,w(),h());
        if(damage() & FL_DAMAGE_ALL) draw_box();
        drawtext(x()+box()->dx()+3, y()+box()->dy(),
                 w()-box()->dw()-6, h()-box()->dh());
        fl_pop_clip();
    }
    void drawtext(int X, int Y, int W, int H) {
        fl_color(text_color());
        fl_font(text_font(), text_size());
        fl_rtl_draw(value(), strlen(value()),
                    X + (int)fl_width(value()), Y + fl_height() -fl_descent());
    }
};

int main(int argc, char** argv) 
{
  Fl_Font myfont = fl_create_font(
#ifdef _WIN32
	"Arial Unicode MS"
	//"MS Gothic"	
	//"MS Mincho"	
#else
	"-*-courier-medium-r-normal--*,"
	"-*-fixed-medium-*-*--*-*-*-*-*-*-iso8859-15,"
	"-*-symbol-*-*-*--*-*-*-*-*-*-adobe-fontspecific,"
	"-*-*dingbats-*-*-*--*-*-*-*-*-*-adobe-fontspecific,"
	"-*-fixed-*-*-*--*-*-*-*-*-*-iso8859-2,"
	"-*-fixed-*-*-*--*-*-*-*-*-*-iso8859-3,"
	"-*-fixed-*-*-*--*-*-*-*-*-*-iso8859-4,"
	"-*-fixed-*-*-*--*-*-*-*-*-*-iso8859-5,"
	"-*-fixed-*-*-*--*-*-*-*-*-*-iso8859-6,"
	"-*-fixed-*-*-*--*-*-*-*-*-*-iso8859-7,"
	"-*-fixed-*-*-*--*-*-*-*-*-*-iso8859-8,"
	"-*-fixed-*-*-*--*-*-*-*-*-*-iso8859-9,"
	"-*-fixed-*-*-*--*-*-*-*-*-*-iso8859-13,"
	"-*-fixed-*-*-*--*-*-*-*-*-*-iso8859-14,"
	"-*-fixed-*-*-*--*-*-*-*-*-*-koi8-*,"
	"-*-fixed-*-*-*--*-*-*-*-*-*-jisx0208.1983-*,"
	//"-*-fixed-*-*-*--*-*-*-*-*-*-jisc6226.1978-*,"
	"-*-fixed-*-*-*--*-*-*-*-*-*-jisx0201.1976-*,"
	"-*-*-*-*-*--*-*-*-*-*-*-ksc5601.1987-*,"
	//"-*-fixed-*-*-*--*-*-*-*-*-*-jisx0208.1990-*,"
	"-*-fixed-medium-r-normal--*-*-*-*-*-*-big5*-*,"
	//"-*-fixed-*-*-*--*-*-*-*-*-*-iso646.1991-*,"
	//"-*-fixed-*-*-*--*-*-*-*-*-*-mulearabic-1,"
	//"-*-fixed-*-*-*--*-*-*-*-*-*-muleindian-1,"
	//"-*-fixed-*-*-*--*-*-*-*-*-*-muleindian-2,"
	//"-*-fixed-*-*-*--*-*-*-*-*-*-mulelao-*,"
	//"-*-fixed-*-*-*--*-*-*-*-*-*-tis620.2529-*,"
	//"-*-fixed-*-*-*--*-*-*-*-*-*-is13194-*,"
	//"-*-fixed-*-*-*--*-*-*-*-*-*-mulearabic-2,"
	//"-*-fixed-*-*-*--*-*-*-*-*-*-sisheng_cwnn-*,"
	//"-*-fixed-*-*-*--*-*-*-*-*-*-omron_udc_zh-*,"
	//"-*-fixed-*-*-*--*-*-*-*-*-*-muleipa-*,"
	//"-*-fixed-*-*-*--*-*-*-*-*-*-viscii1.1-*,"
	//"-*-fixed-*-*-*--*-*-*-*-*-*-gost19768.74-*,"
	"-*-unifont-*-*-*--*-*-*-*-*-*-iso10646-1"
#endif	
  );  

  Fl::init_locale();

#define SCROLL

  Fl_Window window(200 + 5*75,400);
#ifdef SCROLL
  Fl_Scroll scroll(200,0,5*75,400);
#else
  Fl_ListView scroll(200,0,5*75,400);
  scroll.add_column("Range",75);
  scroll.add_column("UTF-8",4*75-20);
  scroll.text_size(14);
  scroll.text_font(myfont);    
#endif
  scroll.begin();

  int off = 2;
  
  if (argc > 1) {
	off = (int)strtoul(argv[1], NULL, 0);
	off /= 16;
  }
  argc = 1;
  for (int y=off; y< 0x10000 / 16/*off + 1024*/; y++) {
    int o = 0;
    char bu[25];
    char buf[16*5];
    int i = 16 * y; 
    for (int x=0; x<16; x++) {
	int l;
	l = fl_ucs2utf(i, buf + o);
	if (l < 1) l = 1;
	o += l;
	i++;
    }
    buf[o] = '\0';
    sprintf(bu, "0x%04X", y * 16);
#ifdef SCROLL
    Fl_Box* box = new Fl_Box(0,(y-off)*25,60,25);
	box->copy_label(bu);
	box->color(FL_WHITE); box->box(FL_DOWN_BOX);    

    Fl_Input *b = new Fl_Input(60,(y-off)*25,300,25);
	b->text_size(14);
    b->text_font(myfont);
    b->value(buf);
#else
    Fl_ListView_Item* b = new Fl_ListView_Item();
	b->copy_label(0, bu);
	b->copy_label(1, buf);
#endif
  }
  scroll.end();
  window.resizable(scroll);

  int l;
  char *latin1 = "ABCabcàèéïâîöüã123";
  char *utf8 = (char*) malloc(strlen(latin1) * 3 + 1);

  Fl_Input i1(5, 5, 190, 25);
  l = fl_latin12utf((const unsigned char*)latin1, strlen(latin1), utf8);
  utf8[l] = '\0';
  i1.value(utf8);

  char *utf8l = (char*) malloc(strlen(utf8) * 3 + 1);
  Fl_Input i2(5, 35, 190, 25);
  l = fl_utf_tolower((const unsigned char*)utf8, l, utf8l);
  utf8l[l] = '\0';
  i2.value(utf8l);

  char *utf8u = (char*) malloc(strlen(utf8l) * 3 + 1);
  Fl_Input i3(5, 65, 190, 25);
  l = fl_utf_toupper((const unsigned char*)utf8l, l, utf8u);
  utf8u[l] = '\0';
  i3.value(utf8u);

  char *ltr_txt = "\\->e\xCC\x82=\xC3\xAA";
  Fl_Input i4(5, 90, 190, 25);
  i4.value(ltr_txt);	
  i4.text_font(FL_COURIER);

  unsigned short arabic[] ={/*8238,*/ 1610, 1608, 1606, 1616, 1603, 1608, 1583, 0};
  char abuf[40];
  l = fl_unicode2utf(arabic, 8, abuf);  
  abuf[l] = 0;
  My_Input i5(5, 115, 190, 50);
  i5.text_font(myfont);
  i5.text_size(36);
  i5.value(abuf);

 unsigned short arabic1[] ={/*8238,*/ 0x5c, 1610, 0x20, 1608, 0x20, 1606, 0x20,  1616, 0x20, 1603, 0x20, 1608, 0x20, 1583, 0};
 
  l = fl_unicode2utf(arabic1, 15, abuf);  
  abuf[l] = 0;
  My_Input i6(5, 175, 190, 50);
  i6.text_font(myfont);
  i6.text_size(30);
  i6.value(abuf);
  window.end();
  window.show(argc,argv);
  return Fl::run();
}

#else

#include <efltk/fl_ask.h>
int main(int argc, char **argv)
{
    fl_alert("This demo needs UTF-8 support!");
    return Fl::run();
}

#endif

