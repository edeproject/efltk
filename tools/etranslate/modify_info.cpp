#include "etranslate.h"

void cb_info_ok(Fl_Button *b, ETranslate *e)
{
    e->modwin->set_value();
    e->modwin->hide();
}

void cb_info_cancel(Fl_Button *, ETranslate *e)
{
    e->modwin->clear_value();
    e->modwin->hide();
}

void ETranslate::show_modify_window()
{
    if(!modwin) {
        modwin = modify_window();
        info_ok->callback((Fl_Callback*)cb_info_ok, this);
        info_cancel->callback((Fl_Callback*)cb_info_cancel, this);
        modwin->callback((Fl_Callback*)cb_info_cancel, this);
    }

    info_comment->value(comment.c_str());
    info_prjname->value(name.c_str());
    info_prjversion->value(version.c_str());
    info_trans->value(translator.c_str());
    info_email->value(email.c_str());
    info_lang->value(lang.c_str());
    info_startdate->value(start_date.c_str());
    info_moddate->value(mod_date.c_str());

    Fl_String scomment = comment;
    Fl_String sname    = name;
    Fl_String sversion = version;
    Fl_String strans   = translator;
    Fl_String semail   = email;
    Fl_String slang    = lang;

    if(modwin->exec()) {
        comment    = info_comment->value();
        name       = info_prjname->value();
        version    = info_prjversion->value();
        translator = info_trans->value();
        email      = info_email->value();
        lang       = info_lang->value();

        prj_output->value(name.c_str());
        lang_output->value(lang.c_str());
        trans_output->value(translator.c_str());
        email_output->value(email.c_str());

        return;
    }

    comment    = scomment;
    name       = sname;
    version    = sversion;
    translator = strans;
    email      = semail;
    lang       = slang;
}
