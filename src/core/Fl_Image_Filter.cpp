#include <efltk/math.h>
#include <efltk/Fl_Image_Filter.h>
#include <efltk/Fl_Image.h>

#include "fl_internal.h"

#define SYSTEM_8BIT (Fl_Renderer::system_format()->bytespp==1)

bool Fl_Image_Filter::apply_to_this(Fl_Image *image, Fl_Rect *rect, Fl_Image_Filter *filter)
{
    return apply_to_this(image, rect, filter, 1.0, 1.0, 1.0);
}

bool Fl_Image_Filter::apply_to_this(Fl_Image *image, Fl_Rect *rect, Fl_Image_Filter *filter, float val1)
{
    return apply_to_this(image, rect, filter, val1, val1, val1);
}

bool Fl_Image_Filter::apply_to_this(Fl_Image *image, Fl_Rect *rect, Fl_Image_Filter *filter, float val1, float val2)
{
    return apply_to_this(image, rect, filter, val1, val2, val1);
}

bool Fl_Image_Filter::apply_to_this(Fl_Image *image, Fl_Rect *rect, Fl_Image_Filter *filter, float val1, float val2, float val3)
{
    Fl_Rect r(0,0,image->width(),image->height());
    if(!rect) { rect = &r; }
    uint8 *data = image->data();
    return filter->execute(&data, *rect, image->pitch(), image->format(), val1, val2, val3);
}

Fl_Image *Fl_Image_Filter::apply_to_new(Fl_Image *image, Fl_Rect *rect, Fl_Image_Filter *filter)
{
    return apply_to_new(image, rect, filter, 1.0, 1.0, 1.0);
}

Fl_Image *Fl_Image_Filter::apply_to_new(Fl_Image *image, Fl_Rect *rect, Fl_Image_Filter *filter, float val1)
{
    return apply_to_new(image, rect, filter, val1, val1, val1);
}

Fl_Image *Fl_Image_Filter::apply_to_new(Fl_Image *image, Fl_Rect *rect, Fl_Image_Filter *filter, float val1, float val2)
{
    return apply_to_new(image, rect, filter, val1, val2, val1);
}

Fl_Image *Fl_Image_Filter::apply_to_new(Fl_Image *image, Fl_Rect *rect, Fl_Image_Filter *filter, float val1, float val2, float val3)
{
    Fl_Rect r(0,0,image->width(),image->height());
    if(!rect) { rect = &r; }
    Fl_Image *ret = new Fl_Image(*image);

    uint8 *data = ret->data();
    if(!filter->execute(&data, *rect, ret->pitch(), ret->format(), val1, val2, val3)) {
        delete ret;
        return 0;
    }
    return ret;
}

FilterBrightness filter_brightness;
bool FilterBrightness::execute(uint8 **data, Fl_Rect &rect, int pitch, Fl_PixelFormat *fmt, float val1, float val2, float val3)
{
    Fl_PixelFormat *srcfmt = fmt;

    int width = rect.w();
    int height = rect.h();
    int srcskip = pitch - width * srcfmt->bytespp;

    int srcbpp = srcfmt->bytespp;

    uint32 pixel=0;
    int16 R=0, G=0, B=0, A=255;

    int val = (int)(val1 * 255);

    ERROR_DIFF_START();

    uint8 *ptr = (uint8 *)*data + rect.y() * pitch + rect.x() * srcfmt->bytespp;
    while ( height-- ) {
        DUFFS_LOOP4(
                    {
                        if(srcbpp==1) fl_disemble_rgb(ptr, srcbpp, srcfmt, pixel, (uint8&)R, (uint8&)G, (uint8&)B);
                        else fl_disemble_rgba(ptr, srcbpp, srcfmt, pixel, (uint8&)R, (uint8&)G, (uint8&)B, (uint8&)A);

                        R+=val;
                        G+=val;
                        B+=val;
                        if(R > 255) R = 255;
                        if(G > 255) G = 255;
                        if(B > 255) B = 255;
                        if(R < 0) R=0;
                        if(G < 0) G=0;
                        if(B < 0) B=0;

                        if(SYSTEM_8BIT) { ERROR_DIFF(R,G,B,*ptr); }
                        else { fl_assemble_rgba(ptr, srcbpp, srcfmt, R, G, B, A); }

                        ptr+=srcbpp;
                    }, width);
        ptr += srcskip;
    }
    ERROR_DIFF_END();

    return true;
}

