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
    if(n->children()>0 || n->is_cdata_section() || n->is_comment()) {
        g = new Fl_Item_Group();
		g->user_data(n);
        g->begin();
        g->set_flag(FL_VALUE);
        w = (Fl_Widget*)g;
		if(n->is_cdata_section() || n->is_comment()) {
			w->label(n->name());
			Fl_Item *i = new Fl_Item();
			i->user_data(n);
			w = (Fl_Widget*)i;
		}
    } else {
        Fl_Item *i = new Fl_Item();
		i->user_data(n);
        w = (Fl_Widget*)i;
    }

    Fl_String label;
	const Fl_XmlAttributes &attr_map = n->attributes();

	switch(n->type()) 
	{
	case Fl_XmlNode::DOM_ELEMENT:
            label = n->name();
            if(n->has_attributes()) {
                for(Fl_XmlAttributes::Iterator it(attr_map); it.current(); it++) {
                    label += " " + it.id() + "=*" + it.value() + "*";
                }
            }
            break;

	case Fl_XmlNode::DOM_PI:
		label = n->name();
		label += ": ";
		label += n->value();
		break;

	case Fl_XmlNode::DOM_DOCUMENT:
		label = n->name();
		break;

	default:
		label = n->value();
		break;
	};

    w->label(label);

	if(n->has_child_nodes()) {
		for(unsigned a=0; a < n->children(); a++) {
			Fl_XmlNode *node = n->child(a);
			build_tree(node);
		}
	}

    if(w->is_group())
        ((Fl_Group*)w)->end();

	if(n->is_cdata_section() || n->is_comment())
		g->end();
}

Fl_XmlDoc *build_doc()
{
	Fl_XmlDoc *doc = new Fl_XmlDoc();	

	Fl_XmlNode *rootnode = doc->create_element("MyDocument");
	doc->append_child(rootnode);

	Fl_XmlNode *hello = doc->create_element("HelloTag");
	rootnode->append_child(hello);				

	Fl_XmlNode *text = doc->create_text("Hello all!");	
	hello->append_child(text);

	try {
		Fl_Buffer savebuffer;
		doc->save(savebuffer);
		savebuffer.save_file("MyML.xml");
	} catch(...) {
		Fl::warning("Error!");
	}

	return doc;
}

int main(int argc, char **argv)
{
    Fl_String f = argc>1 ? argv[1] : fl_select_file(0, "(X)(HT)ML files, *.{xml|htm*}, All, *");
    if(f.empty()) return -1;

    FILE *fp = fopen(f, "r");
    if(!fp) return -1;

	Fl_XmlDoc *doc = 0;
	bool html_mode = false;
	Fl_String ext = fl_file_getext(f);
	if(!strncmp(ext, "htm", 3))
	html_mode = true;

    Fl_Window *window = new Fl_Window(20,20,300,300);
	window->resizable(window);
    window->begin();
	Fl_XmlLocator locator;

	try {

        int time1 = Fl::ticks();
		//doc = build_doc();
		doc = Fl_XmlParser::create_dom(fp, &locator, html_mode);
        int time2 = Fl::ticks();

        Fl_String label;
        label.printf("XML Test - loaded file in %d ms", time2-time1);
        printf("%s\n", label.c_str());
        window->label(label);

        Fl_Browser *tree = new Fl_Browser(5,5,290,290);
        tree->indented(1);
        tree->begin();
		
        build_tree(doc);

        tree->end();
        tree->relayout();

    } catch(Fl_XmlException &exp) {

		Fl_String error;
		error += "\n------------------------\n";
		error += exp.text() + "\n";
        error += "\n------------------------\n";
        error += Fl_XmlLocator::error_line(f, *exp.locator()) + "\n";

        Fl_Input *i = new Fl_Input(10,30,280,260,"ERROR:");
		i->text_font(FL_COURIER);
        i->align(FL_ALIGN_TOP);
        i->input_type(Fl_Input::MULTILINE);
        i->value(error.c_str());
        i->position(i->size());
    }

    fclose(fp);
    window->end();
    window->show();

	try {
		Fl_Buffer savebuffer;
		doc->save(savebuffer);
		savebuffer.save_file("MyML.xml");
	} catch(...) {
		Fl::warning("Error!");
	}

    Fl::run();

    delete window;
    return 0;
}
