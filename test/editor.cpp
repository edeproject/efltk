//
// "$Id$"
//
// A simple text editor program for the Fast Light Tool Kit (FLTK).
//
// This program is described in Chapter 4 of the FLTK Programmer's Guide.
//
// Copyright 1998-2002 by Bill Spitzak and others.
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

//
// Include necessary headers...
//

#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include <efltk/Fl.h>
#include <efltk/Fl_Color.h>
#include <efltk/Fl_Group.h>
#include <efltk/Fl_Pack.h>
#include <efltk/Fl_Double_Window.h>
#include <efltk/fl_ask.h>
#include <efltk/Fl_File_Dialog.h>
#include <efltk/Fl_Menu_Bar.h>
#include <efltk/Fl_Input.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Return_Button.h>
#include <efltk/Fl_Text_Buffer.h>
#include <efltk/Fl_Text_Editor.h>

int                changed = 0;
char               filename[256] = "";
char               title[256];
Fl_Text_Buffer     *textbuf = 0;

#define STYLES 1

#if STYLES

#define UNFINISHED 'A'
#define PLAIN 'B'

// Syntax highlighting stuff...
Fl_Text_Buffer     *stylebuf = 0;
Fl_Text_Display::Style_Table_Entry
    styletable[] = {	// Style table
        { FL_BLACK, FL_COURIER,        12 }, // A - Unfinished
        { FL_BLACK, FL_COURIER,        12 }, // B - Plain
        { FL_DARK3, FL_COURIER_ITALIC, 12 }, // C - Line comments
        { FL_DARK3, FL_COURIER_ITALIC, 12 }, // D - Block comments
        { fl_color_average(FL_BLACK, FL_YELLOW, 0.5), FL_COURIER,   12 }, // E - Strings
        { fl_color_average(FL_BLACK, FL_GREEN, 0.5),  FL_COURIER,   12 }, // F - Directives
        { fl_color_average(FL_BLACK, FL_RED, 0.5),    FL_COURIER,   12 }, // G - Types
        { fl_color_average(FL_BLACK, FL_BLUE, 0.5),   FL_COURIER,   12 }  // H - Keywords
    };

const char *code_keywords[] = {	// List of known C/C++ keywords...
    "and",
    "and_eq",
    "asm",
    "bitand",
    "bitor",
    "break",
    "case",
    "catch",
    "compl",
    "continue",
    "default",
    "delete",
    "do",
    "else",
    "false",
    "for",
    "goto",
    "if",
    "new",
    "not",
    "not_eq",
    "operator",
    "or",
    "or_eq",
    "return",
    "switch",
    "template",
    "this",
    "throw",
    "true",
    "try",
    "while",
    "xor",
    "xor_eq"
};

const char *code_types[] = {	// List of known C/C++ types...
    "auto",
    "bool",
    "char",
    "class",
    "const",
    "const_cast",
    "double",
    "dynamic_cast",
    "enum",
    "explicit",
    "extern",
    "float",
    "friend",
    "inline",
    "int",
    "long",
    "mutable",
    "namespace",
    "private",
    "protected",
    "public",
    "register",
    "short",
    "signed",
    "sizeof",
    "static",
    "static_cast",
    "struct",
    "template",
    "typedef",
    "typename",
    "union",
    "unsigned",
    "virtual",
    "void",
    "volatile"
};


//
// 'compare_keywords()' - Compare two keywords...
//

int
compare_keywords(const void *a,
                 const void *b) {
    return (strcmp(*((const char **)a), *((const char **)b)));
}


//
// 'style_parse()' - Parse text and produce style data.
//

