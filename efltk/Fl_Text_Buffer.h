/*
 * $Id$
 *
 * Extended Fast Light Toolkit (EFLTK)
 * Copyright (C) 2002-2003 by EDE-Team
 * WWW: http://www.sourceforge.net/projects/ede
 *
 * Fast Light Toolkit (FLTK)
 * Copyright (C) 1998-2003 by Bill Spitzak and others.
 * WWW: http://www.fltk.org
 *
 * This library is distributed under the GNU LIBRARY GENERAL PUBLIC LICENSE
 * version 2. See COPYING for details.
 *
 * Author : Mikko Lahteenmaki
 * Email  : mikko@fltk.net
 *
 * Please report all bugs and problems to "efltk-bugs@fltk.net"
 *
 */

#ifndef _FL_TEXT_BUFFER_H_
#define _FL_TEXT_BUFFER_H_

/* Maximum length in characters of a tab or control character expansion
 of a single buffer character */
#define FL_TEXT_MAX_EXP_CHAR_LEN 20

#include <efltk/Fl_Export.h>
#include <efltk/Fl_Ptr_Stack.h>
#include <efltk/Fl_Buffer.h>

typedef void (*Fl_Text_Modify_Cb)(int pos, int nInserted, int nDeleted,
   int nRestyled, const char* deletedText,
   void* cbArg);
typedef void (*Fl_Text_Predelete_Cb)(int pos, int nDeleted, void* cbArg);

/** Fl_Text_Selection */
class FL_API Fl_Text_Selection {
   friend class Fl_Text_Buffer;

public:
   void set(int start, int end);
   void set_rectangular(int start, int end, int rectStart, int rectEnd);
   void update(int pos, int nDeleted, int nInserted);
   char rectangular() { return mRectangular; }
   int start() { return mStart; }
   int end() { return mEnd; }
   int rect_start() { return mRectStart; }
   int rect_end() { return mRectEnd; }
   char selected() { return mSelected; }
   void selected(char b) { mSelected = b; }
   int includes(int pos, int lineStartPos, int dispIndex);
   int position(int* start, int* end);
   int position(int* start, int* end, int* isRect, int* rectStart, int* rectEnd);


protected:
   char mSelected;
   char mRectangular;
   int mStart;
   int mEnd;
   int mRectStart;
   int mRectEnd;
};

typedef void (*Fl_Text_Modify_Cb)(int pos, int nInserted, int nDeleted,
   int nRestyled, const char* deletedText,
   void* cbArg);
typedef void (*Fl_Text_Predelete_Cb)(int pos, int nDeleted, void* cbArg);

//Forward declare...
class Fl_UndoNode_Stack;

/** Fl_Text_Buffer */
class FL_API Fl_Text_Buffer {
public:
   Fl_Text_Buffer(int requestedSize = 0);
   ~Fl_Text_Buffer();

   char *Fl_Text_Buffer::static_buffer();

    // Undo stack size: (default 50)
   int undo_size();
   void undo_size(int newsize);

    // Returns insert position
   int undo();
   void add_undo(const char *str, int pos, int len, bool inserted, bool replaced);

   int length() { return mLength; }
   const char* text();
   void text(const char* text);
   const char* text_range(int start, int end);
   void text_range(Fl_String_Buffer& outStr, int start, int end);
   char character(int pos);
   const char* text_in_rectangle(int start, int end, int rectStart, int rectEnd);

   void insert(int pos, const char* text, int text_len=-1);
   void append(const char* text, int text_len=-1) { insert(length(), text, text_len); }
   void remove(int start, int end);
   void replace(int start, int end, const char *text, int text_len=-1);
   void copy(Fl_Text_Buffer* fromBuf, int fromStart, int fromEnd, int toPos);
   int insertfile(const char *file, int pos, int buflen = 128*1024);
   int appendfile(const char *file, int buflen = 128*1024)
   { return insertfile(file, length(), buflen); }
   int loadfile(const char *file, int buflen = 128*1024)
   { select(0, length()); remove_selection(); return appendfile(file, buflen); }
   int outputfile(const char *file, int start, int end, int buflen = 128*1024);
   int savefile(const char *file, int buflen = 128*1024)
   { return outputfile(file, 0, length(), buflen); }

   void insert_column(int column, int startPos, const char* text,
      int* charsInserted, int* charsDeleted);

   void replace_rectangular(int start, int end, int rectStart, int rectEnd,
      const char* text);

   void overlay_rectangular(int startPos, int rectStart, int rectEnd,
      const char* text, int* charsInserted,
      int* charsDeleted);

   void remove_rectangular(int start, int end, int rectStart, int rectEnd);
   void clear_rectangular(int start, int end, int rectStart, int rectEnd);
   int tab_distance() { return mTabDist; }
   void tab_distance(int tabDist);
   void select(int start, int end);
   int selected() { return mPrimary.selected(); }
   void unselect();
   void select_rectangular(int start, int end, int rectStart, int rectEnd);
   int selection_position(int* start, int* end);

   int selection_position(int* start, int* end, int* isRect, int* rectStart,
      int* rectEnd);

   const char* selection_text();
   void remove_selection();
   void replace_selection(const char* text);
   void secondary_select(int start, int end);
   void secondary_unselect();

