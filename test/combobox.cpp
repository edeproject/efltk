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

int main(int argc, char *argv[]) {
    Fl_Window       window(400,300,"Combo Box test");
    Fl_Combo_Box    cb(100,20,200,23,"Combo Box");
    cb.buttons(FL_CBB_INSERT|FL_CBB_EDIT|FL_CBB_DELETE|FL_CBB_REFRESH);
    cb.callback(cb_callback);
    window.end();

    Fl_ListView *lv = cb.listview();
    lv->add_column("Animal",50);
    lv->add_column("Type",50);

    Fl_ListView_Item *item;

    lv->begin();

    item = new Fl_ListView_Item("Bear","Mammal");
    item->argument(1);

    item = new Fl_ListView_Item("Sardine","Fish");
    item->argument(2);

    item = new Fl_ListView_Item("Albatros","Bird");
    item->argument(3);

    lv->end();

    window.show();
    Fl::run();
}
