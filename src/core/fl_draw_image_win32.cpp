#ifdef _WIN32

#include <efltk/Fl_Image.h>
#include <efltk/x.h>
#include <efltk/fl_draw.h>

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include <config.h>

/* helper fn */
static int SussScreenDepth();
static bool _system_inited = false;

Fl_PixelFormat sys_fmt;
HINSTANCE *sys_display = 0;
BITMAPINFO *bmi;

Fl_PixelFormat *Fl_Renderer::system_format() { return &sys_fmt; }

bool Fl_Renderer::system_inited() {
    return _system_inited;
}

void Fl_Renderer::system_init()
{
	/* Determine the screen depth */
	int bitspp = SussScreenDepth();

	uint32 Rmask=0, Gmask=0, Bmask=0, Amask=0;
	switch(bitspp) {
		case 15:
			Rmask = 0x00007c00;
			Gmask = 0x000003e0;
			Bmask = 0x0000001f;
			bitspp = 16;
			break;
		case 16:
			Rmask = 0x0000f800;
			Gmask = 0x000007e0;
			Bmask = 0x0000001f;
			break;
		case 24:
		case 32:
			/* GDI defined as 8-8-8 */
			Rmask = 0x00ff0000;
			Gmask = 0x0000ff00;
			Bmask = 0x000000ff;
			break;
		default:
			break;
	}

	sys_fmt.init(bitspp,Rmask,Gmask,Bmask,Amask);

	bool is16bit = (sys_fmt.bytespp == 2);

	/* Suss out the bitmap info header */
	int bmi_size = sizeof(*bmi);
	if(is16bit) {
		/* is16bit modes, palette area used for rgb bitmasks */
		bmi_size += 3*sizeof(DWORD);
	} 
#if USE_COLORMAP
	else if(sys_fmt.palette) {
		bmi_size += sys_fmt.palette->ncolors * sizeof(RGBQUAD);
	}
#endif
	bmi = (BITMAPINFO *)malloc(bmi_size);
	
	bmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi->bmiHeader.biPlanes = 1;
	bmi->bmiHeader.biXPelsPerMeter = 0;
	bmi->bmiHeader.biYPelsPerMeter = 0;
	bmi->bmiHeader.biClrUsed = 0;
	bmi->bmiHeader.biClrImportant = 0;
	bmi->bmiHeader.biBitCount = sys_fmt.bitspp;

	if(is16bit) {
		// BI_BITFIELDS tells CreateDIBSection about the rgb masks in the palette
		bmi->bmiHeader.biCompression = BI_BITFIELDS;
		((uint32*)bmi->bmiColors)[0] = sys_fmt.Rmask;
		((uint32*)bmi->bmiColors)[1] = sys_fmt.Gmask;
		((uint32*)bmi->bmiColors)[2] = sys_fmt.Bmask;
	} else {
		bmi->bmiHeader.biCompression = BI_RGB;	// BI_BITFIELDS is for 565 vs 555
#if USE_COLORMAP
                if(sys_fmt.palette) {
                    extern void copy_palette(Fl_Colormap *map);
                    copy_palette(sys_fmt.palette);
                    for (int i=0; i < sys_fmt.palette->ncolors; i++) *((short*)(bmi->bmiColors)+i) = i;
                }
#endif
	}
	_system_inited = true;
}

