#include <efltk/Fl_Image_Filter.h>
#include <efltk/Fl_Image.h>

#include <math.h>

#include "fl_errordiff.h"

#define SYSTEM_8BIT (Fl_Renderer::system_format()->bytespp==1)

bool Fl_Image_Filter::apply_to_this(Fl_Image *image, Fl_Rect *rect, Fl_Image_Filter *filter)
{
    return apply_to_this(image, rect, filter, 1.0, 1.0, 1.0);
}

bool Fl_Image_Filter::apply_to_this(Fl_Image *image, Fl_Rect *rect, Fl_Image_Filter *filter, double val1)
{
    return apply_to_this(image, rect, filter, val1, val1, val1);
}

bool Fl_Image_Filter::apply_to_this(Fl_Image *image, Fl_Rect *rect, Fl_Image_Filter *filter, double val1, double val2)
{
    return apply_to_this(image, rect, filter, val1, val2, val1);
}

bool Fl_Image_Filter::apply_to_this(Fl_Image *image, Fl_Rect *rect, Fl_Image_Filter *filter, double val1, double val2, double val3)
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

Fl_Image *Fl_Image_Filter::apply_to_new(Fl_Image *image, Fl_Rect *rect, Fl_Image_Filter *filter, double val1)
{
    return apply_to_new(image, rect, filter, val1, val1, val1);
}

Fl_Image *Fl_Image_Filter::apply_to_new(Fl_Image *image, Fl_Rect *rect, Fl_Image_Filter *filter, double val1, double val2)
{
    return apply_to_new(image, rect, filter, val1, val2, val1);
}

Fl_Image *Fl_Image_Filter::apply_to_new(Fl_Image *image, Fl_Rect *rect, Fl_Image_Filter *filter, double val1, double val2, double val3)
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
bool FilterBrightness::execute(uint8 **data, Fl_Rect &rect, int pitch, Fl_PixelFormat *fmt, double val1, double val2, double val3)
{
    Fl_PixelFormat *srcfmt = fmt;

    int width = rect.w();
    int height = rect.h();
    int srcskip = pitch - width * srcfmt->bytespp;

    int srcbpp = srcfmt->bytespp;

    uint32 pixel=0;
    int R=0, G=0, B=0, A=255;

    int val = (int)(val1 * 255);

    ERROR_DIFF_START();

    uint8 *ptr = (uint8 *)*data + rect.y() * pitch + rect.x() * srcfmt->bytespp;
    while ( height-- ) {
        DUFFS_LOOP4(
                    {
                        if(srcbpp==1) DISEMBLE_RGB(ptr, srcbpp, srcfmt, pixel, R, G, B);
                        else DISEMBLE_RGBA(ptr, srcbpp, srcfmt, pixel, R, G, B, A);

                        R += val;
                        if(R < 0) R = 0; if(R > 255) R = 255;
                        G += val;
                        if(G < 0) G = 0; if(G > 255) G = 255;
                        B += val;
                        if(B < 0) B = 0; if(B > 255) B = 255;

                        if(SYSTEM_8BIT) { ERROR_DIFF(R,G,B,*ptr); }
                        else { ASSEMBLE_RGBA(ptr, srcbpp, srcfmt, R, G, B, A); }


                        ptr+=srcbpp;
                    }, width);
        ptr += srcskip;
    }
    ERROR_DIFF_END();

    return true;
}

FilterContrast filter_contrast;
bool FilterContrast::execute(uint8 **data, Fl_Rect &rect, int pitch, Fl_PixelFormat *fmt, double val1, double val2, double val3)
{
    Fl_PixelFormat *srcfmt = fmt;

    int width = rect.w();
    int height = rect.h();
    int srcskip = pitch - width * srcfmt->bytespp;

    int srcbpp = srcfmt->bytespp;

    uint32 pixel=0;
    int R=0, G=0, B=0, A=255;

    ERROR_DIFF_START();

    uint8 *ptr = (uint8 *)*data + rect.y() * pitch + rect.x() * srcfmt->bytespp;
    while ( height-- ) {
        DUFFS_LOOP4(
                    {
                        if(srcbpp==1) DISEMBLE_RGB(ptr, srcbpp, srcfmt, pixel, R, G, B);
                        else DISEMBLE_RGBA(ptr, srcbpp, srcfmt, pixel, R, G, B, A);

                        R = (int((R - 127) * val1)) + 127;
                        if(R<0) R = 0; if(R>255) R = 255;

                        G = (int((G - 127) * val2)) + 127;
                        if(G<0) G = 0; if(G>255) G = 255;

                        B = (int((B - 127) * val3)) + 127;
                        if(B<0) B = 0; if(B>255) B = 255;

                        if(SYSTEM_8BIT) { ERROR_DIFF(R,G,B,*ptr); }
                        else { ASSEMBLE_RGBA(ptr, srcbpp, srcfmt, R, G, B, A); }

                        ptr+=srcbpp;
                    }, width);
        ptr += srcskip;
    }
    ERROR_DIFF_END();

    return true;
}

