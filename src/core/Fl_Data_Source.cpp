// Fl_Data_Source.cpp by Alexey Parshin, 2002-10-26

#include <efltk/Fl_Data_Source.h>
#include <efltk/Fl_Widget.h>
#include <efltk/Fl_Group.h>

bool Fl_Data_Source::load() {
   if (!parent_ || !load_data()) return false;
   for (int i = 0; i < parent_->children(); i++) {
      Fl_Widget *widget = parent_->child(i);
      if (widget->field_name()) {
         read_field(widget->field_name());
      }         
   }
   return true; 
}

bool Fl_Data_Source::save() { 
   if (!parent_ || !save_data()) return false;
   for (int i = 0; i < parent_->children(); i++) {
      Fl_Widget *widget = parent_->child(i);
      if (widget->field_name()) {
         write_field(widget->field_name());
      }         
   } 
   return true; 
}
