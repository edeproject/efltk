//
// "$Id$"
//
// Fluid file routines for the Fast Light Tool Kit (FLTK).
//
// You may find the basic read_* and write_* routines to
// be useful for other programs.  I have used them many times.
// They are somewhat similar to tcl, using matching { and }
// to quote strings.
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
#include <efltk/fl_message.h>

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "alignment_panel.h"
#include "Fluid_Image.h"
#include "Fl_Type.h"

extern bool i18n;

////////////////////////////////////////////////////////////////
// BASIC FILE WRITING:

static FILE *fout;

int open_write(const char *s) 
{
	if (!s) { fout = stdout; return 1; }
	FILE *f = fopen(s,"w");
	if (!f) return 0;
	fout = f;
	return 1;
}

int close_write() 
{
	if (fout != stdout) {
		int x = fclose(fout);
		fout = stdout;
		return x >= 0;
	}
	return 1;
}

static int needspace;
int is_id(char); // in code.C

// write a string, quoting characters if necessary:
void write_word(const char *w) 
{
	if (needspace) putc(' ', fout);

	needspace = 1;
	if (!w || !*w) {
		fprintf(fout,"{}"); 
		return;
	}
	const char *p;
	
	// see if it is a single word:
	for (p = w; is_id(*p); p++) ;

	if (!*p) { fprintf(fout,"%s",w); return; }
  
	// see if there are matching braces:
	int n = 0;
	for (p = w; *p; p++) {
		if (*p == '{') n++;
		else if (*p == '}') { n--; if (n<0) break; }
	}
  
	int mismatched = (n != 0);
	// write out brace-quoted string:
	putc('{', fout);
	for (; *w; w++) {
		switch (*w) {
		case '{':
		case '}':
			if (!mismatched) break;
		
		case '\\':
		case '#':
			putc('\\',fout);
			break;
		}
		putc(*w,fout);
	}
	putc('}', fout);
}

// write an arbitrary formatted word, or a comment, etc:
void write_string(const char *format, ...) 
{
	va_list args;
	va_start(args, format);
	if (needspace) fputc(' ', fout);
	vfprintf(fout, format, args);
	va_end(args);
	needspace = !isspace(format[strlen(format)-1]);
}

// start a new line and indent it for a given nesting level:
void write_indent(int n) 
{
	fputc('\n',fout);
	while (n--) { fputc(' ',fout); fputc(' ',fout); }
	needspace = 0;
}

// write a '{' at the given indenting level:
void write_open(int) 
{
	if (needspace) fputc(' ',fout);
	fputc('{',fout);
	needspace = 0;
}

// write a '}' at the given indenting level:
void write_close(int n) 
{
	if (needspace) write_indent(n);
	fputc('}',fout);
	needspace = 1;
}

////////////////////////////////////////////////////////////////
// BASIC FILE READING:

static FILE *fin;
static int lineno;
static const char *fname;

int open_read(const char *s) {
  lineno = 1;
  if (!s) {fin = stdin; fname = "stdin"; return 1;}
  FILE *f = fopen(s,"r");
  if (!f) return 0;
  fin = f;
  fname = s;
  return 1;
}

int close_read() {
  if (fin != stdin) {
    int x = fclose(fin);
    fin = 0;
    return x >= 0;
  }
  return 1;
}

void read_error(const char *format, ...) 
{
  va_list args;
  va_start(args, format);
  //if (!fin) 
  {
    char buffer[1024];
    vsprintf(buffer, format, args);
    fl_message(buffer);
  } /*else {
    fprintf(stderr, "%s:%d: ", fname, lineno);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
  }*/
  va_end(args);
}

static int hexdigit(int x) {
  if (isdigit(x)) return x-'0';
  if (isupper(x)) return x-'A'+10;
  if (islower(x)) return x-'a'+10;
  return 20;
}


static int read_quoted() {	// read whatever character is after a \ .
  int c,d,x;
  switch(c = fgetc(fin)) {
  case '\n': lineno++; return -1;
  case 'a' : return('\a');
  case 'b' : return('\b');
  case 'f' : return('\f');
  case 'n' : return('\n');
  case 'r' : return('\r');
  case 't' : return('\t');
  case 'v' : return('\v');
  case 'x' :	/* read hex */
    for (c=x=0; x<3; x++) {
      int ch = fgetc(fin);
      d = hexdigit(ch);
      if (d > 15) {ungetc(ch,fin); break;}
      c = (c<<4)+d;
    }
    break;
  default:		/* read octal */
    if (c<'0' || c>'7') break;
    c -= '0';
    for (x=0; x<2; x++) {
      int ch = fgetc(fin);
      d = hexdigit(ch);
      if (d>7) {ungetc(ch,fin); break;}
      c = (c<<3)+d;
    }
    break;
  }
  return(c);
}

