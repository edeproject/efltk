#ifndef FL_IMAGE_CACHE_H_
#define FL_IMAGE_CACHE_H_

#include "Fl_Image.h"
#include "Fl_PtrList.h"

class Fl_Image_Cache
{
    typedef struct {
        Fl_Image *image;
        char *identify;
    } CachedImage;

    Fl_PtrList<CachedImage> images;
    int size_;
    bool autodelete_;

public:
    // Size of cache as a param, 0 is unlimited
    Fl_Image_Cache(int size=0) { size_ = size; autodelete_ = false; }
    ~Fl_Image_Cache() { clear(); }

    // Clears cache, deletes images if auto delete is set true
    void clear() {
        for(CachedImage *i=images.first(); i!=0; i=images.next()) {
            if(i->identify) delete []i->identify;
            if(i->image && autodelete_) delete i->image;
            delete i;
        }
        images.clear();
    }
    Fl_Image *get(const char *identify) {
        for(CachedImage *i=images.first(); i!=0; i=images.next()) {
            if(!strcmp(identify, i->identify)) return i->image;
        }
        return 0;
    }

    // Removes image from cache, returns removed image
    Fl_Image *remove(const char *identify) {
        for(CachedImage *i=images.first(); i!=0; i=images.next()) {
            if(!strcmp(identify, i->identify)) {
                images.remove(i);
                if(i->identify) delete []i->identify;
                Fl_Image *tmp = i->image;
                delete i;
                return tmp;
            }
        }
        return 0;
    }

    // Returns replaced image, if any
    Fl_Image *add(Fl_Image *i, const char *identify) {
        if(!i) return 0;

        CachedImage *c;
        // Remove previously cached with same identify
        for(c=images.first(); c!=0; c=images.next()) {
            if(!strcmp(identify, c->identify)) {
                if(c->identify) delete []c->identify;
                c->identify = strdup(identify);
                Fl_Image *tmp = c->image;
                c->image = i;
                return tmp;
            }
        }

        c = new CachedImage;
        c->image = i;
        c->identify = strdup(identify);

        images.append(c);
        check_size();

        return 0;
    }

    // Check cache size and removes images first, if needed
    void check_size() {
        if(size_>0 && images.count() > size_) {
            CachedImage *i = images.first();
            images.remove(i);
            if(i->identify) delete []i->identify;
            if(i->image && autodelete_) delete i->image;
            delete i;
        }
    }

    bool autodelete() { return autodelete_; }
    void autodelete(bool val) { autodelete_ = val; }
    int size() { return size_; }
    void size(int s) { size_ = s; check_size(); }
    int cached() { return images.count(); }
};

#endif

