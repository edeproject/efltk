#include <efltk/Fl_Map.h>

Fl_Map_Iterator::Fl_Map_Iterator(const Fl_Map &map)
{
    m_map = &map;
    first();
}

void *Fl_Map_Iterator::get_pair() const
{
    if(m_y<0 || m_y >= (int)m_map->hash_size())
        return 0;

    Fl_Ptr_List *list = &m_map->m_lists[m_y];

    if(m_x<0 || m_x>=(int)list->size())
        return 0;

    return (*list)[m_x];
}

bool Fl_Map_Iterator::is_valid()
{
    if(m_y < 0 || m_y >= (int)m_map->hash_size())
        return false;

    Fl_Ptr_List &list = m_map->m_lists[m_y];
    return (list.item(m_x) != 0);
}

Fl_Map_Iterator &Fl_Map_Iterator::first()
{
    m_y = m_x = 0;
    for(unsigned y=0; y < m_map->hash_size(); y++)
    {
        Fl_Ptr_List &wlist = m_map->m_lists[y];
        if(wlist.size()>0) {
            m_y = y;
            return *this;
        }
    }

    m_y = m_x = -1;
    return *this;
}

Fl_Map_Iterator &Fl_Map_Iterator::last()
{
    m_y = m_x = 0;
    for(unsigned y=m_map->hash_size()-1; y >= 0 ; y--)
    {
        Fl_Ptr_List &wlist = m_map->m_lists[y];
        if(wlist.size()>0) {
            m_y = y;
            m_x = wlist.size()-1;
            return *this;
        }
    }

    m_y = m_x = -1;
    return *this;
}

Fl_Map_Iterator &Fl_Map_Iterator::next()
{
    if(m_y<0 || m_y >= (int)m_map->hash_size()) return *this;

    m_x++;
    if(m_x >= (int)m_map->m_lists[m_y].size())
    {
        m_x = 0; m_y++;
        for(; m_y < (int)m_map->hash_size(); m_y++)
        {
            Fl_Ptr_List &wlist = m_map->m_lists[m_y];
            if(wlist.size()>0) {
                return *this;
            }
        }
        m_y = m_map->hash_size();
    }
    return *this;
}

Fl_Map_Iterator &Fl_Map_Iterator::prior()
{
    if(m_y<=0) return *this;

    m_x--;
    if(m_x<0) {
        m_x = 0; m_y--;
        for(; m_y>=0; m_y--)
        {
            Fl_Ptr_List &wlist = m_map->m_lists[m_y];
            if(wlist.size()>0) {
                m_x = wlist.size()-1;
                return *this;
            }
        }
        m_y = -1;
    }
    return *this;
}



/**
 * Internal method to test if a positive number is prime.
 * Not an efficient algorithm.
 */
static bool is_prime(int n)
{
    if( n == 2 || n == 3 ) return true;
    if( n == 1 || n % 2 == 0 ) return false;
    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;
    return true;
}

/**
 * Internal method to return a prime number at least as large as n.
 * Assumes n > 0.
 */
static int next_prime(int n)
{
    if( n % 2 == 0 ) n++;
    for( ; !is_prime(n); n += 2 );
    return n;
}

Fl_Map::Fl_Map(int hash_size)
{
    m_lists_size = next_prime(hash_size);
    m_lists = new Fl_Ptr_List[m_lists_size];
    m_items = 0;
}

void Fl_Map::clear() {
    for(uint n=0; n<m_lists_size; n++) {
        Fl_Ptr_List &wlist = m_lists[n];
        for(uint x=0; x<wlist.size(); x++) {
            free_pair(wlist[x]);
        }
        wlist.clear();
    }
    m_items = 0;
}

unsigned Fl_Map::insert_pair(int Y, void *pair)
{
    m_lists[Y].append(pair);
    m_items++;
    return m_lists[Y].size();
}

bool Fl_Map::remove_pair(int Y, void *pair)
{
    Fl_Ptr_List &wlist = m_lists[Y];
    for(uint x=0; x<wlist.size(); x++) {
        if(wlist[x] == pair) {
            free_pair(wlist[x]);
            wlist.remove(x);
            m_items--;
            return true;
        }
    }
    return false;
}

unsigned Fl_Map::hash_string( const char *key, int table_size )
{
    int hval=0;

    const char *ptr = key;
    while(*ptr++)
        hval = 37 * hval + (*ptr);

    hval = hval % table_size;
    if( hval < 0 ) hval += table_size;
    return hval;
}

unsigned Fl_Map::hash_int( int key, int table_size )
{
    if(key < 0) key = -key;
    return unsigned(key % table_size);
}

//////////////////////////

