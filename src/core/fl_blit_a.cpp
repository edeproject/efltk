#include <efltk/Fl_Renderer.h>

#include "fl_internal.h"

/* Functions to perform alpha blended blitting */

/* N->1 blending with per-surface alpha */
static void BlitNto1SurfaceAlpha(BlitInfo *info)
{
    int width = info->d_width;
    int height = info->d_height;
    uint8 *src = info->s_pixels;
    int srcskip = info->s_skip;
    uint8 *dst = info->d_pixels;
    int dstskip = info->d_skip;
    uint8 *palmap = info->table;
    Fl_PixelFormat *srcfmt = info->src;
    Fl_PixelFormat *dstfmt = info->dst;
    int srcbpp = srcfmt->bytespp;
    bool hw=info->hw_surface;

    const unsigned A = srcfmt->alpha;

    uint32 pixel;
    uint8 sR=0, sG=0, sB=0;
    uint8 dR=0, dG=0, dB=0;

    while ( height-- ) {
        DUFFS_LOOP4(
        {
            fl_disemble_rgb(src, srcbpp, srcfmt, pixel, sR, sG, sB);
            dR = dstfmt->palette->colors[*dst].r;
            dG = dstfmt->palette->colors[*dst].g;
            dB = dstfmt->palette->colors[*dst].b;
            fl_alpha_blend(sR, sG, sB, A, dR, dG, dB);
            dR &= 0xff;
            dG &= 0xff;
            dB &= 0xff;
            /* Pack RGB into 8bit pixel */
            if ( palmap == NULL ) {
                if(hw) *dst = fl_xpixel(((dR>>5)<<(3+2)) | ((dG>>5)<<(2)) | ((dB>>6)<<(0)));
                else *dst = ((dR>>5)<<(3+2)) | ((dG>>5)<<(2)) | ((dB>>6)<<(0));
            } else {
                if(hw) *dst = fl_xpixel(palmap[((dR>>5)<<(3+2)) | ((dG>>5)<<(2)) | ((dB>>6)<<(0))]);
                else *dst = palmap[((dR>>5)<<(3+2)) | ((dG>>5)<<(2)) | ((dB>>6)<<(0))];
            }
            dst++;
            src += srcbpp;
        },
        width);
        src += srcskip;
        dst += dstskip;
    }
}

/* N->1 blending with pixel alpha */
static void BlitNto1PixelAlpha(BlitInfo *info)
{
    int width = info->d_width;
    int height = info->d_height;
    uint8 *src = info->s_pixels;
    int srcskip = info->s_skip;
    uint8 *dst = info->d_pixels;
    int dstskip = info->d_skip;
    uint8 *palmap = info->table;
    Fl_PixelFormat *srcfmt = info->src;
    Fl_PixelFormat *dstfmt = info->dst;
    int srcbpp = srcfmt->bytespp;
    bool hw=info->hw_surface;

    uint8 sR;
    uint8 sG;
    uint8 sB;
    uint8 sA;
    uint8 dR;
    uint8 dG;
    uint8 dB;

    /* FIXME: fix alpha bit field expansion here too? */
    while ( height-- ) {
        DUFFS_LOOP4(
        {
            uint32 pixel;
            fl_disemble_rgba(src,srcbpp,srcfmt,pixel,sR,sG,sB,sA);

            dR = dstfmt->palette->colors[*dst].r;
            dG = dstfmt->palette->colors[*dst].g;
            dB = dstfmt->palette->colors[*dst].b;
            fl_alpha_blend(sR, sG, sB, sA, dR, dG, dB);
            dR &= 0xff;
            dG &= 0xff;
            dB &= 0xff;
            /* Pack RGB into 8bit pixel */
            if ( palmap == NULL ) {
                if(hw) *dst = fl_xpixel(((dR>>5)<<(3+2)) | ((dG>>5)<<(2)) | ((dB>>6)<<(0)));
                else *dst = ((dR>>5)<<(3+2)) | ((dG>>5)<<(2)) | ((dB>>6)<<(0));
            } else {
                if(hw) *dst = fl_xpixel(palmap[((dR>>5)<<(3+2)) | ((dG>>5)<<(2)) | ((dB>>6)<<(0))]);
                else *dst = palmap[((dR>>5)<<(3+2)) | ((dG>>5)<<(2)) | ((dB>>6)<<(0))];
            }
            dst++;
            src += srcbpp;
        },
        width);
        src += srcskip;
        dst += dstskip;
    }
}

