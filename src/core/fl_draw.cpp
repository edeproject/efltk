//
// "$Id$"
//
// Label drawing code for the Fast Light Tool Kit (FLTK).
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

// Implementation of fl_draw(const char*,int,int,int,int,Fl_Align)
// Used to draw all the labels and text, this routine:

// Breaks them into lines at \n characters.

// Splits it at every \t tab character and uses fl_column_widths() to
// set each section into a column.

// Parses '&x' combinations to produce MicroSoft style underscores,
// unless FL_RAW_LABEL flag is set.

// Word wraps the labels to fit into their column (if FL_ALIGN_WRAP
// flag is on) and aligns them agains the inside of their boxes.

#include <efltk/fl_math.h>
#include <efltk/fl_draw.h>
#include <string.h>
#include <efltk/Fl_Device.h>

Fl_Device fl_fltk_dev;
Fl_Device *fl_current_dev = &fl_fltk_dev;

#ifndef _WIN32
#warning Where are they?
#endif

void Fl_Device::font(const char* s, float size){puts("font 1");};
void Fl_Device::font(const char* s, int attributes, float size){puts("font 2");};
const char* Fl_Device::fontname(Fl_Font, int *){puts("font 3"); return 0;};	
//

// Any string longer than this does not get &x underscore processing.
#define MAX_LENGTH_FOR_UNDERSCORE 128

const int* fl_column_widths_ = 0;

// The implementation splits the text up into individual calls to fl_draw.
// Each has an x/y position and a segment of text. Probably should be
// expanded to have a font & size, This will allow
// much more complex drawing than we currently support, such as imbedded
// words in different fonts.
struct Segment {
  const char* start;
  const char* end; // points after last character
  float x,y;
};

// The results are put into this array of segments. This may increase
// in size at any time:
static Segment* segments;
static int num_segments;

static float max_x;

// Create a new segment:
static /*inline*/ void set(int index,
		  const char* start,
		  const char* end,
		  float width,
		  float x, float y, float w,
		  Fl_Flags flags
		  )
{
  // enlarge the array if necessary:
  if (index >= num_segments) {
    num_segments = index ? 2*index : 32;
    Segment* new_array = new Segment[num_segments];
    memcpy(new_array, segments, index*sizeof(Segment));
    delete[] segments;
    segments = new_array;
  }
  Segment& s = segments[index];
  s.start = start;
  s.end = end;
  if (x+width > max_x) max_x = x+width;
  if (flags & FL_ALIGN_RIGHT) {
    s.x = x+w-width;
    if (flags & FL_ALIGN_LEFT && s.x > x) s.x = x;
  }
  else if (flags & FL_ALIGN_LEFT) s.x = x;
  else s.x = x+(w-width)/2;
  s.y = y+fl_height()-fl_descent();
}

// word-wrap a section of text into one segment per line:
// Returns the y of the last line
static float wrap(
  const char* start,
  const char* end,
  float x, float y, float w,
  Fl_Flags flags,
  int& index
  )
{
  float width = 0;
  if (flags & FL_ALIGN_WRAP) {
    const char* word_start = start;
    const char* word_end = start;
    for (const char* p = start; ; p++) {
      if (p >= end || *p == ' ') {
	// test for word-wrap:
	if (word_start < p) {
	  float newwidth = width + fl_width(word_end, p-word_end);
	  if (word_end > start && newwidth > w) { // break before this word
	    set(index++, start, word_end, width, x, y, w, flags);
	    y += fl_height();
	    start = word_end = p = word_start;
	    width = 0;
	    continue;
	  } else {
	    width = newwidth;
	    word_end = p;
	  }
	}
	word_start = p+1;
	if (p >= end) break;
      }
    }
  } else {
    width = fl_width(start, end-start);
  }
  if (start < end) set(index++, start, end, width, x, y, w, flags);
  return y;
}

bool fl_hide_shortcut; // set by Fl_Choice

