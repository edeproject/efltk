#include <efltk/Fl.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_ListView.h>
#include <efltk/Fl_String.h>
#include <efltk/Fl_Date_Time.h>

int main(int argc,char *argv[]) {
    Fl_Window window(500,300,"ListView sort test");
    window.layout_spacing(4);

    Fl_ListView listView(0,0,100,100);
    listView.layout_align(FL_ALIGN_CLIENT);

    listView.add_column("Strings",100,VAR_STRING);
    listView.add_column("Integers",80,VAR_INT);
    listView.add_column("Floats",100,VAR_FLOAT);
    listView.add_column("Dates",100,VAR_DATETIME);
    listView.add_column("Dates with time",130,VAR_DATETIME);

    Fl_Date_Time today((int)Fl_Date_Time::Now());
    listView.begin();
    for (int i = 0; i < 1000; i++) {
        Fl_String f1;
        f1.printf("%0.4f",(100-i)/3.0);
        Fl_String   d1 = Fl_Date_Time(today+i*5-500).date_string();
        Fl_Date_Time dd(double(today)-double(i)/24.0);
        Fl_String   d2 = dd.date_string() + " " + dd.time_string();
        new Fl_ListView_Item("String "+Fl_String(i),Fl_String(i),f1,d1,d2);
    }
    listView.end();

    window.end();
    window.show(argc,argv);
    Fl::run();
}