void style_parse(const char *text,
                 char *style,
                 int length)
{
    char current;
    int  col;
    int  last;
    char buf[255];
    char *bufptr;
    const char *temp;
    int pos=0;

    for(current = *style, col = 0, last = 0; length > 0; length --, text ++)
    {
        if(current == PLAIN || current == UNFINISHED || col==0)
        {
            // Check for directives, comments, strings, and keywords...
            if (col == 0 && *text == '#') {
                // Set style to directive
                current = 'F';
            } else if (strncmp(text, "//", 2) == 0) {
                current = 'C';
            } else if (strncmp(text, "/*", 2) == 0) {
                current = 'D';
            } else if (strncmp(text, "\\\"", 2) == 0) {
                // Quoted quote...
                *style++ = current;
                *style++ = current;
                text ++;
                length --;
                col += 2;
                pos+=2;
                continue;
            } else if (*text == '\"') {
                current = 'E';
            } else if (!last && islower(*text) && current!='D' && current!='E') {
                // Might be a keyword...
                for (temp = text, bufptr = buf;
                     islower(*temp) && bufptr < (buf + sizeof(buf) - 1);
                     *bufptr++ = *temp++);

                if (!islower(*temp)) {
                    *bufptr = '\0';
                    bufptr = buf;

                    if (bsearch(&bufptr, code_types,
                                sizeof(code_types) / sizeof(code_types[0]),
                                sizeof(code_types[0]), compare_keywords)) {
                        while (text < temp) {
                            *style++ = 'G';
                            text ++;
                            length --;
                            col ++;
                            pos++;
                        }

                        text --;
                        length ++;
                        last = 1;
                        current=PLAIN;
                        continue;
                    } else if (bsearch(&bufptr, code_keywords,
                                       sizeof(code_keywords) / sizeof(code_keywords[0]),
                                       sizeof(code_keywords[0]), compare_keywords)) {
                        while (text < temp) {
                            *style++ = 'H';
                            text ++;
                            length --;
                            col ++;
                            pos++;
                        }

                        text --;
                        length ++;
                        last = 1;
                        current=PLAIN;
                        continue;
                    } else
                        current=PLAIN;
                }
            } else if(*text=='(') {

		// Might be a function name...
                bufptr = (char*)text-1;
                char *sptr = style;
                int tmp=col, len=0;;
                while(tmp-->=0) {
                    if(*bufptr==' '||*bufptr=='\n'||*bufptr=='\t'||
                       *bufptr=='.'||*bufptr=='>'||*bufptr==':'||
                       *bufptr=='('||*bufptr==')'||*bufptr=='?'||
                       *bufptr=='='||*bufptr=='!') break;
                    bufptr--;
                    len++;
                }
                bufptr++;
                strncpy(buf, bufptr, len);                
                buf[len] = '\0';
                bufptr = buf;

                if(!bsearch(&bufptr, code_types,
                            sizeof(code_types) / sizeof(code_types[0]),
                            sizeof(code_types[0]), compare_keywords)
                   &&
                   !bsearch(&bufptr, code_keywords,
                            sizeof(code_keywords) / sizeof(code_keywords[0]),
                            sizeof(code_keywords[0]), compare_keywords)
                  ) {
		    //It's not keyword or keycode
		    //So it has to then function
                    while(len-->=0) {
                        *sptr-- = 'F';
                    }
                }
            }
            else
                if(current!='E' && current!='D') current=PLAIN;

        } else if (current == 'E') {
            // Continuing in string...
            if (strncmp(text, "\\\"", 2) == 0) {
                // Quoted end quote...
                *style++ = current;
                *style++ = current;
                text ++;
                length --;
                col += 2;
                pos+=2;
                continue;
            } else if (*text == '\"') {
                // End quote...
                *style++ = current;
                col ++;
                pos++;
                current = PLAIN;
                continue;
            }
        }

        if (current == 'D' && strncmp(text, "*/", 2) == 0) {
            // Close a C comment...
            *style++ = current;
            *style++ = current;
            text ++;
            length --;
            current = PLAIN;
            col += 2;
            pos+=2;
            continue;
        }

        // Copy style info...
        if ((current == PLAIN||current == UNFINISHED) && (*text == '{' || *text == '}')) *style++ = 'H';
        else *style++ = current;

        col++;
        pos++;

        last = isalnum(*text) || *text == '.';

        if (*text == '\n') {
            // Reset column and possibly reset the style
            col = 0;
            if (current == 'C' || current == 'F') current = PLAIN;
        }
    }
}


//
// 'style_init()' - Initialize the style buffer...
//

void style_init(void) {
    char *style = new char[textbuf->length() + 1];
    char *text = (char *)textbuf->text();

    memset(style, UNFINISHED, textbuf->length());
    style[textbuf->length()] = '\0';

    if(!stylebuf) stylebuf = new Fl_Text_Buffer(textbuf->length());

    style_parse(text, style, textbuf->length());

    stylebuf->text(style);
    delete[] style;
    free(text);
}


