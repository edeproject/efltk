//
// Browser demo for eFLTK
//
// $Id$
//

#include <efltk/Fl_Browser.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl.h>
#include <efltk/Fl_Pixmap.h>
#include <efltk/Fl_Item.h>
#include <efltk/Fl_Item_Group.h>
#include <efltk/Fl_Check_Button.h>

#include "folder_small.xpm"
#include "file_small.xpm"

#include <stdio.h>

Fl_Pixmap folderSmall(folder_small);
Fl_Pixmap fileSmall(file_small);

void cb_test(Fl_Widget* browser, void*)
{
    Fl_Widget* w = ((Fl_Browser*)browser)->item();
    printf("Callback, browser->item() = '%s'", w ? w->label().c_str() : "(NULL)");
    if (Fl::event_clicks()) printf(", Double Click");
    printf("\n");
}

void cb_remove(Fl_Widget*, void* ptr)
{
    if (Fl::event() != FL_BUTTON_PRESSED) return;

    Fl_Browser* tree = (Fl_Browser*) ptr;
    if (tree->type() & Fl_Browser::MULTI) {
        Fl_Widget* w = tree->goto_top();
        while (w) {
            if (w->selected()) {
                Fl_Group* g = w->parent();
                g->remove(w);
                delete w;
                g->relayout();
                w = tree->goto_top();
            } else {
                w = tree->next();
            }
        }
    } else {
        Fl_Widget* w = tree->goto_focus();
        if (w) {
            Fl_Group* g = w->parent();
            g->remove(w);
            delete w;
            g->relayout();
        }
    }
}

void cb_multi(Fl_Widget* w, void* ptr)
{
    if (Fl::event() != FL_BUTTON_PRESSED) return;

    Fl_Browser* tree = (Fl_Browser*) ptr;
    tree->type(w->value() ? Fl_Browser::MULTI : Fl_Browser::NORMAL);
    tree->relayout();
}

static Fl_Group* current_group(Fl_Browser* tree)
{
    Fl_Widget* w = tree->goto_focus();
    if (!w) return tree;
    if (w->is_group() && w->flags()&FL_VALUE) return (Fl_Group*)w;
    return w->parent() ? w->parent() : tree;
}

static Fl_Group* add_folder(Fl_Group* parent, const char* name, int open, Fl_Pixmap &image)
{
    parent->begin();
    Fl_Item_Group* o = new Fl_Item_Group(name);
    o->image(image);
    if (open) o->set_flag(FL_VALUE);
    return o;
}

static Fl_Widget* add_paper(Fl_Group* parent, const char* name, int, Fl_Pixmap &image)
{
    parent->begin();
    Fl_Item* o = new Fl_Item(name);
    o->image(image);
    return o;
}

void cb_add_folder(Fl_Widget*, void* ptr)
{
    if (Fl::event() != FL_BUTTON_PRESSED) return;

    Fl_Browser* tree = (Fl_Browser*) ptr;
    add_folder(current_group(tree), "Added folder", 1, folderSmall);
    tree->relayout();
}

void cb_add_paper(Fl_Widget*, void* ptr)
{
    if (Fl::event() != FL_BUTTON_PRESSED) return;

    Fl_Browser* tree = (Fl_Browser*) ptr;
    add_paper(current_group(tree), "New paper", 0, fileSmall);
    tree->relayout();
}

int main(int argc,char** argv)
{
    Fl_Window win(240, 304, "Browser Example");

    Fl_Browser tree(10, 10, 220, 180);
    tree.layout_align(FL_ALIGN_CLIENT);
    tree.indented(1);
    tree.callback(cb_test);

    Fl_Group group;
    group.auto_grow(FL_GROUP_GROW_BOTH);

    Fl_Button remove_button("Remove");
    remove_button.callback((Fl_Callback*)cb_remove, (void *)&tree);

    Fl_Button add_paper_button("Add Paper");
    add_paper_button.callback((Fl_Callback*)cb_add_paper, (void *)&tree);

    Fl_Button add_folder_button("Add Folder");
    add_folder_button.callback((Fl_Callback*)cb_add_folder, (void *)&tree);

    Fl_Check_Button multi_button("Multi Seletion");
    multi_button.callback((Fl_Callback*)cb_multi, (void *)&tree);

    group.end();
    group.layout_align(FL_ALIGN_BOTTOM);

    win.resizable(tree);
    win.end();

    //int w[3] = {150, 200, 0};
    //tree.column_widths(w);

    // Add some nodes with icons -- some open, some closed.
    {
        Fl_Group* g;

        g = add_folder(&tree, "aaa\t123", 1, folderSmall);

        add_folder(g, "bbb TWO\t456", 1, folderSmall);

        g = add_folder(&tree, "bbb", 0, folderSmall);

        add_paper(g, "ccc\t789", 1, folderSmall);
        add_paper(g, "ddd\t012", 0, fileSmall);

        g = add_folder(&tree, "eee", 1, folderSmall);
        add_paper(g, "fff", 0, fileSmall);

        g = add_folder(g, "ggg", 1, folderSmall);
        add_paper(g, "hhh", 1, fileSmall);
        add_paper(g, "iii", 1, fileSmall);

        g = add_folder(&tree, "jjj", 1, folderSmall);
        add_paper(g, "kkk", 0, fileSmall);

        add_paper(&tree, "lll", 0, fileSmall);
        g = add_folder(&tree, "mmm", 0, folderSmall);
        add_paper(g, "nnn", 1, folderSmall);
        add_paper(g, "ooo", 0, fileSmall);

        g = add_folder(g, "ppp", 1, folderSmall);
        add_paper(g, "qqq", 0, fileSmall);
        g = g->parent();

        g = add_folder(g, "rrr", 1, folderSmall);
        g = add_folder(g, "sss", 1, folderSmall);
        g = add_folder(g, "ttt", 1, folderSmall);

        g = add_folder(&tree, "uuu", 1, folderSmall);
        add_paper(g, "vvv", 0, fileSmall);

        add_paper(&tree, "www", 0, fileSmall);
        add_paper(&tree, "xxx", 0, fileSmall);
        add_paper(&tree, "yyy", 0, fileSmall);
        add_paper(&tree, "zzz", 0, fileSmall);
    }

    win.show(argc,argv);
    return Fl::run();
}