/* colorkeyed N->1 blending with per-surface alpha */
static void BlitNto1SurfaceAlphaKey(BlitInfo *info)
{
    int width = info->d_width;
    int height = info->d_height;
    uint8 *src = info->s_pixels;
    int srcskip = info->s_skip;
    uint8 *dst = info->d_pixels;
    int dstskip = info->d_skip;
    uint8 *palmap = info->table;
    Fl_PixelFormat *srcfmt = info->src;
    Fl_PixelFormat *dstfmt = info->dst;
    int srcbpp = srcfmt->bytespp;
    uint32 ckey = srcfmt->colorkey;
    bool hw=info->hw_surface;

    const int A = srcfmt->alpha;

    uint32 pixel;
    uint8 sR=0, sG=0, sB=0;
    uint8 dR=0, dG=0, dB=0;

    while ( height-- ) {
        DUFFS_LOOP(
        {
            fl_disemble_rgb(src, srcbpp, srcfmt, pixel, sR, sG, sB);
            if ( pixel != ckey ) {
                dR = dstfmt->palette->colors[*dst].r;
                dG = dstfmt->palette->colors[*dst].g;
                dB = dstfmt->palette->colors[*dst].b;
                fl_alpha_blend(sR, sG, sB, A, dR, dG, dB);
                dR &= 0xff;
                dG &= 0xff;
                dB &= 0xff;
                /* Pack RGB into 8bit pixel */
                if ( palmap == NULL ) {
                    if(hw) *dst = fl_xpixel(((dR>>5)<<(3+2)) | ((dG>>5)<<(2)) | ((dB>>6)<<(0)));
                    else *dst = ((dR>>5)<<(3+2)) | ((dG>>5)<<(2)) | ((dB>>6)<<(0));
                } else {
                    if(hw) *dst = fl_xpixel(palmap[((dR>>5)<<(3+2)) | ((dG>>5)<<(2)) | ((dB>>6)<<(0))]);
                    else *dst = palmap[((dR>>5)<<(3+2)) | ((dG>>5)<<(2)) | ((dB>>6)<<(0))];
                }
            }
            dst++;
            src += srcbpp;
        },
        width);
        src += srcskip;
        dst += dstskip;
    }
}

/* fast RGB888->(A)RGB888 blending with surface alpha=128 special case */
static void BlitRGBtoRGBSurfaceAlpha128(BlitInfo *info)
{
    int width = info->d_width;
    int height = info->d_height;
    uint32 *srcp = (uint32 *)info->s_pixels;
    int srcskip = info->s_skip >> 2;
    uint32 *dstp = (uint32 *)info->d_pixels;
    int dstskip = info->d_skip >> 2;

    while(height--) {
        DUFFS_LOOP4(
        {
            uint32 s = *srcp++;
            uint32 d = *dstp;
            *dstp++ = ((((s & 0x00fefefe) + (d & 0x00fefefe)) >> 1)
                       + (s & d & 0x00010101)) | 0xff000000;
        }, width);
        srcp += srcskip;
        dstp += dstskip;
    }
}

/* fast RGB888->RGB888 blending with surface alpha  (3 bytes per pixel only) */
static void BlitRGBtoRGBSurfaceAlpha_24(BlitInfo *info)
{
    unsigned alpha = info->src->alpha;
	int width = info->d_width;
	int height = info->d_height;
    uint8 *srcp = (uint8 *)info->s_pixels;
    int srcskip = info->s_skip;
    uint8 *dstp = (uint8 *)info->d_pixels;
    int dstskip = info->d_skip;

	uint32 s, d;
    uint32 s1, d1;
	uint32 dp;
    while(height--) {
		DUFFS_LOOP4(
        {
			//s = *((uint32*)srcp);
			//d = *((uint32*)dstp);
			s = (srcp[0]<<16)|(srcp[1]<<8)|srcp[2];
			d = (dstp[0]<<16)|(dstp[1]<<8)|dstp[2];

			if(alpha==128) {				
				dp = ((((s & 0xfefefe) + (d & 0xfefefe)) >> 1) + (s & d & 0x010101)) | 0xff000000;			
			} else {
				s1 = s & 0xff00ff;
				d1 = d & 0xff00ff;
				d1 = (d1 + ((s1 - d1) * alpha >> 8)) & 0xff00ff;
	            s &= 0x00ff00;
				d &= 0x00ff00;
			    d = (d + ((s - d) * alpha >> 8)) & 0x00ff00;				
				dp = d1 | d | 0xff000000;
			}	
			
			dstp[0] = ((dp & 0xFF0000)>>16);
			dstp[1] = ((dp & 0xFF00)>>8);
			dstp[2] = (dp & 0xFF);

			srcp+=info->src->bytespp;
			dstp+=info->dst->bytespp;
		}, width);
        srcp += srcskip;
        dstp += dstskip;
	}    
}