/*
  Helper fn to work out which screen depth windows is currently using.
  15 bit mode is considered 555 format, 16 bit is 565.
  returns 0 for unknown mode.
  (Derived from code in sept 1999 Windows Developer Journal
  http://www.wdj.com/code/archive.html)
*/
static int SussScreenDepth()
{
#ifdef NO_GETDIBITS
	int depth;
	HDC hdc;

	hdc = GetDC(SDL_Window);
	depth = GetDeviceCaps(hdc, PLANES) * GetDeviceCaps(hdc, BITSPIXEL);
	ReleaseDC(SDL_Window, hdc);
#ifndef _WIN32_WCE
	// AFAIK 16 bit CE devices have indeed RGB 565
	if ( depth == 16 ) {
		depth = 15;	/* GDI defined as RGB 555 */
	}
#endif
	return(depth);
#else
	int dib_size;
	LPBITMAPINFOHEADER dib_hdr;
	HDC hdc;
	HBITMAP hbm;

	// Allocate enough space for a DIB header plus palette (for
	// 8-bit modes) or bitfields (for 16- and 32-bit modes)
   	dib_size = sizeof(BITMAPINFOHEADER) + 256 * sizeof (RGBQUAD);
	dib_hdr = (LPBITMAPINFOHEADER) malloc(dib_size);
	memset(dib_hdr, 0, dib_size);
	dib_hdr->biSize = sizeof(BITMAPINFOHEADER);
    
	// Get a device-dependent bitmap that's compatible with the screen.
	hdc = GetDC(NULL);
	hbm = CreateCompatibleBitmap( hdc, 1, 1 );

	// Convert the DDB to a DIB.  We need to call GetDIBits twice:
	// the first call just fills in the BITMAPINFOHEADER; the 
	// second fills in the bitfields or palette.
   	GetDIBits(hdc, hbm, 0, 1, NULL, (LPBITMAPINFO) dib_hdr, DIB_RGB_COLORS);
	GetDIBits(hdc, hbm, 0, 1, NULL, (LPBITMAPINFO) dib_hdr, DIB_RGB_COLORS);
	DeleteObject(hbm);
	ReleaseDC(NULL, hdc);

	switch( dib_hdr->biBitCount )
	{
	case 8:     return 8;
    case 24:    return 24;
    case 32:    return 32;
    case 16:
		if( dib_hdr->biCompression == BI_BITFIELDS ) {
			// check the red mask
			switch( ((DWORD*)((char*)dib_hdr + dib_hdr->biSize))[0] ) {
			case 0xf800: return 16;    /* 565 */
			case 0x7c00: return 15;    /* 555 */
			}
		}
    }
    
	return 0; // poo.
#endif /* NO_GETDIBITS */
}

bool Fl_Renderer::render_to_pixmap(uint8 *src, Fl_Rect *src_rect, Fl_PixelFormat *src_fmt, int src_pitch,
									Pixmap dst, Fl_Rect *dst_rect, GC dst_gc, int flags)
{
    if(!Fl_Renderer::system_inited())
        return false;

    if(flags&FL_ALIGN_SCALE && src_rect->w()==dst_rect->w() && src_rect->h()==dst_rect->h()) {
        flags = 0;
    }

	int X = dst_rect->x();
	int Y = dst_rect->y();
	int W = dst_rect->w();
	int H = dst_rect->h();
	int cx = src_rect->x();
	int cy = src_rect->y();
	bool ret = false;

	if(flags & FL_ALIGN_SCALE)
	{
		int dst_pitch = Fl_Renderer::calc_pitch(sys_fmt.bytespp, W);
		bmi->bmiHeader.biWidth = W;  
		bmi->bmiHeader.biHeight = -H; //Set to negative, cause in windoze bitmaps are upsidedown...
		bmi->bmiHeader.biSizeImage = H * dst_pitch;
		
		uint8 *dst_ptr = new uint8[bmi->bmiHeader.biSizeImage];
		if(Fl_Renderer::stretch(src, sys_fmt.bytespp, src_pitch, src_rect,
			dst_ptr, sys_fmt.bytespp, dst_pitch, dst_rect))
		{			
			SetDIBitsToDevice(dst_gc, 
				X, Y, W, H, //dst points - upper-left
				0, 0, //src points - lower-left
				0, H, //Scanline start/end
				(LPSTR)(dst_ptr), //array
				bmi, //bmi
				(fl_palette ? DIB_PAL_COLORS : DIB_RGB_COLORS)
				);
			ret = true;
		}
		delete []dst_ptr;
	} 
	else
	{
		W = src_rect->w();
		H = src_rect->h();
		bmi->bmiHeader.biWidth = W;  
		bmi->bmiHeader.biHeight = -H; //Set to negative, cause in windoze bitmaps are upsidedown...
		bmi->bmiHeader.biSizeImage = H * src_pitch;
		
		//printf("%d %d %d %d\n", X, Y, W, H);	
		uint8 *src_ptr=src;
		SetDIBitsToDevice(dst_gc, 
			X, Y, W, H, //dst points - upper-left
			0, 0, //src points - lower-left
			0, H, //Scanline start/end
			(LPSTR)(src_ptr), //array
			bmi, //bmi
			(fl_palette ? DIB_PAL_COLORS : DIB_RGB_COLORS)
			);
		ret = true;
	}

	return ret;
}