//
// 'style_unfinished_cb()' - Update unfinished styles.
//
void style_unfinished_cb(Fl_Text_Display *, int, void *) {
}

//
// 'find_safe_pos()' - Finds safe re-parse point
//
int find_safe_pos(Fl_Text_Buffer *buf, int pos, int inc) {
    int p = pos;
    char *buffer = buf->static_buffer();
    char *ptr=0;
    while(p+=inc) {
        if(p<0) break;
        if(p>buf->length()) break;
        ptr = buffer+p;
        if(!strncmp(ptr, "/*", 2) ||
           !strncmp(ptr, "*/", 2) ||
           !strncmp(ptr, "#include", 8) ||
           !strncmp(ptr, "#if", 3) ||
           *ptr=='{' || *ptr=='}'
          ) {
            p+=inc;
            break;
        }
    }
    return p;
}

//
// 'style_update()' - Update the style buffer...
//
void
style_update(int        pos,		// I - Position of update
             int        nInserted,	// I - Number of inserted chars
             int        nDeleted,	// I - Number of deleted chars
             int        /*nRestyled*/,	// I - Number of restyled chars
             const char * /*deletedText*/,	// I - Text that was deleted
             void       *cbArg) {	// I - Callback data

    int	start,				// Start of text
    end;				// End of text
    char last,				// Last style on line
        *style,				// Style data
        *text;				// Text data

    // If this is just a selection change, just unselect the style buffer...
    if (nInserted == 0 && nDeleted == 0) {
        stylebuf->unselect();
        return;
    }

    // Track changes in the text buffer...
    if (nInserted > 0) {
        // Insert characters into the style buffer...
        style = new char[nInserted + 1];
        memset(style, UNFINISHED, nInserted);
        style[nInserted] = '\0';

        stylebuf->replace(pos, pos + nDeleted, style);
        delete[] style;
    } else {
        // Just delete characters in the style buffer...
        stylebuf->remove(pos, pos + nDeleted);
    }

    // Select the area that was just updated to avoid unnecessary
    // callbacks...
    stylebuf->select(pos, pos + nInserted - nDeleted);

    // Re-parse the changed region; we do this by parsing from the
    // beginning of the line of the changed region to the end of
    // the line of the changed region...  Then we check the last
    // style character and keep updating if we have a multi-line
    // comment character...

    // Try to find last SAFE parsing point.
    int p=0;
    if (nDeleted > 0 && nInserted==0) {
        p = find_safe_pos(textbuf, pos, 1);
        p=p<textbuf->length()?p:textbuf->length();
        start = textbuf->line_start(pos);
        end   = textbuf->line_end(p + nDeleted);
    } else {
        p = find_safe_pos(textbuf, pos, -1);
        p=p>=0?p:0;
        start = textbuf->line_start(p);
        end   = textbuf->line_end(pos + nInserted - nDeleted);
    }

    text  = (char *)textbuf->text_range(start, end);
    style = (char *)stylebuf->text_range(start, end);
    last  = style[end - start - 1];
    style_parse(text, style, end - start);

    if (last != style[end - start - 1])
    {
        // The last character on the line changed styles, so reparse the
        // remainder of the buffer...
        free(text);
        free(style);

        end   = textbuf->length();
        text  = (char *)textbuf->text_range(start, end);
        style = (char *)stylebuf->text_range(start, end);
        style_parse(text, style, end - start);
        stylebuf->replace(start, end, style);

    } else
        stylebuf->replace(start, end, style);

    ((Fl_Text_Editor *)cbArg)->redisplay_range(start, end);
    free(text);
    free(style);
}
#endif

// Editor window functions and class...
void save_cb();
void saveas_cb();
void find2_cb(Fl_Widget*, void*);
void replall_cb(Fl_Widget*, void*);
void replace2_cb(Fl_Widget*, void*);
void replcan_cb(Fl_Widget*, void*);

class EditorWindow : public Fl_Window {
public:
    EditorWindow(int w, int h, const char* t);
    ~EditorWindow();

