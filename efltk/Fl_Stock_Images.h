#ifndef _FL_IMAGE_STOCK_IMAGES_H_
#define _FL_IMAGE_STOCK_IMAGES_H_

/** Fl_Stock_Images class allows to access to the set of predefined images
  * by the image id. That approach allows to use a small set of images and
  * reuse them over and over again
  */

enum Fl_Stock_Image {
    FL_IMAGE_UNDEFINED,
    FL_IMAGE_ADD,
    FL_IMAGE_DELETE,
    FL_IMAGE_EDIT,
    FL_IMAGE_BROWSE,
    FL_IMAGE_REFRESH,
    FL_IMAGE_CALENDAR,
    FL_IMAGE_CANCEL,
    FL_IMAGE_HELP,
    FL_IMAGE_NO,
    FL_IMAGE_OK,
    FL_IMAGE_OPEN,
    FL_IMAGE_PRINT,
    FL_IMAGE_SAVE,
    FL_IMAGE_INSERT,
    FL_IMAGE_LEFT,
    FL_IMAGE_NEW,
    FL_IMAGE_NEXT,
    FL_IMAGE_PRINTER,
    FL_IMAGE_PRIOR, 
    FL_IMAGE_RIGHT,
    FL_IMAGE_SEARCH,
    FL_IMAGE_SEND,
    FL_IMAGE_STEPLEFT,
    FL_IMAGE_STEPRIGHT,
    FL_IMAGE_VIEW
};

class Fl_Stock_Images
{
public:
    Fl_Stock_Images(); // Constructor
    ~Fl_Stock_Images(); // Destructor
};

#endif
