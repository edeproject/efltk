#include <efltk/xml/Fl_Xml.h>

#include <efltk/fl_ask.h>
#include <efltk/Fl.h>
#include <efltk/Fl_Exception.h>
#include <efltk/Fl_Window.h>
#include <efltk/Fl_Browser.h>
#include <efltk/Fl_File_Dialog.h>
#include <efltk/Fl_Item.h>
#include <efltk/Fl_Item_Group.h>

class ExampleHandler : public Fl_XmlHandler
{
public:
    Fl_Window *win;
    ExampleHandler() { win=0; }
    virtual ~ExampleHandler() { if(win) delete win; }

    // Called after header of document parsed
    virtual void start_document(Fl_String &dtd_type,
                                Fl_String &dtd_location,
                                Fl_String &dtd_uri)
    {
        Fl_String label = dtd_type + " " + dtd_location + " " + dtd_uri;
        win = new Fl_Window(300,300);
        win->copy_label(label.c_str());
        win->begin();
        Fl_Browser *tree = new Fl_Browser(10,10,280,280);
        tree->indented(1);
        tree->begin();
        //printf("start_document\n");
    }

    // Called when parsing a document finished
    virtual void end_document() {
        win->end();
        win->show();
        //printf("end_document\n");
    }

    // Called when parsing a processing instruction
    virtual void processing_instruction(Fl_XmlNode &/*pinode*/) {
        //printf("processing_instruction\n");
    }

    // Called when start parsing a node
    virtual void start_node(Fl_String &nodename) {
        Fl_Item_Group *g = new Fl_Item_Group();
        g->set_flag(FL_VALUE);
        g->copy_label(nodename.c_str());
        g->begin();
        //printf("start_node(%s)\n", nodename.c_str());
    }

    // Called when an attribute list was parsed
    virtual void parsed_attributes(Fl_String &/*nodename*/, AttrMap &attr_map) {
        Fl_Group *g = Fl_Group::current();
        Fl_String label = g->label();
        for(uint a=0; a<attr_map.size(); a++) {
            AttrMap_Pair *p = attr_map.item(a);
            label += " " + p->id + "=\"" + p->val + "\"";
        }
        g->copy_label(label.c_str());
        //printf("parsed_attributes\n");
    }

    // Called when parsing of a node was finished
    virtual void end_node(Fl_String &nodename) {
        Fl_Group::current()->end();
        //printf("end_node(%s)\n", nodename.c_str());
    }

    // Called when a cdata section ended
    virtual void cdata(Fl_String &cdata) {
        Fl_Item *i = new Fl_Item();
        i->copy_label(cdata.c_str());
        //printf("cdata(%s)\n", cdata.c_str());
    }

    // Called when a comment section ended
    virtual void comment(Fl_String &comment) {
        Fl_Item_Group *g = new Fl_Item_Group("COMMENT");
        g->begin();
        Fl_Item *i = new Fl_Item();
        i->copy_label(comment.c_str());
        g->end();
        //printf("comment(%s)\n", comment.c_str());
    }
};

int main(int argc, char *argv[])
{
#ifndef _WIN32
    const char *f = argc>1 ? argv[1] : "test.xml";
#else
    const char *f = fl_select_file(0, "XML files, *.xml");
    if(!f) return -1;
#endif
    FILE *fp = fopen(f, "r");
    if(!fp) return -1;

    ExampleHandler h;
    Fl_XmlDoc d;
    d.context()->handler(&h, false);

    fl_try {

        int time1 = Fl::ticks();
        d.load(fp);
        int time2 = Fl::ticks();

        Fl_String label;
        label.printf("XML Test - loaded file in %d ms", time2-time1);
        printf("%s\n", label.c_str());

        if(h.win) h.win->copy_label(label.c_str());

    } fl_catch(exc) {
        fl_alert(exc.text());
    }

    fclose(fp);

    return Fl::run();
}

