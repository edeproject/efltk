#ifndef _FL_IO_H_
#define _FL_IO_H_

#include "Fl_Flags.h"
#include "Fl_Buffer.h"

/**
 * IO Device abstraction for eFLTK.
 * @see Fl_File_IO
 */
class Fl_IO
{
public:
	/**
	 * Access flags device.
	 * @see can_read, can_write, can_seek
	 */
	enum AccessFlags {
		CAN_READ	= 1, ///< IO has read access.
		CAN_WRITE	= 2, ///< IO has write access.
		CAN_SEEK	= 4  ///< IO is seekable.
	};

	/**
	 * Seek methods for seek() function.
	 */
	enum SeekMethod {
		BEGIN	= 1,	///< Start seek from start of the IO stream
		END,			///< Start seek from end of the IO stream
		CURRENT			///< Seek from current location
	};

	virtual ~Fl_IO() { }

	/** Return AccessFlags for IO device. */
	Fl_Flags flags() const { return m_flags; }

	/** Return true if device has read permission */
	bool can_read()	 const { return m_flags.is_set(CAN_READ); }
	/** Return true if device has write permission */
	bool can_write() const { return m_flags.is_set(CAN_WRITE); }
	/** Return true if device can seek in stream */
	bool can_seek()	 const { return m_flags.is_set(CAN_SEEK); }

	/** READ, Return -1 on error */
	virtual int read(void *buffer, int buffer_len)	{ return -1; }
	/** WRITE, Return -1 on error */
	virtual int write(void *buffer, int buffer_len)	{ return -1; }
	/** SEEK, Return -1 on error */
	virtual long seek(long pos, int method=BEGIN)	{ return -1; }
	/** Current position in stream. Return -1 on error */
	virtual long tell()								{ return -1; }
	/** Is end-of-stream. Return -1 on error */
	virtual bool eos()								{ return true; }
	/** Flushes the buffer. Return -1 on error */
	virtual int flush() { return 0; }
	/** Flushes all buffers. Returns ? (maybe the number of buffers flushed ?) */
	static int flush_all() { return 0;/* TODO */}

protected:
	Fl_IO() { }

	/** Set access flags. */
	void flags(Fl_Flags f) { m_flags = f; }

	Fl_Flags m_flags; ///< AccessFlags must be set by child class.
};

#endif /* _FL_IO_H_ */
