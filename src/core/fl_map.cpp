#include <efltk/Fl_Renderer.h>

#include <string.h>
#include <stdio.h>

// Calculate an 8-bit (3 red, 3 green, 2 blue) dithered palette of colors
void DitherColors(Fl_Colormap_Color *colors, int bitspp)
{    
    if(bitspp != 8)
        return;		/* only 8bpp supported right now */

    uint i;

    for(i = 0; i < 256; i++) {
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
uint8 FindColor(Fl_Colormap *pal, uint8 R, uint8 G, uint8 B)
{
    /* Do colorspace distance matching */
    unsigned int smallest;
    unsigned int distance;
    int rd, gd, bd;
    int i;
    uint8 pixel=0;

    smallest = ~0;
    for ( i=0; i<pal->ncolors; ++i ) {
        rd = pal->colors[i].r - R;
        gd = pal->colors[i].g - G;
        bd = pal->colors[i].b - B;
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
        map[i] = FindColor(dst, src->colors[i].r, src->colors[i].g, src->colors[i].b);
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
        ASSEMBLE_RGBA(&map[i*bpp], dst->bytespp, dst,
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
    DitherColors(dithered.colors, 8);

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
            if(FORMAT_EQUAL(this, dstfmt) )
                identity = 1;
            break;
        }
        break;
    }

    dst = dstfmt;
    format_version = dstfmt->format_version;

    return true;
}

