// generated by Fast Light User Interface Designer (fluid) version 2.0003

#ifndef image_loader_h
#define image_loader_h
#include <efltk/Fl.h>
#include <efltk/Fl_Double_Window.h>
#include <efltk/Fl_Box.h>
extern Fl_Box* imbox;
extern Fl_Box* filename_box;
#include <efltk/Fl_Group.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_File_Dialog.h>
#include <efltk/Fl_Divider.h>
#include <efltk/Fl_Choice.h>
extern Fl_Choice* filter_choice;
#include <efltk/Fl_Item.h>
#include <efltk/Fl_Value_Slider.h>
extern Fl_Value_Slider* Rslider;
extern Fl_Value_Slider* Gslider;
extern Fl_Value_Slider* Bslider;
#include <efltk/Fl_Check_Button.h>
extern Fl_Check_Button* lock;
Fl_Double_Window* make_window();
int main(int argc, char *argv[]);
void apply_cur_effect();
#endif