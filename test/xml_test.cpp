#include <efltk/xml/Fl_Xml.h>

#include <efltk/fl_ask.h>
#include <efltk/Fl.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Browser.h>
#include <efltk/Fl_File_Dialog.h>
#include <efltk/Fl_Item.h>
#include <efltk/Fl_Item_Group.h>

void build_tree(Fl_XmlNode *n)
{
    Fl_Widget *w=0;
    Fl_Item_Group *g=0;
    if(n->children()>0 || (n->type()!=FL_XML_TYPE_NODE && n->type()!=FL_XML_TYPE_LEAF)) {
        g = new Fl_Item_Group();
        g->begin();
        g->set_flag(FL_VALUE);
        w = (Fl_Widget*)g;
    } else {
        Fl_Item *i = new Fl_Item();
        w = (Fl_Widget*)i;
    }

    Fl_String label;
    switch(n->type()) {
    default: {
        label = n->name();
        AttrMap &attr_map = n->attributes();
        for(uint a=0; a<attr_map.size(); a++) {
            AttrMap_Pair *p = attr_map.item(a);
            label += " " + p->id + "=\"" + p->val + "\"";
        }
        break;
    }
    case FL_XML_TYPE_FIXED_CDATA: {
        w->label("Fixed cdata: ");
        w = (Fl_Widget*)new Fl_Item();
        label = n->context()->unXMLize(n->cdata());
        g->clear_flag(FL_VALUE); g->end();
        break;
    }

    case FL_XML_TYPE_CDATA: {
        w->label("Cdata: ");
        w = (Fl_Widget*)new Fl_Item();
        label = n->context()->unXMLize(n->cdata());
        g->clear_flag(FL_VALUE); g->end();
        break;
    }

    case FL_XML_TYPE_COMMENT: {
        w->label("Comment: ");
        w = (Fl_Widget*)new Fl_Item();
        label = n->context()->unXMLize(n->cdata());
        g->clear_flag(FL_VALUE); g->end();
        break;
    }
    }
    w->copy_label(label.c_str());

    for(int a=0; a<n->children(); a++) {
        Fl_XmlNode *node = n->child(a);
        build_tree(node);
    }

    if(g) g->end();
}

int main(int argc, char **argv)
{
    const char *f = fl_select_file(0, "XML files, *.xml");
    if(!f) return -1;

    FILE *fp = fopen(f, "r");
    if(!fp) return -1;

    Fl_XmlDoc doc;
    bool ret = doc.load(fp);
    fclose(fp);

    Fl_Window *window = new Fl_Window(20,20,300,300,"XML Test");
    window->begin();

    if(!ret) {
        Fl_String error = doc.context()->get_error();
        error += "\n------------------------\n";
        error += doc.context()->get_error_line(f) + "\n";

        Fl_Input *i = new Fl_Input(10,30,280,260,"ERROR:");
        i->input_type(Fl_Input::MULTILINE);
        i->wordwrap(1);
        i->value(error.c_str());
        i->position(i->size());

    } else {

        Fl_Browser *tree = new Fl_Browser(10,10,280,280);
        tree->indented(1);
        tree->begin();

        build_tree(&doc);

        tree->end();
        tree->relayout();
    }

    window->end();
    window->show();

    Fl::run();

    delete window;

    return 0;
}
