#ifndef _FL_STOCK_IMAGES_H_
#define _FL_STOCK_IMAGES_H_

#include <efltk/Fl_Image.h>

/**
 * Fl_Stock_Images class allows to access to the set of predefined images
 * by the image id. That approach allows to use a small set of images and
 * reuse them over and over again.
 *
 * Themes may replace these images with images that fits to scheme.
 * Themes must restore images to default, when unloading theme.
 *
 * NOTE: You may not access pixel data of images!
 */

class Fl_Stock_Images
{
public:
    /**
     * Types for predefined stock images.
     */
    enum Type {
        OK,
        CANCEL,
        NO,
        OPEN,
        SAVE,
        BROWSE,
        HELP,
        NEXT,
        PREV,
        LEFT,
        RIGHT,
        ADD,
        DELETE,
        EDIT,
        REFRESH,
        CALENDAR,
        PRINT,
        PRINTER,
        INSERT,
        NEW,
        SEARCH,
        SEND,
        STEPLEFT,
        STEPRIGHT,
        VIEW,
        LAST_STOCK_TYPE,

        // Same
        PRIOR = PREV
    };

    /**
     * Returns image of given type.
     */
    static Fl_Image *get_image(Type type);

    /**
     * Set new image for type. You can set default image back by calling this
     * with image parameter as NULL pointer.
     */
    static void set_image(Type type, Fl_Image *image);
};

// Defines :)
#define FL_IMAGE_OK        Fl_Stock_Images::OK
#define FL_IMAGE_CANCEL    Fl_Stock_Images::CANCEL
#define FL_IMAGE_NO        Fl_Stock_Images::NO
#define FL_IMAGE_OPEN      Fl_Stock_Images::OPEN
#define FL_IMAGE_SAVE      Fl_Stock_Images::SAVE
#define FL_IMAGE_BROWSE    Fl_Stock_Images::BROWSE
#define FL_IMAGE_HELP      Fl_Stock_Images::HELP
#define FL_IMAGE_NEXT      Fl_Stock_Images::NEXT
#define FL_IMAGE_PREV      Fl_Stock_Images::PREV
#define FL_IMAGE_PRIOR     Fl_Stock_Images::PRIOR
#define FL_IMAGE_LEFT      Fl_Stock_Images::LEFT
#define FL_IMAGE_RIGHT     Fl_Stock_Images::RIGHT
#define FL_IMAGE_ADD       Fl_Stock_Images::ADD
#define FL_IMAGE_DELETE    Fl_Stock_Images::DELETE
#define FL_IMAGE_EDIT      Fl_Stock_Images::EDIT
#define FL_IMAGE_REFRESH   Fl_Stock_Images::REFRESH
#define FL_IMAGE_CALENDAR  Fl_Stock_Images::CALENDAR
#define FL_IMAGE_PRINT     Fl_Stock_Images::PRINT
#define FL_IMAGE_PRINTER   Fl_Stock_Images::PRINTER
#define FL_IMAGE_INSERT    Fl_Stock_Images::INSERT
#define FL_IMAGE_NEW       Fl_Stock_Images::NEW
#define FL_IMAGE_SEARCH    Fl_Stock_Images::SEARCH
#define FL_IMAGE_SEND      Fl_Stock_Images::SEND
#define FL_IMAGE_STEPLEFT  Fl_Stock_Images::STEPLEFT
#define FL_IMAGE_STEPRIGHT Fl_Stock_Images::STEPRIGHT
#define FL_IMAGE_VIEW      Fl_Stock_Images::VIEW

#endif
