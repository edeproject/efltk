#ifndef FL_FILEDIALOG_H_
#define FL_FILEDIALOG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Enumerations.h"
#include "Fl_Util.h"
#include "Fl_ListView.h"
#include "Fl_ListView_Item.h"
#include "Fl_Image.h"
#include "Fl_Image_Cache.h"
#include "Fl_Input_Browser.h"
#include "Fl.h"
#include "Fl_Box.h"
#include "Fl_Window.h"
#include "Fl_Double_Window.h"
#include "Fl_Group.h"
#include "Fl_Button.h"
#include "Fl_Check_Button.h"
#include "Fl_Return_Button.h"
#include "Fl_Input.h"
#include "Fl_FileInput.h"
#include "Fl_Item.h"
#include "Fl_Highlight_Button.h"

typedef struct {
    const char *type_str;
    const char *pattern;
} Filter;

class Fl_FileItem : public Fl_ListView_Item
{
public:
    Fl_FileItem(const char *filename, Fl_FileAttr *attr);
    ~Fl_FileItem();

    enum {
        FILE = 0,
        DIR = 1,
        DEVICE,
        NETWORK
    };

    Fl_FileAttr *attr;
    char fname[FL_PATH_MAX];
    char size[32];
    char free[32]; //used in device
};

#define CLOSE_OK     false
#define CLOSE_CANCEL true

//typedef Fl_Double_Window FileDialogType;
typedef Fl_Window FileDialogType;

class PreviewBox;

class Fl_File_Dialog : public FileDialogType
{
public:
    enum {
        DEFAULT = 0,
        SAVE,
        DIRECTORY
    };

    static int initial_w, initial_h;
    static bool initial_preview;

    Fl_File_Dialog(int w, int h, const char *label=0, int mode=0);
    ~Fl_File_Dialog();

    void close(bool cancel);

    void fullpath(const char *p) { char *tmp=0; if(p)tmp=strdup(p); if(fullpath_)delete []fullpath_; fullpath_ = tmp; }
    char *fullpath() { return fullpath_; }

    const char *location() { return location_->value(); }
    int mode() { return mode_; }

    char **get_selected();

    Fl_ListView *listview() { return listview_; }
    bool cancelled() { return cancelled_; }

    void read_dir(const char *_path);
    bool new_dir();

    void set_filter(Filter *f) { _cur_filter = f; }
    void filters(Filter **filters);

    void parse_dirs(const char *fp);

    // Builds filter array, takes format e.g. "All Files, *, C++ Files, *.{cpp|cxx}"
    static Filter **build_filters(char *ptr);

    bool preview() { return preview_on; }
    void preview(bool show);
    void update_preview(const char *filename);

#ifdef _WIN32
    // Windoze network stuff:
    bool enum_netresources(Fl_Callback *cb, LPNETRESOURCE lpnr, DWORD scope);
    void read_network(LPNETRESOURCE net=0);
    void add_netitem(LPNETRESOURCE net);
    DWORD scope;
#endif

    // Returns full path to file including filename, path could be e.g. 'filename.ext' or c:\filename.ext
    char *get_filename(const char *path, char *buf);
    // Returns full path to directory w/o filename, path could be e.g. 'c:\dir\somef' is returned c:\dir
    char *get_filepath(const char *path, char *buf);
private:

    Fl_ListView *listview_;
    bool cancelled_;

    Fl_Image_Cache image_cache;
    PreviewBox *preview_;
    Fl_Box *preview_info_;
    Fl_Check_Button *preview_but_;
    bool preview_on;
    char preview_text[1024], preview_info[256];

    Fl_Highlight_Button *up_;
    Fl_Highlight_Button *home_;
    Fl_Highlight_Button *refresh_;
    Fl_Highlight_Button *new_folder_;

    Fl_Input_Browser *path_;
    Fl_Input_Browser *filter_;

    Fl_Input_Browser *location_;

    Fl_Return_Button *ok_;
    Fl_Button *cancel_;

    char files[4096]; //Files buffer for location (multisel)
    char *fullpath_;

    Filter **_filters;
    Filter *_cur_filter;

    int mode_;

    void init();
    void make_group(int w, int h);

    void file_clicked(Fl_FileItem *i);
    void folder_clicked(Fl_FileItem *i);

    static void cb_list(Fl_Widget *, void *);
    static void cb_preview(Fl_Widget *, void *);

    static void cb_ok(Fl_Widget *, void *);
    static void cb_cancel(Fl_Widget *, void *);
    static void cb_new(Fl_Widget *, void *);
    static void cb_home(Fl_Widget *, void *);
    static void cb_refresh(Fl_Widget *, void *);
    static void cb_up(Fl_Widget *, void *);

    static void cb_dirc(Fl_Widget *, void *);
    static void cb_filter(Fl_Widget *, void *);
    static void cb_location(Fl_Widget *, void *);
};

// Filter string format:
// char *filters = "All Files, *, Cpp Files, *.{cpp|cxx|C}";
// There MUST be always 'Typename' and 'Pattern'!

// File select dialogs
extern char *fl_select_file(const char *path=0, char *filters=0, const char *cap=0);
extern char **fl_select_files(const char *path=0, char *filters=0, const char *cap=0);

// Save file dialog
extern char *fl_save_file(const char *path=0, char *filters=0, const char *cap=0);

// Directory select dialog
extern char *fl_select_dir(const char *path=0, const char *cap=0);

#endif

