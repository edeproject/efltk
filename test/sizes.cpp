#include <efltk/Fl_Widget.h>
#include <efltk/Fl_Browser.h>
#include <efltk/Fl_Button.h>
#include <efltk/Fl_Menu_Item.h>
#include <efltk/Fl_Check_Button.h>
#include <efltk/Fl_Light_Button.h>
#include <efltk/Fl_Return_Button.h>
#include <efltk/Fl_Menu_.h>
#include <efltk/Fl_Menu_Bar.h>
#include <efltk/Fl_Menu_Button.h>
#include <efltk/Fl_Choice.h>
#include <efltk/Fl_Adjuster.h>
#include <efltk/Fl_Clock.h>
#include <efltk/Fl_Group.h>
#include <efltk/Fl_Color_Chooser.h>
#include <efltk/Fl_Dial.h>
#include <efltk/Fl_Valuator.h>
#include <efltk/Fl_Value_Input.h>
#include <efltk/Fl_Value_Output.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Input.h>
#include <efltk/Fl_Output.h>
#include <efltk/Fl_Double_Window.h>
#include <efltk/Fl_Roller.h>
#include <efltk/Fl_Scroll.h>
#include <efltk/Fl_Slider.h>
#include <efltk/Fl_Scrollbar.h>
#include <efltk/Fl_Tabs.h>
#include <efltk/Fl_Style.h>
#include <efltk/Fl_Text_Buffer.h>
#include <efltk/Fl_Text_Display.h>
#include <efltk/Fl_Text_Editor.h>

#include <stdio.h>

int main() {
  printf("sizeof(Fl_Menu_Item) = %lu\n", (unsigned long)sizeof(struct Fl_Menu_Item));
  printf("sizeof(Fl_Style) = %lu\n", (unsigned long)sizeof(struct Fl_Style));
  printf("sizeof(Fl_Widget) = %lu\n", (unsigned long)sizeof(class Fl_Widget));
  printf("  sizeof(Fl_Box) = %lu\n", (unsigned long)sizeof(class Fl_Box));
  printf("  sizeof(Fl_Button) = %lu\n", (unsigned long)sizeof(class Fl_Button));
  printf("    sizeof(Fl_Light_Button) = %lu\n", (unsigned long)sizeof(class Fl_Light_Button));
  printf("      sizeof(Fl_Check_Button) = %lu\n", (unsigned long)sizeof(class Fl_Check_Button));
  printf("    sizeof(Fl_Return_Button) = %lu\n", (unsigned long)sizeof(class Fl_Return_Button));
  printf("  sizeof(Fl_Clock) = %lu\n", (unsigned long)sizeof(class Fl_Clock));
  printf("  sizeof(Fl_Group) = %lu\n", (unsigned long)sizeof(class Fl_Group));
  printf("    sizeof(Fl_Browser) = %lu\n", (unsigned long)sizeof(class Fl_Browser));
  printf("    sizeof(Fl_Color_Chooser) = %lu\n", (unsigned long)sizeof(class Fl_Color_Chooser));
  printf("    sizeof(Fl_Scroll) = %lu\n", (unsigned long)sizeof(class Fl_Scroll));
  printf("    sizeof(Fl_Tabs) = %lu\n", (unsigned long)sizeof(class Fl_Tabs));
  printf("    sizeof(Fl_Text_Display) = %lu\n", (unsigned long)sizeof(class Fl_Text_Display));
  printf("      sizeof(Fl_Text_Editor) = %lu\n", (unsigned long)sizeof(class Fl_Text_Editor));
  printf("    sizeof(Fl_Window) = %lu\n", (unsigned long)sizeof(class Fl_Window));
  printf("      sizeof(Fl_Double_Window) = %lu\n", (unsigned long)sizeof(class Fl_Double_Window));
  printf("  sizeof(Fl_Input) = %lu\n", (unsigned long)sizeof(class Fl_Input));
  printf("  sizeof(Fl_Output) = %lu\n", (unsigned long)sizeof(class Fl_Output));
  printf("  sizeof(Fl_Menu_) = %lu\n", (unsigned long)sizeof(class Fl_Menu_));
  printf("    sizeof(Fl_Choice) = %lu\n", (unsigned long)sizeof(class Fl_Choice));
  printf("    sizeof(Fl_Menu_Bar) = %lu\n", (unsigned long)sizeof(class Fl_Menu_Bar));
  printf("    sizeof(Fl_Menu_Button) = %lu\n", (unsigned long)sizeof(class Fl_Menu_Button));
  printf("  sizeof(Fl_Roller) = %lu\n", (unsigned long)sizeof(class Fl_Roller));
  printf("  sizeof(Fl_Text_Buffer) = %lu\n", (unsigned long)sizeof(class Fl_Text_Buffer));
  printf("  sizeof(Fl_Valuator) = %lu\n", (unsigned long)sizeof(class Fl_Valuator));
  printf("    sizeof(Fl_Adjuster) = %lu\n", (unsigned long)sizeof(class Fl_Adjuster));
  printf("    sizeof(Fl_Dial) = %lu\n", (unsigned long)sizeof(class Fl_Dial));
  printf("    sizeof(Fl_Slider) = %lu\n", (unsigned long)sizeof(class Fl_Slider));
  printf("      sizeof(Fl_Scrollbar) = %lu\n", (unsigned long)sizeof(class Fl_Scrollbar));
  printf("    sizeof(Fl_Value_Input) = %lu\n", (unsigned long)sizeof(class Fl_Value_Input));
  printf("    sizeof(Fl_Value_Output) = %lu\n", (unsigned long)sizeof(class Fl_Value_Output));

  printf("sizeof(Fl_String) = %lu\n", (unsigned long)sizeof(class Fl_String));
  return 0;
}