    Fl_Window          *replace_dlg;
    Fl_Input           *replace_find;
    Fl_Input           *replace_with;
    Fl_Button          *replace_all;
    Fl_Return_Button   *replace_next;
    Fl_Button          *replace_cancel;

    Fl_Text_Editor     *editor;
    char               search[256];
};

EditorWindow::EditorWindow(int w, int h, const char* t) : Fl_Window(w, h, t) {
  replace_dlg = new Fl_Window(300, 105, "Replace");
    replace_find = new Fl_Input(80, 10, 210, 25, "Find:");
    replace_find->align(FL_ALIGN_LEFT);

    replace_with = new Fl_Input(80, 40, 210, 25, "Replace:");
    replace_with->align(FL_ALIGN_LEFT);

    replace_all = new Fl_Button(10, 70, 90, 25, "Replace All");
    replace_all->callback((Fl_Callback *)replall_cb, this);

    replace_next = new Fl_Return_Button(105, 70, 120, 25, "Replace Next");
    replace_next->callback((Fl_Callback *)replace2_cb, this);

    replace_cancel = new Fl_Button(230, 70, 60, 25, "Cancel");
    replace_cancel->callback((Fl_Callback *)replcan_cb, this);
  replace_dlg->end();
  replace_dlg->set_non_modal();
  editor = 0;
  *search = (char)0;
}

EditorWindow::~EditorWindow() {
  delete replace_dlg;
}

int check_save(void) {
  if (!changed) return 1;

  int r = fl_choice("The current file has not been saved.\n"
                    "Would you like to save it now?",
                    "Cancel", "Save", "Discard");

  if (r == 1) {
    save_cb(); // Save the file...
    return !changed;
  }

  return (r == 2) ? 1 : 0;
}

int loading = 0;
void load_file(char *newfile, int ipos)
{	
    loading = 1;
    int insert = (ipos != -1);
    changed = insert;	
    if (!insert) strcpy(filename, "");
    int r;	
    if (!insert) r = textbuf->loadfile(newfile);
    else r = textbuf->insertfile(newfile, ipos);
    if (r)
        fl_alert("Error reading from file \'%s\':\n%s.", newfile, strerror(errno));
    else
        if (!insert) strcpy(filename, newfile);
    loading = 0;
    textbuf->call_modify_callbacks();	
}

void save_file(char *newfile) {
  if (textbuf->savefile(newfile))
    fl_alert("Error writing to file \'%s\':\n%s.", newfile, strerror(errno));
  else
    strcpy(filename, newfile);
  changed = 0;
  textbuf->call_modify_callbacks();
}

void copy_cb(Fl_Widget*, void* v) {
  EditorWindow* e = (EditorWindow*)v;
  Fl_Text_Editor::kf_copy(0, e->editor);
}

void cut_cb(Fl_Widget*, void* v) {
  EditorWindow* e = (EditorWindow*)v;
  Fl_Text_Editor::kf_cut(0, e->editor);
}

void delete_cb(Fl_Widget*, void*) {
  textbuf->remove_selection();
}

void find_cb(Fl_Widget* w, void* v) {
  EditorWindow* e = (EditorWindow*)v;
  const char *val;

  val = fl_input("Search String:", e->search);
  if (val != NULL) {
    // User entered a string - go find it!
    strcpy(e->search, val);
    find2_cb(w, v);
  }
}

void find2_cb(Fl_Widget* w, void* v) {
  EditorWindow* e = (EditorWindow*)v;
  if (e->search[0] == '\0') {
    // Search string is blank; get a new one...
    find_cb(w, v);
    return;
  }

  int pos = e->editor->insert_position();
  int found = textbuf->search_forward(pos, e->search, &pos);
  if (found) {
    // Found a match; select and update the position...
    textbuf->select(pos, pos+strlen(e->search));
    e->editor->insert_position(pos+strlen(e->search));
    e->editor->show_insert_position();
  }
  else fl_alert("No occurrences of \'%s\' found!", e->search);
}

void set_title(Fl_Window* w) {
  if (filename[0] == '\0') strcpy(title, "Untitled");
  else {
    char *slash_;
    slash_ = strrchr(filename, '/');
#ifdef WIN32
    if (slash_ == NULL) slash_ = strrchr(filename, '\\');
#endif
    if (slash_ != NULL) strcpy(title, slash_ + 1);
    else strcpy(title, filename);
  }

  if (changed) strcat(title, " (modified)");

  w->label(title);
}