//make device context from pixmap and palette
static HDC make_DC(HBITMAP pixmap, HPALETTE pal) 
{
  HDC new_gc = CreateCompatibleDC(fl_gc);
  SetTextAlign(new_gc, TA_BASELINE|TA_LEFT);
  SetBkMode(new_gc, TRANSPARENT);

  if(pal) SelectPalette(new_gc, pal, FALSE);

  SelectObject(new_gc, pixmap);
  return new_gc;
}


void Fl_Image::to_screen(int XP, int YP, int WP, int HP, int, int)
{	
    int X,Y,W,H;
    fl_clip_box(XP, YP, WP, HP, X, Y, W, H);

    int cx = X-XP;
    int cy = Y-YP;

    if(cx+W > WP)
        W = WP-cx;

    if(W <= 0)
        return;

    if(cy+H > HP)
        H = HP-cy;

    if(H <= 0)
        return;

    // convert to Xlib coordinates:
    fl_transform(X,Y);

	if(mask) {			
		if(id) {		
			// both color and mask:
#if 0
	      HDC new_gc = make_DC((Pixmap)id, fl_palette);
      
			if(_masktype == ALPHA)
			{
				TransparentBlt(
					fl_gc,
					X,
					Y,
					W,
					H,
				
					new_gc,
					cx,
					cy,
					W,
					H,
				
					0
				);
			} else if(_masktype == COLOR_KEY)
			{
				TransparentBlt(
					fl_gc,
					X,
					Y,
					W,
					H,
				
					new_gc,
					cx,
					cy,
					W,
					H,
				
					fmt.colorkey
				);
			} else {
				BitBlt(fl_gc, X, Y, W, H, new_gc, cx, cy, SRCCOPY);
			}

			DeleteDC(new_gc);
# else
      fl_color(0);
      SetTextColor(fl_gc, 0);
      HDC new_gc = make_DC((Pixmap)mask, fl_palette);
	  HDC new_gc2= make_DC((Pixmap)id, fl_palette);

	  BitBlt(new_gc2, 0, 0, w, h, new_gc, 0, 0, SRCAND); // This should be done only once for performance
      // secret bitblt code found in old MSWindows reference manual:
      BitBlt(fl_gc, X, Y, W, H, new_gc, cx, cy, 0xE20746L);
      BitBlt(fl_gc, X, Y, W, H, new_gc2, cx, cy, SRCPAINT);
      DeleteDC(new_gc);
      DeleteDC(new_gc2);		
# endif
    } else {
      // mask only
      HDC tempdc = CreateCompatibleDC(fl_gc);
      SelectObject(tempdc, (HGDIOBJ)mask);
      SetTextColor(fl_gc, 0); // VP : seems necessary at least under win95
      //SelectObject(fl_gc, fl_brush);
      // secret bitblt code found in old MSWindows reference manual:
      BitBlt(fl_gc, X, Y, W, H, tempdc, cx, cy, 0xE20746L);
      DeleteDC(tempdc);	  
    }
  }
	else if (id) {		
		// pix only, no mask
		//fl_copy_offscreen(X, Y, W, H, (Pixmap)id, cx, cy);
		HDC new_gc = make_DC((Pixmap)id, fl_palette);		
		BitBlt(fl_gc, X, Y, W, H, new_gc, cx, cy, SRCCOPY);				
		DeleteDC(new_gc);
		
  } // else { no mask or id, probably an error... }
}

void Fl_Image::to_screen_tiled(int XP, int YP, int WP, int HP, int, int)
{
    // Figure out the smallest rectangle enclosing this and the clip region:
    int X,Y,W,H; fl_clip_box(XP, YP, WP, HP, X, Y, W, H);
    if (W <= 0 || H <= 0) return;
    int cx = 0;
    int cy = 0;
    cx += X-XP; cy += Y-YP;
    fl_push_clip(X, Y, W, H);

    {
        int temp = -cx % w;
        cx = (temp>0 ? w : 0) - temp;
        temp = -cy % h;
        cy = (temp>0 ? h : 0) - temp;

        int ccx=cx;
        while (-cy < H) {
            while (-cx < W) {
                to_screen(X-cx, Y-cy, w, h, 0,0);
                cx -= w;
            }
            cy -= h;
            cx = ccx;
        }

    }

    fl_pop_clip();
}


#endif // _WIN32