FilterGamma filter_gamma;
bool FilterGamma::execute(uint8 **data, Fl_Rect &rect, int pitch, Fl_PixelFormat *fmt, double val1, double val2, double val3)
{
    if(val1 < 0.01) val1 = 0.01;
    if(val2 < 0.01) val2 = 0.01;
    if(val3 < 0.01) val3 = 0.01;

    Fl_PixelFormat *srcfmt = fmt;

    int width = rect.w();
    int height = rect.h();
    int srcskip = pitch - width * srcfmt->bytespp;

    int srcbpp = srcfmt->bytespp;

    uint32 pixel=0;
    int R=0, G=0, B=0, A=255;

    ERROR_DIFF_START();

    uint8 *ptr = (uint8 *)*data + rect.y() * pitch + rect.x() * srcfmt->bytespp;
    while ( height-- ) {
        DUFFS_LOOP4(
                    {
                        if(srcbpp==1) DISEMBLE_RGB(ptr, srcbpp, srcfmt, pixel, R, G, B);
                        else DISEMBLE_RGBA(ptr, srcbpp, srcfmt, pixel, R, G, B, A);

                        R = (int)(pow(((double)R / 255), (1 / val1)) * 255);
                        if(R<0) R = 0; if(R>255) R = 255;

                        G = (int)(pow(((double)G / 255), (1 / val2)) * 255);
                        if(G<0) G = 0; if(G>255) G = 255;

                        B = (int)(pow(((double)B / 255), (1 / val3)) * 255);
                        if(B<0) B = 0; if(B>255) B = 255;

                        if(SYSTEM_8BIT) { ERROR_DIFF(R,G,B,*ptr); }
                        else { ASSEMBLE_RGBA(ptr, srcbpp, srcfmt, R, G, B, A); }

                        ptr+=srcbpp;
                    }, width);
        ptr += srcskip;
    }

    ERROR_DIFF_END();
    return true;
}

FilterDesaturate filter_desaturate;
bool FilterDesaturate::execute(uint8 **data, Fl_Rect &rect, int pitch, Fl_PixelFormat *fmt, double val1, double val2, double val3)
{	
    Fl_PixelFormat *srcfmt = fmt;

    int width = rect.w();
    int height = rect.h();
    int srcskip = pitch - width * srcfmt->bytespp;

    int srcbpp = srcfmt->bytespp;

    uint32 pixel=0;
    int R=0, G=0, B=0, A=255;

    ERROR_DIFF_START();

    uint8 *ptr = (uint8 *)*data + rect.y() * pitch + rect.x() * srcfmt->bytespp;
    while ( height-- ) {
        DUFFS_LOOP4(
                    {
                        if(srcbpp==1) {
                            DISEMBLE_RGB(ptr, srcbpp, srcfmt, pixel, R, G, B);								
                        } else {
                            DISEMBLE_RGBA(ptr, srcbpp, srcfmt, pixel, R, G, B, A);                                                        
                        }
	
						R = G = B = (31 * R + 61 * G + 8 * B) / 100;

						if(SYSTEM_8BIT) {
							ERROR_DIFF(R,G,B,*ptr);
						} else {
							ASSEMBLE_RGBA(ptr, srcbpp, srcfmt, R, G, B, A);
						}
                        ptr+=srcbpp;
                    }, width);
        ptr += srcskip;
    }

    ERROR_DIFF_END();

    return true;
}
