#ifndef _FL_UTILS_H
#define _FL_UTILS_H

#include "Enumerations.h"
#include "Fl_Flags.h"

#define FL_DIR	  (1<<1) //Directory
#define FL_FILE   (1<<2) //Regular file
#define FL_LINK   (1<<3) //Sym link (ignored on WIN32)
#define FL_DEVICE (1<<4) //Logical disk (ignored on Linux)

class Fl_FileAttr
{
public:
	Fl_FileAttr() { size=0; flags=0; }
	bool parse(const char *filename);
	
	ulong size; // size of file
	ulong modified; // time modified
	char time[128]; // time modified str
	Fl_Flags flags; // type flags

#ifdef _WIN32
	uint64 free; //Free space
	uint64 capacity; //total capacity space
#endif
};

// return pointer to .ext or NULL if no extension
FL_API const char *fl_file_getext(const char *);

// clobber .ext
FL_API char *fl_file_setext(char *,const char *ext);

// return pointer to name
FL_API const char *fl_file_filename(const char *);

// convert $x and ~x
FL_API bool fl_file_expand(char *buf, const char *from);

// prepend getcwd()
FL_API bool fl_file_absolute(char *buf, const char *from);
FL_API bool fl_file_match(const char *, const char *pattern); // glob match

// Returns homepath in WIN32 and Linux
extern FL_API char *fl_get_homedir();

extern FL_API Fl_FileAttr *fl_file_attr(const char *name);

extern FL_API bool fl_file_exists(const char *name);

// Get file array from given dir
extern FL_API char **fl_get_files(char *path, int *files_count=0);

// Check if given name is dir
extern FL_API bool fl_is_dir(const char *path);

// removes leading spaces
extern FL_API char *fl_trimleft(char *string);

// removes trailing spaces
extern FL_API char *fl_trimright(char *string);

// Removes trailing and leading spaces
#define fl_trim(string) fl_trimright(fl_trimleft(string))

extern FL_API char *fl_tolower(char *string);
extern FL_API char *fl_toupper(char *string);

extern FL_API char *fl_strdup_printf(char *s1, ...);

extern FL_API char** fl_split(const char *string, const char *delimiter, int max_tokens);

extern FL_API int fl_start_child_process(char *cmd);

extern FL_API void fl_freev (char **str_array);

extern FL_API const char *fl_cut_line(const char *str, int maxwidth);
extern FL_API const char *fl_cut_multiline(const char *str, int maxwidth);

class FL_API Fl_Point
{
	int x_, y_;
public:
	Fl_Point() : x_(0), y_(0) {}
	Fl_Point(int x, int y) : x_(x), y_(y) {}
	int x() { return x_; }
	int y() { return y_; }
	void x(int x) { x_ = x; }
	void y(int y) { y_ = y; }
};

class FL_API Fl_Size
{
	int width_, height_;
public:
	Fl_Size() : width_(0), height_(0) {}
	Fl_Size(int w, int h) : width_(w), height_(h) {}
	
	int width() { return width_; }
	int w() { return width_; }
	
	int h() { return height_; }	
	int height() { return height_; }
	
	void width(int w) { width_ = w; }
	void height(int h) { height_ = h; }
};

class FL_API Fl_Rect
{
	int x_, y_, width_, height_;
public:
	Fl_Rect() : x_(0), y_(0), width_(0), height_(0) {}
	Fl_Rect(int x, int y, int w, int h) : x_(x), y_(y), width_(w), height_(h) {}
	inline bool posInRect(int xs, int ys)
	{ 	
		if( xs > x_  && xs < (x_ + width_) &&
	    ys > y_  && ys < (y_ + height_) )
		{
			return true;
		}
		return false;
 	}
	inline bool posInRect(Fl_Point p)
	{ 	
		if( p.x() > x_  && p.x() < (x_ + width_) &&
	    p.y() > y_  && p.y() < (y_ + height_) )
		{
			return true;
		}
		return false;
 	}
	int x() { return x_; }
	int y() { return y_; }
	
	int w() { return width(); }
	int width() { return width_; }
	
	int h() { return height(); }
	int height() { return height_; }	

        int left() { return x(); }
        int right() { return x()+w(); }
        int top() { return y(); }
        int bottom() { return y()+h(); }

	void x(int x) { x_ = x; }
	void y(int y) { y_ = y; }
	void w(int w) { width_ = w; }
	void h(int h) { height_ = h; }

	void set(int x, int y, int w, int h) { x_=x; y_=y; width_=w; height_=h; }
};

#endif