// return a word read from the file, or NULL at the EOF:
// This will skip all comments (# to end of line), and evaluate
// all \xxx sequences and use \ at the end of line to remove the newline.
// A word is any one of:
//	a continuous string of non-space chars except { and } and #
//	everything between matching {...} (unless wantbrace != 0)
//	the characters '{' and '}'

static Fl_String buffer;

Fl_String &read_word(int wantbrace) 
{
	buffer.clear();
	int x;
	
	// skip all the whitespace before it:
	for (;;) {
		x = getc(fin);
		if (x < 0) {	// eof
			return buffer;
		} else if (x == '#') {	// comment
			do x = getc(fin); while (x >= 0 && x != '\n');
			lineno++;
			continue;
		} else if (x == '\n') {
			lineno++;
		} else if (!isspace(x)) {
			break;
		}
	}
	
	if (x == '{' && !wantbrace) {
		
		// read in whatever is between braces
		int nesting = 0;
		for (;;) {
			x = getc(fin);
			if (x<0) {
				read_error("Missing '}'"); 
				break;
			}
			else if (x == '#') { // embedded comment
				do x = getc(fin); while (x >= 0 && x != '\n');
				lineno++;
				continue;
			} 
			else if (x == '\n') lineno++;
			else if (x == '\\') { x = read_quoted(); if (x<0) continue; }
			else if (x == '{') nesting++;
			else if (x == '}') { if (!nesting--) break; }
			buffer += (char)x;			
		}
		return buffer;
		
	} else if (x == '{' || x == '}') {
		// all the punctuation is a word:
		buffer += (char)x;
		return buffer;
		
	} else {
		
		// read in an unquoted word:
		for (;;) {
			if (x == '\\') { x = read_quoted(); if (x<0) continue; }
			else if (x<0 || isspace(x) || x=='{' || x=='}' || x=='#') break;
			buffer += (char)x;
			x = getc(fin);
		}
		ungetc(x, fin);
		return buffer;
		
	}
}

////////////////////////////////////////////////////////////////

// global int variables:
extern int gridx, gridy, snap;
static struct {const char* name; int* value;} inttable[] = {
  {"gridx", &gridx},
  {"gridy", &gridy},
  {"snap", &snap}
};


extern int header_file_set;
extern int code_file_set;
extern const char* header_file_name;
extern const char* code_file_name;
extern char* theme;

int write_file(const char *filename, int selected_only) {
  if (!open_write(filename)) return 0;
  write_string("# data file for the eFLTK User Interface Designer (eFLUID)\n"
	       "version %.4f",FL_VERSION);
  if(strlen(images_dir)) write_string("\nimages_dir %s", images_dir);
  if(!include_H_from_C)
      write_string("\ndo_not_include_H_from_C");
  if(i18n)
      write_string("\ni18n");
  if (!selected_only) {
    write_string("\nheader_name"); write_word(header_file_name);
    write_string("\ncode_name"); write_word(code_file_name);
    for (unsigned int i=0; i<sizeof(inttable)/sizeof(*inttable); i++)
      write_string("\n%s %d",inttable[i].name, *inttable[i].value);
  }
  if (theme && *theme) { write_string("\ntheme "); write_word(theme); }
  for (Fl_Type *p = Fl_Type::first; p;) {
    if (!selected_only || p->selected) {
      p->write();
      write_string("\n");
      p = p->next_brother;
    } else {
      p = p->walk();
    }
  }
  return close_write();
}

extern char *lc2(const char *v);

////////////////////////////////////////////////////////////////
// read all the objects out of the input file:

double read_version;

extern Fl_Type *Fl_Type_make(const char *tn);
extern void set_theme(const char* s);

extern int pasteoffset;

