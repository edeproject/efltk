#include <efltk/Fl_Renderer.h>
#include <efltk/x.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Fl_PixelFormat::Fl_PixelFormat()
{
    palette = 0;
    bitspp = bytespp = 0;

    Rloss = Gloss = Bloss = Aloss = 0;
    Rshift = Gshift = Bshift = Ashift = 0;
    Rmask = Gmask = Bmask = Amask = 0;
    colorkey = 0;
    alpha = 255;

    dst=0;
    table=0;
    format_version=(uint)-1;
    identity=false;
}

Fl_PixelFormat::~Fl_PixelFormat()
{
    invalidate_map();
    if(palette) delete palette;
}

void Fl_PixelFormat::realloc(int bits_pp, uint32 R_mask, uint32 G_mask, uint32 B_mask, uint32 A_mask)
{
    if(palette) delete palette;
    palette = 0;
    init(bits_pp, R_mask, G_mask, B_mask, A_mask);
}

void Fl_PixelFormat::copy(Fl_PixelFormat *fmt)
{
    if(palette) delete palette;
    palette = 0;
    if(fmt->palette) {
        palette = new Fl_Colormap();
        palette->copy(fmt->palette);
    }

    bitspp = fmt->bitspp;
    bytespp = fmt->bytespp;

    Rloss = fmt->Rloss;
    Gloss = fmt->Gloss;
    Bloss = fmt->Bloss;
    Aloss = fmt->Aloss;
    Rshift = fmt->Rshift;
    Gshift = fmt->Gshift;
    Bshift = fmt->Bshift;
    Ashift = fmt->Ashift;
    Rmask = fmt->Rmask;
    Gmask = fmt->Gmask;
    Bmask = fmt->Bmask;
    Amask = fmt->Amask;

    colorkey = fmt->colorkey;
    alpha = fmt->alpha;

    //if(fmt->table && fmt->dst)
    //map_this(fmt);

    dst = fmt->dst;
}

void Fl_PixelFormat::init(int bits_pp, uint32 R_mask, uint32 G_mask, uint32 B_mask, uint32 A_mask)
{
	uint32 mask;

	/* Set up the format */
	bitspp = bits_pp;
	bytespp = (bits_pp+7)/8;
	switch(bits_pp) {
	case 1:
		/* Create the 2 color black-white palette */
		palette = new Fl_Colormap(2);
		palette->colors[0].r = 0xFF;
		palette->colors[0].g = 0xFF;
		palette->colors[0].b = 0xFF;
		palette->colors[1].r = 0x00;
		palette->colors[1].g = 0x00;
		palette->colors[1].b = 0x00;
		Rloss = Gloss = Bloss = Aloss = 8;
		Rshift = Gshift = Bshift = Ashift = 0;
		Rmask = Gmask = Bmask = Amask = 0;
		break;

	case 4:
		/* Create the 16 color VGA palette */
		palette = new Fl_Colormap(16);
		/* Punt for now, will this ever be used? */
		memset(palette->colors, 0, palette->ncolors*sizeof(Fl_Color));

		/* Palettized formats have no mask info */
		Rloss = Gloss = Bloss = Aloss = 8;
		Rshift = Gshift = Bshift = Ashift = 0;
		Rmask = Gmask = Bmask = Amask = 0;
		break;

	case 8:
		/* Create an empty 256 color palette */
		palette = new Fl_Colormap(256);
		memset(palette->colors, 0, palette->ncolors*sizeof(Fl_Color));

		/* Palettized formats have no mask info */
		Rloss = Gloss = Bloss = Aloss = 8;
		Rshift = Gshift = Bshift = Ashift = 0;
		Rmask = Gmask = Bmask = Amask = 0;
		break;

	default:
        /* No palette, just packed pixel info */
        palette = 0;
        Rshift = 0;
        Rloss = 8;
        if(R_mask) {
            for(mask = R_mask; !(mask&0x01); mask >>= 1 )
                ++Rshift;
            for(; (mask&0x01); mask >>= 1 )
                --Rloss;
        }
        Gshift = 0;
        Gloss = 8;
        if(G_mask) {
            for(mask = G_mask; !(mask&0x01); mask >>= 1 )
                ++Gshift;
            for(; (mask&0x01); mask >>= 1 )
                --Gloss;
        }
        Bshift = 0;
        Bloss = 8;
        if(B_mask) {
            for(mask = B_mask; !(mask&0x01); mask >>= 1 )
                ++Bshift;
            for(; (mask&0x01); mask >>= 1 )
                --Bloss;
        }
        Ashift = 0;
        Aloss = 8;
        if(A_mask) {
            for(mask = A_mask; !(mask&0x01); mask >>= 1 )
                ++Ashift;
            for(; (mask&0x01); mask >>= 1 )
                --Aloss;
        }
        Rmask = R_mask;
        Gmask = G_mask;
        Bmask = B_mask;
        Amask = A_mask;
        break;
  }
  // Calculate some standard bitmasks, if necessary
  // Note:  This could conflict with an alpha mask, if given.
  if((bits_pp > 8) && !Rmask && !Gmask && !Bmask ) {
      /* R-G-B */
      if(bits_pp > 24 )
          bits_pp = 24;
      Rloss = 8-(bits_pp/3);
      Gloss = 8-(bits_pp/3)-(bits_pp%3);
      Bloss = 8-(bits_pp/3);
      Rshift = ((bits_pp/3)+(bits_pp%3))+(bits_pp/3);
      Gshift = (bits_pp/3);
      Bshift = 0;
      Rmask = ((0xFF>>Rloss)<<Rshift);
      Gmask = ((0xFF>>Gloss)<<Gshift);
      Bmask = ((0xFF>>Bloss)<<Bshift);
  }
}

uint8 *Fl_Renderer::system_convert(Fl_PixelFormat *src_fmt, Fl_Size *src_size, uint8 *src, int flags)
{
    if(!Fl_Renderer::system_inited()) {
        // Init renderer before first convert
        Fl_Renderer::system_init();
    }

    int sbpp = src_fmt->bytespp;
    int dbpp = Fl_Renderer::system_format()->bytespp;

    int src_pitch = Fl_Renderer::calc_pitch(sbpp, src_size->w());
    int dst_pitch = Fl_Renderer::calc_pitch(dbpp, src_size->w());

    uint8 *tmp = new uint8[dst_pitch*src_size->h()];

    Fl_Rect r(0,0,src_size->w(), src_size->h());
    Fl_Renderer::blit(src, &r, src_fmt, src_pitch,
                       tmp, &r, Fl_Renderer::system_format(), dst_pitch, flags);

    return tmp;
}

