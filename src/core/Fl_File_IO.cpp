// Fl_File_IO.cpp: implementation of the Fl_File_IO class.
//
//////////////////////////////////////////////////////////////////////

#include <efltk/Fl_File_IO.h>
#include <stdlib.h> //free

#ifdef _WIN32

#include <windows.h>
#include <io.h>

#ifndef INVALID_SET_FILE_POINTER
# define INVALID_SET_FILE_POINTER 0xFFFFFFFF
#endif

Fl_File_IO::Fl_File_IO()
{
	m_eos = false;
	m_handle = INVALID_HANDLE_VALUE;
	m_flags.set(CAN_SEEK|CAN_WRITE|CAN_WRITE);
	m_mode = IO_READ | IO_WRITE;
}

Fl_File_IO::Fl_File_IO(const char *filename, int mode)
{
	m_eos = false;
	m_handle = INVALID_HANDLE_VALUE;
	m_flags.set(CAN_SEEK|CAN_WRITE|CAN_WRITE);
	m_filename = filename;
	this->mode(mode);
	open();
}

Fl_File_IO::Fl_File_IO(FILE *file)
{		
	m_eos = false;
	m_handle = (void*)_get_osfhandle(fileno(file));
	m_flags.set(CAN_SEEK|CAN_WRITE|CAN_WRITE|IO_EXTERN_HANDLE);	
	m_mode = IO_READ | IO_WRITE;
}

Fl_File_IO::Fl_File_IO(int fd)
{
	m_handle = (void*)_get_osfhandle(fd);
	m_flags.set(CAN_SEEK|CAN_WRITE|CAN_WRITE|IO_EXTERN_HANDLE);
	m_mode = IO_READ | IO_WRITE;
}

Fl_File_IO::~Fl_File_IO()
{
	close();
}

void Fl_File_IO::mode(int mode)
{
	m_flags.clear(CAN_READ | CAN_WRITE);

	if(mode & IO_READ)
		m_flags.flags(CAN_READ);

	if(mode & IO_WRITE)
		m_flags.flags(CAN_WRITE);

	m_mode = mode;
}

bool Fl_File_IO::open()
{
	if(m_handle!=INVALID_HANDLE_VALUE) return false;
	
#ifdef UNICODE
	TCHAR *file = NULL;
	int len = m_filename.to_unicode(file);
	if(len<=0 || !file) return false;
	file[len] = 0;
#else
	const char *file = m_filename.c_str();
#endif
	
	DWORD access_rights = 0;
	DWORD disposition   = OPEN_EXISTING;
	DWORD attributes	= FILE_ATTRIBUTE_NORMAL;
	DWORD share = FILE_SHARE_DELETE|FILE_SHARE_READ|FILE_SHARE_WRITE;

	// Find access permissions
	if(mode() & IO_READ)
		access_rights |= GENERIC_READ;
	if(mode() & IO_WRITE)
		access_rights |= GENERIC_WRITE;
	
	// Is temp file?
	if(mode() & IO_TEMP) {
		attributes = FILE_ATTRIBUTE_TEMPORARY;
		attributes |= FILE_FLAG_DELETE_ON_CLOSE;
	}

	// Optimize access?
	if(mode() & IO_RANDOM)
		attributes |= FILE_FLAG_RANDOM_ACCESS;
	if(mode() & IO_SEQ)
		attributes |= FILE_FLAG_SEQUENTIAL_SCAN;
	if(mode() & IO_SYNC)
		attributes |= FILE_FLAG_WRITE_THROUGH;

	// Create / Truncate?
	if(mode() & IO_CREATE)
		disposition = CREATE_ALWAYS;
	else if(mode() & IO_TRUNCATE)
		disposition = TRUNCATE_EXISTING;	

	// Lock file?
	if(mode() & IO_LOCKED)
		share = 0;

	// Make it so!
	m_handle = (void*)CreateFile(file,
					access_rights,
					share,
					NULL,
					disposition,
					attributes,
					NULL);

	// If in append mode, seek to end
	if(mode() & IO_APPEND)
		seek(0, END);

#ifdef UNICODE
	// Free unicode converted string
	free(file);
#endif

	return is_open();
}

bool Fl_File_IO::close()
{
	// Do not close external handle!
	if(m_flags.is_set(IO_EXTERN_HANDLE)) return false;	
	if(m_handle==INVALID_HANDLE_VALUE) return false;

	BOOL ret = CloseHandle((HANDLE)m_handle);
	m_handle = INVALID_HANDLE_VALUE;
	
	return (ret==TRUE);
}

bool Fl_File_IO::is_open() const
{
	return (m_handle!=INVALID_HANDLE_VALUE);
}

int Fl_File_IO::read(void *buffer, int buffer_len)
{
	if(!m_flags.is_set(CAN_READ)) return false;
	if(m_handle==INVALID_HANDLE_VALUE) return -1;
	DWORD read_bytes = 0;

	if(ReadFile(m_handle, buffer, buffer_len, &read_bytes, NULL)) {
		m_eos = (read_bytes == 0);
		return read_bytes;
	}

	printf("ERR %d\n", GetLastError());

	m_eos = true;//(GetLastError()==ERROR_HANDLE_EOF);
	return -1;
}

int Fl_File_IO::write(void *buffer, int buffer_len)
{
	if(!m_flags.is_set(CAN_WRITE)) return false;
	if(m_handle==INVALID_HANDLE_VALUE) return -1;
	DWORD written_bytes = 0;

	if(WriteFile(m_handle, buffer, buffer_len, &written_bytes, NULL)) {
		return written_bytes;
	}

	m_eos = (GetLastError()==ERROR_HANDLE_EOF);
	return -1;
}

long Fl_File_IO::seek(long pos, Fl_IO::SeekMethod method)
{
	if(m_handle==INVALID_HANDLE_VALUE) return -1;

	DWORD W32method = FILE_BEGIN;
	switch(method) {
	case Fl_IO::END:		W32method = FILE_END; break;
	case Fl_IO::CURRENT:	W32method = FILE_CURRENT; break;
	default: break;
	};

	DWORD ret = SetFilePointer(m_handle, pos, NULL, W32method);	
	if(ret == INVALID_SET_FILE_POINTER) {
		m_eos = (GetLastError()==ERROR_HANDLE_EOF);
		return -1;
	}
	return (long)ret;
}

long Fl_File_IO::tell()
{
	if(m_handle==INVALID_HANDLE_VALUE) return -1;

	DWORD ret = SetFilePointer(m_handle, 0, NULL, FILE_CURRENT);	
	if(ret == INVALID_SET_FILE_POINTER) {
		m_eos = (GetLastError()==ERROR_HANDLE_EOF);
		return -1;
	}
	return (long)ret;
}

#endif /* _WIN32 */ 