/* fast RGB888->(A)RGB888 blending with surface alpha */
static void BlitRGBtoRGBSurfaceAlpha(BlitInfo *info)
{
    unsigned alpha = info->src->alpha;
    if(alpha == 128) {
        BlitRGBtoRGBSurfaceAlpha128(info);
    } else {
        int width = info->d_width;
        int height = info->d_height;
        uint32 *srcp = (uint32 *)info->s_pixels;
        int srcskip = info->s_skip >> 2;
        uint32 *dstp = (uint32 *)info->d_pixels;
        int dstskip = info->d_skip >> 2;

        while(height--) {
            DUFFS_LOOP4(
            {
                uint32 s;
                uint32 d;
                uint32 s1;
                uint32 d1;
                s = *srcp;
                d = *dstp;
                s1 = s & 0xff00ff;
                d1 = d & 0xff00ff;
                d1 = (d1 + ((s1 - d1) * alpha >> 8))
                    & 0xff00ff;
                s &= 0xff00;
                d &= 0xff00;
                d = (d + ((s - d) * alpha >> 8)) & 0xff00;
                *dstp = d1 | d | 0xff000000;
                ++srcp;
                ++dstp;
            }, width);
            srcp += srcskip;
            dstp += dstskip;
        }
    }
}

/* fast ARGB888->(A)RGB888 blending with pixel alpha */
static void BlitRGBtoRGBPixelAlpha(BlitInfo *info)
{
    int width = info->d_width;
    int height = info->d_height;
    uint32 *srcp = (uint32 *)info->s_pixels;
    int srcskip = info->s_skip >> 2;
    uint32 *dstp = (uint32 *)info->d_pixels;
    int dstskip = info->d_skip >> 2;

    while(height--) {
        DUFFS_LOOP4(
        {
            uint32 dalpha;
            uint32 d;
            uint32 s1;
            uint32 d1;
            uint32 s = *srcp;
            uint32 alpha = s >> 24;
            /* FIXME: Here we special-case opaque alpha since the
             compositioning used (>>8 instead of /255) doesn't handle
             it correctly. Also special-case alpha=0 for speed?
             Benchmark this! */
            if(alpha == 255) {
                *dstp = (s & 0x00ffffff) | (*dstp & 0xff000000);
            } else {
                /*
                 * take out the middle component (green), and process
                 * the other two in parallel. One multiply less.
                 */
                d = *dstp;
                dalpha = d & 0xff000000;
                s1 = s & 0xff00ff;
                d1 = d & 0xff00ff;
                d1 = (d1 + ((s1 - d1) * alpha >> 8)) & 0xff00ff;
                s &= 0xff00;
                d &= 0xff00;
                d = (d + ((s - d) * alpha >> 8)) & 0xff00;
                *dstp = d1 | d | dalpha;
            }
            ++srcp;
            ++dstp;
        }, width);
        srcp += srcskip;
        dstp += dstskip;
    }
}

/* 16bpp special case for per-surface alpha=50%: blend 2 pixels in parallel */

/* blend a single 16 bit pixel at 50% */
#define BLEND16_50(d, s, mask)						\
    ((((s & mask) + (d & mask)) >> 1) + (s & d & (~mask & 0xffff)))

/* blend two 16 bit pixels at 50% */
#define BLEND2x16_50(d, s, mask)					     \
    (((s & (mask | mask << 16)) >> 1) + ((d & (mask | mask << 16)) >> 1) \
    + (s & d & (~(mask | mask << 16))))

