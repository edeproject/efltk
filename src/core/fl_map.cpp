#include <efltk/Fl_Renderer.h>

#include <string.h>
#include <stdio.h>

// Calculate an 8-bit (3 red, 3 green, 2 blue) dithered palette of colors
void Fl_Colormap::dither_colors(int bitspp)
{
    if(bitspp != 8)
        return;		/* only 8bpp supported right now */

    for(uint i = 0; i < 256; i++) {
        int r, g, b;
        // map each bit field to the full [0, 255] interval,
        // so 0 is mapped to (0, 0, 0) and 255 to (255, 255, 255)

        r = i & 0xe0;
        r |= r >> 3 | r >> 6;
        colors[i].r = r;
        g = (i << 3) & 0xe0;
        g |= g >> 3 | g >> 6;
        colors[i].g = g;
        b = i & 0x3;
        b |= b << 2;
        b |= b << 4;
        colors[i].b = b;
    }
}

// Match an RGB value to a particular palette index
uint8 Fl_Colormap::find_color(uint8 R, uint8 G, uint8 B)
{
    // Do colorspace distance matching
    unsigned int smallest;
    unsigned int distance;
    int rd, gd, bd;
    int i;
    uint8 pixel=0;

    smallest = ~0;
    for ( i=0; i<ncolors; ++i ) {
        rd = colors[i].r - R;
        gd = colors[i].g - G;
        bd = colors[i].b - B;
        distance = (rd*rd)+(gd*gd)+(bd*bd);
        if ( distance < smallest ) {
            pixel = i;
            if ( distance == 0 ) { // Perfect match!
                break;
            }
            smallest = distance;
        }
    }
    return pixel;
}

#define COLOR_EQUAL(c1, c2) (c1.r==c2.r && c1.g==c2.g && c1.b==c2.b)
/* Map from Palette to Palette */
static uint8 *Map1to1(Fl_Colormap *src, Fl_Colormap *dst, bool &identical)
{
    uint8 *map;
    int i;

    if(src->ncolors <= dst->ncolors)
    {
        identical = true;
        /* If an identical palette, no need to map */
        for(int n=0; n<src->ncolors; n++) {
            if(!COLOR_EQUAL(src->colors[n], dst->colors[n])) { identical = false; break; }
        }
        if(identical) return 0;
    }
    identical = false;

    map = new uint8[src->ncolors];
    for ( i=0; i<src->ncolors; i++ ) {
        map[i] = dst->find_color(src->colors[i].r, src->colors[i].g, src->colors[i].b);
    }
    return map;
}

/* Map from Palette to BitField */
static uint8 *Map1toN(Fl_Colormap *src, Fl_PixelFormat *dst)
{
    uint8 *map;
    int i;
    int  bpp;
    unsigned alpha;

    bpp = ((dst->bytespp == 3) ? 4 : dst->bytespp);
    map = new uint8[src->ncolors*bpp];

    alpha = dst->Amask ? 255 : 0;
    /* We memory copy to the pixel map so the endianness is preserved */
    for ( i=0; i<src->ncolors; ++i ) {
        fl_assemble_rgba(&map[i*bpp], dst->bytespp, dst,
                      src->colors[i].r, src->colors[i].g,
                      src->colors[i].b, alpha);
    }
    return map;
}

/* Map from BitField to Dithered-Palette to Palette */
static uint8 *MapNto1(Fl_PixelFormat *src, Fl_Colormap *dst, bool &identical)
{
    /* Generate a 256 color dither palette */
    Fl_Colormap dithered(256);
    dithered.dither_colors(8);

    return Map1to1(&dithered, dst, identical);
}

void Fl_PixelFormat::invalidate_map()
{
    if(!table)
        return;

    dst = 0;
    format_version = (uint)-1;
    if(table) {
        delete []table;
        table = 0;
    }
}

