#include <efltk/fl_math.h>
#include <efltk/Fl_Image_Filter.h>
#include <efltk/Fl_Image.h>

#include "fl_internal.h"

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
    uint8 R=0, G=0, B=0, A=255;
    int dR,dG,dB;

    int val = (int)((val1-1) * 255);

    uint8 *ptr = (uint8 *)*data + rect.y() * pitch + rect.x() * srcfmt->bytespp;
    if(srcbpp>1) {
        while ( height-- ) {
            DUFFS_LOOP4(
            {
                fl_disemble_rgba(ptr, srcbpp, srcfmt, pixel, R, G, B, A);

                dR = R+val;
                dG = G+val;
                dB = B+val;
                if(dR > 255) dR = 255; else if(dR < 0) dR=0;
                if(dG > 255) dG = 255; else if(dG < 0) dG=0;
                if(dB > 255) dB = 255; else if(dB < 0) dB=0;

                fl_assemble_rgba(ptr, srcbpp, srcfmt, dR, dG, dB, A);

                ptr+=srcbpp;
            }, width);
            ptr += srcskip;
        }

    } else {

        // indexed
        Fl_Colormap *pal = srcfmt->palette;
        for(int n=0;n<pal->ncolors; n++) {
            dR = pal->colors[n].r+val;
            dG = pal->colors[n].b+val;
            dB = pal->colors[n].g+val;
            if(dR > 255) dR = 255; else if(dR < 0) dR=0;
            if(dG > 255) dG = 255; else if(dG < 0) dG=0;
            if(dB > 255) dB = 255; else if(dB < 0) dB=0;

            pal->colors[n].r = dR;
            pal->colors[n].b = dG;
            pal->colors[n].g = dB;
        }
    }

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
    uint8 R=0, G=0, B=0, A=255;
    int dR,dG,dB;

    uint8 *ptr = (uint8 *)*data + rect.y() * pitch + rect.x() * srcfmt->bytespp;
    if(srcbpp>1) {
        while ( height-- ) {
            DUFFS_LOOP4(
            {
                fl_disemble_rgba(ptr, srcbpp, srcfmt, pixel, R, G, B, A);

                dR = (int((R - 127) * val1)) + 127;
                dG = (int((G - 127) * val2)) + 127;
                dB = (int((B - 127) * val3)) + 127;
                if(dR > 255) dR = 255; else if(dR < 0) dR=0;
                if(dG > 255) dG = 255; else if(dG < 0) dG=0;
                if(dB > 255) dB = 255; else if(dB < 0) dB=0;

                fl_assemble_rgba(ptr, srcbpp, srcfmt, dR, dG, dB, A);

                ptr+=srcbpp;
            }, width);
            ptr += srcskip;
        }
    } else {

        // indexed
        Fl_Colormap *pal = srcfmt->palette;
        for(int n=0;n<pal->ncolors; n++) {
            dR = (int((pal->colors[n].r - 127) * val1)) + 127;
            dG = (int((pal->colors[n].g - 127) * val2)) + 127;
            dB = (int((pal->colors[n].b - 127) * val3)) + 127;
            if(dR > 255) dR = 255; else if(dR < 0) dR=0;
            if(dG > 255) dG = 255; else if(dG < 0) dG=0;
            if(dB > 255) dB = 255; else if(dB < 0) dB=0;

            pal->colors[n].r = dR;
            pal->colors[n].b = dG;
            pal->colors[n].g = dB;
        }
    }

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
    uint8 R=0, G=0, B=0, A=255;
    int dR,dG,dB;

    uint8 *ptr = (uint8 *)*data + rect.y() * pitch + rect.x() * srcfmt->bytespp;
    if(srcbpp>1) {
        while ( height-- ) {
            DUFFS_LOOP4(
            {
                fl_disemble_rgba(ptr, srcbpp, srcfmt, pixel, R, G, B, A);

                dR = (int)(pow(((float)R / 255), (1 / val1)) * 255);
                dG = (int)(pow(((float)G / 255), (1 / val2)) * 255);
                dB = (int)(pow(((float)B / 255), (1 / val3)) * 255);
                if(dR > 255) dR = 255; else if(dR < 0) dR=0;
                if(dG > 255) dG = 255; else if(dG < 0) dG=0;
                if(dB > 255) dB = 255; else if(dB < 0) dB=0;

                fl_assemble_rgba(ptr, srcbpp, srcfmt, dR, dG, dB, A);

                ptr+=srcbpp;
            }, width);
            ptr += srcskip;
        }
    } else {

        // indexed
        Fl_Colormap *pal = srcfmt->palette;
        for(int n=0;n<pal->ncolors; n++) {
            dR = (int)(pow(((float)pal->colors[n].r / 255), (1 / val1)) * 255);
            dG = (int)(pow(((float)pal->colors[n].g / 255), (1 / val2)) * 255);
            dB = (int)(pow(((float)pal->colors[n].b / 255), (1 / val3)) * 255);
            if(dR > 255) dR = 255; else if(dR < 0) dR=0;
            if(dG > 255) dG = 255; else if(dG < 0) dG=0;
            if(dB > 255) dB = 255; else if(dB < 0) dB=0;

            pal->colors[n].r = dR;
            pal->colors[n].b = dG;
            pal->colors[n].g = dB;
        }
    }

    return true;
}

