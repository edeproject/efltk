#ifndef _FL_XML_NODELIST_H_
#define _FL_XML_NODELIST_H_

#include "../Fl_Ptr_List.h"

class Fl_XmlNode;

/**
 * The Fl_XmlNode_List interface provides the an ordered collection of nodes, 
 * The items in the NodeList are accessible via an integral index, starting from 0.
 */
class Fl_XmlNode_List : public Fl_Ptr_List {
public:
    Fl_XmlNode_List() : Fl_Ptr_List() { }

	Fl_XmlNode *item(unsigned index) const { return (Fl_XmlNode*)Fl_Ptr_List::item(index); }
	Fl_XmlNode *operator [](unsigned index) const { return (Fl_XmlNode *)items[index]; }

    void append(Fl_XmlNode *item) { Fl_Ptr_List::append((void *)item); }
    void prepend(Fl_XmlNode *item) { Fl_Ptr_List::prepend((void *)item); }
    void insert(uint pos, Fl_XmlNode *item) { Fl_Ptr_List::insert(pos, (void *)item); }
    void replace(uint pos, Fl_XmlNode *item) { Fl_Ptr_List::replace(pos, (void *)item); }
    void remove(uint pos) { Fl_Ptr_List::remove(pos); }
    bool remove(Fl_XmlNode *item) { return Fl_Ptr_List::remove((void *)item); }
    int index_of(const Fl_XmlNode *w) const { return Fl_Ptr_List::index_of((void*)w); }
    
	Fl_XmlNode **data() { return (Fl_XmlNode**)items; }

protected:
    void free_item(Fl_XmlNode *item);
};

#endif
