#include <efltk/Fl_Config_Dialog_DS.h>
#include <efltk/Fl_Group.h>

bool Fl_Config_Dialog_DS::load_data() 
{ 
    if (!m_config)
        return true;

	if (!m_widgetsScanned) scan_widgets();

	// parent() == Fl_Tabs from dialog - ALWAYS!
	for(int n=0; n<parent()->children(); n++) 
	{
		Fl_Group *g = (Fl_Group*)parent()->child(n);
		// Set section to TAB label
		m_config->set_section(g->label());
		
		for(int m=0; m<g->children(); m++) 
		{
			// Read all entrys
			Fl_Widget *w = g->child(m);
			if(!w->field_name().empty()) {
				Fl_String val;
				m_config->read(w->field_name(), val, "");
				(*this)[w->field_name()] = val;
			}
		}
	}
	return true;
}

bool Fl_Config_Dialog_DS::save_data() 
{ 
    if (!m_config)
        return true; 

	if (!m_widgetsScanned) scan_widgets();

	for(int n=0; n<parent()->children(); n++) 
	{
		Fl_Group *g = (Fl_Group*)parent()->child(n);

		// Set section
		m_config->set_section(g->label());
		
		for(int m=0; m<g->children(); m++) 
		{
			// Write all entrys
			Fl_Widget *w = g->child(m);
			if(!w->field_name().empty()) {
				Fl_Variant var;
				if(read_field(w->field_name(), var)) {
					m_config->write(w->field_name(), var.as_string());
				}
			}
		}
	}
	// Sync to file
	m_config->flush();

    return true; 
}
