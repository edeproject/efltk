#include <efltk/net/Fl_Mail_Message.h>

Fl_Mail_Message_Part::Fl_Mail_Message_Part(const Fl_String_List& source,unsigned start,unsigned end) {
    for (unsigned i = start; i <= end; i++ )
        m_messageText.append(source[i]);
}

void Fl_Mail_Message_Part_List::clear() {
    for (unsigned i = 0; i < m_messageParts.count(); i++ )
        delete (Fl_Mail_Message_Part *)m_messageParts[i];
}

