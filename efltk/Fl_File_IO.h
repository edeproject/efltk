#ifndef _FL_FILE_IO_H_
#define _FL_FILE_IO_H_

#include "Fl_IO.h"
#include "Fl_String.h"

#include <stdio.h> // FILE

/**
 * Local file IO access object. 
 *
 * Default mode is IO_READ|IO_WRITE.
 *
 * IO can be optimized several ways, for different purpose.
 *
 * @see IOModes
 */
class Fl_File_IO : public Fl_IO
{
public:
	/**
	 * Possible IO modes for open.
	 */
	enum IOModes {
		IO_READ		= (1<<1),	///< Open file with read access.
		IO_WRITE	= (1<<2),	///< Open file with write access.
		IO_BINARY	= (1<<3),	///< Open file in binary mode (does not affect under W32)
		IO_APPEND	= (1<<4),	///< File position is at end of file, when open.
		IO_TRUNCATE	= (1<<5),	///< Truncate existing file.
		IO_CREATE	= (1<<6),	///< Create file, if not exists
		IO_TEMP		= (1<<7),	///< Temporary file, deleted after close
		IO_RANDOM	= (1<<8),	///< Optimize for "Random Access"
		IO_SEQ		= (1<<9),	///< Optimize for "Sequential Access"
		IO_SYNC		= (1<<10),	///< Non-buffered access. i.e. No flush after write needed.
		IO_LOCKED	= (1<<11),	///< Open file in locked mode, so another processes cannot access it while its open.

		IO_EXTERN_HANDLE = (1<<31) ///< Internal use only. Defined in flags(), file handle not created by object.
	};

	/**
	 * Create File IO object, filename and mode must be set explicitly.
	 */
	Fl_File_IO();
	/**
	 * Open File with given parameters.
	 * @param filename Absolute path to filename to open.
	 * @param mode Defines mode for IO
	 * @see IOModes
	 */
	Fl_File_IO(const char *filename, int mode);
	/**
	 * Create IO object from FILE pointer.
	 * @param file Valid pointer to FILE
	 */
	Fl_File_IO(FILE *file);
	/**
	 * Create IO object from valid fd (file descriptor).
	 * @param fd Valid file descriptor handle.
	 */
	Fl_File_IO(int fd);

	/**
	 * Destroys object. Closes file, if not opened from FILE or FD.
	 */
	virtual ~Fl_File_IO();

	/** Return filename */
	const Fl_String &filename() const	{ return m_filename; }
	/** Set new filename */
	void filename(const Fl_String &f)	{ m_filename = f; }
	/** Set new filename */
	void filename(const char *f)		{ m_filename = f; }
	
	/** 
	 * Set new access mode. 
	 * If file is already open, it must be re-opened
	 * to make this take effect.
	 */
	void mode(int mode);
	/**
	 * Return current IO access.
	 */
	int mode() const { return m_mode; }

	/**
	 * Try to open file. Open will fail, if file is already open.
	 * Returns true on success.
	 */
	bool open();
	/**
	 * Try to close file.
	 * Returns true on success.
	 */
	bool close();

	/** Return tru if file is open. */
	bool is_open() const;

	/** 
	 * Read from opened file. 
	 * Returns bytes readed.
	 * @param buffer Buffer to store readed data.
	 * @param buffer_len Size of input buffer
	 */
	virtual int read(void *buffer, int buffer_len);

	/** 
	 * Write to opened file. 
	 * Returns bytes written.
	 * @param buffer Buffer to write in file.
	 * @param buffer_len Size of input buffer
	 */
	virtual int write(void *buffer, int buffer_len);

	/**
	 * Seek to specific position in file.
	 * Returns position in file or -1 in error.
	 * @param pos Position to seek, regarding to method
	 * @param method Which seek method to use in seek
	 * @see Fl_IO::SeekMethod
	 */
	virtual long seek(long pos, Fl_IO::SeekMethod method=BEGIN);

	/** Return current position in file. */
	virtual long tell();

	/** 
	 * Return true, passed to end-of-file. 
	 */
	virtual bool eos() { return m_eos; }

	/**
	 * Returns file handle.
	 *  @li Under Win32 this is 'HANDLE' created by CreateFile.
	 *  @li Under *nix this is 'int' (fd?) created by open(?).
	 */
	void *handle() { return m_handle; }
	
	/**
	 * Flushes the buffers
	 * Returns 0 on succes, -1 on error
	 */
	int flush();

private:
	Fl_String m_filename;
	int m_mode;
	void *m_handle;
	bool m_eos;
};

#endif /* _FL_FILE_IO_H_ */
