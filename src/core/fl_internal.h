#ifndef FL_INTERNAL_H_
#define FL_INTERNAL_H_

#include <config.h>

#include <efltk/Fl_Color.h>

// Internal define file for EFLTK
// include ONLY from source files!

////////////////////////////////////////
// NLS

#include <locale.h>

#if !ENABLE_NLS
# define _(String) (String)
#else
#include <efltk/Fl_Translator.h>
# define _(String) Fl_Translator::dtr("efltk", String)
#endif
#define N_(String) (String)

//////////////////////////////////
// DUFFS LOOPING

/* This is a very useful loop for optimizing blitters */
#if USE_DUFFS_LOOP

/* 8-times unrolled loop */
#define DUFFS_LOOP8(pixel_copy_increment, width)			\
{ int n = (width+7)/8;							\
	switch (width & 7) {						\
	case 0: do {	pixel_copy_increment;				\
	case 7:		pixel_copy_increment;				\
	case 6:		pixel_copy_increment;				\
	case 5:		pixel_copy_increment;				\
	case 4:		pixel_copy_increment;				\
	case 3:		pixel_copy_increment;				\
	case 2:		pixel_copy_increment;				\
	case 1:		pixel_copy_increment;				\
		} while ( --n > 0 );					\
	}								\
}

/* 4-times unrolled loop */
#define DUFFS_LOOP4(pixel_copy_increment, width)			\
{ int n = (width+3)/4;							\
	switch (width & 3) {						\
	case 0: do {	pixel_copy_increment;				\
	case 3:		pixel_copy_increment;				\
	case 2:		pixel_copy_increment;				\
	case 1:		pixel_copy_increment;				\
		} while ( --n > 0 );					\
	}								\
}

/* Use the 8-times version of the loop by default */
#define DUFFS_LOOP(pixel_copy_increment, width)				\
	DUFFS_LOOP8(pixel_copy_increment, width)

#else

/* Don't use Duff's device to unroll loops */
#define DUFFS_LOOP(pixel_copy_increment, width)				\
{ int n;								\
  for ( n=width; n > 0; --n ) {					\
    pixel_copy_increment;					\
  }								\
}
#define DUFFS_LOOP8(pixel_copy_increment, width)			\
	DUFFS_LOOP(pixel_copy_increment, width)
#define DUFFS_LOOP4(pixel_copy_increment, width)			\
	DUFFS_LOOP(pixel_copy_increment, width)

#endif /* USE_DUFFS_LOOP */


////////////////////////////////////////////
// ERROR DIFFUSION

#ifdef _WIN32

#define fl_xpixel(x) (x)

#endif /* _WIN32 */

#if defined(NO_ERROR_DIFFUSION) || !USE_COLORMAP

#define ERROR_DIFF_START()
#define ERROR_DIFF(R,G,B, DST) DST = srcfmt->table[((R>>5)<<(3+2)) | ((G>>5)<<(2)) | ((B>>6)<<(0))]
#define ERROR_DIFF_END()

#else

#define ERROR_DIFF_START() static int ri=0, gi=0, bi=0; int r=ri, g=gi, b=bi
#define ERROR_DIFF_END() ri = r; gi = g; bi = b

#ifdef _WIN32
// Error diffusion code from FLTK2 by Bill Spitzak and others...

#define ERROR_DIFF(R,G,B, DST) { \
    r += R; if (r < 0) r = 0; else if (r>255) r = 255; \
    int rr = r*FL_NUM_RED/256; \
    r -= rr*255/(FL_NUM_RED-1); \
    g += G; if (g < 0) g = 0; else if (g>255) g = 255; \
    int gg = g*FL_NUM_GREEN/256; \
    g -= gg*255/(FL_NUM_GREEN-1); \
    b += B; if (b < 0) b = 0; else if (b>255) b = 255; \
    int bb = b*FL_NUM_BLUE/256; \
    b -= bb*255/(FL_NUM_BLUE-1); \
    DST = uchar(FL_COLOR_CUBE+(bb*FL_NUM_RED+rr)*FL_NUM_GREEN+gg); \
}

#else