FilterGrayscale filter_grayscale;
bool FilterGrayscale::execute(uint8 **data, Fl_Rect &rect, int pitch, Fl_PixelFormat *fmt, float val1, float val2, float val3)
{	
    Fl_PixelFormat *srcfmt = fmt;

    int width = rect.w();
    int height = rect.h();
    int srcskip = pitch - width * srcfmt->bytespp;

    int srcbpp = srcfmt->bytespp;

    uint32 pixel=0;
    uint8 R=0, G=0, B=0, A=255;
    int D;

    val3 = .114f * val1;
    val2 = .587f * val1;
    val1 = .299f * val1;

    uint8 *ptr = (uint8 *)*data + rect.y() * pitch + rect.x() * srcfmt->bytespp;
    if(srcbpp>1) {
        while ( height-- ) {
            DUFFS_LOOP4(
            {
                fl_disemble_rgba(ptr, srcbpp, srcfmt, pixel, R, G, B, A);

                D = (int)(val1 * R + val2 * G + val3 * B);
                if(D > 255) D = 255; else if(D < 0) D=0;

                fl_assemble_rgba(ptr, srcbpp, srcfmt, D, D, D, A);
                ptr+=srcbpp;
            }, width);
            ptr += srcskip;
        }
    } else {
        // indexed
        Fl_Colormap *pal = srcfmt->palette;
        for(int n=0;n<pal->ncolors; n++) {

            D = (int)(val1 * pal->colors[n].r + val2 * pal->colors[n].g + val3 * pal->colors[n].b);
            if(D > 255) D = 255; else if(D < 0) D=0;

            pal->colors[n].r = D;
            pal->colors[n].b = D;
            pal->colors[n].g = D;
        }
    }

    return true;
}

FilterForeBlend filter_foreblend;
bool FilterForeBlend::execute(uint8 **data, Fl_Rect &rect, int pitch, Fl_PixelFormat *fmt, float val1, float val2, float val3)
{	
    Fl_PixelFormat *srcfmt = fmt;

    int width = rect.w();
    int height = rect.h();
    int srcskip = pitch - width * srcfmt->bytespp;

    int srcbpp = srcfmt->bytespp;

    if(val1>1.0f) val1=1.0f; else if(val1<0) val1=0;
    if(val2>1.0f) val2=1.0f; else if(val2<0) val2=0;
    if(val3>1.0f) val3=1.0f; else if(val3<0) val3=0;

    int sR = (int)(val1 * 255);
    int sG = (int)(val2 * 255);
    int sB = (int)(val3 * 255);
    int sA = fmt->alpha;

    uint32 pixel=0;
    uint8 R=0, G=0, B=0;

    uint8 *ptr = (uint8 *)*data + rect.y() * pitch + rect.x() * srcfmt->bytespp;
    if(srcbpp>1) {
        while ( height-- ) {
            DUFFS_LOOP4(
            {
                fl_disemble_rgb(ptr, srcbpp, srcfmt, pixel, R, G, B);

                fl_alpha_blend(sR, sG, sB, sA, R, G, B);

                fl_assemble_rgba(ptr, srcbpp, srcfmt, R, G, B, sA);
                ptr+=srcbpp;
            }, width);
            ptr += srcskip;
        }
    } else {

        // indexed
        Fl_Colormap *pal = srcfmt->palette;
        for(int n=0;n<pal->ncolors; n++)
        {
            R = pal->colors[n].r;
            G = pal->colors[n].g;
            B = pal->colors[n].b;

            fl_alpha_blend(sR, sG, sB, sA, R, G, B);

            pal->colors[n].r = R;
            pal->colors[n].g = G;
            pal->colors[n].b = B;
        }
    }

    return true;
}

FilterBackBlend filter_backblend;
bool FilterBackBlend::execute(uint8 **data, Fl_Rect &rect, int pitch, Fl_PixelFormat *fmt, float val1, float val2, float val3)
{	
    Fl_PixelFormat *srcfmt = fmt;

    int width = rect.w();
    int height = rect.h();
    int srcskip = pitch - width * srcfmt->bytespp;

    int srcbpp = srcfmt->bytespp;

    if(val1>1.0f) val1=1.0f; else if(val1<0) val1=0;
    if(val2>1.0f) val2=1.0f; else if(val2<0) val2=0;
    if(val3>1.0f) val3=1.0f; else if(val3<0) val3=0;

    int sR = (int)(val1 * 255);
    int sG = (int)(val2 * 255);
    int sB = (int)(val3 * 255);
    uint8 A = fmt->alpha;
    uint8 bR, bG, bB;

    uint32 pixel=0;
    uint8 R=0, G=0, B=0;

    uint8 *ptr = (uint8 *)*data + rect.y() * pitch + rect.x() * srcfmt->bytespp;
    if(srcbpp>1) {
        while ( height-- ) {
            DUFFS_LOOP4(
            {
                if(srcfmt->Amask)
                    fl_disemble_rgba(ptr, srcbpp, srcfmt, pixel, R, G, B, A);
                else
                    fl_disemble_rgb(ptr, srcbpp, srcfmt, pixel, R, G, B);

                bR=sR; bG=sG; bB=sB;
                fl_alpha_blend(R, G, B, A, bR, bG, bB);

                fl_assemble_rgba(ptr, srcbpp, srcfmt, bR, bG, bB, A);
                ptr+=srcbpp;
            }, width);
            ptr += srcskip;
        }
    } else {

        // indexed
        Fl_Colormap *pal = srcfmt->palette;
        for(int n=0;n<pal->ncolors; n++)
        {
            R = pal->colors[n].r;
            G = pal->colors[n].g;
            B = pal->colors[n].b;

            bR=sR; bG=sG; bB=sB;
            fl_alpha_blend(R, G, B, A, bR, bG, bB);

            pal->colors[n].r = bR;
            pal->colors[n].b = bG;
            pal->colors[n].g = bB;
        }
    }

    return true;
}
