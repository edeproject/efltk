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

#ifndef _FL_FILEDIALOG_H_
#define _FL_FILEDIALOG_H_

#include "Enumerations.h"
#include "Fl_Image_Cache.h"
#include "Fl_Input_Browser.h"
#include "Fl_Item.h"
#include "Fl_Dialog.h"
#include "Fl_Group.h"
#include "Fl_Check_Button.h"
#include "Fl_Highlight_Button.h"
#include "Fl_FileBrowser.h"

class PreviewBox;

/** Fl_File_Chooser */
class Fl_File_Chooser : public Fl_Dialog
{
public:
    // Modes:
    enum {
        _DEFAULT = 0,
        _SAVE,
        _DIRECTORY
    };

    // ctor / dtor
    //Fl_File_Chooser(int x, int y, int w, int h, const char *label=0, int mode=0);
	Fl_File_Chooser(int w, int h, const char *label=0, int mode=0);
    ~Fl_File_Chooser();

    // When Opening directory, it tries to find 'default filename' and mark item as selected.
    void default_filename(const Fl_String &f) { m_default_filename = f; }
    void default_filename(const char *f) { m_default_filename = f; }

    // Change directory to 'path'
    void directory(const Fl_String &path);
    void directory(const char *path) { Fl_String tmp(path); directory(tmp); }

    // Get current path
    const Fl_String &directory() const { return m_filebrowser->directory(); }

    const char *file_input() const { return m_file_input->value(); }
    void file_input(const char *v) { m_file_input->value(v); }

    // Get current pattern, e.g. "*.xpm"
    const char *pattern() const { return m_filter_input->item() ? (const char *)m_filter_input->item()->user_data() : ""; }

    // Get current filter name, e.g. "Xpm Files"
    const char *filter_name() const { return m_filter_input->value(); }

    // Returns mode of file chooser
    int mode() const { return m_mode; }

    // Returns NULL terminated list of selected files.
    char **get_selected();

    // Store selected files to 'list'
    void get_selected(Fl_String_List &list);

    // Set / Get multi selection
    void multi_selection(bool v) { if(v) m_filebrowser->type(m_filebrowser->type()|Fl_ListView::MULTI_SELECTION); else m_filebrowser->type(m_filebrowser->type()&~Fl_ListView::MULTI_SELECTION); }
    bool multi_selection() { return m_filebrowser->multi(); }

    bool preview() const { return m_preview->value(); }
    void preview(bool show);

    // Updates preview box
    void update_preview(const Fl_String filename);

    // Stores full path to file 'buf'. Includes filename, path could be e.g. 'filename.ext' or 'c:\filename.ext'.
    // Prepends directory(), if needed.
    void get_filename(Fl_String path, Fl_String &buf);

    // Stores full path to directory w/o filename to 'buf'. Path could be e.g. 'c:\dir\somef' then 'c:\dir\' is returned
    void get_filepath(Fl_String path, Fl_String &buf);

    // Get file listview object
    Fl_File_Browser *filebrowser() { return m_filebrowser; }

    // Go one dir up
    void up();
    // Refresh contents
    void refresh() { directory(directory()); }
    // Create new dir. Popup dialog, for asking dirname.
    // Returns fullpath to created dir or empty string in error
    Fl_String new_dir();

    // Set new filters.
    // Format e.g. "All Files, *, Cpp Files, *.{cpp|cxx|C}";
    void filters(const char *filters);

    // Backward compatibility:
    void read_dir(const char *path) { directory(path); }

    virtual int handle(int e);
    virtual void layout();

    /* BROKEN, for now..
     #ifdef _WIN32
     // MS Windows network stuff:
     bool enum_netresources(Fl_Callback *cb, LPNETRESOURCE lpnr, DWORD scope);
     void read_network(LPNETRESOURCE net=0);
     void add_netitem(LPNETRESOURCE net);
     DWORD scope;
     #endif
     */

	virtual bool save_data(Fl_Data_Source *ds=0);

protected:
    // Creates group
    void make_group();

    //Parses 'fp' to 'm_path_input'
    void parse_dirs(const Fl_String &fp);

    Fl_Highlight_Button *m_up;
    Fl_Highlight_Button *m_home;
    Fl_Highlight_Button *m_refresh;
    Fl_Highlight_Button *m_new_folder;

    Fl_Input_Browser	*m_path_input;
    Fl_Input_Browser	*m_filter_input;
    Fl_Input_Browser	*m_file_input;
    Fl_Check_Button		*m_preview;

    Fl_File_Browser		*m_filebrowser;

private:
    PreviewBox *m_preview_box;
    Fl_String m_default_filename;
    int m_mode;

    void file_clicked(Fl_ListView_Item *i);
    void folder_clicked(Fl_ListView_Item *i);

    static void cb_list          (Fl_File_Browser *w, Fl_File_Chooser *d);
    static inline void cb_preview(Fl_Widget *w, Fl_File_Chooser *d) { d->preview(bool(w->value()==1)); }

    static inline void cb_new	 (Fl_Widget *, Fl_File_Chooser *d) { d->new_dir(); }
    static inline void cb_home	 (Fl_Widget *, Fl_File_Chooser *d) { d->directory(fl_homedir()); }
    static inline void cb_refresh(Fl_Widget *, Fl_File_Chooser *d) { d->refresh(); }
    static inline void cb_up	 (Fl_Widget *, Fl_File_Chooser *d) { d->up(); }

    static inline void cb_dirc	(Fl_Input_Browser *w, Fl_File_Chooser *d) { d->directory(w->value()); }
    static inline void cb_filter(Fl_Input_Browser *w, Fl_File_Chooser *d) { d->filebrowser()->pattern((const char *)w->item()->user_data()); d->refresh(); }
    static void cb_location     (Fl_Input_Browser *w, Fl_File_Chooser *d);
};

// Filter string format:
// char *filters = "All Files, *, Cpp Files, *.{cpp|cxx|C}";
// There MUST be always 'Typename' and 'Pattern'!

// File select dialogs
extern FL_API char *fl_select_file(const char *path=0, char *filters=0, const char *caption=0);
extern FL_API char **fl_select_files(const char *path=0, char *filters=0, const char *caption=0);

// Save file dialog
extern FL_API char *fl_save_file(const char *path=0, char *filters=0, const char *caption=0);

// Directory select dialog
extern FL_API char *fl_select_dir(const char *path=0, const char *cap=0);

extern FL_API int fc_initial_w;
extern FL_API int fc_initial_h;
extern FL_API bool fc_initial_preview;

#endif
