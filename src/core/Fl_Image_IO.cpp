#include <efltk/Fl_Image_IO.h>
#include <efltk/Fl_Image.h>

#include "fl_internal.h"

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

extern Fl_Image_IO xpm_reader;
extern Fl_Image_IO bmp_reader;
extern Fl_Image_IO gif_reader;

static bool xpm_data = false;

Fl_Image* Fl_Image::read_xpm(const char *filename, const char * const *data)
{
    xpm_data=true;
    Fl_Image *ret = new Fl_Image();
    if(ret->read_image(filename, (const uint8 *)data, sizeof(data)))
        return ret;
    delete ret;
    return 0;
}

Fl_Image* Fl_Image::read(const char *filename, const uint8 *data, uint32 data_size)
{
    xpm_data=false;
    Fl_Image *ret = new Fl_Image();
    if(ret->read_image(filename, data, data_size))
        return ret;
    delete ret;
    return 0;
}

bool Fl_Image::read_image(const char *filename, const char * const *data)
{
    xpm_data=true;
    return read_image(filename, (const uint8 *)data, sizeof(data));
}

bool Fl_Image::read_image(const char *filename, const uint8 *data, uint32 data_size)
{
    fl_register_imageio(&xpm_reader);
    fl_register_imageio(&bmp_reader);
    fl_register_imageio(&gif_reader);

    clear();

    bool ret = false;

	if(!filename && !data) 
		return ret;
    else if(filename && !fl_file_exists(filename)) {
		return ret;
    }

    if(xpm_data) {

        // ONLY XPM DATA READ:
        Fl_Image_IO *r = &xpm_reader;
        if(r->is_valid_mem(data, 0)) {
            ret = r->read_mem(data, data_size, m_quality, m_data, m_fmt, m_width, m_height);
		}

    } else {

        for(uint n=0; n < fl_count_imageio(); n++) {
            Fl_Image_IO *r = fl_get_imageio(n);
            if(filename) {
                if(r->is_valid_file && r->read_file && r->is_valid_file(filename)) {
                    ret = r->read_file(filename, m_quality , m_data, m_fmt, m_width, m_height);				
				}
            } else {
                if(r->is_valid_mem && r->is_valid_mem(data, data_size)) {
                    ret = r->read_mem(data, data_size, m_quality, m_data, m_fmt, m_width, m_height);
				}
            }
        }
    }

    if(ret && format()->Amask) {
        // Default mask for images with alpha mask
        mask_type(FL_MASK_ALPHA);
    }

    if(ret && m_data) {
        m_data_alloc = true;
        m_pitch = Fl_Renderer::calc_pitch(bytespp(), width());
    }
    
    xpm_data=false;
    return ret;
}

bool Fl_Image::write_image(const char *filename, const char *io_name)
{
    return write_image(filename, fl_find_imageio(io_name, 0));
}

bool Fl_Image::write_image(const char *filename, Fl_Image_IO *io)
{
    if(!filename || !io || !io->write_file) return false;

    fl_register_imageio(&xpm_reader);
    fl_register_imageio(&bmp_reader);
    fl_register_imageio(&gif_reader);

    return io->write_file(filename, m_quality, m_data, m_fmt, m_width, m_height);
}

bool Fl_Image::write_image(uint8 *&data, int &data_size, const char *io_name)
{
    return write_image(data, data_size, fl_find_imageio(io_name, 0));
}

bool Fl_Image::write_image(uint8 *&data, int &data_size, Fl_Image_IO *io)
{
    if(!io || !io->write_mem) return false;

    fl_register_imageio(&xpm_reader);
    fl_register_imageio(&bmp_reader);
    fl_register_imageio(&gif_reader);

    return io->write_mem(data, data_size, m_quality, m_data, m_fmt, m_width, m_height);
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

static Fl_Ptr_List imageio_list;

Fl_Image_IO *fl_find_imageio(Fl_Image_IO *io) 
{
    int index = imageio_list.index_of(io);
    return (Fl_Image_IO *)(index!=-1?imageio_list[index]:0);
}

void fl_unregister_imageio(Fl_Image_IO *io) 
{
    Fl_Image_IO *item = fl_find_imageio(io);
    if(!item) return;
    imageio_list.remove(io);
}

void fl_register_imageio(Fl_Image_IO *io) 
{
    if(fl_find_imageio(io)) return;
    imageio_list.append(io);
}

Fl_Image_IO *fl_find_imageio(const char *name, const char *extension) 
{
    for(uint n=0; n<imageio_list.size(); n++) {
        Fl_Image_IO *item = (Fl_Image_IO *)imageio_list[n];
        if(name) if(!strcasecmp(item->name, name)) return item;
        if(extension) if(strstr(item->extensions, extension)) return item;
    }
    return 0;
}

Fl_Image_IO *fl_get_imageio(unsigned index) 
{
    return (Fl_Image_IO *)imageio_list.item(index);
}

unsigned fl_count_imageio() 
{
    return imageio_list.size();
}