void changed_cb(int, int nInserted, int nDeleted,int, const char*, void* v) {
  if ((nInserted || nDeleted) && !loading) changed = 1;
  EditorWindow *w = (EditorWindow *)v;
  set_title(w);
  if (loading) w->editor->show_insert_position();
}

void new_cb(Fl_Widget*, void*) {
  if (!check_save()) return;

  filename[0] = '\0';
  textbuf->select(0, textbuf->length());
  textbuf->remove_selection();
  changed = 0;
  textbuf->call_modify_callbacks();
}

void open_cb(Fl_Widget*, void*) {
  if (!check_save()) return;

  char *newfile = fl_select_file(filename, 0, "Open File?");
  if (newfile != NULL) load_file(newfile, -1);
}

void insert_cb(Fl_Widget*, void *v) {
  char *newfile = fl_select_file(filename, 0, "Insert File?");
  EditorWindow *w = (EditorWindow *)v;
  if (newfile != NULL) load_file(newfile, w->editor->insert_position());
}

void paste_cb(Fl_Widget*, void* v) {
  EditorWindow* e = (EditorWindow*)v;
  Fl_Text_Editor::kf_paste(0, e->editor);
}

int num_windows = 0;

void close_cb(Fl_Widget*, void* v) {
  Fl_Window* w = (Fl_Window*)v;
  if (num_windows == 1 && !check_save()) {
    return;
  }

  w->hide();
  textbuf->remove_modify_callback(changed_cb, w);
  delete w;
  num_windows--;
  if (!num_windows) exit(0);
}

void quit_cb(Fl_Widget*, void*) {
  if (changed && !check_save())
    return;

  exit(0);
}

void replace_cb(Fl_Widget*, void* v) {
  EditorWindow* e = (EditorWindow*)v;
  e->replace_dlg->show();
}

void replace2_cb(Fl_Widget*, void* v) {
  EditorWindow* e = (EditorWindow*)v;
  const char *find = e->replace_find->value();
  const char *replace = e->replace_with->value();

  if (find[0] == '\0') {
    // Search string is blank; get a new one...
    e->replace_dlg->show();
    return;
  }

  e->replace_dlg->hide();

  int pos = e->editor->insert_position();
  int found = textbuf->search_forward(pos, find, &pos);

  if (found) {
    // Found a match; update the position and replace text...
    textbuf->select(pos, pos+strlen(find));
    textbuf->remove_selection();
    textbuf->insert(pos, replace);
    textbuf->select(pos, pos+strlen(replace));
    e->editor->insert_position(pos+strlen(replace));
    e->editor->show_insert_position();
  }
  else fl_alert("No occurrences of \'%s\' found!", find);
}

void replall_cb(Fl_Widget*, void* v) {
  EditorWindow* e = (EditorWindow*)v;
  const char *find = e->replace_find->value();
  const char *replace = e->replace_with->value();

  find = e->replace_find->value();
  if (find[0] == '\0') {
    // Search string is blank; get a new one...
    e->replace_dlg->show();
    return;
  }

  e->replace_dlg->hide();

  e->editor->insert_position(0);
  int times = 0;

  // Loop through the whole string
  for (int found = 1; found;) {
    int pos = e->editor->insert_position();
    found = textbuf->search_forward(pos, find, &pos);

    if (found) {
      // Found a match; update the position and replace text...
      textbuf->select(pos, pos+strlen(find));
      textbuf->remove_selection();
      textbuf->insert(pos, replace);
      e->editor->insert_position(pos+strlen(replace));
      e->editor->show_insert_position();
      times++;
    }
  }

  if (times) fl_message("Replaced %d occurrences.", times);
  else fl_alert("No occurrences of \'%s\' found!", find);
}

void replcan_cb(Fl_Widget*, void* v) {
  EditorWindow* e = (EditorWindow*)v;
  e->replace_dlg->hide();
}

void save_cb() {
  if (filename[0] == '\0') {
    // No filename - get one!
    saveas_cb();
    return;
  }
  else save_file(filename);
}