FilterContrast filter_contrast;
bool FilterContrast::execute(uint8 **data, Fl_Rect &rect, int pitch, Fl_PixelFormat *fmt, float val1, float val2, float val3)
{
    Fl_PixelFormat *srcfmt = fmt;

    int width = rect.w();
    int height = rect.h();
    int srcskip = pitch - width * srcfmt->bytespp;

    int srcbpp = srcfmt->bytespp;

    uint32 pixel=0;
    int16 R=0, G=0, B=0, A=255;

    ERROR_DIFF_START();

    uint8 *ptr = (uint8 *)*data + rect.y() * pitch + rect.x() * srcfmt->bytespp;
    while ( height-- ) {
        DUFFS_LOOP4(
                    {
                        if(srcbpp==1) fl_disemble_rgb(ptr, srcbpp, srcfmt, pixel, (uint8&)R, (uint8&)G, (uint8&)B);
                        else fl_disemble_rgba(ptr, srcbpp, srcfmt, pixel, (uint8&)R, (uint8&)G, (uint8&)B, (uint8&)A);

                        R = (int((R - 127) * val1)) + 127;
                        G = (int((G - 127) * val2)) + 127;
                        B = (int((B - 127) * val3)) + 127;
                        if(R > 255) R = 255;
                        if(G > 255) G = 255;
                        if(B > 255) B = 255;
                        if(R < 0) R=0;
                        if(G < 0) G=0;
                        if(B < 0) B=0;

                        if(SYSTEM_8BIT) { ERROR_DIFF(R,G,B,*ptr); }
                        else { fl_assemble_rgba(ptr, srcbpp, srcfmt, R, G, B, A); }

                        ptr+=srcbpp;
                    }, width);
        ptr += srcskip;
    }
    ERROR_DIFF_END();

    return true;
}

FilterGamma filter_gamma;
bool FilterGamma::execute(uint8 **data, Fl_Rect &rect, int pitch, Fl_PixelFormat *fmt, float val1, float val2, float val3)
{
    if(val1 < 0.01) val1 = 0.01f;
    if(val2 < 0.01) val2 = 0.01f;
    if(val3 < 0.01) val3 = 0.01f;

    Fl_PixelFormat *srcfmt = fmt;

    int width = rect.w();
    int height = rect.h();
    int srcskip = pitch - width * srcfmt->bytespp;

    int srcbpp = srcfmt->bytespp;

    uint32 pixel=0;
    int16 R=0, G=0, B=0, A=255;

    ERROR_DIFF_START();

    uint8 *ptr = (uint8 *)*data + rect.y() * pitch + rect.x() * srcfmt->bytespp;
    while ( height-- ) {
        DUFFS_LOOP4(
                    {
                        if(srcbpp==1) fl_disemble_rgb(ptr, srcbpp, srcfmt, pixel, (uint8&)R, (uint8&)G, (uint8&)B);
                        else fl_disemble_rgba(ptr, srcbpp, srcfmt, pixel, (uint8&)R, (uint8&)G, (uint8&)B, (uint8&)A);

                        R = (int)(pow(((float)R / 255), (1 / val1)) * 255);
                        G = (int)(pow(((float)G / 255), (1 / val2)) * 255);
                        B = (int)(pow(((float)B / 255), (1 / val3)) * 255);
                        if(R > 255) R = 255;
                        if(G > 255) G = 255;
                        if(B > 255) B = 255;
                        if(R < 0) R=0;
                        if(G < 0) G=0;
                        if(B < 0) B=0;

                        if(SYSTEM_8BIT) { ERROR_DIFF(R,G,B,*ptr); }
                        else { fl_assemble_rgba(ptr, srcbpp, srcfmt, R, G, B, A); }

                        ptr+=srcbpp;
                    }, width);
        ptr += srcskip;
    }

    ERROR_DIFF_END();
    return true;
}

FilterDesaturate filter_desaturate;
bool FilterDesaturate::execute(uint8 **data, Fl_Rect &rect, int pitch, Fl_PixelFormat *fmt, float val1, float val2, float val3)
{	
    Fl_PixelFormat *srcfmt = fmt;

    int width = rect.w();
    int height = rect.h();
    int srcskip = pitch - width * srcfmt->bytespp;

    int srcbpp = srcfmt->bytespp;

    uint32 pixel=0;
    int16 R=0, G=0, B=0, A=255;

    ERROR_DIFF_START();

    uint8 *ptr = (uint8 *)*data + rect.y() * pitch + rect.x() * srcfmt->bytespp;
    while ( height-- ) {
        DUFFS_LOOP4(
                    {
                        if(srcbpp==1) {
                            fl_disemble_rgb(ptr, srcbpp, srcfmt, pixel, (uint8&)R, (uint8&)G, (uint8&)B);
                        } else {
                            fl_disemble_rgba(ptr, srcbpp, srcfmt, pixel, (uint8&)R, (uint8&)G, (uint8&)B, (uint8&)A);
                        }

                        R = G = B = (31 * R + 61 * G + 8 * B) / 100;

                        if(SYSTEM_8BIT) {
                            ERROR_DIFF(R,G,B,*ptr);
                        } else {
                            fl_assemble_rgba(ptr, srcbpp, srcfmt, R, G, B, A);
                        }
                        ptr+=srcbpp;
                    }, width);
        ptr += srcskip;
    }

    ERROR_DIFF_END();

    return true;
}
