// generated by Extended Fast Light User Interface Designer (eFluid) version 2.0003

#include "widget_panel.h"

Fl_Tabs* panel_tabs;
Fl_Box* image_label;
Fl_Check_Button* include_image_button;
Fl_Value_Input* widget_x;
Fl_Value_Input* widget_y;
Fl_Value_Input* widget_width;
Fl_Value_Input* widget_height;
Fl_Check_Button* set_xy;
Fl_Text_Editor* extra_code_input;
Fl_Check_Button* overlaybutton;

Fl_Window* make_widget_panel() {
  Fl_Window* w;
   {Fl_Window* o = new Fl_Window(380, 405);
    w = o;
    o->shortcut(0xff1b);
     {Fl_Tabs* o = panel_tabs = new Fl_Tabs(0, 3, 380, 353);
      o->color((Fl_Color)0xfffffffe);
      o->callback((Fl_Callback*)propagate_tabs);
       {Fl_Group* o = new Fl_Group(1, 24, 378, 328, _("GUI"));
        o->callback((Fl_Callback*)propagate_group);
         {Fl_Input* o = new Fl_Input(80, 8, 176, 22, _("Class"));
          o->callback((Fl_Callback*)user_class_cb, (void*)(4));
          o->when(FL_WHEN_CHANGED);
          o->tooltip(_("This allows you to name a user-defined class that this widget is an instance \
of, rather than an fltk built-in class. You will need to add a #include declar\
ation so that the definition of your class is included in the fluid output."));
        }
         {Fl_Choice* o = new Fl_Choice(256, 8, 109, 22); o->begin();
          o->callback((Fl_Callback*)subtype_cb);
          o->tooltip(_("Selects a value for type() for this widget"));
          o->end();
        }
         {Fl_Input* o = new Fl_Input(80, 31, 285, 22, _("Label"));
          o->callback((Fl_Callback*)label_cb);
          o->when(FL_WHEN_CHANGED);
          o->tooltip(_("Text displayed on or next to the widget"));
          o->take_focus();
        }
         {Fl_Box* o = image_label = new Fl_Box(9, 55, 71, 22, _("Image"));
          o->align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
        }
         {Fl_Button* o = new Fl_Button(80, 54, 215, 22, _("Image name"));
          o->box(FL_DOWN_BOX);
          o->color((Fl_Color)7);
          o->callback((Fl_Callback*)image_cb);
          o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
          o->tooltip(_("Select an image to label the widget"));
        }
         {Fl_Check_Button* o = include_image_button = new Fl_Check_Button(300, 54, 72, 22, _("inline"));
          o->label_size(10);
          o->callback((Fl_Callback*)image_inlined_cb);
          o->tooltip(_("The image data is inserted as inline data into the output C++ code, rather th\
an generating code to read the image file."));
        }
         {Fl_Box* o = new Fl_Box(10, 77, 70, 22, _("Alignment"));
          o->align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
        }
         {Fl_Button* o = new Fl_Button(80, 79, 20, 20, _("@-1<-"));
          o->type(Fl_Button::TOGGLE);
          o->label_type(FL_SYMBOL_LABEL);
          o->callback((Fl_Callback*)align_cb, (void*)(FL_ALIGN_LEFT));
          o->tooltip(_("Places label on the left of the widget"));
        }
         {Fl_Button* o = new Fl_Button(100, 79, 21, 20, _("@-1->"));
          o->type(Fl_Button::TOGGLE);
          o->label_type(FL_SYMBOL_LABEL);
          o->callback((Fl_Callback*)align_cb, (void*)(FL_ALIGN_RIGHT));
          o->tooltip(_("Places label on the right of the widget"));
        }
         {Fl_Button* o = new Fl_Button(121, 79, 21, 20, _("@-18"));
          o->type(Fl_Button::TOGGLE);
          o->label_type(FL_SYMBOL_LABEL);
          o->callback((Fl_Callback*)align_cb, (void*)(FL_ALIGN_TOP));
          o->tooltip(_("Places label on the top of the widget"));
        }
         {Fl_Button* o = new Fl_Button(142, 79, 20, 20, _("@-12"));
          o->type(Fl_Button::TOGGLE);
          o->label_type(FL_SYMBOL_LABEL);
          o->callback((Fl_Callback*)align_cb, (void*)(FL_ALIGN_BOTTOM));
          o->tooltip(_("Places label on the bottom of the widget"));
        }
         {Fl_Button* o = new Fl_Button(165, 79, 45, 20, _("inside"));
          o->type(Fl_Button::TOGGLE);
          o->label_type(FL_SYMBOL_LABEL);
          o->callback((Fl_Callback*)align_cb, (void*)(FL_ALIGN_INSIDE));
          o->tooltip(_("Places label inside the widget"));
        }
         {Fl_Button* o = new Fl_Button(210, 79, 40, 20, _("clip"));
          o->type(Fl_Button::TOGGLE);
          o->callback((Fl_Callback*)align_cb, (void*)(FL_ALIGN_CLIP));
          o->tooltip(_("Turn on clipping to the widget\'s area when drawing label.  This is slower so\
 it should be left off if label will fit"));
        }
         {Fl_Button* o = new Fl_Button(250, 79, 40, 20, _("wrap"));
          o->type(Fl_Button::TOGGLE);
          o->callback((Fl_Callback*)align_cb, (void*)(FL_ALIGN_WRAP));
          o->tooltip(_("Word-wrap the label"));
        }
         {Fl_Value_Input* o = widget_x = new Fl_Value_Input(80, 125, 57, 22, _("x"));
          o->label_size(10);
          o->maximum(2000);
          o->step(1);
          o->value(10);
          o->callback((Fl_Callback*)x_cb);
          o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
          o->tooltip(_("The x coordinate of the widget."));
        }
         {Fl_Value_Input* o = widget_y = new Fl_Value_Input(137, 125, 57, 22, _("y"));
          o->label_size(10);
          o->maximum(2000);
          o->step(1);
          o->value(10);
          o->callback((Fl_Callback*)y_cb);
          o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
          o->tooltip(_("The y coordinate of the widget."));
        }
         {Fl_Value_Input* o = widget_width = new Fl_Value_Input(194, 125, 57, 22, _("w"));
          o->label_size(10);
          o->maximum(2000);
          o->step(1);
          o->value(10);
          o->callback((Fl_Callback*)width_cb);
          o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
          o->tooltip(_("The width of the widget."));
        }
         {Fl_Value_Input* o = widget_height = new Fl_Value_Input(251, 125, 57, 22, _("h"));
          o->label_size(10);
          o->maximum(2000);
          o->step(1);
          o->value(10);
          o->callback((Fl_Callback*)height_cb);
          o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
          o->tooltip(_("The height of the widget."));
        }
         {Fl_Check_Button* o = new Fl_Check_Button(80, 150, 100, 22, _("Border"));
          o->callback((Fl_Callback*)border_cb);
          o->tooltip(_("Enable the window manager border"));
        }
         {Fl_Check_Button* o = set_xy = new Fl_Check_Button(180, 150, 100, 22, _("Set xy"));
          o->callback((Fl_Callback*)set_xy_cb);
          o->tooltip(_("Window will use this x,y rather than being positioned by the operating system\
."));
        }
         {Fl_Check_Button* o = new Fl_Check_Button(80, 175, 100, 22, _("Modal"));
          o->callback((Fl_Callback*)modal_cb);
          o->tooltip(_("This window will stay on top of others in the application and will block even\
ts from going to other windows until it is hidden or closed."));
        }
         {Fl_Check_Button* o = new Fl_Check_Button(180, 175, 100, 22, _("Child"));
          o->callback((Fl_Callback*)non_modal_cb);
          o->tooltip(_("This window will stay on top of others in the application."));
        }
         {Fl_Value_Input* o = new Fl_Value_Input(80, 150, 90, 22, _("value"));
          o->label_size(10);
          o->callback((Fl_Callback*)value_cb);
          o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
          o->tooltip(_("The initial value of this widget"));
        }
         {Fl_Value_Input* o = new Fl_Value_Input(175, 150, 90, 22, _("min"));
          o->label_size(10);
          o->callback((Fl_Callback*)min_cb);
          o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
          o->tooltip(_("The minimum value for this valuator"));
        }
         {Fl_Value_Input* o = new Fl_Value_Input(270, 150, 100, 22, _("max"));
          o->label_size(10);
          o->value(1);
          o->callback((Fl_Callback*)max_cb);
          o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
          o->tooltip(_("The maximum value for this valuator"));
        }
         {Fl_Value_Input* o = new Fl_Value_Input(80, 175, 90, 22, _("step"));
          o->label_size(10);
          o->callback((Fl_Callback*)step_cb);
          o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
          o->tooltip(_("step:\nRound all movements to multiples of this.\n"));
        }
         {Fl_Value_Input* o = new Fl_Value_Input(175, 175, 90, 22, _("line"));
          o->label_size(10);
          o->minimum(1);
          o->step(1);
          o->callback((Fl_Callback*)line_cb);
          o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
          o->tooltip(_("linesize:\nIncrement/decrement for arrow keys."));
        }
         {Fl_Value_Input* o = new Fl_Value_Input(270, 175, 100, 22, _("size"));
          o->label_size(10);
          o->callback((Fl_Callback*)slider_size_cb);
          o->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
          o->tooltip(_("The size of the scroller"));
          o->step(0.01);
        }
         {Fl_Group* o = new Fl_Group(75, 202, 300, 40, _("Attributes"));
          o->callback((Fl_Callback*)propagate_group);
          o->align(FL_ALIGN_LEFT);
           {Fl_Check_Button* o = new Fl_Check_Button(0, 0, 145, 20, _("Resizable"));
            o->callback((Fl_Callback*)resizable_cb);
            o->tooltip(_("If on, this widget and all it\'s parents are resizable.  When the parent resi\
zes it moves/resizes all it\'s children so that this widget\'s edges remain th\
e same distance from all four sides of the parent.  If this is off this widget\
 will not resize, unless it overlaps a resizable sibling."));
          }
           {Fl_Check_Button* o = new Fl_Check_Button(170, 0, 120, 20, _("Hotspot"));
            o->callback((Fl_Callback*)hotspot_cb);
            o->tooltip(_("Positions the window so this widget is under the mouse.  This is done when sh\
ow() is called."));
          }
           {Fl_Check_Button* o = new Fl_Check_Button(0, 20, 150, 20, _("Visible"));
            o->callback((Fl_Callback*)visible_cb);
            o->tooltip(_("If unchecked the widget is initially invisible."));
          }
           {Fl_Check_Button* o = new Fl_Check_Button(170, 20, 120, 20, _("Active"));
            o->callback((Fl_Callback*)active_cb);
            o->tooltip(_("If unchecked the widget is initially inactive (disabled, grayed out)."));
          }
          o->end();
        }
         {Shortcut_Button* o = new Shortcut_Button(75, 245, 294, 22, _("Shortcut"));
          o->box(FL_DOWN_BOX);
          o->color((Fl_Color)7);
          o->callback((Fl_Callback*)shortcut_in_cb);
          o->align(FL_ALIGN_LEFT);
          o->tooltip(_("To set a shortcut:\n   Click here, then type the key combination you want.\nT\
o delete the shortcut:\n   Click here, then type backspace.\nTo get out of sho\
rtcut-setting mode:\n   Click the mouse on this again, or on some other field."));
        }
         {Fl_Wordwrap_Input* o = new Fl_Wordwrap_Input(75, 272, 294, 51, _("Tooltip"));
          o->type(20);
          o->color((Fl_Color)0xffffe100);
          o->callback((Fl_Callback*)tooltip_cb);
          o->tooltip(_("The pop up tooltip which should be used for the widget."));
        }
         {Fl_Box* o = new Fl_Box(5, 272, 370, 55, _("resizable"));
          o->hide();
          o->deactivate();
          o->parent()->resizable(o);
        }
         {Fl_Box* o = new Fl_Box(10, 125, 70, 22, _("Dimensions"));
          o->align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
        }
         {Fl_Button* o = new Fl_Button(290, 79, 40, 20, _("tile"));
          o->type(Fl_Button::TOGGLE);
          o->callback((Fl_Callback*)align_cb, (void*)(FL_ALIGN_TILED));
          o->tooltip(_("Tile image"));
        }
         {Fl_Button* o = new Fl_Button(330, 79, 40, 20, _("scale"));
          o->type(Fl_Button::TOGGLE);
          o->callback((Fl_Callback*)align_cb, (void*)(FL_ALIGN_SCALE));
          o->tooltip(_("Scale image"));
        }
         {Fl_Choice* o = new Fl_Choice(80, 101, 175, 22, _("Layout")); o->begin();
          o->callback((Fl_Callback*)layoutalign_cb);
          o->tooltip(_("Change the layout align"));
          o->end();
        }
         {Fl_Value_Input* o = new Fl_Value_Input(315, 101, 55, 22, _("Spacing"));
          o->maximum(50);
          o->step(1);
          o->value(1);
          o->callback((Fl_Callback*)layoutspacing_cb);
        }
        o->parent()->resizable(o);
        o->end();
      }
       {Fl_Group* o = new Fl_Group(1, 24, 378, 328, _("Style"));
        o->callback((Fl_Callback*)propagate_group);
        o->hide();
         {Fl_Choice* o = new Fl_Choice(100, 10, 250, 23, _("box")); o->begin();
          o->callback((Fl_Callback*)box_cb);
          o->tooltip(_("Type of box to draw around the widget."));
          o->end();
        }
         {Fl_Light_Button* o = new Fl_Light_Button(100, 33, 125, 23, _("Color"));
          o->label_size(10);
          o->callback((Fl_Callback*)color_cb);
          o->tooltip(_("Color of the widget."));
          o->type(0);
        }
         {Fl_Light_Button* o = new Fl_Light_Button(225, 33, 125, 23, _("Highlight Color"));
          o->label_size(10);
          o->callback((Fl_Callback*)highlight_color_cb);
          o->tooltip(_("Color to use to draw the widget highlighted.  Use color zero (the black top-l\
eft chip in the color chooser) to disable highlighting."));
          o->type(0);
        }
         {Fl_Choice* o = new Fl_Choice(100, 63, 250, 23, _("Button box")); o->begin();
          o->callback((Fl_Callback*)button_box_cb);
          o->tooltip(_("Type of box to draw around buttons that are in the widget."));
          o->end();
        }
         {Fl_Light_Button* o = new Fl_Light_Button(100, 86, 125, 23, _("Button Color"));
          o->label_size(10);
          o->callback((Fl_Callback*)button_color_cb);
          o->tooltip(_("Color to draw buttons inside the widget."));
          o->type(0);
        }
         {Fl_Light_Button* o = new Fl_Light_Button(225, 86, 125, 23, _("Selection Color"));
          o->label_size(10);
          o->callback((Fl_Callback*)selection_color_cb);
          o->tooltip(_("Color to draw behind selected text, or to color in buttons that are turned on\
."));
          o->type(0);
        }
         {Fl_Choice* o = new Fl_Choice(100, 117, 250, 22, _("Focus box")); o->begin();
          o->callback((Fl_Callback*)focus_box_cb);
          o->tooltip(_("Type of box to draw around widget that are focused"));
          o->end();
        }
         {Fl_Choice* o = new Fl_Choice(100, 147, 250, 23, _("Label Type")); o->begin();
          o->callback((Fl_Callback*)label_type_cb);
          o->tooltip(_("How to draw the label"));
          o->end();
        }
         {Fl_Choice* o = new Fl_Choice(100, 170, 190, 23, _("Label Font")); o->begin();
          o->callback((Fl_Callback*)label_font_cb);
          o->tooltip(_("Font to use for the label"));
          o->end();
        }
         {Fl_Value_Input* o = new Fl_Value_Input(290, 170, 60, 23);
          o->maximum(100);
          o->step(1);
          o->value(14);
          o->callback((Fl_Callback*)label_size_cb);
          o->when(FL_WHEN_ENTER_KEY);
          o->tooltip(_("Size of the font to use for the label"));
        }
         {Fl_Light_Button* o = new Fl_Light_Button(100, 193, 125, 23, _("Label Color"));
          o->label_size(10);
          o->callback((Fl_Callback*)label_color_cb);
          o->tooltip(_("Color to draw the label"));
          o->type(0);
        }
         {Fl_Light_Button* o = new Fl_Light_Button(225, 193, 125, 23, _("Highlight Label Color"));
          o->label_size(10);
          o->callback((Fl_Callback*)highlight_label_color_cb);
          o->tooltip(_("Color to draw the label when the widget is highlighted.  Use color zero (the \
black top-left chip in the color chooser) to leave the label colors unchanged."));
          o->type(0);
        }
         {Fl_Choice* o = new Fl_Choice(100, 227, 190, 23, _("Text Font")); o->begin();
          o->callback((Fl_Callback*)text_font_cb);
          o->tooltip(_("Font to use for text displayed inside the widget"));
          o->end();
        }
         {Fl_Value_Input* o = new Fl_Value_Input(290, 227, 60, 23);
          o->maximum(100);
          o->step(1);
          o->value(14);
          o->callback((Fl_Callback*)text_size_cb);
          o->when(FL_WHEN_ENTER_KEY);
          o->tooltip(_("Size of the font to use for text displayed inside the widget"));
        }
         {Fl_Light_Button* o = new Fl_Light_Button(100, 250, 125, 23, _("Text Color"));
          o->label_size(10);
          o->callback((Fl_Callback*)text_color_cb);
          o->tooltip(_("Color to draw text displayed inside the widget"));
          o->type(0);
        }
         {Fl_Light_Button* o = new Fl_Light_Button(225, 250, 125, 23, _("Selected Text Color"));
          o->label_size(10);
          o->callback((Fl_Callback*)selected_text_color_cb);
          o->tooltip(_("Color to draw selected text inside the widget"));
          o->type(0);
        }
         {Fl_Button* o = new Fl_Button(5, 300, 124, 23, _("Reset to default"));
          o->callback((Fl_Callback*)default_cb);
          o->tooltip(_("Reset all the above items to the default values for this widget class."));
        }
         {Fl_Box* o = new Fl_Box(135, 277, 215, 25);
          o->hide();
          o->parent()->resizable(o);
        }
        o->end();
      }
       {Fl_Group* o = new Fl_Group(1, 24, 378, 328, _("C++"));
        o->callback((Fl_Callback*)propagate_group);
        o->hide();
         {Fl_Input* o = new Fl_Input(90, 8, 200, 22, _("Name"));
          o->callback((Fl_Callback*)name_cb);
          o->when(FL_WHEN_CHANGED);
          o->tooltip(_("The variable or member name in which to store a pointer to this widget."));
        }
         {Fl_Check_Button* o = new Fl_Check_Button(295, 8, 70, 22, _("public"));
          o->label_size(10);
          o->callback((Fl_Callback*)name_public_cb);
          o->tooltip(_("Make the variable public"));
        }
         {Fl_Text_Editor* o = extra_code_input = new Fl_Text_Editor(90, 35, 275, 110, _("Extra Code"));
          o->callback((Fl_Callback*)extra_code_input_cb, (void*)(0));
          o->tooltip(_("Extra code to be exectuted after the widget is created. The variable \"o\" po\
ints at the widget."));
          Fl_Text_Buffer *buf = new Fl_Text_Buffer; o->buffer(buf);
          o->align(FL_ALIGN_LEFT);
        }
         {Fl_Text_Editor* o = new Fl_Text_Editor(90, 151, 275, 110, _("Callback"));
          o->callback((Fl_Callback*)callback_cb);
          o->tooltip(_("The name of the callback function, or code body of the callback function"));
          Fl_Text_Buffer *buf = new Fl_Text_Buffer; o->buffer(buf);
          o->align(FL_ALIGN_LEFT);
        }
         {Fl_Input* o = new Fl_Input(90, 271, 135, 22, _("User Data"));
          o->callback((Fl_Callback*)user_data_cb);
          o->tooltip(_("Value passed as the second argument to the callback.  This must be of the typ\
e given below."));
        }
         {Fl_Choice* o = new Fl_Choice(275, 271, 90, 22, _("When")); o->begin();
          o->callback((Fl_Callback*)when_cb);
          o->when(FL_WHEN_NEVER);
          o->tooltip(_("What actions cause the callback to be called."));
          o->end();
        }
         {Fl_Input* o = new Fl_Input(90, 296, 135, 22, _("Type"));
          o->callback((Fl_Callback*)user_data_type_cb);
          o->tooltip(_("Type of User Data. This must be \"long\" or a pointer."));
        }
         {Fl_Box* o = new Fl_Box(50, 107, 165, 80, _("resizable"));
          o->hide();
          o->deactivate();
          o->parent()->resizable(o);
        }
        o->end();
      }
      o->parent()->resizable(o);
      o->end();
    }
     {Fl_Group* o = new Fl_Group(0, 373, 380, 32);
       {Fl_Check_Button* o = overlaybutton = new Fl_Check_Button(5, 5, 230, 22, _("&Overlays"));
        o->callback((Fl_Callback*)overlay_cb);
        o->tooltip(_("Turns the overlays (red outlines) off so you can see the edges better."));
        o->value(!overlays_invisible);
        o->parent()->resizable(o);
      }
       {Fl_Button* o = new Fl_Button(310, 4, 65, 23, _("&Cancel"));
        o->callback((Fl_Callback*)cancel_cb);
      }
       {Fl_Button* o = new Fl_Button(240, 4, 65, 23, _("&OK"));
        o->callback((Fl_Callback*)ok_cb);
        o->tooltip(_("Closes this attribute window"));
      }
      o->end();
    }
     {Fl_Divider* o = new Fl_Divider(0, 356, 380, 20, _("label"));
      o->color((Fl_Color)49);
    }
    o->window_type(Fl_WM::UTIL);
    o->size_range(o->w(), o->h());
    o->end();
    o->resizable(o);
  }
  return w;
}