static void Blit16to16SurfaceAlpha128(BlitInfo *info, uint16 mask)
{
    int width = info->d_width;
    int height = info->d_height;
    uint16 *srcp = (uint16 *)info->s_pixels;
    int srcskip = info->s_skip >> 1;
    uint16 *dstp = (uint16 *)info->d_pixels;
    int dstskip = info->d_skip >> 1;

    while(height--) {
        if(((unsigned long)srcp ^ (unsigned long)dstp) & 2) {
            /*
             * Source and destination not aligned, pipeline it.
             * This is mostly a win for big blits but no loss for
             * small ones
             */
            uint32 prev_sw;
            int w = width;

            /* handle odd destination */
            if((unsigned long)dstp & 2) {
                uint16 d = *dstp, s = *srcp;
                *dstp = BLEND16_50(d, s, mask);
                dstp++;
                srcp++;
                w--;
            }
            srcp++;	/* srcp is now 32-bit aligned */

            /* bootstrap pipeline with first halfword */
            prev_sw = ((uint32 *)srcp)[-1];

            while(w > 1) {
                uint32 sw, dw, s;
                sw = *(uint32 *)srcp;
                dw = *(uint32 *)dstp;
                if(Fl_Renderer::lil_endian())
                    s = (prev_sw >> 16) + (sw << 16);
                else
                    s = (prev_sw << 16) + (sw >> 16);
                prev_sw = sw;
                *(uint32 *)dstp = BLEND2x16_50(dw, s, mask);
                dstp += 2;
                srcp += 2;
                w -= 2;
            }

            /* final pixel if any */
            if(w) {
                uint16 d = *dstp, s;
                if(Fl_Renderer::lil_endian())
                    s = prev_sw >> 16;
                else
                    s = prev_sw;
                *dstp = BLEND16_50(d, s, mask);
                srcp++;
                dstp++;
            }
            srcp += srcskip - 1;
            dstp += dstskip;
        } else {
            /* source and destination are aligned */
            int w = width;

            /* first odd pixel? */
            if((unsigned long)srcp & 2) {
                uint16 d = *dstp, s = *srcp;
                *dstp = BLEND16_50(d, s, mask);
                srcp++;
                dstp++;
                w--;
            }
            /* srcp and dstp are now 32-bit aligned */

            while(w > 1) {
                uint32 sw = *(uint32 *)srcp;
                uint32 dw = *(uint32 *)dstp;
                *(uint32 *)dstp = BLEND2x16_50(dw, sw, mask);
                srcp += 2;
                dstp += 2;
                w -= 2;
            }

            /* last odd pixel? */
            if(w) {
                uint16 d = *dstp, s = *srcp;
                *dstp = BLEND16_50(d, s, mask);
                srcp++;
                dstp++;
            }
            srcp += srcskip;
            dstp += dstskip;
        }
    }
}

/* fast RGB565->RGB565 blending with surface alpha */
static void Blit565to565SurfaceAlpha(BlitInfo *info)
{
    unsigned alpha = info->src->alpha;
    if(alpha == 128) {
        Blit16to16SurfaceAlpha128(info, 0xf7de);
    } else {
        int width = info->d_width;
        int height = info->d_height;
        uint16 *srcp = (uint16 *)info->s_pixels;
        int srcskip = info->s_skip >> 1;
        uint16 *dstp = (uint16 *)info->d_pixels;
        int dstskip = info->d_skip >> 1;
        alpha >>= 3;	/* downscale alpha to 5 bits */

        while(height--) {
            DUFFS_LOOP4(
            {
                uint32 s = *srcp++;
                uint32 d = *dstp;
                /*
                 * shift out the middle component (green) to
                 * the high 16 bits, and process all three RGB
                 * components at the same time.
                 */
                s = (s | (s << 16)) & 0x07e0f81f;
                d = (d | (d << 16)) & 0x07e0f81f;
                d = (d + (((s - d) * alpha) >> 5)) & 0x07e0f81f;
				//d += (s - d) * alpha >> 5;
				//d &= 0x07e0f81f;                
                *dstp++ = (d | (d >> 16));
            }, width);
            srcp += srcskip;
            dstp += dstskip;
        }
    }
}