bool Fl_String_String_Map::insert(const char *id, const char *val)
{
    int Y = Fl_Map::hash_string(id, hash_size());
    Pair *pair = find_pair(Y, id);
    if(!pair) {
        pair = Fl_String_String_Map::pair(id, val);
        insert_pair(Y, pair);
        pair->val = val;
        return true;
    }
    return false;
}

bool Fl_String_String_Map::insert(const char *id, const Fl_String &val)
{
    int Y = Fl_Map::hash_string(id, hash_size());
    Pair *pair = find_pair(Y, id);
    if(!pair) {
        pair = Fl_String_String_Map::pair(id, val);
        insert_pair(Y, pair);
        pair->val = val;
        return true;
    }
    return false;
}

bool Fl_String_String_Map::remove(const char *id)
{
    int Y = Fl_Map::hash_string(id, hash_size());
    Pair *pair = find_pair(Y, id);
    if(!pair) return false;
    return remove_pair(Y, pair);
}

void Fl_String_String_Map::set_value(const char *id, const Fl_String &val)
{
    int Y = Fl_Map::hash_string(id, hash_size());
    Pair *pair = find_pair(Y, id);
    if(!pair) {
        pair = Fl_String_String_Map::pair(id, val);
        insert_pair(Y, pair);
    }
    pair->val = val;
}

void Fl_String_String_Map::set_value(const char *id, const char *val)
{
    int Y = Fl_Map::hash_string(id, hash_size());
    Pair *pair = find_pair(Y, id);
    if(!pair) {
        pair = Fl_String_String_Map::pair(id, val);
        insert_pair(Y, pair);
    }
    pair->val = val;
}

bool Fl_String_String_Map::contains(const char *id) const
{
    int Y = Fl_Map::hash_string(id, hash_size());
    return (find_pair(Y, id) != 0);
}

Fl_String &Fl_String_String_Map::get_value(const char *id) const
{
    int Y = Fl_Map::hash_string(id, hash_size());
    Pair *pair = find_pair(Y, id);
    if(pair) return pair->val;
    return Fl_String::null_object;
}

Fl_String_String_Map::Pair *Fl_String_String_Map::pair(const char *id, const char *val)
{
    Pair *pair = new Pair;
    pair->id = id;
    pair->val = val;
    return pair;
}

Fl_String_String_Map::Pair *Fl_String_String_Map::pair(const char *id, const Fl_String &val)
{
    Pair *pair = new Pair;
    pair->id = id;
    pair->val = val;
    return pair;
}

Fl_String_String_Map::Pair *Fl_String_String_Map::find_pair(int Y, const char *id) const
{
    Fl_Ptr_List &wlist = m_lists[ Y ];

    if(wlist.size()<2) {
        if(wlist.size()==0) return 0;
        Pair *p = (Pair*)wlist[0];
        if(p->id == id) return (Pair *)wlist[0];
        else            return 0;
    }

    // Do binary search
    int bottom=0, top=wlist.size()-1, mid;
    int L = ( top + bottom ) / 2 ;
    Pair *test = (Pair*)wlist[L];
    if(test->id == id) return test;
    while(bottom <= top) {
        mid = top + bottom / 2 ;
        test = (Pair*)wlist[mid];
        int d = strcmp(id, test->id);
        if(!d)
            return test;
        else if(d>0)
            bottom = mid + 1;
        else
            top = mid-1;
    }
    return 0;
}

Fl_String &Fl_String_String_Map::operator [](const char *id)
{
    int Y = Fl_Map::hash_string(id, hash_size());
    Pair *pair = find_pair(Y, id);
    if(!pair) {
        pair = Fl_String_String_Map::pair(id, "");
        insert_pair(Y, pair);
    }
    return pair->val;
}

const Fl_String &Fl_String_String_Map::operator [](const char *id) const
{
    int Y = Fl_Map::hash_string(id, hash_size());
    Pair *pair = find_pair(Y, id);
    if(!pair) return Fl_String::null_object;
    return pair->val;
}

//////////////////////////

bool Fl_Int_String_Map::insert(int id, const char *val)
{
    int Y = Fl_Map::hash_int(id, hash_size());
    Pair *pair = find_pair(Y, id);
    if(!pair) {
        pair = Fl_Int_String_Map::pair(id, val);
        insert_pair(Y, pair);
        pair->val = val;
        return true;
    }
    return false;
}

bool Fl_Int_String_Map::insert(int id, const Fl_String &val)
{
    int Y = Fl_Map::hash_int(id, hash_size());
    Pair *pair = find_pair(Y, id);
    if(!pair) {
        pair = Fl_Int_String_Map::pair(id, val);
        insert_pair(Y, pair);
        pair->val = val;
        return true;
    }
    return false;
}