bool Fl_PixelFormat::map_this(Fl_PixelFormat *dstfmt)
{
    /* Clear out any previous mapping */
    invalidate_map();

    /* Figure out what kind of mapping we're doing */
    identity = 0;
    switch(bytespp)
    {
    case 1:
        switch(dstfmt->bytespp)
        {
        case 1:
            /* Palette --> Palette */
            table = Map1to1(palette, dstfmt->palette, identity);
            if(!identity) {
                if(!table) {
                  return false;
                }
            }
            if(bitspp != dstfmt->bitspp)
                identity = 0;
            break;

        default:
            /* Palette --> BitField */
            table = Map1toN(palette, dstfmt);
            if(!table) {
                return false;
            }
            break;
        }
        break;
    default:
        switch(dstfmt->bytespp) {
        case 1:
            /* BitField --> Palette */
            table = MapNto1(this, dstfmt->palette, identity);
            if(!identity) {
                if(!table) {
                    return false;
                }
            }
            identity = 0;	/* Don't optimize to copy */
            break;
        default:
            /* BitField --> BitField */
            if(fl_format_equal(this, dstfmt) )
                identity = 1;
            break;
        }
        break;
    }

    dst = dstfmt;
    format_version = dstfmt->format_version;

    return true;
}

/* Find the opaque pixel value corresponding to an RGB triple */
uint32 Fl_PixelFormat::map_rgb(uint8 r, uint8 g, uint8 b)
{
    if(!palette) {
        return (r >> Rloss) << Rshift
            | (g >> Gloss) << Gshift
            | (b >> Bloss) << Bshift
            | Amask;
    }

    return palette->find_color(r, g, b);
}

/* Find the pixel value corresponding to an RGBA quadruple */
uint32 Fl_PixelFormat::map_rgba(uint8 r, uint8 g, uint8 b, uint8 a)
{
    if(!palette) {
        return (r >> Rloss) << Rshift
            | (g >> Gloss) << Gshift
            | (b >> Bloss) << Bshift
            | ((a >> Aloss) << Ashift & Amask);
    }

    return palette->find_color(r, g, b);
}

void Fl_PixelFormat::get_rgba(uint32 pixel, uint8 &r, uint8 &g, uint8 &b, uint8 &a)
{
    if(!palette) {
        /*
         * This makes sure that the result is mapped to the
         * interval [0..255], and the maximum value for each
         * component is 255. This is important to make sure
         * that white is indeed reported as (255, 255, 255),
         * and that opaque alpha is 255.
         * This only works for RGB bit fields at least 4 bit
         * wide, which is almost always the case.
         */
        unsigned rv, gv, bv, av;
        rv = (pixel & Rmask) >> Rshift;
        r = (rv << Rloss) + (rv >> (8 - Rloss));
        gv = (pixel & Gmask) >> Gshift;
        g = (gv << Gloss) + (gv >> (8 - Gloss));
        bv = (pixel & Bmask) >> Bshift;
        b = (bv << Bloss) + (bv >> (8 - Bloss));
        if(Amask) {
            av = (pixel & Amask) >> Ashift;
            a = (av << Aloss) + (av >> (8 - Aloss));
        } else
            a = 255;
    } else {
        r = palette->colors[pixel].r;
        g = palette->colors[pixel].g;
        b = palette->colors[pixel].b;
        a = 255;
    }
}

void Fl_PixelFormat::get_rgb(uint32 pixel, uint8 &r, uint8 &g, uint8 &b)
{
    if(!palette) {
        /* the note for SDL_GetRGBA above applies here too */
        unsigned rv, gv, bv;
        rv = (pixel & Rmask) >> Rshift;
        r = (rv << Rloss) + (rv >> (8 - Rloss));
        gv = (pixel & Gmask) >> Gshift;
        g = (gv << Gloss) + (gv >> (8 - Gloss));
        bv = (pixel & Bmask) >> Bshift;
        b = (bv << Bloss) + (bv >> (8 - Bloss));
    } else {
        r = palette->colors[pixel].r;
        g = palette->colors[pixel].g;
        b = palette->colors[pixel].b;
    }
}

