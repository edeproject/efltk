#include <efltk/Fl_Renderer.h>

#include "fl_internal.h"

static void Blit1to1(BlitInfo *info)
{
    int width, height;
    uint8 *src, *map, *dst;
    int srcskip, dstskip;

    /* Set up some basic variables */
    width = info->d_width;
    height = info->d_height;
    src = info->s_pixels;
    srcskip = info->s_skip;
    dst = info->d_pixels;
    dstskip = info->d_skip;
    map = info->table;
    bool hw=info->hw_surface;

    while ( height-- ) {
        DUFFS_LOOP(
                   {
                       if(hw) *dst = fl_xpixel(map[*src]);
                       else *dst = map[*src];
                   }
                   dst++;
                   src++;
                   , width);
        src += srcskip;
        dst += dstskip;
    }
}

static void Blit1to2(BlitInfo *info)
{
    int width, height;
    uint8 *src, *dst;
    uint16 *map;
    int srcskip, dstskip;

    /* Set up some basic variables */
    width = info->d_width;
    height = info->d_height;
    src = info->s_pixels;
    srcskip = info->s_skip;
    dst = info->d_pixels;
    dstskip = info->d_skip;
    map = (uint16 *)info->table;

    while ( height-- ) {
        DUFFS_LOOP(
                   {
                       *(uint16 *)dst = map[*src++];
                       dst += 2;
                   },
                   width);
        src += srcskip;
        dst += dstskip;
    }
}

static void Blit1to3(BlitInfo *info)
{
    int o;
    int width, height;
    uint8 *src, *map, *dst;
    int srcskip, dstskip;

    /* Set up some basic variables */
    width = info->d_width;
    height = info->d_height;
    src = info->s_pixels;
    srcskip = info->s_skip;
    dst = info->d_pixels;
    dstskip = info->d_skip;
    map = info->table;

    while ( height-- ) {
        DUFFS_LOOP(
                   {
                       o = *src * 4;
                       dst[0] = map[o++];
                       dst[1] = map[o++];
                       dst[2] = map[o++];
                   }
                   src++;
                   dst += 3;
                   , width);
        src += srcskip;
        dst += dstskip;
    }
}
static void Blit1to4(BlitInfo *info)
{
    int width, height;
    uint8 *src;
    uint32 *map, *dst;
    int srcskip, dstskip;

    /* Set up some basic variables */
    width = info->d_width;
    height = info->d_height;
    src = info->s_pixels;
    srcskip = info->s_skip;
    dst = (uint32 *)info->d_pixels;
    dstskip = info->d_skip/4;
    map = (uint32 *)info->table;

    while ( height-- ) {
        DUFFS_LOOP(
                   *dst++ = map[*src++];
                   , width);
        src += srcskip;
        dst += dstskip;
    }
}

static void Blit1to1Key(BlitInfo *info)
{
    int width = info->d_width;
    int height = info->d_height;
    uint8 *src = info->s_pixels;
    int srcskip = info->s_skip;
    uint8 *dst = info->d_pixels;
    int dstskip = info->d_skip;
    uint8 *palmap = info->table;
    uint32 ckey = info->src->colorkey;
    bool hw=info->hw_surface;

    if ( palmap ) {
        while ( height-- ) {
            DUFFS_LOOP(
                       {
                           if ( *src != ckey ) {
                               if(hw) *dst = fl_xpixel(palmap[*src]);
                               else *dst = palmap[*src];
                           }
                           dst++;
                           src++;
                       },
                       width);
            src += srcskip;
            dst += dstskip;
        }
    } else {
        while ( height-- ) {
            DUFFS_LOOP(
                       {
                           if ( *src != ckey ) {
                               if(hw) *dst = fl_xpixel(*src);
                               else *dst = *src;
                           }
                           dst++;
                           src++;
                       },
                       width);
            src += srcskip;
            dst += dstskip;
        }
    }
}

static void Blit1to2Key(BlitInfo *info)
{
	int width = info->d_width;
	int height = info->d_height;
	uint8 *src = info->s_pixels;
	int srcskip = info->s_skip;
	uint16 *dstp = (uint16 *)info->d_pixels;
	int dstskip = info->d_skip;
	uint16 *palmap = (uint16 *)info->table;
	uint32 ckey = info->src->colorkey;

	/* Set up some basic variables */
	dstskip /= 2;

	while ( height-- ) {
		DUFFS_LOOP(
		{
			if ( *src != ckey ) {
				*dstp=palmap[*src];
			}
			src++;
			dstp++;
		},
		width);
		src += srcskip;
		dstp += dstskip;
	}
}

static void Blit1to3Key(BlitInfo *info)
{
	int width = info->d_width;
	int height = info->d_height;
	uint8 *src = info->s_pixels;
	int srcskip = info->s_skip;
	uint8 *dst = info->d_pixels;
	int dstskip = info->d_skip;
	uint8 *palmap = info->table;
	uint32 ckey = info->src->colorkey;
	int o;

	while ( height-- ) {
		DUFFS_LOOP(
		{
			if ( *src != ckey ) {
				o = *src * 4;
				dst[0] = palmap[o++];
				dst[1] = palmap[o++];
				dst[2] = palmap[o++];
			}
			src++;
			dst += 3;
		},
		width);
		src += srcskip;
		dst += dstskip;
	}
}