bool Fl_Int_String_Map::remove(int id)
{
    int Y = Fl_Map::hash_int(id, hash_size());
    Pair *pair = find_pair(Y, id);
    if(!pair) return false;
    return remove_pair(Y, pair);
}

void Fl_Int_String_Map::set_value(int id, const Fl_String &val)
{
    int Y = Fl_Map::hash_int(id, hash_size());
    Pair *pair = find_pair(Y, id);
    if(!pair) {
        pair = Fl_Int_String_Map::pair(id, val);
        insert_pair(Y, pair);
    }
    pair->val = val;
}

void Fl_Int_String_Map::set_value(int id, const char *val)
{
    int Y = Fl_Map::hash_int(id, hash_size());
    Pair *pair = find_pair(Y, id);
    if(!pair) {
        pair = Fl_Int_String_Map::pair(id, val);
        insert_pair(Y, pair);
    }
    pair->val = val;
}

bool Fl_Int_String_Map::contains(int id) const
{
    int Y = Fl_Map::hash_int(id, hash_size());
    return (find_pair(Y, id) != 0);
}

Fl_String &Fl_Int_String_Map::get_value(int id) const
{
    int Y = Fl_Map::hash_int(id, hash_size());
    Pair *pair = find_pair(Y, id);
    if(pair) return pair->val;
    return Fl_String::null_object;
}

Fl_Int_String_Map::Pair *Fl_Int_String_Map::pair(int id, const char *val)
{
    Pair *pair = new Pair;
    pair->id = id;
    pair->val = val;
    return pair;
}

Fl_Int_String_Map::Pair *Fl_Int_String_Map::pair(int id, const Fl_String &val)
{
    Pair *pair = new Pair;
    pair->id = id;
    pair->val = val;
    return pair;
}

Fl_Int_String_Map::Pair *Fl_Int_String_Map::find_pair(int Y, int id) const
{
    Fl_Ptr_List &wlist = m_lists[ Y ];

    if(wlist.size()<2) {
        if(wlist.size()==0) return 0;
        Pair *p = (Pair*)wlist[0];
        if(p->id == id) return (Pair *)wlist[0];
        else            return 0;
    }

    // Do binary search
    int bottom=0, top=wlist.size()-1, mid;
    int L = ( top + bottom ) / 2 ;
    Pair *test = (Pair*)wlist[L];
    if(test->id == id) return test;
    while(bottom <= top) {
        mid = top + bottom / 2 ;
        test = (Pair*)wlist[mid];
        int d = id - test->id;
        if(!d)
            return test;
        else if(d>0)
            bottom = mid + 1;
        else
            top = mid-1;
    }
    return 0;
}

Fl_String &Fl_Int_String_Map::operator [](int id)
{
    int Y = Fl_Map::hash_int(id, hash_size());
    Pair *pair = find_pair(Y, id);
    if(!pair) {
        pair = Fl_Int_String_Map::pair(id, "");
        insert_pair(Y, pair);
    }
    return pair->val;
}

const Fl_String &Fl_Int_String_Map::operator [](int id) const
{
    int Y = Fl_Map::hash_int(id, hash_size());
    Pair *pair = find_pair(Y, id);
    if(!pair) return Fl_String::null_object;
    return pair->val;
}

//////////////////////////

bool Fl_String_Ptr_Map::insert(const char *id, void *val)
{
    int Y = Fl_Map::hash_string(id, hash_size());
    Pair *pair = find_pair(Y, id);
    if(!pair) {
        pair = Fl_String_Ptr_Map::pair(id, val);
        insert_pair(Y, pair);
        pair->val = val;
        return true;
    }
    return false;
}

bool Fl_String_Ptr_Map::remove(const char *id)
{
    int Y = Fl_Map::hash_string(id, hash_size());
    Pair *pair = find_pair(Y, id);
    if(!pair) return false;
    return remove_pair(Y, pair);
}

void Fl_String_Ptr_Map::set_value(const char *id, void *val)
{
    int Y = Fl_Map::hash_string(id, hash_size());
    Pair *pair = find_pair(Y, id);
    if(!pair) {
        pair = Fl_String_Ptr_Map::pair(id, val);
        insert_pair(Y, pair);
    }
    pair->val = val;
}

bool Fl_String_Ptr_Map::contains(const char *id) const
{
    int Y = Fl_Map::hash_string(id, hash_size());
    return (find_pair(Y, id) != 0);
}

void *Fl_String_Ptr_Map::get_value(const char *id) const
{
    int Y = Fl_Map::hash_string(id, hash_size());
    Pair *pair = find_pair(Y, id);
    if(pair) return pair->val;
    return 0;
}

