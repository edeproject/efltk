#include <efltk/Fl_Map.h>

Fl_Map::~Fl_Map() {
    clear();
}
void Fl_Map::clear() {
    for(uint n=0; n<size(); n++)
        free_pair((Fl_MapPair *)items[n]);
    items.clear();
}

Fl_MapPair *Fl_Map::append_pair(Fl_MapPair *item) {
    if(!item) return 0;
    items.append((void *)item);
    return item;
}
Fl_MapPair *Fl_Map::prepend_pair(Fl_MapPair *item) {
    if(!item) return 0;
    items.prepend((void *)item);
    return item;
}
Fl_MapPair *Fl_Map::insert_pair(uint pos, Fl_MapPair *item) {
    if(!item) return 0;
    items.insert(pos, (void *)item);
    return item;
}
Fl_MapPair *Fl_Map::replace_pair(uint pos, Fl_MapPair *item) {
    if(!item) return 0;
    free_pair((Fl_MapPair *)items[pos]);
    items.replace(pos, (void *)item);
    return item;
}

bool Fl_Map::remove_pair(uint pos) {
    if(pos<0 && pos>=size()) return false;
    free_pair((Fl_MapPair *)items[pos]);
    items.remove(pos);
    return true;
}
bool Fl_Map::remove_pair(Fl_MapPair *item) {
    if(!item) return false;
    free_pair(item);
    return items.remove((void *)item);
}

//////////////////////////

void Fl_String_String_Map::set_value(const char *id, const Fl_String &val)
{
    Pair *pair = find_pair(id);
    if(!pair) pair = (Pair *)append_pair(Fl_String_String_Map::pair(id, val));
    pair->val = val;
}

void Fl_String_String_Map::set_value(const char *id, const char *val)
{
    Pair *pair = find_pair(id);
    if(!pair) pair = (Pair *)append_pair(Fl_String_String_Map::pair(id, val));
    pair->val = val;
}

Fl_String *Fl_String_String_Map::get_value(const char *id) const
{
    Pair *pair = find_pair(id);
    if(pair) return &pair->val;
    return 0;
}

Fl_String_String_Pair *Fl_String_String_Map::pair(const char *id, const char *val)
{
    Pair *pair = new Pair;
    pair->id = id;
    pair->val = val;
    return pair;
}

Fl_String_String_Pair *Fl_String_String_Map::pair(const char *id, const Fl_String &val)
{
    Pair *pair = new Pair;
    pair->id = id;
    pair->val = val;
    return pair;
}

Fl_String_String_Pair *Fl_String_String_Map::find_pair(const char *id) const
{
    for(uint n=0; n < size(); n++) {
        Pair *pair = item(n);
        if(pair->id == id)
            return pair;
    }
    return 0;
}

Fl_String &Fl_String_String_Map::operator [](const char *id)
{
    Pair *pair = find_pair(id);
    if(!pair) pair = (Pair *)append_pair(Fl_String_String_Map::pair(id, ""));
    return pair->val;
}

//////////////////////////////////////////////////////////////

void Fl_Int_String_Map::set_value(const int id, const Fl_String &val)
{
    Pair *pair = find_pair(id);
    if(!pair) pair = (Pair *)append_pair(Fl_Int_String_Map::pair(id, val));
    pair->val = val;
}

void Fl_Int_String_Map::set_value(const int id, const char *val)
{
    Pair *pair = find_pair(id);
    if(!pair) pair = (Pair *)append_pair(Fl_Int_String_Map::pair(id, val));
    pair->val = val;
}

Fl_String *Fl_Int_String_Map::get_value(const int id) const
{
    Pair *pair = find_pair(id);
    if(pair) return &pair->val;
    return 0;
}

Fl_Int_String_Pair *Fl_Int_String_Map::pair(const int id, const Fl_String &val)
{
    Fl_Int_String_Pair *pair = new Fl_Int_String_Pair;
    pair->id = id;
    pair->val = val;
    return pair;
}

Fl_Int_String_Pair *Fl_Int_String_Map::pair(const int id, const char *val)
{
    Fl_Int_String_Pair *pair = new Fl_Int_String_Pair;
    pair->id = id;
    pair->val = val;
    return pair;
}

Fl_Int_String_Pair *Fl_Int_String_Map::find_pair(int id) const
{
    for(uint n=0; n < size(); n++) {
        Pair *pair = item(n);
        if(pair->id == id)
            return pair;
    }
    return 0;
}

Fl_String &Fl_Int_String_Map::operator [](const int id)
{
    Pair *pair = find_pair(id);
    if(!pair) pair = (Pair *)append_pair(Fl_Int_String_Map::pair(id, ""));
    return pair->val;
}