void saveas_cb() {
  char *newfile = fl_save_file(filename, 0, "Save File?");
  if (newfile != NULL) save_file(newfile);
}

Fl_Window* new_view();

void view_cb(Fl_Widget*, void*) {
  Fl_Window* w = new_view();
  w->show();
}

Fl_Menu_Item menuitems[] = {
  { "&File",              0, 0, 0, FL_SUBMENU },
    { "&New File",        0, (Fl_Callback *)new_cb },
    { "&Open File...",    FL_CTRL + 'o', (Fl_Callback *)open_cb },
    { "&Insert File...",  FL_CTRL + 'i', (Fl_Callback *)insert_cb, 0, FL_MENU_DIVIDER },
    { "&Save File",       FL_CTRL + 's', (Fl_Callback *)save_cb },
    { "Save File &As...", FL_CTRL + FL_SHIFT + 's', (Fl_Callback *)saveas_cb, 0, FL_MENU_DIVIDER },
    { "New &View", FL_ALT + 'v', (Fl_Callback *)view_cb, 0 },
    { "&Close View", FL_CTRL + 'w', (Fl_Callback *)close_cb, 0, FL_MENU_DIVIDER },
    { "E&xit", FL_CTRL + 'q', (Fl_Callback *)quit_cb, 0 },
    { 0 },

  { "&Edit", 0, 0, 0, FL_SUBMENU },
    { "Cu&t",        FL_CTRL + 'x', (Fl_Callback *)cut_cb },
    { "&Copy",       FL_CTRL + 'c', (Fl_Callback *)copy_cb },
    { "&Paste",      FL_CTRL + 'v', (Fl_Callback *)paste_cb },
    { "&Delete",     0, (Fl_Callback *)delete_cb },
    { 0 },

  { "&Search", 0, 0, 0, FL_SUBMENU },
    { "&Find...",       FL_CTRL + 'f', (Fl_Callback *)find_cb },
    { "F&ind Again",    FL_CTRL + 'g', find2_cb },
    { "&Replace...",    FL_CTRL + 'r', replace_cb },
    { "Re&place Again", FL_CTRL + 't', replace2_cb },
    { 0 },

  { 0 }
};

#if !STYLES && HAVE_XUTF8
Fl_Font myfont = 0;
#endif

Fl_Window* new_view() {
    EditorWindow* w = new EditorWindow(660, 400, title);
    w->begin();

    Fl_Pack *pack = new Fl_Pack(0,0,660,400);
    pack->begin();

    Fl_Menu_Bar* m = new Fl_Menu_Bar(0, 0, 660, 30);
    m->copy(menuitems, w);
    m->end();

#if !STYLES && HAVE_XUTF8
	if(!myfont) 
		myfont = fl_create_font(
#ifdef _WIN32
			"Arial Unicode MS"
			//"MS Gothic"				
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
#endif

    w->editor = new Fl_Text_Editor(0, 30, 660, 370);
#if !STYLES
    w->editor->text_size(14);
#if HAVE_XUTF8
	w->editor->text_font(myfont);
#endif
#endif
    //w->editor->cursor_style(Fl_Text_Editor::BLOCK_CURSOR);
    //w->editor->cursor_color(FL_RED);
    //w->editor->wrap_mode(1, 0);

    w->editor->set_linenumber_area(0, 42);
    w->editor->buffer(textbuf);
#if STYLES
    w->editor->highlight_data(stylebuf, styletable,
                              sizeof(styletable) / sizeof(styletable[0]),
                              UNFINISHED, style_unfinished_cb, 0);
#endif
    w->end();
    w->callback((Fl_Callback *)close_cb, w);

    pack->resizable(w->editor);
    w->resizable(pack);

#if STYLES
    textbuf->add_modify_callback(style_update, w->editor);
#endif
    textbuf->add_modify_callback(changed_cb, w);
    textbuf->call_modify_callbacks();

    num_windows++;
    return w;
}

int main(int argc, char **argv) 
{
  textbuf = new Fl_Text_Buffer;
  textbuf->tab_distance(4);
#if STYLES
  style_init();
#endif
  Fl_Window* window = new_view();

  window->show(1, argv);

  if (argc > 1) load_file(argv[1], -1);

  return Fl::run();
}

//
// End of "$Id$".
//
