/* -*- mode: C++ -*-
 * "$Id$"
 *
 * This file is used to compile fltk. It should not be necessary for
 * programs that use fltk to refer to this file, and this file is not
 * included by any of the fltk header files.
 *
 * If this file is "configh.in" it is the input to ./configure.
 */

/* The fltk libraries are compiled as shared libraries ("dlls"). Due
   to stupid Windoze stuff, this is passed as a compile-time option,
   to avoid having *every* file depend on config.h, and because the
   programs linked with fltk *also* need to know this.
*/
/* #define FL_SHARED 0 */

/* Set this to 0 if your system does not have OpenGL. This will
   disable all the code in libfltk_gl and disable the demo programs
   that use OpenGL.
*/


#define HAVE_GL 1

/* Setting this to zero will delete code to handle X and win32
   colormaps, this will save a good deal of code (especially for
   fl_draw_image), but fltk will only work on TrueColor visuals.
*/
#define USE_COLORMAP 0

/* Use the new Xft library to draw fonts. If you have a new XServer
   with the XRender extension and you have FreeType and some Type1
   or TrueType fonts, you will get anti-aliased text. However,
   contrary to popular belief, Xft is useful without these. It
   replaces a huge amount of cruft used to figure out fonts with
   a standardized system. I see no reason Xft cannot be improved
   to work at least as well as fltk does at selecting fonts, at
   that point there is no reason not to use it.
*/
#define USE_XFT 0

/* Do we have the X double-buffer extension?  Turning this on will
   make the list_visuals program produce more information.
*/
#define HAVE_XDBE 0

/* Actually try to use the double-buffer extension? Fl_Double_Window
   and Fl_Overlay_Window will use this. The new version limits itself
   to doing swap without clipping turned on and should work on more
   X servers than the fltk1 version.
*/
#ifdef HAVE_XDBE
#define USE_XDBE 0
#endif

/* Did we detect the X overlay extension? This enables code to locate
   the overlay visual for use by Fl_Overlay_Window and Fl_Gl_Window.
*/
#define HAVE_OVERLAY 0

/* Use the X overlay extension?  FLTK will try to use an overlay
   visual for Fl_Overlay_Window and for Fl_Menu_Window (ie the menus
   and tooltips). This also adds a substantial amount of code to FLTK
   so that it can manage an extra visual. Tested on IRIX and
   XFree86. Does not work with current versions of Xft because Xft
   cannot handle the colormapped visuals that overlays normally use.
*/
#if USE_XFT
# define USE_OVERLAY 0
#else
# define USE_OVERLAY HAVE_OVERLAY
#endif

/* Does OpenGL have the ability to draw into the overlay? Currently
   this uses the same code as X for finding the overlay visual,
   however it is possible that future versions of GLX will use
   other methods.
*/
#define HAVE_GL_OVERLAY HAVE_OVERLAY

/* Use the OpenGL overlay for Gl_Window::draw_overlay(). There is
   probably no reason to turn this off if overlays are possible.
   Fonts work even if Xft is used because OpenGL bypasses the Xft
   font mechanism.
*/
#if HAVE_GL
# define USE_GL_OVERLAY HAVE_GL_OVERLAY
#else
# define USE_GL_OVERLAY 0
#endif

/* Byte order of your machine: 1 = big-endian, 0 = little-endian.
*/
#define WORDS_BIGENDIAN 0

/* Types used by fl_draw_image.  One of U32 or U64 must be defined.
   U16 is optional but FLTK will work better with it!
*/
#define U16 unsigned short
#define U32 unsigned
#undef U64

/* Unix header files that differ on some older systems:
*/
#define HAVE_DIRENT_H 1
#define HAVE_SYS_NDIR_H 0
#define HAVE_SYS_DIR_H 0
#define HAVE_NDIR_H 0
#define HAVE_SCANDIR 0
#define HAVE_SYS_SELECT_H 0

/* Does the system have the really useful snprintf() and vsnprintf()
   functions? If not, fltk includes emulation functions. Also see the
   fltk/vsnprintf.h header which allows user programs to access these
   emulations.
*/
#define HAVE_SNPRINTF 0
#define HAVE_VSNPRINTF 0

/* Possibly missing function and inline replacement: */
#define HAVE_STRCASECMP 0

#if ! HAVE_STRCASECMP
# define strcasecmp(a,b) stricmp(a,b)
# define strncasecmp(a,b,c) strnicmp(a,b,c)
#endif

/* Possibly missing function and inline replacement: */
#define HAVE_STRTOK_R 0

#if ! HAVE_STRTOK_R
#  define strtok_r(a,b,c) strtok(a,b)
#endif

/* Use the Posix poll() call instead of select() ? */
#define USE_POLL 0

/* Do we have libpng ? (for reading .png images) */
#define HAVE_PNG 0

/* Do we have libjpeg ? (for reading .jpg images) */
#define HAVE_JPEG 0

/* Enables Fl::lock() and Fl::unlock() on Unix */
#define HAVE_PTHREAD 0

/* Enables fl_load_plugin() on Unix */
#define HAVE_DLOPEN 0

/* Prefix */
#define PREFIX "/usr/local"

/* Where, after ~/.ede, to look for configuration files */
#define CONFIGDIR "/usr/local/share/ede"

/* The BoXX machines (and possibly other Linux machines) have bugs in
   the X/OpenGL driver for FireGL for handling hardware overlays. Turn
   this on to work around these, but it will cause the overlay to
   blink unnecessarily.
*/
#define BOXX_OVERLAY_BUGS 0

/* The SGI 320 NT machines have a bug where the cursor interferes with
   the hardware overlay. Turn this on to work around this. I have been
   told this slows down display quite a bit on some NT machines.
*/
#define SGI320_BUG 0

/* Enables Windows GUI emulation: clicking on most widgets (such as
   buttons) moves the focus to them. This makes some useful GUI designs
   impossible.
*/
#define CLICK_MOVES_FOCUS 1

/* Enables Windows GUI emulation: hitting the Alt key navigates the
   focus to the menubar. This makes using Alt as a modifier very
   difficult because the user can't press it and then change their
   mind and release it.
*/
#define ALT_GOES_TO_MENUBAR 1

/* Enables loop unrolling using Duffs looping, this generally
   very good way to speed up all image operations, but it make
   binary ~80Kb bigger.
*/
#define USE_DUFFS_LOOP 1

/* Disables all assembly code inside Efltk library. */
#define DISABLE_ASM 0

/* Enables NLS localization support */
#define ENABLE_NLS 0

/* Enables UTF8 */
#define HAVE_XUTF8 1
#define UNICODE 1

/*
 * End of "$Id$".
 */
