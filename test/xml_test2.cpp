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
	Fl_XmlLocator my_locator;
    Fl_Window *win;

    ExampleHandler() { win=0; }
    virtual ~ExampleHandler() { if(win) delete win; }

	virtual void set_locator(Fl_XmlLocator **locator) { 
		*locator = &my_locator;
	}

    // Called after header of document parsed
    virtual void start_document()
    {
		//printf("start_document\n");

        win = new Fl_Window(300,300);
		win->resizable(win);
        win->begin();
        
		Fl_Browser *tree = new Fl_Browser(0,0,300,300);
		tree->layout_align(FL_ALIGN_CLIENT);
        tree->indented(1);
        tree->begin();
    }

    // Called when parsing a document finished
    virtual void end_document() {
        //printf("end_document\n");
        if(win) {
			win->end();
			win->show();
		}
    }

    // Called when parsing a processing instruction
	virtual void processing_instruction(const Fl_String &target, const Fl_String &data) { 
		//printf("processing_instruction\n");
	}

    // Called when start parsing a node
	virtual void start_node(const Fl_String &name, const Fl_XmlAttributes &attrs) { 

        //printf("start_node(%s)\n", nodename.c_str());
        Fl_Item_Group *g = new Fl_Item_Group();
        g->set_flag(FL_VALUE);

        Fl_String label = name;
        for(Fl_XmlAttributes::Iterator it(attrs); it.current(); it++) {
            label += " " + it.id() + "=\"" + it.value() + "\"";
        }

        g->label(label);
        g->begin();
    }

    // Called when parsing of a node was finished
    virtual void end_node(const Fl_String &name) {
		//printf("end_node(%s)\n", nodename.c_str());
        if(Fl_Group::current()) Fl_Group::current()->end();
    }

    // Called when a cdata section ended
	virtual void cdata(const Fl_String &cdata) { 
		//printf("cdata(%s)\n", cdata.c_str());
        Fl_Item *i = new Fl_Item();
		i->label(cdata);		
    }

    // Called when a comment section ended
    virtual void comment(const Fl_String &comment) { 
		//printf("comment(%s)\n", comment.c_str());
        Fl_Item_Group *g = new Fl_Item_Group("COMMENT");
        g->begin();
        Fl_Item *i = new Fl_Item();
        i->label(comment);
        g->end();
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

    try {

        int time1 = Fl::ticks();
        Fl_XmlParser::create_sax(h, fp);
        int time2 = Fl::ticks();

        Fl_String label;
        label.printf("XML Test - loaded file in %d ms", time2-time1);
        printf("%s\n", label.c_str());

		if(!h.win->label())
			h.win->label(label);

    } catch(Fl_Exception &exc) {
        fl_alert(exc.text());
    }

    fclose(fp);

    return Fl::run();
}

