#include <config.h>
#include <efltk/Fl_Image.h>

#if HAVE_PNG
extern Fl_Image_IO png_reader;
#endif
#if HAVE_JPEG
extern Fl_Image_IO jpeg_reader;
#endif

void fl_init_images_lib()
{
    static bool registered = false;
    if(!registered) {
#if HAVE_PNG
        fl_register_imageio(&png_reader);
#endif
#if HAVE_JPEG
        fl_register_imageio(&jpeg_reader);
#endif
        registered = true;
    }
}
