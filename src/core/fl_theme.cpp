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
    char *val=0;
    const char *p = colstr;
    val = cf->read_string("aliases", colstr);
    if(val) p = val;
    char* q;
    long l = strtoul(p, &q, 0);
    if(!*q) return (Fl_Color)l;
    //if(val) delete []val; //LEAK!!
    return fl_rgb(p);
}

static Fl_Font grok_font(Fl_Config *cf, const char* fontstr)
{
    char *val;
    const char *p = fontstr;
    val = cf->read_string("aliases", fontstr);
    if(val) p = val;
    char* q;
    long l = strtoul(p, &q, 0);
    if(!*q) return fl_fonts+l;
    //if(val) delete []val; //LEAK!!
    return fl_find_font(p);
}


extern "C" bool fltk_theme()
{
    fl_get_system_colors();

    char temp[PATH_MAX];

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

    char *themefile = conf.read_string("general", "themes");
    if(themefile && !conf.error())
    {
        recurse = true;
        Fl_Theme f = Fl_Style::load_theme(themefile);
        if(f) f();
        else fprintf(stderr,"Unable to load %s theme\n", themefile);
        recurse = false;
        delete []themefile;
    }

    char *valstr;
    Fl_Color col;

    valstr = conf.read_string("global colors", "background");
    if(valstr && !conf.error()) {
        col = grok_color(&conf, valstr);
        fl_background(fl_get_color(col));
        delete []valstr;
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
        valstr = conf.read_string("global colors", temp);
        int res = conf.error();
        if(!res && valstr) {
            col = grok_color(&conf, valstr);
            fl_set_color(colors[i].col, col);
            delete []valstr;
        }
    }

    SectionList *section_list;
    Section *cent=0;

    Fl_Font font;
    Fl_Labeltype labeltype;
    Fl_Boxtype boxtype;

    section_list = conf.section_list("widgets");
    if(section_list)
    {
        for(cent = section_list->first(); cent; cent=section_list->next())
        {
            Fl_Style* style = Fl_Style::find(cent->name);
            if(!style) continue;

            conf.set_section(cent);

            // box around widget
            if( (valstr=conf.read_string("box")) ) {
                if ( (boxtype = Fl_Boxtype_::find(valstr)) ) style->box = boxtype;
                delete []valstr;
            }

            // box around buttons within widget
            if( (valstr=conf.read_string("button box")) ) {
                if ( (boxtype = Fl_Boxtype_::find(valstr)) ) style->button_box = boxtype;
                delete []valstr;
            }

            // color of widget background
            if( (valstr=conf.read_string("color")) ) {
                style->color = grok_color(&conf, valstr);
                delete []valstr;
            }

            // color of widget's label
            if( (valstr=conf.read_string("label color")) ) {
                style->label_color = grok_color(&conf, valstr);
                delete []valstr;
            }

            // color of widget's background when widget is selected
            if( (valstr=conf.read_string("selection color" )) ) {
                style->selection_color = grok_color(&conf, valstr);
                delete []valstr;
            }

            // color of widget's text when text selected
            // color of widget's label when widget selected
            // color of widget's glyph when widget selected and no glyph box
            if( (valstr=conf.read_string("selection text color")) ) {
                style->selection_text_color = grok_color(&conf, valstr);
                delete []valstr;
            }

            // color of widget's background when widget is highlighted
            if( (valstr=conf.read_string("highlight color" ))) {
                style->highlight_color = grok_color(&conf, valstr);
                delete []valstr;
            }

            // color of widget's label when widget highlighted
            // color of widget's glyph/text when widget highlighted and no text/glyph box
            if( (valstr=conf.read_string("highlight label color" ))) {
                style->highlight_label_color = grok_color(&conf, valstr);
                delete []valstr;
            }

            // color of text/glyph within widget
            if( (valstr=conf.read_string("text color")) ) {
                style->text_color = grok_color(&conf, valstr);
                delete []valstr;
            }

            // font used for widget's label
            if( (valstr=conf.read_string("label font")) ) {
                if ( (font = grok_font(&conf, valstr)) ) style->label_font = font;
                delete []valstr;
            }

            // font used for text within widget
            if( (valstr=conf.read_string("text font" )) ) {
                if ( (font = grok_font(&conf, valstr)) ) style->text_font = font;
                delete []valstr;
            }

            // type of widget's label
            if( (valstr=conf.read_string("label type" )) ) {
                if ( (labeltype = Fl_Labeltype_::find(valstr)) ) style->label_type = labeltype;
                delete []valstr;
            }

            // font size of widget's label
            if( (valstr=conf.read_string("label size")) ) {
                style->label_size = (int)strtol(valstr,0,0);
                delete []valstr;
            }

            // font size of text within widget
            if( (valstr=conf.read_string("text size")) ) {
                style->text_size = (int)strtol(valstr,0,0);
                delete []valstr;
            }

            // leading
            if( (valstr=conf.read_string("leading")) ) {
                style->leading = (int)strtol(valstr,0,0);
                delete []valstr;
            }

            // font encoding
            if( (valstr=conf.read_string("font encoding")) ) {
                fl_encoding(valstr);
                //delete []valstr; //LEAK??
            }

        }
    }
    return true;    
}