struct Fl_XColor {
    unsigned char r,g,b;	// actual color used by X
    unsigned char mapped;	// true when XAllocColor done
    unsigned long pixel;	// the X pixel to use
};
extern Fl_XColor fl_xmap[256];
extern void fl_allocate_xpixel(Fl_XColor& xmap, uchar r, uchar g, uchar b);

#define ERROR_DIFF(R,G,B, DST) { \
    r += R; if (r < 0) r = 0; else if (r>255) r = 255; \
    g += G; if (g < 0) g = 0; else if (g>255) g = 255; \
    b += B; if (b < 0) b = 0; else if (b>255) b = 255; \
    Fl_Color i = fl_color_cube(r*FL_NUM_RED/256,g*FL_NUM_GREEN/256,b*FL_NUM_BLUE/256); \
    Fl_XColor& xmap = fl_xmap[i]; \
    if (!xmap.mapped) fl_allocate_xpixel(xmap,r,g,b); \
    r -= xmap.r; \
    g -= xmap.g; \
    b -= xmap.b; \
    DST = uchar(xmap.pixel); \
}

#endif //_WIN32

#endif //defined(NO_ERROR_DIFFUSION) || !USE_COLORMAP

#include <string.h>
#include <stdio.h>

// Used by image reader/writers
// And XML
class Fl_IO
{
public:
    Fl_IO() { fp=0; buf=0; buf_size=buf_offset=0; }
    Fl_IO(FILE *f) { init_io(f,0,0); }
    Fl_IO(uint8 *b, uint32 size) { init_io(0, b, size); }

    void init_io(FILE *file_fp, uint8 *buffer, uint32 buffer_size) {
        fp = file_fp;
        buf = buffer;
        buf_size = buffer_size;
        buf_offset=0;
    }

    uint read(void *b, int len) {
        if(fp) {
            return fread(b, 1, len, fp);
        } else if(buf && buf_size>0) {
            uint32 pos = buf_offset+len;
            if(pos>buf_size) len = len-(pos-buf_size);
            if(len>0) {
                memcpy(b, buf+buf_offset, len);
                buf_offset+=len;
                return len;
            }
        }
        return 0;
    }
    uint write(void *b, int len) {
        if(fp) {
            return fwrite(b, 1, len, fp);
        } else if(buf && buf_size>0) {
            uint32 pos = buf_offset+len;
            if(pos>buf_size) len = len-(pos-buf_size);
            if(len>0) {
                memcpy(buf+buf_offset, b, len);
                buf_offset+=len;
                return len;
            }
        }
        return 0;
    }
    uint seek(uint pos) {
        if(fp) {
            return fseek(fp, pos, SEEK_SET);
        } else if(buf) {
            if(pos>buf_size) pos = buf_size;
            buf_offset = pos;
            return pos;
        }
        return 0;
    }
    uint tell() {
        if(fp) {
            return ftell(fp);
        } else if(buf) {
            return buf_offset;
        }
        return 0;
    }
    bool eos() {
        if(fp) return feof(fp)!=0;
        else if(buf) return buf_offset>=buf_size;
        return true;
    }

    FILE *fp;
    uint8 *buf;
    uint32 buf_size;
    uint32 buf_offset;
};

/////////////////////////////////////////////////

#ifdef _WIN32

#include <windows.h>
#include <efltk/Fl_Point.h>
#include <efltk/Fl_Int_List.h>
class Fl_Line_Drawer
{
public:
	Fl_Line_Drawer() { cur_pat = cur_stretch = 0; }
	~Fl_Line_Drawer() { }

	// Set linestyle pattern 
	void set_pattern(int size, DWORD *dash_pattern, int dash_count);

	// MoveToEx replacement
	void move(int x, int y);

	// LineTo replacement
	void line(int x, int y);

private:
	void reset();
	
	void bresenham_line(int to_x, int to_y);
	void h_line(int to_x, int direction);
	void v_line(int to_y, int direction);

	Fl_Int_List patterns;

	int	cur_pat;
	int	cur_stretch;	
	POINT cur_pos;
};

extern FL_API Fl_Line_Drawer fl_line_drawer;

#endif /* _WIN32 */

#endif
