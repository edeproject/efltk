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
    enum SI_Type {
        SI_OK,
        SI_CANCEL,
        SI_NO,
        SI_OPEN,
        SI_SAVE,
        SI_BROWSE,
        SI_HELP,
        SI_NEXT,
        SI_PREV,
        SI_LEFT,
        SI_RIGHT,
        SI_ADD,
        SI_DELETE,
        SI_EDIT,
        SI_REFRESH,
        SI_CALENDAR,
        SI_PRINT,
        SI_PRINTER,
        SI_INSERT,
        SI_NEW,
        SI_SEARCH,
        SI_SEND,
        SI_STEPLEFT,
        SI_STEPRIGHT,
        SI_VIEW,
        LAST_STOCK_TYPE,

        // Same
        SI_PRIOR = SI_PREV
    };

    /**
     * Returns image of given type.
     */
    static Fl_Image *get_image(SI_Type type);

    /**
     * Set new image for type. You can set default image back by calling this
     * with image parameter as NULL pointer.
     */
    static void set_image(SI_Type type, Fl_Image *image);
};

// Defines :)
#define FL_IMAGE_OK        Fl_Stock_Images::SI_OK
#define FL_IMAGE_CANCEL    Fl_Stock_Images::SI_CANCEL
#define FL_IMAGE_NO        Fl_Stock_Images::SI_NO
#define FL_IMAGE_OPEN      Fl_Stock_Images::SI_OPEN
#define FL_IMAGE_SAVE      Fl_Stock_Images::SI_SAVE
#define FL_IMAGE_BROWSE    Fl_Stock_Images::SI_BROWSE
#define FL_IMAGE_HELP      Fl_Stock_Images::SI_HELP
#define FL_IMAGE_NEXT      Fl_Stock_Images::SI_NEXT
#define FL_IMAGE_PREV      Fl_Stock_Images::SI_PREV
#define FL_IMAGE_PRIOR     Fl_Stock_Images::SI_PRIOR
#define FL_IMAGE_LEFT      Fl_Stock_Images::SI_LEFT
#define FL_IMAGE_RIGHT     Fl_Stock_Images::SI_RIGHT
#define FL_IMAGE_ADD       Fl_Stock_Images::SI_ADD
#define FL_IMAGE_DELETE    Fl_Stock_Images::SI_DELETE
#define FL_IMAGE_EDIT      Fl_Stock_Images::SI_EDIT
#define FL_IMAGE_REFRESH   Fl_Stock_Images::SI_REFRESH
#define FL_IMAGE_CALENDAR  Fl_Stock_Images::SI_CALENDAR
#define FL_IMAGE_PRINT     Fl_Stock_Images::SI_PRINT
#define FL_IMAGE_PRINTER   Fl_Stock_Images::SI_PRINTER
#define FL_IMAGE_INSERT    Fl_Stock_Images::SI_INSERT
#define FL_IMAGE_NEW       Fl_Stock_Images::SI_NEW
#define FL_IMAGE_SEARCH    Fl_Stock_Images::SI_SEARCH
#define FL_IMAGE_SEND      Fl_Stock_Images::SI_SEND
#define FL_IMAGE_STEPLEFT  Fl_Stock_Images::SI_STEPLEFT
#define FL_IMAGE_STEPRIGHT Fl_Stock_Images::SI_STEPRIGHT
#define FL_IMAGE_VIEW      Fl_Stock_Images::SI_VIEW

#endif
