/***************************************************************************
                          Fl_Data_Source.cpp  -  description
                             -------------------
    begin                : Oct 31 2002
    copyright            : (C) 2000-2002 by Alexey S.Parshin
    email                : alexeyp@m7.tts-sf.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <efltk/Fl_Data_Source.h>
#include <efltk/Fl_Widget.h>
#include <efltk/Fl_Group.h>

bool Fl_Data_Source::load() {
    // loading data into DS
    if (!m_parent || !load_data()) 
        return false;
    // loading data from DS to the widgets in the connected group
    return m_parent->load_data(this);
}

bool Fl_Data_Source::save() { 
    // storing data from the widgets in the connected group to DS
    if (!m_parent || !m_parent->save_data(this))
        return false;
    // Storing data from DS
    return save_data();
}