static void read_children(Fl_Type *p, int paste) 
{
	Fl_Type::current = p;
	for (;;) {
		unsigned int i;
		Fl_String &c = read_word();
REUSE_C:
		if(c.empty()) {
			if(p && !paste) read_error("Missing '}'");
			break;
		}

		if(c=="}") {
			if (!p) read_error("Unexpected '}'");
			break;
		}

		if(c=="version") {
			c = lc2(read_word());
			read_version = strtod(c,0);
			if(read_version<=0) read_error("unknown version '%s'", c.c_str());
			continue;
		}

		// back compatability with Vincent Penne's original class code:
		if (!p && c=="define_in_struct") {
			Fl_Type *t = Fl_Type_make("class");
			t->name(read_word());
			Fl_Type::current = p = t;
			paste = 1; // stops "missing }" error
			continue;
		}

		if(c=="do_not_include_H_from_C")
		{
			include_H_from_C=0;
			goto CONTINUE;
		} 
		else if(c=="i18n")
		{
			i18n=true;
			goto CONTINUE;
		} 
		else if(c=="images_dir")
		{
			images_dir = strdup(read_word()); // This will never get deleted ...
			goto CONTINUE;
		}
		else if(c=="header_name") {
			if (!header_file_set) header_file_name = strdup(read_word());
			else read_word();
			goto CONTINUE;
		}
		else if(c=="code_name") {
			if (!code_file_set) code_file_name = strdup(read_word());
			else read_word();
			goto CONTINUE;
		}
		else if(c=="theme" || c=="scheme") {
			set_theme(read_word());
			goto CONTINUE;
		}

		for (i=0; i<sizeof(inttable)/sizeof(*inttable); i++) {
			if(c==inttable[i].name) {
				c = read_word();
				*inttable[i].value = strtol(c,0,10);
				goto CONTINUE;
			}
		}

		{
			Fl_Type *t = Fl_Type_make(c);
			if (!t) {
				read_error("Unknown word \"%s\"", c);
				continue;
			}
			t->name(read_word());

			c = read_word(1);
			if(c!="{") {
				read_error("Missing property list for %s\n", t->title());
				goto REUSE_C;
			}

			t->open_ = 0;
			for (;;) {
				const Fl_String &c = read_word();
				if(c.empty() || c=="}") break;
				t->read_property(c);
			}

			if (!t->is_parent()) 
				continue;
			
			c = read_word(1);
			if(c!="{") {
				read_error("Missing child list for %s\n",t->title());
				goto REUSE_C;
			}
    
			// Start of ugly hack
			int saved_pasteoffset=pasteoffset;
			pasteoffset=0;
			read_children(t, 0);
			pasteoffset=saved_pasteoffset;
			// End of Ugly hack
		}
		Fl_Type::current = p;
CONTINUE: ;
	}
}

extern void deselect();

int read_file(const char *filename, int merge) {
  read_version = 0.0;
  if (!open_read(filename)) return 0;
  if (merge) deselect(); 
  else delete_all();
  read_children(Fl_Type::current, merge);
  Fl_Type::current = 0;
  for (Fl_Type *o = Fl_Type::first; o; o = o->walk())
    if (o->selected) {Fl_Type::current = o; break;}
  return close_read();
}

#include <efltk/Fl_String_List.h>
// For back compatabilty any lines that start with # are written at
// into the include header file:

#define isinclude(str) ((*(str) == '#') && (strstr((str), "include")!=NULL))
#define isextern(str)  (!strncmp((str), "extern", 6))
#define istypedef(str) (!strncmp((str), "typedef", 7))

// Test to see if extra code is a declaration:
static bool isdeclare(const char *c) {
	while (isspace(*c)) c++;
	if(isinclude(c))	return true;
	if(isextern(c))		return true;
	if(istypedef(c))	return true;
	return false;
}

void write_includes_from_code(const Fl_String &pBlock)
{
	Fl_String_List lines(pBlock, "\n");
	for(unsigned n=0; n<lines.size(); n++) {
		if (isinclude(lines[n].c_str())) 
			write_declare("%s", lines[n].c_str());
	}
}

void write_externs_from_code(const Fl_String &pBlock)
{
	Fl_String_List lines(pBlock, "\n");
	for(unsigned n=0; n<lines.size(); n++) {
		if (isextern(lines[n].c_str())) 
			write_declare("%s", lines[n].c_str());
	}
}

void write_typedefs_from_code(const Fl_String &pBlock)
{
	Fl_String_List lines(pBlock, "\n");
	for(unsigned n=0; n<lines.size(); n++) {
		if (istypedef(lines[n].c_str())) 
			write_declare("%s", lines[n].c_str());
	}
}

// And the code is written out with all the # lines removed:
void write_code_block(const Fl_String &pBlock)
{
	Fl_String_List lines(pBlock, "\n");
	for(unsigned n=0; n<lines.size(); n++) {
		if (!isdeclare(lines[n])) 
			write_c("%s%s\n", indent(), lines[n].c_str());
	}
}

//
// End of "$Id$".
//