Fl_String_Ptr_Map::Pair *Fl_String_Ptr_Map::pair(const char *id, void *val)
{
    Pair *pair = new Pair;
    pair->id = id;
    pair->val = val;
    return pair;
}

Fl_String_Ptr_Map::Pair *Fl_String_Ptr_Map::find_pair(int Y, const char *id) const
{
    Fl_Ptr_List &wlist = m_lists[ Y ];

    if(wlist.size()<2) {
        if(wlist.size()==0) return 0;
        Pair *p = (Pair*)wlist[0];
        if(p->id == id) return (Pair *)wlist[0];
        else            return 0;
    }

    // Do binary search
    int bottom=0, top=wlist.size()-1, mid;
    int L = ( top + bottom ) / 2 ;
    Pair *test = (Pair*)wlist[L];
    if(test->id == id) return test;
    while(bottom <= top) {
        mid = top + bottom / 2 ;
        test = (Pair*)wlist[mid];
        int d = strcmp(id, test->id);
        if(!d)
            return test;
        else if(d>0)
            bottom = mid + 1;
        else
            top = mid-1;
    }
    return 0;
}

void *Fl_String_Ptr_Map::operator [](const char *id)
{
    int Y = Fl_Map::hash_string(id, hash_size());
    Pair *pair = find_pair(Y, id);
    if(!pair) {
        pair = Fl_String_Ptr_Map::pair(id, 0);
        insert_pair(Y, pair);
    }
    return pair->val;
}

const void *Fl_String_Ptr_Map::operator [](const char *id) const
{
    int Y = Fl_Map::hash_string(id, hash_size());
    Pair *pair = find_pair(Y, id);
    if(!pair) return 0;
    return pair->val;
}

//////////////////////////

bool Fl_Int_Ptr_Map::insert(int id, void *val)
{
    int Y = Fl_Map::hash_int(id, hash_size());
    Pair *pair = find_pair(Y, id);
    if(!pair) {
        pair = Fl_Int_Ptr_Map::pair(id, val);
        insert_pair(Y, pair);
        pair->val = val;
        return true;
    }
    return false;
}

bool Fl_Int_Ptr_Map::remove(int id)
{
    int Y = Fl_Map::hash_int(id, hash_size());
    Pair *pair = find_pair(Y, id);
    if(!pair) return false;
    return remove_pair(Y, pair);
}

void Fl_Int_Ptr_Map::set_value(int id, void *val)
{
    int Y = Fl_Map::hash_int(id, hash_size());
    Pair *pair = find_pair(Y, id);
    if(!pair) {
        pair = Fl_Int_Ptr_Map::pair(id, val);
        insert_pair(Y, pair);
    }
    pair->val = val;
}

bool Fl_Int_Ptr_Map::contains(int id) const
{
    int Y = Fl_Map::hash_int(id, hash_size());
    return (find_pair(Y, id) != 0);
}

void *Fl_Int_Ptr_Map::get_value(int id) const
{
    int Y = Fl_Map::hash_int(id, hash_size());
    Pair *pair = find_pair(Y, id);
    if(pair) return pair->val;
    return 0;
}

Fl_Int_Ptr_Map::Pair *Fl_Int_Ptr_Map::pair(int id, void *val)
{
    Pair *pair = new Pair;
    pair->id = id;
    pair->val = val;
    return pair;
}

Fl_Int_Ptr_Map::Pair *Fl_Int_Ptr_Map::find_pair(int Y, int id) const
{
    Fl_Ptr_List &wlist = m_lists[ Y ];

    if(wlist.size()<2) {
        if(wlist.size()==0) return 0;
        Pair *p = (Pair*)wlist[0];
        if(p->id == id) return (Pair *)wlist[0];
        else            return 0;
    }

    // Do binary search
    int bottom=0, top=wlist.size()-1, mid;
    int L = ( top + bottom ) / 2 ;
    Pair *test = (Pair*)wlist[L];
    if(test->id == id) return test;
    while(bottom <= top) {
        mid = top + bottom / 2 ;
        test = (Pair*)wlist[mid];
        int d = id - test->id;
        if(!d)
            return test;
        else if(d>0)
            bottom = mid + 1;
        else
            top = mid-1;
    }
    return 0;
}

void *Fl_Int_Ptr_Map::operator [](int id)
{
    int Y = Fl_Map::hash_int(id, hash_size());
    Pair *pair = find_pair(Y, id);
    if(!pair) {
        pair = Fl_Int_Ptr_Map::pair(id, 0);
        insert_pair(Y, pair);
    }
    return pair->val;
}

const void *Fl_Int_Ptr_Map::operator [](int id) const
{
    int Y = Fl_Map::hash_int(id, hash_size());
    Pair *pair = find_pair(Y, id);
    if(!pair) return 0;
    return pair->val;
}