/* fast RGB555->RGB555 blending with surface alpha */
static void Blit555to555SurfaceAlpha(BlitInfo *info)
{
    unsigned alpha = info->src->alpha; /* downscale alpha to 5 bits */
    if(alpha == 128) {
        Blit16to16SurfaceAlpha128(info, 0xfbde);
    } else {
        int width = info->d_width;
        int height = info->d_height;
        uint16 *srcp = (uint16 *)info->s_pixels;
        int srcskip = info->s_skip >> 1;
        uint16 *dstp = (uint16 *)info->d_pixels;
        int dstskip = info->d_skip >> 1;
        alpha >>= 3;		/* downscale alpha to 5 bits */

        while(height--) {
            DUFFS_LOOP4(
            {
                uint32 s = *srcp++;
                uint32 d = *dstp;
                /*
                 * shift out the middle component (green) to
                 * the high 16 bits, and process all three RGB
                 * components at the same time.
                 */
                s = (s | (s << 16)) & 0x03e07c1f;
                d = (d | (d << 16)) & 0x03e07c1f;
				d += (((s - d) * alpha) >> 5) & 0x03e07c1f;
                //d += (s - d) * alpha >> 5;
                //d &= 0x03e07c1f;
                *dstp++ = d | d >> 16;
            }, width);
            srcp += srcskip;
            dstp += dstskip;
        }
    }
}

/* fast ARGB8888->RGB565 blending with pixel alpha */
static void BlitARGBto565PixelAlpha(BlitInfo *info)
{
    int width = info->d_width;
    int height = info->d_height;
    uint32 *srcp = (uint32 *)info->s_pixels;
    int srcskip = info->s_skip >> 2;
    uint16 *dstp = (uint16 *)info->d_pixels;
    int dstskip = info->d_skip >> 1;

    while(height--) {
        DUFFS_LOOP4(
        {
            uint32 s = *srcp;
            unsigned alpha = s >> 27; /* downscale alpha to 5 bits */
            /* FIXME: Here we special-case opaque alpha since the
             compositioning used (>>8 instead of /255) doesn't handle
             it correctly. Also special-case alpha=0 for speed?
             Benchmark this! */
            if(alpha == (255 >> 3)) {
                *dstp = (s >> 8 & 0xf800) + (s >> 5 & 0x7e0)
                    + (s >> 3  & 0x1f);
            } else {
                uint32 d = *dstp;
                /*
                 * convert source and destination to G0RAB65565
                 * and blend all components at the same time
                 */
                s = ((s & 0xfc00) << 11) + (s >> 8 & 0xf800)
                    + (s >> 3 & 0x1f);
                d = (d | (d << 16)) & 0x07e0f81f;
                d += (((s - d) * alpha) >> 5) & 0x07e0f81f;
                //d += (s - d) * alpha >> 5;
                //d &= 0x07e0f81f;
                *dstp = d | d >> 16;
            }
            srcp++;
            dstp++;
        }, width);
        srcp += srcskip;
        dstp += dstskip;
    }
}

/* fast ARGB8888->RGB555 blending with pixel alpha */
static void BlitARGBto555PixelAlpha(BlitInfo *info)
{
    int width = info->d_width;
    int height = info->d_height;
    uint32 *srcp = (uint32 *)info->s_pixels;
    int srcskip = info->s_skip >> 2;
    uint16 *dstp = (uint16 *)info->d_pixels;
    int dstskip = info->d_skip >> 1;

    while(height--) {
        DUFFS_LOOP4(
        {
            unsigned alpha;
            uint32 s = *srcp;
            alpha = s >> 27; /* downscale alpha to 5 bits */
            /* FIXME: Here we special-case opaque alpha since the
             compositioning used (>>8 instead of /255) doesn't handle
             it correctly. Also special-case alpha=0 for speed?
             Benchmark this! */
            if(alpha == (255 >> 3)) {
                *dstp = (s >> 9 & 0x7c00) + (s >> 6 & 0x3e0)
                    + (s >> 3  & 0x1f);
            } else {
                uint32 d = *dstp;
                /*
                 * convert source and destination to G0RAB65565
                 * and blend all components at the same time
                 */
                s = ((s & 0xf800) << 10) + (s >> 9 & 0x7c00)
                    + (s >> 3 & 0x1f);
                d = (d | d << 16) & 0x03e07c1f;
                d += (s - d) * alpha >> 5;
                d &= 0x03e07c1f;
                *dstp = d | d >> 16;
            }
            srcp++;
            dstp++;
        }, width);
        srcp += srcskip;
        dstp += dstskip;
    }
}