static void Blit1to4Key(BlitInfo *info)
{
	int width = info->d_width;
	int height = info->d_height;
	uint8 *src = info->s_pixels;
	int srcskip = info->s_skip;
	uint32 *dstp = (uint32 *)info->d_pixels;
	int dstskip = info->d_skip;
	uint32 *palmap = (uint32 *)info->table;
	uint32 ckey = info->src->colorkey;

	/* Set up some basic variables */
	dstskip /= 4;

	while ( height-- ) {
		DUFFS_LOOP(
		{
			if ( *src != ckey ) {
				*dstp = palmap[*src];
			}
			src++;
			dstp++;
		},
		width);
		src += srcskip;
		dstp += dstskip;
	}
}

static void Blit1toNAlpha(BlitInfo *info)
{
    int width = info->d_width;
    int height = info->d_height;
    uint8 *src = info->s_pixels;
    int srcskip = info->s_skip;
    uint8 *dst = info->d_pixels;
    int dstskip = info->d_skip;
    //Fl_PixelFormat *srcfmt = info->src;
    Fl_PixelFormat *dstfmt = info->dst;
    const Fl_Colormap_Color *srcpal = info->src->palette->colors;
    int dstbpp;
    const int A = info->src->alpha;

    /* Set up some basic variables */
    dstbpp = dstfmt->bytespp;
    uint8 sR=0, sG=0, sB=0;
    uint8 dR=0, dG=0, dB=0;

    while ( height-- ) {
        DUFFS_LOOP4(
                    {
                        uint32 pixel;
                        sR = srcpal[*src].r;
                        sG = srcpal[*src].g;
                        sB = srcpal[*src].b;
                        fl_disemble_rgb(dst, dstbpp, dstfmt,
                                     pixel, dR, dG, dB);
                        fl_alpha_blend(sR, sG, sB, A, dR, dG, dB);
                        fl_assemble_rgb(dst, dstbpp, dstfmt, dR, dG, dB);
                        src++;
                        dst += dstbpp;
                    },
                    width);
        src += srcskip;
        dst += dstskip;
    }
}

static void Blit1toNAlphaKey(BlitInfo *info)
{
    int width = info->d_width;
    int height = info->d_height;
    uint8 *src = info->s_pixels;
    int srcskip = info->s_skip;
    uint8 *dst = info->d_pixels;
    int dstskip = info->d_skip;
    Fl_PixelFormat *srcfmt = info->src;
    Fl_PixelFormat *dstfmt = info->dst;
    const Fl_Colormap_Color *srcpal	= info->src->palette->colors;
    uint32 ckey = srcfmt->colorkey;
    int dstbpp;
    const int A = srcfmt->alpha;

    /* Set up some basic variables */
    dstbpp = dstfmt->bytespp;

    uint8 sR=0, sG=0, sB=0;
    uint8 dR=0, dG=0, dB=0;

    while ( height-- ) {
        DUFFS_LOOP(
                   {
                       if ( *src != ckey ) {
                           uint32 pixel;
                           sR = srcpal[*src].r;
                           sG = srcpal[*src].g;
                           sB = srcpal[*src].b;
                           fl_disemble_rgb(dst, dstbpp, dstfmt,
                                        pixel, dR, dG, dB);
                           fl_alpha_blend(sR, sG, sB, A, dR, dG, dB);
                           fl_assemble_rgb(dst, dstbpp, dstfmt, dR, dG, dB);
                       }
                       src++;
                       dst += dstbpp;
                   },
                   width);
        src += srcskip;
        dst += dstskip;
    }
}

static Blit_Function one_blit[] = {
    NULL, Blit1to1, Blit1to2, Blit1to3, Blit1to4
};

static Blit_Function one_blitkey[] = {
    NULL, Blit1to1Key, Blit1to2Key, Blit1to3Key, Blit1to4Key
};

Blit_Function get_blit_1(Fl_PixelFormat *srcfmt, Fl_PixelFormat *dstfmt, int flags)
{
    int which;
    if(dstfmt->bitspp < 8 ) {
        which = 0;
    } else {
        which = dstfmt->bytespp;
    }	

    switch(flags) {
    case 0:			// copy
        return one_blit[which];

    case 1:			// colorkey
        return one_blitkey[which];

    case 2:			// alpha
        // Supporting 8bpp->8bpp alpha is doable but requires lots of
        // tables which consume space and takes time to precompute,
        // so is better left to the user
        return which >= 2 ? Blit1toNAlpha : NULL;

    case 3:			// alpha + colorkey
        return which >= 2 ? Blit1toNAlphaKey : NULL;
    }

    return 0;
}

