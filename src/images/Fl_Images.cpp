#include <efltk/Fl_Image.h>
#include <config.h>

#if HAVE_PNG
extern ImageReader png_reader;
#endif
#if HAVE_JPEG
extern ImageReader jpeg_reader;
#endif
extern ImageReader bmp_reader;

void fl_init_images_lib()
{
#if HAVE_PNG
    Fl_Image::register_reader(&png_reader);
#endif
#if HAVE_JPEG
    Fl_Image::register_reader(&jpeg_reader);
#endif
}