/* General (slow) N->N blending with per-surface alpha */
static void BlitNtoNSurfaceAlpha(BlitInfo *info)
{
    int width = info->d_width;
    int height = info->d_height;
    uint8 *src = info->s_pixels;
    int srcskip = info->s_skip;
    uint8 *dst = info->d_pixels;
    int dstskip = info->d_skip;
    Fl_PixelFormat *srcfmt = info->src;
    Fl_PixelFormat *dstfmt = info->dst;
    int srcbpp = srcfmt->bytespp;
    int dstbpp = dstfmt->bytespp;
    unsigned sA = srcfmt->alpha;
    unsigned dA = dstfmt->Amask ? 255 : 0;

    uint32 pixel;
    uint8 sR=0, sG=0, sB=0;
    uint8 dR=0, dG=0, dB=0;

    while ( height-- ) {
        DUFFS_LOOP4(
        {
            fl_disemble_rgb(src, srcbpp, srcfmt, pixel, sR, sG, sB);
            fl_disemble_rgb(dst, dstbpp, dstfmt, pixel, dR, dG, dB);
            fl_alpha_blend(sR, sG, sB, sA, dR, dG, dB);
            fl_assemble_rgba(dst, dstbpp, dstfmt, dR, dG, dB, dA);
            src += srcbpp;
            dst += dstbpp;
        },
        width);
        src += srcskip;
        dst += dstskip;
    }
}

/* General (slow) colorkeyed N->N blending with per-surface alpha */
static void BlitNtoNSurfaceAlphaKey(BlitInfo *info)
{
    int width = info->d_width;
    int height = info->d_height;
    uint8 *src = info->s_pixels;
    int srcskip = info->s_skip;
    uint8 *dst = info->d_pixels;
    int dstskip = info->d_skip;
    Fl_PixelFormat *srcfmt = info->src;
    Fl_PixelFormat *dstfmt = info->dst;
    uint32 ckey = srcfmt->colorkey;
    int srcbpp = srcfmt->bytespp;
    int dstbpp = dstfmt->bytespp;
    unsigned sA = srcfmt->alpha;
    unsigned dA = dstfmt->Amask ? 255 : 0;

    uint32 pixel;
    uint8 sR=0, sG=0, sB=0;
    uint8 dR=0, dG=0, dB=0;

    while ( height-- ) {
        DUFFS_LOOP4(
        {
            fl_retrieve_rgb_pixel(src, srcbpp, pixel);
            if(pixel != ckey) {
                fl_rgb_from_pixel(pixel, srcfmt, sR, sG, sB);
                fl_disemble_rgb(dst, dstbpp, dstfmt, pixel, dR, dG, dB);
                fl_alpha_blend(sR, sG, sB, sA, dR, dG, dB);
                fl_assemble_rgba(dst, dstbpp, dstfmt, dR, dG, dB, dA);
            }
            src += srcbpp;
            dst += dstbpp;
        },
        width);
        src += srcskip;
        dst += dstskip;
    }
}

/* General (slow) N->N blending with pixel alpha */
static void BlitNtoNPixelAlpha(BlitInfo *info)
{
    int width = info->d_width;
    int height = info->d_height;
    uint8 *src = info->s_pixels;
    int srcskip = info->s_skip;
    uint8 *dst = info->d_pixels;
    int dstskip = info->d_skip;
    Fl_PixelFormat *srcfmt = info->src;
    Fl_PixelFormat *dstfmt = info->dst;

    int  srcbpp;
    int  dstbpp;

    /* Set up some basic variables */
    srcbpp = srcfmt->bytespp;
    dstbpp = dstfmt->bytespp;

	uint8 sR, sG, sB, sA;
	uint8 dR, dG, dB, dA;

    /* FIXME: for 8bpp source alpha, this doesn't get opaque values
     quite right. for <8bpp source alpha, it gets them very wrong
     (check all macros!)
     It is unclear whether there is a good general solution that doesn't
     need a branch (or a divide). */
    while ( height-- ) {
        DUFFS_LOOP4(
        {
            uint32 pixel;
            fl_disemble_rgba(src, srcbpp, srcfmt, pixel, sR, sG, sB, sA);
            fl_disemble_rgba(dst, dstbpp, dstfmt, pixel, dR, dG, dB, dA);
            fl_alpha_blend(sR, sG, sB, sA, dR, dG, dB);
            fl_assemble_rgba(dst, dstbpp, dstfmt, dR, dG, dB, dA);
            src += srcbpp;
            dst += dstbpp;
        },
        width);
        src += srcskip;
        dst += dstskip;
    }
}

