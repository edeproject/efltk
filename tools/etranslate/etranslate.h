#ifndef _ETRANSLATE_H_
#define _ETRANSLATE_H_

#include <efltk/xml/Fl_Xml.h>

#include <efltk/Fl_Date_Time.h>
#include <efltk/Fl_String.h>
#include <efltk/Fl_File_Dialog.h>
#include <efltk/fl_ask.h>
#include <efltk/Fl.h>
#include <efltk/Fl_String_List.h>
#include <efltk/Fl_Int_List.h>
#include <efltk/Fl_String_Hash.h>

#include "main_ui.h"

//#define N_(s) (s)

class TranslateItem;

class ETranslate
{
public:
    ETranslate();
    ~ETranslate();

    void handle_action(int a);
    void sort_strings();

    void compile(const char *file=0);

    void load_etm(FILE *fp);
    void load_pot(FILE *fp);

    void load(const char *file=0);
    void save(const char *file=0);

    void show_translation(TranslateItem *i);
    void save_translation();
    void next_unfinished();

    void update_status();

    void show_modify_window();

    Fl_XmlContext ctx;
    Fl_Window *win, *modwin;
    TranslateItem *current;

    Fl_String filename;
    Fl_String status_str;

    // Project information
    Fl_String comment;
    Fl_String name;
    Fl_String version;
    Fl_String start_date;
    Fl_String mod_date;
    Fl_String translator;
    Fl_String email;
    Fl_String lang;
};

class TranslateItem : public Fl_ListView_ItemExt
{
public:
    TranslateItem();

    bool finished() { return finished_; }
    void finished(bool v);

    Fl_String &orig()    { return orig_; }
    void orig(Fl_String s)    { orig_ = s; label(0, orig_.c_str()); }

    Fl_String &tr()      { return tr_; }
    void tr(Fl_String s)      { tr_ = s; label(1, tr_.c_str()); }

    Fl_String &comment() { return comment_; }
    void comment(Fl_String s) { comment_ = s; }

private:
    bool finished_;
    Fl_String orig_;
    Fl_String tr_;
    Fl_String comment_;
};

#endif