   void secondary_select_rectangular(int start, int end, int rectStart,
      int rectEnd);

   int secondary_selection_position(int* start, int* end, int* isRect,
      int* rectStart, int* rectEnd);

   const char* secondary_selection_text();
   void remove_secondary_selection();
   void replace_secondary_selection(const char* text);
   void highlight(int start, int end);
   void unhighlight();
   void highlight_rectangular(int start, int end, int rectStart, int rectEnd);

   int highlight_position(int* start, int* end, int* isRect, int* rectStart,
      int* rectEnd);

   const char* highlight_text();

   void add_modify_callback(Fl_Text_Modify_Cb bufModifiedCB, void* cbArg);
   void remove_modify_callback(Fl_Text_Modify_Cb bufModifiedCB, void* cbArg);
   void call_modify_callbacks() { call_modify_callbacks(0, 0, 0, 0, 0); }

   void add_predelete_callback(Fl_Text_Predelete_Cb bufPredelCB, void* cbArg); 
   void remove_predelete_callback(Fl_Text_Predelete_Cb predelCB, void* cbArg); 
   void call_predelete_callbacks() { call_predelete_callbacks(0, 0); } 

   const char* line_text(int pos);
   int line_start(int pos);
   int line_end(int pos);
   int word_start(int pos);
   int word_end(int pos);
   int expand_character(int pos, int indent, char *outStr);

   static int expand_character(char c, int indent, char* outStr, int tabDist);

   static int character_width(char c, int indent, int tabDist);
   int count_displayed_characters(int lineStartPos, int targetPos);
   int skip_displayed_characters(int lineStartPos, int nChars);
   int count_lines(int startPos, int endPos);
   int skip_lines(int startPos, int nLines);
   int rewind_lines(int startPos, int nLines);
   int findchar_forward(int startPos, char searchChar, int* foundPos);
   int findchar_backward(int startPos, char searchChar, int* foundPos);
   int findchars_forward(int startPos, const char* searchChars, int* foundPos);
   int findchars_backward(int startPos, const char* searchChars, int* foundPos);

   int search_forward(int startPos, const char* searchString, int* foundPos,
      int matchCase = 0);

   int search_backward(int startPos, const char* searchString, int* foundPos,
      int matchCase = 0);

   Fl_Text_Selection* primary_selection() { return &mPrimary; }
   Fl_Text_Selection* secondary_selection() { return &mSecondary; }
   Fl_Text_Selection* highlight_selection() { return &mHighlight; }

protected:
   void call_modify_callbacks(int pos, int nDeleted, int nInserted,
      int nRestyled, const char* deletedText);

   void call_predelete_callbacks(int pos, int nDeleted);

   int insert_(int pos, const char* text, int text_len);
   void remove_(int start, int end);

   void remove_rectangular_(int start, int end, int rectStart, int rectEnd,
							int* replaceLen, int* endPos);

   void insert_column_( int column, int startPos, const char* insText,
						int* nDeleted, int* nInserted, int* endPos);

   void overlay_rectangular_(int startPos, int rectStart, int rectEnd,
							 const char* insText, int* nDeleted,
							 int* nInserted, int* endPos);

   void redisplay_selection(Fl_Text_Selection* oldSelection,
							Fl_Text_Selection* newSelection);

   void move_gap(int pos);
   void reallocate_with_gap(int newGapStart, int newGapLen);
   const char* selection_text_(Fl_Text_Selection* sel);
   void remove_selection_(Fl_Text_Selection* sel);
   void replace_selection_(Fl_Text_Selection* sel, const char* text);

   void rectangular_selection_boundaries(int lineStartPos, int rectStart,
										 int rectEnd, int* selStart,
										 int* selEnd);

   void update_selections(int pos, int nDeleted, int nInserted);

   Fl_UndoNode_Stack *undo_stack;

   Fl_Text_Selection mPrimary; /* highlighted areas */
   Fl_Text_Selection mSecondary;
   Fl_Text_Selection mHighlight;
   int mLength;                /* length of the text in the buffer (the length
                                   of the buffer itself must be calculated:
                                   gapEnd - gapStart + length) */
   char* mBuf;                 /* allocated memory where the text is stored */
   int mGapStart;              /* points to the first character of the gap */
   int mGapEnd;                /* points to the first char after the gap */
    // The hardware tab distance used by all displays for this buffer,
    // and used in computing offsets for rectangular selection operations.
   int mTabDist;               /* equiv. number of characters in a tab */
   int mUseTabs;               /* True if buffer routines are allowed to use
                                   tabs for padding in rectangular operations */
   int mNModifyProcs;          /* number of modify-redisplay procs attached */
   Fl_Text_Modify_Cb*          /* procedures to call when buffer is */
      mNodifyProcs;               /* modified to redisplay contents */
   void** mCbArgs;             /* caller arguments for modifyProcs above */

   int mNPredeleteProcs;       /* number of pre-delete procs attached */ 
   Fl_Text_Predelete_Cb*       /* procedure to call before text is deleted */ 
      mPredeleteProcs;       /* from the buffer; at most one is supported. */ 
   void **mPredeleteCbArgs;    /* caller argument for pre-delete proc above */ 

   int mCursorPosHint;         /* hint for reasonable cursor position after
                                   a buffer modification operation */
};

#endif