#ifdef _DEBUG
#include <stdio.h>
#define once(t) { static bool once=true; if(once) { printf("Using '%s' alpha blitter\n", t); once=false; } }
#else
#define once(t)
#endif

Blit_Function get_blit_a(Fl_PixelFormat *src_fmt, Fl_PixelFormat *dst_fmt, int flags)
{
    Fl_PixelFormat *sf = src_fmt;
    Fl_PixelFormat *df = dst_fmt;

    if(sf->Amask == 0) {
        if(flags==1) {
            if(df->bytespp == 1) {
                once("BlitNto1SurfaceAlphaKey");
                return BlitNto1SurfaceAlphaKey;
            } else {
                once("BlitNtoNSurfaceAlphaKey");
                return BlitNtoNSurfaceAlphaKey;
            }
        } else {
            /* Per-surface alpha blits */
            switch(df->bytespp) {
            case 1:
                once("BlitNto1SurfaceAlpha");
                return BlitNto1SurfaceAlpha;

            case 2:
                if(sf->identity)
                {					
                    if(df->Gmask == 0x7e0) {
                        once("Blit565to565SurfaceAlpha");						
                        return Blit565to565SurfaceAlpha;
                    } else if(df->Gmask == 0x3e0) {
                        once("Blit555to555SurfaceAlpha");
                        return Blit555to555SurfaceAlpha;
                    }
                }
                once("BlitNtoNSurfaceAlpha");
                return BlitNtoNSurfaceAlpha;                

            case 4:
                if(sf->Rmask == df->Rmask
                   && sf->Gmask == df->Gmask
                   && sf->Bmask == df->Bmask
                   && (sf->Rmask | sf->Gmask | sf->Bmask) == 0xffffff
                   && sf->bytespp == 4) {
                    once("BlitRGBtoRGBSurfaceAlpha");
                    return BlitRGBtoRGBSurfaceAlpha;
                } else {
                    once("BlitNtoNSurfaceAlpha");
                    return BlitNtoNSurfaceAlpha;
                }
            case 3:
            default:
				if(sf->Rmask == df->Rmask
                   && sf->Gmask == df->Gmask
                   && sf->Bmask == df->Bmask
                   && (sf->Rmask | sf->Gmask | sf->Bmask) == 0xffffff
                   && sf->bytespp == 3) {
					once("BlitRGBtoRGBSurfaceAlpha_24");
					return BlitRGBtoRGBSurfaceAlpha_24;
				}
				once("BlitNtoNSurfaceAlpha");
                return BlitNtoNSurfaceAlpha;
            }
        }
    } else {
        /* Per-pixel alpha blits */
        switch(df->bytespp) {
        case 1:
            once("BlitNto1PixelAlpha");
            return BlitNto1PixelAlpha;

        case 2:
            if((sf->bytespp == 4 && sf->Amask == 0xff000000)
               && sf->Gmask == 0xff00
               && ((sf->Rmask == 0xff && df->Rmask == 0x1f)
               || (sf->Bmask == 0xff && df->Bmask == 0x1f)))
            {
                if(df->Gmask == 0x7e0) {
                    once("BlitARGBto565PixelAlpha");
                    return BlitARGBto565PixelAlpha;
                }
                else if(df->Gmask == 0x3e0) {
                    once("BlitARGBto555PixelAlpha");
                    return BlitARGBto555PixelAlpha;
                }
            }
            once("BlitNtoNPixelAlpha");
            return BlitNtoNPixelAlpha;

        case 4:
            if(sf->Amask == 0xff000000
               && sf->Rmask == df->Rmask
               && sf->Gmask == df->Gmask
               && sf->Bmask == df->Bmask
               && sf->bytespp == 4) {
                once("BlitRGBtoRGBPixelAlpha");
                return BlitRGBtoRGBPixelAlpha;
            }

            once("BlitNtoNPixelAlpha");
            return BlitNtoNPixelAlpha;

        case 3:
        default:
            once("BlitNtoNPixelAlpha");
            return BlitNtoNPixelAlpha;
        }
    }
}

