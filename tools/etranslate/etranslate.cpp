#include "etranslate.h"
#include "compile.h"

ETranslate *app;

void cb_menu(Fl_Menu_ *w, ETranslate *e)
{
    e->handle_action(w->item()->argument());
}

void cb_listview(Fl_ListView *w, ETranslate *e)
{
    e->show_translation((TranslateItem*)w->item());
}

void cb_save_button(Fl_Button *, ETranslate *e)
{
    e->save_translation();
    e->next_unfinished();
}

void cb_modify_button(Fl_Button *, ETranslate *e)
{
    e->show_modify_window();
}

void cb_toolbar_button(Fl_Button *w, void *)
{
    app->handle_action(w->argument());
}

ETranslate::ETranslate()
{
    app = this;
    current = 0;
    modwin = 0;

    win = main_window();
    activate(false);

    menubar->callback((Fl_Callback*)cb_menu, this);
    browser->callback((Fl_Callback*)cb_listview, this);

    save_button->callback((Fl_Callback*)cb_save_button, this);
    modify_button->callback((Fl_Callback*)cb_modify_button, this);

    tb_quit->callback((Fl_Callback1*)cb_toolbar_button, QUIT);
    tb_load->callback((Fl_Callback1*)cb_toolbar_button, LOAD);
    tb_save->callback((Fl_Callback1*)cb_toolbar_button, SAVE);
    tb_comp->callback((Fl_Callback1*)cb_toolbar_button, COMPILE);

    win->show();
}

ETranslate::~ETranslate()
{
    delete win;
    if(modwin) delete modwin;
}

void ETranslate::activate(bool val)
{
    if(!val) {
        maingroup->deactivate();
        info_group->deactivate();

        tb_save->deactivate();
        tb_saveas->deactivate();
        tb_comp->deactivate();
        tb_extract->deactivate();

        menubar->find("&File/&Save")->deactivate();
        menubar->find("&File/Save &As")->deactivate();

    } else {
        maingroup->activate();
        info_group->activate();

        tb_save->activate();
        tb_saveas->activate();
        tb_comp->activate();
        tb_extract->activate();

        menubar->find("&File/&Save")->activate();
        menubar->find("&File/Save &As")->activate();
    }
}

void ETranslate::handle_action(int a)
{
    switch(a) {
    case QUIT:
        win->hide();
        break;
    case LOAD:
        load();
        break;
    case SAVE:
        save(filename.c_str());
        break;
    case SAVEAS:
        save();
        break;
    case COMPILE:
        compile();
        break;
    default:
        Fl::warning("Unhandled action (%d)", a);
        break;
    }
}

void ETranslate::load(const char *file)
{
    browser->clear();

    if(!file) {
        const char *f = fl_select_file(filename.c_str(),
                                       _("Translation Files, *.{etm|po|pot},"
                                         "Efltk Tr Files, *.etm,"
                                         "GNU gettext files, *.{po|pot}")
                                      );
        if(!f) return;
        file = f;
    }

    FILE *fp = fopen(file, "r");
    if(!fp) return;
    filename = file;

    if(strstr(filename.c_str(), ".etm"))
        load_etm(fp);
    else if(strstr(filename.c_str(), ".po") || strstr(filename.c_str(), ".pot"))
        load_pot(fp);
    else
        filename.clear();

    if(filename.length()>0) {
        sort_strings();
        if(browser->children()>0)
            show_translation((TranslateItem*)browser->child(0));
        update_status();
        activate(true);
    } else {
        activate(false);
    }

    fclose(fp);
}

void ETranslate::compile(const char *file)
{
    if(!file) {
        const char *f = fl_save_file(filename.c_str(), _("Translation Binary Files, *.etb,"));
        if(!f) return;
        file = f;
    }

    FILE *fp = fopen(file, "wb");
    if(!fp) {
        return;
    }

    int numstrings=0;
    Fl_Int_List lengths;
    Fl_String_List strings;

    for(uint n=0; n<browser->children(); n++) {
        TranslateItem *i = (TranslateItem *)browser->child(n);
        if(i->finished()) {
            numstrings++;
            lengths.append(i->orig().length());
            lengths.append(i->tr().length());
            strings.append(i->orig());
            strings.append(i->tr());
        }
    }

    Compiler::compile(fp, numstrings, lengths, strings);
    fclose(fp);
}

void ETranslate::show_translation(TranslateItem *i)
{
    current = i;
    orig_input->value(i->orig().c_str());
    trans_input->value(i->tr().c_str());
    comment_output->value(i->comment().c_str());

    fin_button->value(i->finished());
    browser->select_only(i);
    browser->show_item(i);

    trans_input->take_focus();
    browser->take_focus();
}

void ETranslate::save_translation()
{
    current->tr(trans_input->value());
    current->finished(fin_button->value());

    sort_strings();
    update_status();
}

void ETranslate::next_unfinished()
{
    for(uint n=0; n<browser->children(); n++) {
        TranslateItem *i = (TranslateItem *)browser->child(n);
        if(!i->finished()) {
            show_translation(i);
            return;
        }
    }
}

void ETranslate::update_status()
{
    int finished=0;
    for(uint n=0; n<browser->children(); n++) {
        TranslateItem *i = (TranslateItem *)browser->child(n);
        if(i->finished()) finished++;
    }
    status_str.printf("%s: %d / %d finished.", filename.c_str(), finished, browser->children());
    statusbar->label(status_str.c_str());
    statusbar->redraw();
}

static int sortf(const void *w1, const void *w2) {
    TranslateItem *i1 = *(TranslateItem **)w1;
    TranslateItem *i2 = *(TranslateItem **)w2;
    if(i1->finished()!=i2->finished())
        return i1->finished()-i2->finished();
	return i1->orig().casecmp(i2->orig());
}

void ETranslate::sort_strings()
{
    browser->array().sort(sortf);
    browser->calc_totalheight();

    browser->redraw();
    browser->layout();
}

//////////////////////////////////////////////////
//////////////////////////////////////////////////

TranslateItem::TranslateItem()
{
    finished_ = false;
}

void TranslateItem::finished(bool v)
{
    finished_ = v;
    if(v) {
        label_color(0, FL_BLACK);
        label_color(1, FL_BLACK);
    } else {
        label_color(0, FL_RED);
        label_color(1, FL_RED);
    }
}