// Parses and lays out the text into segments. Return value is the
// y height of the text. The width is stored in max_x. The index is
// set to be the number of segments.
static float split(
    const char* str,
    int W, int /*H*/,
    Fl_Flags flags,
    int& index,
    char* tempbuf // for the underscore stuff...
    )
{
  const int* column = fl_column_widths_;

  bool look_for_underscore = !(flags & FL_RAW_LABEL);
  bool saw_underscore = false;

  float x = 0;
  max_x = 0;
  float y = 0;
  float max_y = 0;
  const char* p = str;
  for (;;) {
    // find the next newline or tab:
    float w; // width to format this segment into
    if (!*p || *p == '\n') {
      w = W-x;
    } else if (*p == '\t') {
      if (column && *column) w = float(*column++);
      else w = ((p-str+8)&-8)*fl_width("2",1);
    } else {
      if (*p == '&' && look_for_underscore) saw_underscore = true;
      p++;
      continue;
    }
    float newy;
    // Edit out any '&' sign if this is reasonably short label and use
    // it's position later to underscore a letter. This is done by
    // copying the text to the tempbuf and then reusing that buffer
    // as the source for this text:
    if (saw_underscore && p-str < MAX_LENGTH_FOR_UNDERSCORE) {
      look_for_underscore = false;
      char* a = tempbuf;
      const char* b = str;
      const char* underscore_at = 0;
      while (b < p) {
	if (*b == '&' && b+1 < p) {
	  b++;
	  if (*b != '&' && !fl_hide_shortcut && !underscore_at)
	    underscore_at = a;
	}
	*a++ = *b++;
      }
      int i = index; // remember where it starts
      // create segments for the text:
      newy = wrap(tempbuf, a, x, y, w, flags, index);
      // add a segment to print the underscore:
      if (underscore_at) for (; i < index; i++) {
	Segment& s = segments[i];
	if (underscore_at >= s.start && underscore_at < s.end) {
	  const char* text = "_";
	  float save_y = s.y;
	  set(index, text, text+1, 0,
	      s.x+fl_width(s.start, underscore_at-s.start), y, 0,
	      FL_ALIGN_LEFT);
	  segments[index].y = save_y;
	  index++;
	  break;
	}
      }
    } else {
      newy = wrap(str, p, x, y, w, flags, index);
    }
    if (newy > max_y) max_y = newy;
    if (!*p) {
      return max_y+fl_height();
    } else if (*p == '\n') {
      x = 0; y = max_y+fl_height(); max_y = y; column = fl_column_widths_;
    } else { // tab
      x += w;
    }
    str = ++p;
  }
}

void fl_draw(
    const char* str,	// the (multi-line) string
    int X, int Y, int W, int H,	// bounding box
    Fl_Flags flags
) {
  if (!str || !*str) return;
  char tempbuf[MAX_LENGTH_FOR_UNDERSCORE];
  int index = 0;
  int h = int(split(str, W, H, flags, index, tempbuf)+.5);
  fl_transform(X,Y);
  int dy;
  if (flags & FL_ALIGN_BOTTOM) {
    dy = Y+H-h;
    if ((flags & FL_ALIGN_TOP) && dy > Y) dy = Y;
  } else if (flags & FL_ALIGN_TOP) {
    dy = Y;
  } else {
    dy = Y+((H-h)>>1);
  }
  for (int i = 0; i < index; i++) {
    Segment& s = segments[i];
    fl_transformed_draw(s.start, s.end-s.start, s.x+X, s.y+dy);
  }
}

void fl_draw(
             const Fl_String &str,	// the (multi-line) string
             int X, int Y, int W, int H,	// bounding box
             Fl_Flags flags
            )
{
    fl_draw(str.c_str(), X,Y,W,H, flags);
}

void fl_measure(const char* str, int& w, int& h, Fl_Flags flags)
{
    if (!str || !*str) {w = 0; h = int(fl_height()); return;}
    char tempbuf[MAX_LENGTH_FOR_UNDERSCORE];
    int index = 0;
    h = int(split(str, w, h, flags, index, tempbuf)+.5);
    w = int(max_x+.5);
}

void fl_measure(const Fl_String &str, int& w, int& h, Fl_Flags flags)
{
    fl_measure(str.c_str(), w, h, flags);
}

// back-compatable one:
//  void fl_measure(const char* str, int& w, int& h) {
//    fl_measure(str, w, h, w ? FL_ALIGN_WRAP : 0);
//  }

/*void Fl_Device::draw_Bitmap(Fl_Bitmap * im, int X, int Y, int W, int H, int cx, int cy)
{
	im->draw_screen(X, Y, W, H, cx, cy);
}

void Fl_Device::draw_Pixmap(Fl_Pixmap * im, int X, int Y, int W, int H, int cx, int cy)
{
	im->draw_screen(X, Y, W, H, cx, cy);
}

void Fl_Device::draw_RGB(Fl_RGB_Image * im, int X, int Y, int W, int H, int cx, int cy)
{
	im->draw_screen(X, Y, W, H, cx, cy);
}

void Fl_Bitmap::draw(int X, int Y, int W, int H, int cx, int cy)
{
	fl->draw_Bitmap(this, X, Y, W, H, cx, cy);
}

void Fl_Pixmap::draw(int X, int Y, int W, int H, int cx, int cy)
{
	fl->draw_Pixmap(this, X, Y, W, H, cx, cy);
}

void Fl_RGB_Image::draw(int X, int Y, int W, int H, int cx, int cy)
{
	fl->draw_RGB(this, X, Y, W, H, cx, cy);
}
*/


//
// End of "$Id$".
//
