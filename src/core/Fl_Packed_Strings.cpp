#include <efltk/Fl_Packed_Strings.h>

#include <string.h>
#include <stdlib.h>

typedef char * charp;

Fl_Packed_Strings::Fl_Packed_Strings()
{
    m_size = sizeof(unsigned);
    m_buffer = malloc(m_size);
    *(unsigned*)m_buffer = 0;
}

Fl_Packed_Strings::Fl_Packed_Strings(int cnt, const char *strings[])
{
    unsigned *offset = new unsigned[cnt*2];
    unsigned *len = offset + cnt;

    int offsetsSpace = cnt * sizeof(unsigned);
    int sz = offsetsSpace + sizeof(unsigned);

    // compute buffer size and offsets
    for (int i = 0; i < cnt; i++) {
        register unsigned l = unsigned(strlen(strings[i]) + 1);
        offset[i] = unsigned(sz);
        len[i] = l;
        sz += l;
    }

    // create buffer
    m_size = (unsigned)sz;
    m_buffer = malloc(m_size);

    // Set count
    *(unsigned *)m_buffer = unsigned(cnt);

    // Copy offsets
    memcpy((unsigned *)m_buffer + 1, offset, offsetsSpace);

    // Copy strings
    for (int i = 0; i < cnt; i++)
        memcpy(charp(m_buffer)+offset[i], strings[i], len[i]);

    delete [] offset;
}

Fl_Packed_Strings::~Fl_Packed_Strings() {
    free(m_buffer);
}

const char *Fl_Packed_Strings::get(unsigned index) const
{
    if(index>=count()) return 0;
    unsigned *offsets  = (unsigned *)m_buffer + 1;
    return (const char*)m_buffer + offsets[index];
}

Fl_Packed_Strings& Fl_Packed_Strings::operator=(const Fl_Packed_Strings& strings) {
    if(m_size != strings.m_size) {
        m_size = strings.m_size;
        m_buffer = realloc(m_buffer, m_size);
    }
    memcpy(m_buffer, strings.m_buffer, m_size);
    return *this;
}

void Fl_Packed_Strings::set(unsigned index, const char *string)
{
    // Offset of string to change
    int offset  = *(((unsigned *)m_buffer) + index+1);

    // Old string
    const char *old_string = charp(m_buffer) + offset;
    int old_len = *old_string ? strlen(old_string)+1 : 1;

    // New string
    const char *new_string = string ? string : "\0";
    int new_len = *new_string ? strlen(new_string)+1 : 1;

    // Change bytes in string lengths
    int len_change = (new_len-old_len);

    // New size of total buffer (m_buffer)
    int new_size = m_size + len_change;

    if(len_change > 0) {
        // New string is longer than old one.

        // Allocate new size for buffer
        m_buffer = realloc(m_buffer, new_size+1);

        // Move existing content away from new string
        memmove(charp(m_buffer)+(offset+new_len),
                charp(m_buffer)+(offset+old_len),
                (m_size-offset-old_len) );

    }
    else if(len_change < 0) {
        // New string is smaller than old one

        // Move existing content to correct place,
        // i.e. move it back "length smaller" bytes
        memmove(charp(m_buffer)+(offset+new_len),
                charp(m_buffer)+(offset+old_len),
                m_size-(offset+old_len) );

        // Shrink buffer size
        m_buffer = realloc(m_buffer, new_size);
    }
    m_size = new_size;

    // Copy new string in memory
    memcpy(charp(m_buffer)+offset, new_string, new_len);

    if(len_change!=0) {
        // Update offsets
        unsigned *offsets  = (unsigned *)m_buffer + 1;
        for(index++; index<count(); index++) {
            offsets[index] += len_change;
        }
    }
}

void Fl_Packed_Strings::resize(unsigned new_count)
{
    unsigned old_count = count();
    int count_change = new_count - old_count;

    if(count_change==0) {
        // Count was not changed, return.
        return;
    }

    // Compute old and new needed space for offsets
    int old_offset_space = sizeof(unsigned) * old_count + sizeof(unsigned);
    int new_offset_space = sizeof(unsigned) * new_count + sizeof(unsigned);
    int off_change = new_offset_space - old_offset_space;

    if(count_change>0)
    {
        // new count is bigger than old one.
        int new_size = m_size + (off_change) + (count_change);

        // Allocate needed space
        m_buffer = realloc(m_buffer, new_size);

        // Move content to start from new offset_space end
        int move = m_size-old_offset_space;
        if(move>0) {
            memmove(charp(m_buffer)+new_offset_space,
                    charp(m_buffer)+old_offset_space,
                    move);
        }

        unsigned *offsets = (unsigned *)m_buffer + 1;

        // Update old strings offsets
        for(unsigned n=0; n<old_count; n++)
            offsets[n] += off_change;

        // Update new strings offsets and init offsets in buffer to NULL
        int off_start = m_size+off_change;
        for(; old_count<new_count; old_count++) {
            *(charp(m_buffer)+off_start) = '\0';
            offsets[old_count] = off_start++;
        }
        // Set new size
        m_size = new_size;

    } else {
        // new count is smaller then old one

        unsigned *offsets = (unsigned *)m_buffer + 1;

        // Compute new size needed
        int new_size = offsets[new_count]- old_offset_space + new_offset_space;

        // Move content to start from new offset_space end
        memmove(charp(m_buffer)+new_offset_space,
                charp(m_buffer)+old_offset_space,
                new_size);

        // Shink buffer
        m_buffer = realloc(m_buffer, new_size);

        // Update offsets
        offsets = (unsigned *)m_buffer + 1;
        for(unsigned n=0; n<new_count; n++) {
            offsets[n] += off_change;
        }
        // Set new size
        m_size = new_size;
    }

    // Set new count to buffer
    *(unsigned*)m_buffer = new_count;
}
