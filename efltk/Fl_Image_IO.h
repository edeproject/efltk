#ifndef _FL_IMAGE_IO_H_
#define _FL_IMAGE_IO_H_

#include "Enumerations.h"
#include "Fl_Renderer.h"
#include "Fl_PtrList.h"
#include "Fl_Export.h"

#include <stdio.h> //For FILE

/** 
 * Fl_Image_IO quality types.
 * See Fl_Image_IO
 */
typedef enum Fl_ImageQualityEnum {	
    FL_QUALITY_POOR = 0,	///< Poor quality
    FL_QUALITY_NORMAL,		///< Default quality type.
    FL_QUALITY_GOOD,		///< Good quality
    FL_QUALITY_BEST			///< Best quality
} Fl_ImageQuality;

/** 
 * Fl_Image IO struct. Support for eFLTK basic image read/write operations.
 * Features of IO can be obtained by checking if function of this struct is not NULL.
 * For example, if IO supports only reading, are write methods NULL.
 *
 * Fl_Image_IO functions are NOT allowed to throw any exceptions that it doesn't handle it self!
 *
 * Currently only PNG supports writing.
 */
typedef struct FL_API Fl_Image_IO_Struct
{
    /* GENERAL: */

    /**
	 * Name of image type, e.g. "JPEG" or "PNG" 
	 */
    char *name;

    /**
	 * Supported file extension, separated by semicolon.
	 * e.g. "jpeg;jpg" 
	 */
    char *extensions;

    /* VALIDATE FUNCTIONS: */

    /**
	 * Check if filename has valid extension and/or contains valid image data. 
	 * Returns true if success.
	 * 
	 * @param filename Absolute path to file.
	 */
    bool (*is_valid_file)(const char *filename);

    /**
	 * Check if 'data' is valid image data.
	 * Returns true if success.
	 * 
	 * @param data	Pointer to data in memory.
	 * @param size	Size of data.
	 */
    bool (*is_valid_mem)(const uint8 *data, uint32 size);

    /* READ FUNCTIONS: */

	/**
	 * Read and uncompress image from file. 
	 * Returns true if success.
	 *
	 * @param filename	Absolute path to filename to write.
	 * @param quality	Quality for uncompress engine, not all image types supports this.
	 * @param data		Uncompressed image data is stored to this.
	 * @param format	Format of image data is stored to this. Caller MUST free data using "free()" function.
	 * @param w			Width of readed image is stored to this.
	 * @param h			Height of readed image is stored to this.
	 */
    bool (*read_file)(const char *filename, int quality, uint8 *&data, Fl_PixelFormat &data_format, int &w, int &h);

	/**
	 * Read and uncompress image from data. 
	 * Returns true if success.
	 *
	 * @param stream	Pointer to data to read in memory.
	 * @param size		Size of data in bytes.
	 * @param quality	Quality for uncompress engine, not all image types supports this.
	 * @param data		Uncompressed image data is stored to this.
	 * @param format	Format of image data is stored to this. Caller MUST free data using "free()" function.
	 * @param w			Width of readed image is stored to this.
	 * @param h			Height of readed image is stored to this.
	 */
    bool (*read_mem)(const uint8 *stream, uint32 size, int quality, uint8 *&data, Fl_PixelFormat &data_format, int &w, int &h);

    /* WRITE FUNCTIONS: */

    /** 
	 * Write and/or compress image data to memory.
	 * Returns true if success.
	 * 
	 * @param stream	Compressed data is stored to this. Caller MUST free data with "free()" function. 
	 * @param size		Size of data.
	 * @param quality	Preffered saving quality, not all image types supports this.
	 * @param data		Uncompressed image data.
	 * @param format	Format of uncompressed image data.
	 * @param w			Width of uncompressed image.
	 * @param h			Height of uncompressed image.
	 */
    bool (*write_mem)(uint8 *&stream, int &size, int quality, const uint8 *data, const Fl_PixelFormat &data_format, int w, int h);

    /** 
	 * Write and/or compress image data to memory.
	 * Returns true if success.
	 * 
	 * @param filename	Absolute path to filename to write.
	 * @param quality	Preffered saving quality, not all image types supports this.
	 * @param data		Uncompressed image data.
	 * @param format	Format of uncompressed image data.
	 * @param w			Width of uncompressed image.
	 * @param h			Height of uncompressed image.
	 */
    bool (*write_file)(const char *filename, int quality, const uint8 *data, const Fl_PixelFormat &data_format, int w, int h);

} Fl_Image_IO;

// Image IO functions:
extern FL_API void fl_register_imageio(Fl_Image_IO *reader);
extern FL_API void fl_unregister_imageio(Fl_Image_IO *reader);

extern FL_API Fl_Image_IO *fl_find_imageio(Fl_Image_IO *reader);
extern FL_API Fl_Image_IO *fl_find_imageio(const char *name, const char *extension);

extern FL_API unsigned		fl_count_imageio();
extern FL_API Fl_Image_IO *	fl_get_imageio(unsigned index);

#endif /* _FL_IMAGE_IO_H_ */

