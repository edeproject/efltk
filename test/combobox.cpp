#include <efltk/Fl.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Combo_Box.h>
#include <efltk/fl_ask.h>

void cb_callback(Fl_Widget *combo_box,void *) {
    char *msg = "Not a combo box specific event";
    switch (combo_box->event()) {
        case FL_DATA_CHANGE: {
                msg = "Data changed"; 
            }
            break;
        case FL_UC_INSERT:      msg = "Insert command"; break;
        case FL_UC_EDIT:        msg = "Edit command"; break;
        case FL_UC_DELETE:      msg = "Delete command"; break;
        case FL_UC_REFRESH:     msg = "Refresh command"; break;
    }
    puts(msg);
}

void fill_list(Fl_Combo_Box *cb) {
    cb->listview()->add_column("Animal",50);
    cb->listview()->add_column("Type",50);

    Fl_ListView_Item *item;

    cb->begin();

    item = new Fl_ListView_Item("Bear","Mammal");
    item->argument(1);

    item = new Fl_ListView_Item("Sardine","Fish");
    item->argument(2);

    item = new Fl_ListView_Item("Albatros","Bird");
    item->argument(3);

    cb->end();
}

int main(int argc, char *argv[]) {
    Fl_Window       window(400,300,"Combo Box test");
    window.layout_spacing(4);

    Fl_Combo_Box    cb1("Regular combo box");
    fill_list(&cb1);
    cb1.callback(cb_callback);

    Fl_Combo_Box    cb2("CB with all buttons");
    fill_list(&cb2);
    cb2.buttons(FL_CBB_INSERT|FL_CBB_EDIT|FL_CBB_DELETE|FL_CBB_REFRESH);
    cb2.callback(cb_callback);

    window.end();

    window.show();
    Fl::run();
}
