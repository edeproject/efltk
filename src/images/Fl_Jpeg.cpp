#include <config.h>

#if HAVE_JPEG

#include <efltk/Fl_Image.h>
#include <efltk/Fl.h>

extern "C" {
#include <jpeglib.h>
}
#include <setjmp.h>

#include "../core/fl_internal.h"
static int jpeg_quality;

/* Define this for fast loading and not as good image quality */
/*#define FAST_JPEG*/

#define JPEG_BYTES_TO_CHECK 4

static bool jpeg_is_valid_file(const char *filename, FILE *fp)
{
    uint8 type[JPEG_BYTES_TO_CHECK];
    bool ret = false;
    uint32 pos = ftell(fp);
    if( fread(type, 2, 1, fp) ) {
        if ( (type[0] == 0xFF) && (type[1] == 0xD8) ) {
            fread(type, 4, 1, fp);
            fread(type, 4, 1, fp);
            ret = (memcmp((char *)type, "JFIF", 4) == 0);
            if(!ret) ret = (memcmp((char *)type, "Exif", 4) == 0);
        }
    }
    fseek(fp, pos, SEEK_SET); //return position in file

    return ret;
}

static bool jpeg_is_valid_mem(const uint8 *stream, uint32 size)
{
    bool ret = false;
    if(size>=10) {
        uint8 *type = (uint8*)stream;
        if ( (type[0] == 0xFF) && (type[1] == 0xD8) ) {
            ret = (memcmp((char *)&type[6], "JFIF", 4) == 0);
            if(!ret) ret = (memcmp((char *)type, "Exif", 4) == 0);
        }
    }
    return ret;
}

#define INPUT_BUFFER_SIZE 4096
typedef struct {
    struct jpeg_source_mgr pub;
    uint8 buffer[INPUT_BUFFER_SIZE];
    void *io;
} my_source_mgr;

/*
 * Initialize source --- called by jpeg_read_header
 * before any data is actually read.
 */
static void init_source (j_decompress_ptr cinfo)
{
    /* We don't actually need to do anything */
    return;
}

/*
 * Fill the input buffer --- called whenever buffer is emptied.
 */
static boolean fill_input_buffer (j_decompress_ptr cinfo)
{
    my_source_mgr *src = (my_source_mgr *)cinfo->src;
    int nbytes;

    nbytes = ((Fl_IO*)src->io)->read(src->buffer, INPUT_BUFFER_SIZE);
    if (nbytes <= 0) {
        /* Insert a fake EOI marker */
        src->buffer[0] = (uint8) 0xFF;
        src->buffer[1] = (uint8) JPEG_EOI;
        nbytes = 2;
    }
    src->pub.next_input_byte = src->buffer;
    src->pub.bytes_in_buffer = nbytes;

    return TRUE;
}

/*
 * Skip data --- used to skip over a potentially large amount of
 * uninteresting data (such as an APPn marker).
 *
 * Writers of suspendable-input applications must note that skip_input_data
 * is not granted the right to give a suspension return.  If the skip extends
 * beyond the data currently in the buffer, the buffer can be marked empty so
 * that the next read will cause a fill_input_buffer call that can suspend.
 * Arranging for additional bytes to be discarded before reloading the input
 * buffer is the application writer's problem.
 */
static void skip_input_data (j_decompress_ptr cinfo, long num_bytes)
{
    my_source_mgr * src = (my_source_mgr *) cinfo->src;

    /* Just a dumb implementation for now.	Could use fseek() except
     * it doesn't work on pipes.  Not clear that being smart is worth
     * any trouble anyway --- large skips are infrequent.
     */
    if (num_bytes > 0) {
        while (num_bytes > (long) src->pub.bytes_in_buffer) {
            num_bytes -= (long) src->pub.bytes_in_buffer;
            (void) src->pub.fill_input_buffer(cinfo);
            /* note we assume that fill_input_buffer will never
             * return FALSE, so suspension need not be handled.
             */
        }
        src->pub.next_input_byte += (size_t) num_bytes;
        src->pub.bytes_in_buffer -= (size_t) num_bytes;
    }
}

/*
 * Terminate source --- called by jpeg_finish_decompress
 * after all data has been read.
 */
static void term_source (j_decompress_ptr cinfo)
{
    /* We don't actually need to do anything */
    return;
}

/*
 * Prepare for input from a stdio stream.
 * The caller must have already opened the stream, and is responsible
 * for closing it after finishing decompression.
 */
static void jpeg_src(j_decompress_ptr cinfo, Fl_IO &jpeg_io)
{
    my_source_mgr *src;

    /* The source object and input buffer are made permanent so that a series
     * of JPEG images can be read from the same file by calling jpeg_stdio_src
     * only before the first one.  (If we discarded the buffer at the end of
     * one image, we'd likely lose the start of the next one.)
     * This makes it unsafe to use this manager and a different source
     * manager serially with the same JPEG object.  Caveat programmer.
     */
    if(cinfo->src == NULL) {	/* first time for this JPEG object? */
        cinfo->src = (struct jpeg_source_mgr *)
            (*cinfo->mem->alloc_small)((j_common_ptr) cinfo, JPOOL_PERMANENT,
                                       sizeof(my_source_mgr));
        src = (my_source_mgr *) cinfo->src;
    }

    src = (my_source_mgr *)cinfo->src;
    src->pub.init_source = init_source;
    src->pub.fill_input_buffer = fill_input_buffer;
    src->pub.skip_input_data = skip_input_data;
    src->pub.resync_to_restart = jpeg_resync_to_restart; /* use default method */
    src->pub.term_source = term_source;
    src->pub.bytes_in_buffer = 0; /* forces fill_input_buffer on first read */
    src->pub.next_input_byte = NULL; /* until buffer loaded */
    src->io = &jpeg_io;
}

