#include <efltk/Fl_Renderer.h>
#include <efltk/Fl.h>

/* The ASM code doesn't handle 24-bpp stretch blits */
void copy_row3(uint8 *src, int src_w, uint8 *dst, int dst_w)
{
	int i;
	int pos, inc;
	uint8 pixel[3];

	pos = 0x10000;
	inc = (src_w << 16) / dst_w;
	for ( i=dst_w; i>0; --i ) {
		while ( pos >= 0x10000L ) {
			pixel[0] = *src++;
			pixel[1] = *src++;
			pixel[2] = *src++;
			pos -= 0x10000L;
		}
		*dst++ = pixel[0];
		*dst++ = pixel[1];
		*dst++ = pixel[2];
		pos += inc;
	}
}

//#define DISABLE_ASM 1

#if (defined(_WIN32) && !defined(_M_ALPHA) && !defined(_WIN32_WCE) && \
    !defined(__WATCOMC__) && !defined(__LCC__) && !defined(__FREEBCC__)) || \
    (defined(i386) && defined(__GNUC__) && !DISABLE_ASM)
# define USE_ASM_STRETCH
#endif

#ifdef USE_ASM_STRETCH

#if defined(WIN32) || defined(i386)
#define PREFIX16	0x66
#define STORE_BYTE	0xAA
#define STORE_WORD	0xAB
#define LOAD_BYTE	0xAC
#define LOAD_WORD	0xAD
#define RETURN		0xC3
#else
#error Need assembly opcodes for this architecture
#endif

static unsigned char copy_row[8192];

static int generate_rowbytes(int src_w, int dst_w, int bpp)
{
	static struct {
		int bpp;
		int src_w;
		int dst_w;
	} last;

	int i;
	int pos, inc;
	unsigned char *eip;
	unsigned char load, store;

	/* See if we need to regenerate the copy buffer */
	if ( (src_w == last.src_w) &&
	     (dst_w == last.src_w) && (bpp == last.bpp) ) {
		return(0);
	}
	last.bpp = bpp;
	last.src_w = src_w;
	last.dst_w = dst_w;

	switch (bpp) {
	    case 1:
		load = LOAD_BYTE;
		store = STORE_BYTE;
		break;
	    case 2:
	    case 4:
		load = LOAD_WORD;
		store = STORE_WORD;
		break;
	    default:
//		printf("ASM stretch of %d bytes isn't supported\n", bpp);
		return(-1);
	}
	pos = 0x10000;
	inc = (src_w << 16) / dst_w;
	eip = copy_row;
	for ( i=0; i<dst_w; ++i ) {
		while ( pos >= 0x10000L ) {
			if ( bpp == 2 ) {
				*eip++ = PREFIX16;
			}
			*eip++ = load;
			pos -= 0x10000L;
		}
		if ( bpp == 2 ) {
			*eip++ = PREFIX16;
		}
		*eip++ = store;
		pos += inc;
	}
	*eip++ = RETURN;

	/* Verify that we didn't overflow (too late) */
	if ( eip > (copy_row+sizeof(copy_row)) ) {
            //printf("Copy buffer overflow");
            return(-1);
	}
	return(0);
}

#else

#define DEFINE_COPY_ROW(name, type)			\
void name(type *src, int src_w, type *dst, int dst_w)	\
{							\
	int i;						\
	int pos, inc;					\
	type pixel = 0;					\
							\
	pos = 0x10000;					\
	inc = (src_w << 16) / dst_w;			\
	for ( i=dst_w; i>0; --i ) {			\
		while ( pos >= 0x10000L ) {		\
			pixel = *src++;			\
			pos -= 0x10000L;		\
		}					\
		*dst++ = pixel;				\
		pos += inc;				\
	}						\
}
DEFINE_COPY_ROW(copy_row1, uint8)
DEFINE_COPY_ROW(copy_row2, uint16)
DEFINE_COPY_ROW(copy_row4, uint32)

#endif /* USE_ASM_STRETCH */

bool Fl_Renderer::stretch(uint8 *src, int src_bpp, int src_pitch, Fl_Rect *srcrect,
                           uint8 *dst, int dst_bpp, int dst_pitch, Fl_Rect *dstrect)
{
    if(!src || !dst || !srcrect || !dstrect) {
        return false;
    }

    int pos, inc;
    int dst_width;
    int dst_maxrow;
    int src_row, dst_row;
    uint8 *srcp = NULL;
    uint8 *dstp;

#if defined(USE_ASM_STRETCH) && defined(__GNUC__)
    int u1, u2;
#endif

    const int bpp = dst_bpp;

    if(src_bpp != dst_bpp) {
        Fl::warning("Stretch works only with same format surfaces");
        return false;
    }

    /* Set up the data... */
    pos = 0x10000;
    inc = (srcrect->h() << 16) / dstrect->h();
    src_row = srcrect->y();
    dst_row = dstrect->y();
    dst_width = dstrect->w()*bpp;

#ifdef USE_ASM_STRETCH
    /* Write the opcodes for this stretch */
    if((bpp != 3) && (generate_rowbytes(srcrect->w(), dstrect->w(), bpp) < 0) ) {
        return false;
    }
#endif

    int dstx = dstrect->x()*bpp;
    int srcx = srcrect->x()*bpp;	
	
    /* Perform the stretch blit */
    for(dst_maxrow = dst_row + dstrect->h(); dst_row < dst_maxrow; ++dst_row)
    {
        // 4-byte align
        dstp = (uint8 *)dst + (dst_row * dst_pitch) + dstx;

        while(pos >= 0x10000L)
        {
            // 4-byte align
            srcp = (uint8 *)src + (src_row* src_pitch) + srcx;

            ++src_row;
            pos -= 0x10000L;
        }
#ifdef USE_ASM_STRETCH
        switch (bpp) {
        case 3:
            copy_row3(srcp, srcrect->w(), dstp, dstrect->w());
            break;
        default:
#ifdef __GNUC__
            __asm__ __volatile__ ("\
                                  call copy_row\
            "
            : "=&D" (u1), "=&S" (u2)
            : "0" (dstp), "1" (srcp)
            : "memory" );
#else
#ifdef WIN32
            { void *code = &copy_row;
                __asm {
                    push edi
                        push esi

                        mov edi, dstp
                        mov esi, srcp
                        call dword ptr code

                        pop esi
                        pop edi
                }
            }
#else
#error Need inline assembly for this compiler
#endif
#endif /* __GNUC__ */
            break;
        }
#else		
		switch(bpp)
        {
        case 1:			
            copy_row1(srcp, srcrect->w(), dstp, dstrect->w());			
            break;
        case 2:
            copy_row2((uint16 *)srcp, srcrect->w(),
                      (uint16 *)dstp, dstrect->w());
            break;
        case 3:
            copy_row3(srcp, srcrect->w(), dstp, dstrect->w());
            break;
        case 4:
            copy_row4((uint32 *)srcp, srcrect->w(), (uint32 *)dstp, dstrect->w());
            break;
        }
#endif
        pos += inc;
    }
    return true;
}


