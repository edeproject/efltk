#include <efltk/xml/Fl_Xml.h>

#include <efltk/fl_ask.h>
#include <efltk/Fl.h>
#include <efltk/Fl_Exception.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Browser.h>
#include <efltk/Fl_File_Dialog.h>
#include <efltk/Fl_Item.h>
#include <efltk/Fl_Item_Group.h>

void build_tree(Fl_XmlNode *n)
{
    if(!n) return;

    Fl_Widget *w=0;
    Fl_Item_Group *g=0;
    if(n->children()>0) {
        g = new Fl_Item_Group();
        g->begin();
        g->set_flag(FL_VALUE);
        w = (Fl_Widget*)g;
    } else {
        Fl_Item *i = new Fl_Item();
        w = (Fl_Widget*)i;
    }

    Fl_String label;
    uint a;

    if(n->has_cdata()) {
        label = n->context()->unXMLize(n->cdata());
    } else {
        label = n->name();
        AttrMap &attr_map = n->attributes();
        for(a=0; a<attr_map.size(); a++) {
            AttrMap_Pair *p = attr_map.item(a);
            label += " " + p->id + "=\"" + p->val + "\"";
        }
    }

    w->copy_label(label.c_str());

    for(a=0; a<(uint)n->children(); a++) {
        Fl_XmlNode *node = n->child(a);
        build_tree(node);
    }

    if(w->is_group())
        ((Fl_Group*)w)->end();
}

int main(int argc, char **argv)
{
    const char *f = argc>1 ? argv[1] : fl_select_file(0, "XML files, *.xml");
    if(!f) return -1;

    FILE *fp = fopen(f, "r");
    if(!fp) return -1;

    Fl_XmlDoc doc;

    Fl_Window *window = new Fl_Window(20,20,300,300);
    window->begin();

    try {

        int time1 = Fl::ticks();
        doc.load(fp);
        int time2 = Fl::ticks();

        Fl_String label;
        label.printf("XML Test - loaded file in %d ms", time2-time1);
        printf("%s\n", label.c_str());
        window->copy_label(label.c_str());

        Fl_Browser *tree = new Fl_Browser(10,10,280,280);
        tree->indented(1);
        tree->begin();
		
        build_tree(doc.root_node());

        tree->end();
        tree->relayout();

    } catch(Fl_Exception &exp) {

        Fl_String error = doc.context()->get_error();
        error += "\n------------------------\n";
        error += doc.context()->get_error_line(f) + "\n";

        Fl_Input *i = new Fl_Input(10,30,280,260,"ERROR:");
        i->align(FL_ALIGN_TOP);
        i->input_type(Fl_Input::MULTILINE);
        i->value(error.c_str());
        i->position(i->size());
    }

    fclose(fp);
    window->end();
    window->show();

    Fl::run();

    delete window;
    return 0;
}