struct my_error_mgr {
    struct jpeg_error_mgr errmgr;
    jmp_buf escape;
};

static void my_error_exit(j_common_ptr cinfo)
{
    struct my_error_mgr *err = (struct my_error_mgr *)cinfo->err;
    longjmp(err->escape, 1);
}

static void output_no_message(j_common_ptr cinfo)
{
    /* do nothing */
}

/* Load a JPEG type image from an stream datasource */
static bool jpeg_create(Fl_IO &jpeg_io, uint8 *&data, Fl_PixelFormat &fmt, int &w, int &h)
{
    struct jpeg_decompress_struct cinfo;
    JSAMPROW rowptr[1];    
    struct my_error_mgr jerr;

    /* Create a decompression structure and load the JPEG header */
    cinfo.err = jpeg_std_error(&jerr.errmgr);
    jerr.errmgr.error_exit = my_error_exit;
    jerr.errmgr.output_message = output_no_message;

    if(setjmp(jerr.escape)) {
        /* If we get here, libjpeg found an error */
        jpeg_destroy_decompress(&cinfo);
        Fl::warning("Error loading JPEG");
        if(data) free(data);
        if(data) free(data);
        return false;
    }

    jpeg_create_decompress(&cinfo);
    jpeg_src(&cinfo, jpeg_io);
    jpeg_read_header(&cinfo, TRUE);

    /* Set 24-bit RGB output */
    cinfo.out_color_space = JCS_RGB;
    cinfo.quantize_colors = FALSE;
    switch(jpeg_quality) {
    case FL_QUALITY_GOOD:
        cinfo.dct_method = JDCT_FLOAT;
        cinfo.do_fancy_upsampling = TRUE;
    case FL_QUALITY_BEST:
        cinfo.dct_method = JDCT_ISLOW;
        cinfo.do_block_smoothing = TRUE;
        break;
    case FL_QUALITY_POOR:
        cinfo.scale_num   = 1;
        cinfo.scale_denom = 1;
    default:
    case FL_QUALITY_NORMAL:
        cinfo.dct_method = JDCT_IFAST;
        cinfo.do_fancy_upsampling = FALSE;
        break;
    }
    jpeg_calc_output_dimensions(&cinfo);

    /* Allocate an output surface to hold the image */
    fmt.realloc(24,
#if !WORDS_BIGENDIAN
                0x0000FF, 0x00FF00, 0xFF0000,
#else
                0xFF0000, 0x00FF00, 0x0000FF,
#endif
                0);
    w = cinfo.output_width;
    h = cinfo.output_height;
    int pitch = Fl_Renderer::calc_pitch(fmt.bytespp, w);
    data = (uint8*)malloc(h*pitch*sizeof(uint8));

    /* Decompress the image */
    jpeg_start_decompress(&cinfo);
    while ( cinfo.output_scanline < cinfo.output_height ) {
        rowptr[0] = (JSAMPROW)(uint8 *)data + cinfo.output_scanline * pitch;
        jpeg_read_scanlines(&cinfo, rowptr, (JDIMENSION) 1);
    }
    jpeg_finish_decompress(&cinfo);

    /* Clean up and return */
    jpeg_destroy_decompress(&cinfo);
    return true;
}

static bool jpeg_read_file(FILE *fp, int quality, uint8 *&data, Fl_PixelFormat &format, int &w, int &h)
{
    jpeg_quality = quality;
    Fl_IO jpeg_io;
    jpeg_io.init_io(fp, 0, 0);
    return jpeg_create(jpeg_io, data, format, w, h);
}

static bool jpeg_read_mem(uint8 *stream, uint32 size, int quality, uint8 *&data, Fl_PixelFormat &format, int &w, int &h)
{
    jpeg_quality = quality;
    Fl_IO jpeg_io;
    jpeg_io.init_io(0, stream, size);
    return jpeg_create(jpeg_io, data, format, w, h);
}

Fl_Image_IO jpeg_reader =
{
    /* GENERAL: */
    "JPEG", //name
    "jpeg;jpg", //filename extension

    /* VALIDATE FUNCTIONS: */
    jpeg_is_valid_file, //bool (*is_valid_file)(const char *filename, FILE *fp);
    jpeg_is_valid_mem, //bool (*is_valid_mem)(uint8 *stream, uint32 size);
    NULL, //bool (*is_valid_xpm)(uint8 **stream);

    /* READ FUNCTIONS: */
    jpeg_read_file, //bool (*read_file)(FILE *fp, int quality, uint8 *&data, Fl_PixelFormat &format, int &w, int &h);
    jpeg_read_mem, //bool (*read_mem)(uint8 *stream, uint32 size, int quality, uint8 *&data, Fl_PixelFormat &format, int &w, int &h);

    /* WRITE FUNCTIONS: */
    NULL, //bool (*write_mem)(uint8 *&stream, int &size, int quality, uint8 *data, Fl_PixelFormat &data_format, int w, int h);
    NULL //bool (*write_file)(FILE *fp, int quality, uint8 *data, Fl_PixelFormat &format, int w, int h);
};

#endif
