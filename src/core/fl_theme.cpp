/* fltk_theme.cxx

   This function is in a file by itself so that a program that statically
   links with fltk can customize it's theme by linking one of the theme
   plugins. Because the theme plugins define a function called fltk_theme()
   they will override this and cause fltk to call the plugin instead.
*/


#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <efltk/Fl.h>
#include <efltk/fl_load_plugin.h>
#include <efltk/Fl_Color.h>
#include <efltk/Fl_Font.h>
#include <efltk/Fl_Labeltype.h>
#include <efltk/Fl_Style.h>
#include <efltk/Fl_Widget.h>
#include <efltk/fl_draw.h>
#include <efltk/x.h>

#include <efltk/Fl_Config.h>

#ifndef _WIN32
#include <unistd.h>
#else
#include <io.h>
#define access(a,b) _access(a,b)
#define R_OK        04
#endif

#ifndef PATH_MAX
#define PATH_MAX 128
#endif

static Fl_Color grok_color(Fl_Config* cf, const char *colstr)
{
    char val[32];
    const char *p = colstr;
    if(!cf->get("aliases", colstr, val, 0, sizeof(val)))
        p = val;
    char *q;
    long l = strtoul(p, &q, 0);
    if(!*q) return (Fl_Color)l;
    return fl_rgb(p);
}

static Fl_Font grok_font(Fl_Config *cf, const char* fontstr)
{
    char val[80];
    const char *p = fontstr;
    if(!cf->get("aliases", fontstr, val, 0, sizeof(val)))
        p = val;

    char* q;
    long l = strtoul(p, &q, 0);
    if (!*q) return fl_fonts+l;

    return fl_find_font(p);
}

extern "C" bool fltk_theme()
{
    fl_get_system_colors();

    char temp[FL_PATH_MAX];

    const char* sfile = fl_find_config_file("schemes/Active.scheme", 0);
    if (!sfile) {
        fprintf(stderr, "Cannot find default scheme \"%s\"\n", sfile);
        return false;
    }

    static bool recurse=false;
    if (recurse) {
        fprintf(stderr, "%s recusively loaded scheme.theme\n", sfile);
        return false;
    }

    Fl_Config conf(sfile);
    conf.set_section("general");

    if(!conf.read("themes", temp, 0, sizeof(temp))) {
        recurse = true;
        Fl_Theme f = Fl_Style::load_theme(temp);
        if(f) f();
        else fprintf(stderr,"Unable to load %s theme\n", temp);
        recurse = false;
    }

    char valstr[80];
    Fl_Color col;

    conf.set_section("global colors");
    if(!conf.read("background", valstr, 0, sizeof(valstr))) {
        col = grok_color(&conf, valstr);
        fl_background(fl_get_color(col));
    }

    static struct { const char* key; Fl_Color col; } colors[] = {
        { "DARK1", FL_DARK1 },
        { "DARK2", FL_DARK2 },
        { "DARK3", FL_DARK3 },
        { "LIGHT1", FL_LIGHT1 },
        { "LIGHT2", FL_LIGHT2 },
        { "LIGHT3", FL_LIGHT3 },
        { 0, 0 }
    };

    for (int i = 0; colors[i].key; i++) {
        snprintf(temp, sizeof(temp)-1, "%s", colors[i].key);
        if(!conf.read(temp, valstr, 0, sizeof(valstr))) {
            col = grok_color(&conf, valstr);
            fl_set_color(colors[i].col, col);
        }
    }

    SectionList *section_list;
    Section *cent=0;

    Fl_Font font;
    Fl_Labeltype labeltype;
    Fl_Boxtype boxtype;

    section_list = conf.section_list("widgets");
    if(section_list) {
        for(cent = section_list->first(); cent; cent=section_list->next())
        {
            Fl_Style* style = Fl_Style::find(cent->name);
            if(!style) continue;

            conf.set_section(cent);

            // box around widget
            if(!conf.read("box", valstr, 0, sizeof(valstr))) {
                if( (boxtype = Fl_Boxtype_::find(valstr)) ) style->box = boxtype;
            }

            // box around buttons within widget
            if(!conf.read("button box", valstr, 0, sizeof(valstr))) {
                if ( (boxtype = Fl_Boxtype_::find(valstr)) ) style->button_box = boxtype;
            }

            // color of widget background
            if(!conf.read("color", valstr, 0, sizeof(valstr))) {
                style->color = grok_color(&conf, valstr);
            }

            // color of widget's label
            if(!conf.read("label color", valstr, 0, sizeof(valstr))) {
                style->label_color = grok_color(&conf, valstr);
            }

            // color of widget's background when widget is selected
            if(!conf.read("selection color", valstr, 0, sizeof(valstr))) {
                style->selection_color = grok_color(&conf, valstr);
            }

            // color of widget's text when text selected
            // color of widget's label when widget selected
            // color of widget's glyph when widget selected and no glyph box
            if(!conf.read("selection text color", valstr, 0, sizeof(valstr))) {
                style->selection_text_color = grok_color(&conf, valstr);
            }

            // color of widget's background when widget is highlighted
            if(!conf.read("highlight color", valstr, 0, sizeof(valstr))) {
                style->highlight_color = grok_color(&conf, valstr);
            }

            // color of widget's label when widget highlighted
            // color of widget's glyph/text when widget highlighted and no text/glyph box
            if(!conf.read("highlight label color", valstr, 0, sizeof(valstr))) {
                style->highlight_label_color = grok_color(&conf, valstr);
            }

            // color of text/glyph within widget
            if(!conf.read("text color", valstr, 0, sizeof(valstr))) {
                style->text_color = grok_color(&conf, valstr);
            }

            // font used for widget's label
            if(!conf.read("label font", valstr, 0, sizeof(valstr))) {
                if ( (font = grok_font(&conf, valstr)) ) style->label_font = font;
            }

            // font used for text within widget
            if(!conf.read("text font", valstr, 0, sizeof(valstr))) {
                if ( (font = grok_font(&conf, valstr)) ) style->text_font = font;
            }

            // type of widget's label
            if(!conf.read("label type", valstr, 0, sizeof(valstr))) {
                if ( (labeltype = Fl_Labeltype_::find(valstr)) ) style->label_type = labeltype;
            }

            // font size of widget's label
            if(!conf.read("label size", valstr, 0, sizeof(valstr))) {
                style->label_size = (int)strtol(valstr,0,0);
            }

            // font size of text within widget
            if(!conf.read("text size", valstr, 0, sizeof(valstr))) {
                style->text_size = (int)strtol(valstr,0,0);
            }

            // leading
            if(!conf.read("leading", valstr, 0, sizeof(valstr))) {
                style->leading = (int)strtol(valstr,0,0);
            }

            // font encoding
            static char encoding[128];
            if(!conf.read("font encoding", encoding, 0, sizeof(encoding))) {
                fl_encoding(encoding);
            }
        }
    }
    return true;
}
