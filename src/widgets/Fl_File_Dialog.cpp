#include <config.h>

#include <efltk/Fl_File_Dialog.h>
#include <efltk/Fl_Divider.h>
#include <efltk/Fl_Pixmap.h>
#include <efltk/fl_ask.h>
#include <efltk/fl_draw.h>
#include <efltk/fl_utf8.h>

#include <efltk/Fl_Dialog.h>

// For NLS stuff
#include "../core/fl_internal.h"

#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

#ifdef _WIN32
# include <windows.h>
# include <direct.h>
# include <io.h>
#else
# include <unistd.h>
# include <pwd.h>
#endif /* _WIN32 */

#include <config.h>

#ifndef EEXIST
# define EEXIST 17
#endif

#include "Pixmaps.h"

static Fl_Pixmap m_homepix(datas_home);
static Fl_Pixmap new_pix(datas_new);
static Fl_Pixmap up_pix(datas_up);
static Fl_Pixmap refresh_pix(datas_refresh);

static Fl_Pixmap file_pix(datas_file);
static Fl_Pixmap fold_pix(datas_filefolder);

#ifndef S_ISDIR
# define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)
#endif

/*
uint uint64_to_uint(uint64 size) {
	size /= 1024;
	return (uint)size;
}

int Fl_FileItem::compare(Fl_ListView_Item *other, int column, int sort_type)
{
#ifdef _WIN32
	if(type()==DEVICE && ((Fl_FileItem*)other)->type()==DEVICE) {						
		switch(column) {
		case 2: {
				uint c1 = uint64_to_uint(attr->capacity);
				uint c2 = uint64_to_uint(((Fl_FileItem*)other)->attr->capacity);
				if(sort_type==Fl_ListView::SORT_ASC) return c1-c2;
				else if(sort_type==Fl_ListView::SORT_DESC) return c2-c1;
			}
			break;
		case 3: {
				uint c1 = uint64_to_uint(attr->free);
				uint c2 = uint64_to_uint(((Fl_FileItem*)other)->attr->free);
				if(sort_type==Fl_ListView::SORT_ASC) return c1-c2;
				else if(sort_type==Fl_ListView::SORT_DESC) return c2-c1;
			}
			break;
		default:
			break;
		}

	} else 
#endif
	{
		switch(column) {
		case 1:
			if(sort_type==Fl_ListView::SORT_ASC) return (attr->size - ((Fl_FileItem*)other)->attr->size);
			else if(sort_type==Fl_ListView::SORT_DESC) return (((Fl_FileItem*)other)->attr->size - attr->size);
			break;
		case 3:
			if(sort_type==Fl_ListView::SORT_ASC) return (attr->modified - ((Fl_FileItem*)other)->attr->modified);
			else if(sort_type==Fl_ListView::SORT_DESC) return (((Fl_FileItem*)other)->attr->modified - attr->modified);
			break;
		default:
			break;
		}
	}
	return Fl_ListView_Item::compare(other, column, sort_type);
}
*/
///////////////////////////////
// Static select functions:

int fc_initial_w = 400;//370;
int fc_initial_h = 350;//320;
bool fc_initial_preview = false;

#define MODAL false
//#define MODAL true

static char **select_files(const char *m_path_input, const char *filters, const char *cap, int mode=0)
{
    Fl_Dialog w(fc_initial_w, fc_initial_h, cap);
    w.size_range(320, 300);
    w.buttons(FL_DLG_OK|FL_DLG_CANCEL, FL_DLG_OK);
    w.resizable(w);

    Fl_File_Chooser *chooser = new Fl_File_Chooser(0,0, 100,100, 0, mode);
    chooser->ok_button(w.button(FL_DLG_OK));

    w.end();

    Fl_String def_file;
    Fl_String read_path(m_path_input);

    if(read_path.empty()) {
		
        char tmp[FL_PATH_MAX];
        fl_getcwd(tmp, sizeof(tmp));
        read_path = tmp;
    }
    else if(!fl_is_dir(m_path_input)) {
        int pos = read_path.rpos('/');
        if(pos==-1) pos = read_path.rpos('\\');

        if(pos>=0) {
            pos++;
            def_file = read_path.sub_str(pos, read_path.length()-pos);
            read_path.sub_delete(pos, read_path.length()-pos);
        }
    }

    chooser->multi_selection(true);
    chooser->default_filename(def_file);
    chooser->filters(filters);
    chooser->directory(read_path);

    switch(w.show_modal())
    {
    case FL_DLG_OK:
        break;
    default:
        return 0;
    }

    char **tmp = chooser->get_selected();
    if(!tmp) {
        tmp = new char*[2];
        Fl_String path;
        chooser->get_filename(chooser->file_input(), path);
        if(!path.empty()) {
            tmp[0] = new char[path.length()+1];
            memcpy(tmp[0], path.c_str(), path.length()+1);
        }
        tmp[1] = 0;
    }
    return tmp;
}

static char *select_file(const char *m_path_input, const char *filters, const char *cap, int mode=0)
{
    Fl_Dialog w(fc_initial_w, fc_initial_h, cap);
    w.size_range(320, 300);
    w.buttons(FL_DLG_OK|FL_DLG_CANCEL, FL_DLG_OK);
    w.resizable(w);

    Fl_File_Chooser *chooser = new Fl_File_Chooser(0,0, 100,100, 0, mode);
    chooser->ok_button(w.button(FL_DLG_OK));

    w.end();

    Fl_String def_file;
    Fl_String read_path(m_path_input);

    if(read_path.empty()) {

        char tmp[FL_PATH_MAX];
        fl_getcwd(tmp, sizeof(tmp)-1);
        read_path = tmp;
    }
    else if(!fl_is_dir(m_path_input)) {
        int pos = read_path.rpos('/');
        if(pos==-1) pos = read_path.rpos('\\');

        if(pos>0) {
            pos++;
            def_file = read_path.sub_str(pos, read_path.length()-pos);
            read_path.sub_delete(pos, read_path.length()-pos);
        }
    }

    chooser->default_filename(def_file);
    chooser->filters(filters);
    chooser->directory(read_path);

    switch(w.show_modal())
    {
    case FL_DLG_OK:
        break;
    default:
        return 0;
    }

    Fl_String path;
    chooser->get_filename(chooser->file_input(), path);
    if(!path.empty()) {
        char *ret = new char[path.length()+1];
        memcpy(ret, path.c_str(), path.length()+1);
        return ret;
    }

    return 0;
}

////////////////////////
// Global select functions:

char **fl_select_files(const char *m_path_input, char *filters, const char *cap)
{
    const char *caption = cap;
    if(!caption) caption=_("Choose Files:");
    return select_files(m_path_input, filters, caption);
}

char *fl_select_file(const char *m_path_input, char *filters, const char *cap)
{
    const char *caption = cap;
    if(!caption) caption=_("Choose File:");
    return select_file(m_path_input, filters, caption, Fl_File_Chooser::_DEFAULT);
}

char *fl_select_dir(const char *m_path_input, const char *cap)
{
    const char *caption = cap;
    if(!caption) caption=_("Choose Directory:");
    return select_file(m_path_input, 0, caption, Fl_File_Chooser::_DIRECTORY);
}

char *fl_save_file(const char *m_path_input, char *filters, const char *cap)
{
    const char *caption = cap;
    if(!caption) caption=_("Save File:");
    return select_file(m_path_input, filters, caption, Fl_File_Chooser::_SAVE);
}

////////////////////////////////////////////////

class PreviewBox : public Fl_Widget
{
public:
    PreviewBox(int x, int y, int w, int h) : Fl_Widget(x,y,w,h,0) { 
		color(FL_WHITE); 
	    image_cache.size(10);
	    image_cache.autodelete(true);	
	}
	~PreviewBox() {
		image_cache.clear();
	}
	
	Fl_String info;
    Fl_Image_Cache image_cache;
	
	void update_preview(const Fl_String &filename)
	{
		image(0);
		label("");
		info = "";
		
		if(filename.empty()) {
			redraw();
			return;
		}

		Fl_File_Attr *a = fl_file_attr(filename);
		int size = a ? a->size : 0;
		
		bool loaded = false;
		if(fl_file_match(filename, "*.{gif|bmp|xpm|png|jpg|jpeg}")) 
		{
			Fl_Image *im = 0;
			im = image_cache.get(filename);
			if(!im) {
				// Not in cache
				fl_cursor(FL_CURSOR_WAIT);
				Fl::check();
				im= Fl_Image::read(filename);
			}
			if(im) {		
				if(im->format()->Amask) {
					// If image has alpha pixel, blend it to preview box backgroud
					Fl_Image *blended = im->back_blend(color());
                    delete im;
                    im = blended;
				}
				
				info.printf("%s\n\n%s %d x %d\n%s %d",
					fl_file_filename(filename).c_str(),
					_("Size:"), im->width(), im->height(),
					_("File Size:"), size);
				
				im->system_convert();
				image_cache.add(im, filename);
				image(im);
				redraw();
				loaded = true;
			}
		} else {
			
			fl_cursor(FL_CURSOR_WAIT);
			Fl::check();
			
			FILE *fp;
			int	 bytes;
			char *ptr;
			
			fp = fl_fopen(filename, "rb");
			if (fp != NULL) {
				// Try reading the first 1k of data for a label...
				char buf[1024];
				bytes = fread(buf, 1, sizeof(buf) - 1, fp);
				buf[bytes] = '\0';
				fclose(fp);
				loaded = true;
				label(buf);
			}
			
			// Scan the buffer for printable chars...
			for(ptr = (char*)label().c_str(); *ptr && (isprint(*ptr) || isspace(*ptr)); ptr ++);
			
			if(*ptr || ptr == label().c_str()) {
				loaded = false;
			} else {
				// remove '\r' from text EOL
				for(ptr = (char*)label().c_str(); *ptr; ptr++) if(*ptr=='\r') *ptr=' ';
					
				align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_LEFT|FL_ALIGN_TOP);
				label_font(FL_COURIER);			
			}
			
			info.printf("%s\n\n%s %d", 
				fl_file_filename(filename).c_str(), 
				_("File Size:"), size);
		}
		
		if(!loaded) {
			label("?"); 
			align(FL_ALIGN_CLIP);
			label_font(FL_HELVETICA);
		}
		
		redraw();
		fl_cursor(FL_CURSOR_DEFAULT);
		Fl::check();
	}

    void draw() 
	{
        if(!(damage()&(FL_DAMAGE_ALL|FL_DAMAGE_EXPOSE))) return;

        draw_frame();

        int X=0,Y=0,W=w(),H=h();
        box()->inset(X,Y,W,H);
        fl_push_clip(X,Y,W,H);

		int prevH = int(h()*0.60f);

        if(image()) {

            Fl_Image *im = image();

            W=im->width();
            H=im->height();
            int pbw = w() - 10;
            int pbh = prevH - 10;
            if(W > pbw || H > pbh) {
                W = pbw;
                H = W * im->height() / im->width();
                if(H > pbh) {
                    H = pbh;
                    W = H * im->width() / im->height();
                }
            }
            X=(w()/2)-W/2;
            if(X<5) X=5;
            Y=5;
			prevH = Y+H;

            im->mask_type(MASK_NONE);
            im->draw(X,Y,W,H,FL_ALIGN_SCALE);

            fl_clip_out(X,Y,W,H);

            X=0,Y=0,W=w(),H=h();
            box()->inset(X,Y,W,H);

            fl_color(color());
            fl_rectf(X,Y,W,H);

        } else {

            if(w()<=120) label_size(8);
            else if(w()>120) label_size(10);
            else if(w()>180) label_size(12);
            else if(w()>250) label_size(14);

            if(label()[0]=='?' && label().length()==1) label_size(92);

            fl_color(color());
            fl_rectf(X,Y,W,H);
            draw_label(X, Y, W, prevH, align());
        }

		prevH += 10;
		FL_THIN_UP_BOX->draw(5, prevH, w()-10, 2, fl_darker(color()), 0);
		prevH += 10;

		fl_font(Fl_Widget::default_style->label_font, Fl_Widget::default_style->label_size);
		label_type()->draw(info, 5, prevH, w()-10, H-prevH, label_color(), FL_ALIGN_TOP|FL_ALIGN_LEFT|FL_ALIGN_WRAP);

		fl_pop_clip();
    }
};

///////////////////////////
// FILE DIALOG CLASS

#define FD ((Fl_File_Chooser *)d)

void normalize_path(Fl_String &path)
{
	Fl_String ret;
    char ch=0;
    int cnt=0;
    for(int n=0; n<path.length(); n++)	
    {
		ch = path[n];
#ifdef _WIN32
		if(ch=='/') ch='\\'; //Convert slashes..
#endif
        if(ch==slash) cnt++; else cnt=0;
        if(cnt>1) continue;
        ret += ch;
    }
	path = ret;
}

Fl_File_Chooser::Fl_File_Chooser(int x, int y, int w, int h, const char *label, int mode)
	: Fl_Group(x, y, w, h, label)
{
	m_ok_button = 0;
    m_mode = mode;
    make_group();
	filters(0);
}

Fl_File_Chooser::~Fl_File_Chooser()
{
	for(int n=0; n<m_filter_input->children(); n++) {
		free((char*)m_filter_input->child(n)->user_data());
	}	
}

bool Fl_File_Chooser::show_dialog(const char *caption)
{
	Fl_Button *saved_ok = ok_button();
	Fl_Group *saved_parent = parent();

	Fl_Dialog w(h()+40, w()+20, caption);
	if(has_size_range()) w.size_range(minw(), minh());
	w.buttons(FL_DLG_OK|FL_DLG_CANCEL, FL_DLG_OK);
	w.resizable(w);
	
	Fl_Group::current()->add(this);
	ok_button(w.button(FL_DLG_OK));

	w.end();

	refresh();
	bool ret = (w.show_modal()==FL_DLG_OK);

	parent()->remove(this);

	ok_button(saved_ok);
	parent(saved_parent);
	
	return ret;
}

void Fl_File_Chooser::make_group()
{	
    {
        Fl_Group* o = new Fl_Group(0, 5, 100, 31);
        o->layout_align(FL_ALIGN_TOP);
        o->layout_spacing(2);

        m_up = new Fl_Highlight_Button(0, 0, 25, 25);
        m_up->callback(cb_up, this);
        m_up->image(up_pix);
        m_up->layout_align(FL_ALIGN_LEFT);

        m_home = new Fl_Highlight_Button(0, 0, 25, 25);
        m_home->callback(cb_home, this);
        m_home->image(m_homepix);
        m_home->layout_align(FL_ALIGN_LEFT);

        m_refresh = new Fl_Highlight_Button(0, 0, 25, 25);
        m_refresh->callback(cb_refresh, this);
        m_refresh->image(refresh_pix);
        m_refresh->layout_align(FL_ALIGN_LEFT);

        m_new_folder = new Fl_Highlight_Button(0, 0, 25, 25);
        m_new_folder->callback(cb_new, this);
        m_new_folder->image(new_pix);
        m_new_folder->layout_align(FL_ALIGN_LEFT);

        m_path_input = new Fl_Input_Browser(0, 0, 100, 25);
        m_path_input->callback(cb_dirc, this);
        m_path_input->layout_align(FL_ALIGN_CLIENT);
        m_path_input->type(Fl_Input_Browser::NONEDITABLE);
        m_path_input->end();

        int H = m_path_input->text_size()+15;
        if(H > o->h()) o->h(H);

        o->end();
    } //end top

    {
        Fl_Group* o = new Fl_Group(0, 0, 100, 100);
        o->layout_align(FL_ALIGN_CLIENT);
        o->layout_spacing(2);

        m_filebrowser = new Fl_File_Browser(0, 0, 100, 100);
        m_filebrowser->callback(cb_list, this);
        m_filebrowser->add_up_item(false);
        m_filebrowser->end();
        m_filebrowser->layout_align(FL_ALIGN_CLIENT);

        m_preview = new Fl_Check_Button(0, 0, 100, 10, _("Show Preview"));
        m_preview->callback(cb_preview, this);
        m_preview->h(m_preview->label_size()+8);
        m_preview->value(false);
        m_preview->layout_align(FL_ALIGN_BOTTOM);

        m_preview_box = new PreviewBox(0, 0, 100, 100);
        m_preview_box->hide();
        m_preview_box->box(Fl_Input::default_style->box);
        m_preview_box->layout_align(FL_ALIGN_RIGHT);

        if(mode()==Fl_File_Chooser::_DIRECTORY) m_preview->deactivate();

        o->end();
    }

    {
        Fl_Group* o = new Fl_Group(0, 0, 100, 60);
        o->layout_align(FL_ALIGN_BOTTOM);
        o->layout_spacing(2);

        Fl_Box *box = new Fl_Box(0,0,100,60);
        box->layout_align(FL_ALIGN_LEFT);

        m_file_input = new Fl_Input_Browser(60, 0, 100, 0, _("Location:"));
        m_file_input->h(m_file_input->text_size()+12);
        m_file_input->callback(cb_location, this);
        m_file_input->when(FL_WHEN_CHANGED | FL_WHEN_ENTER_KEY_ALWAYS);
        m_file_input->end();
        m_file_input->layout_align(FL_ALIGN_TOP);

        m_filter_input = new Fl_Input_Browser(60, 0, 100, 0, _("Filter:"));
        m_filter_input->h(m_filter_input->text_size()+12);
        m_filter_input->type(Fl_Input_Browser::NONEDITABLE);
        m_filter_input->end();
        m_filter_input->layout_align(FL_ALIGN_TOP);
        m_filter_input->callback(cb_filter, this);


        fl_font(m_file_input->label_font(), m_file_input->label_size());
        int file_label_w = int(fl_width(m_file_input->label()));

        fl_font(m_filter_input->label_font(), m_filter_input->label_size());
        int filter_label_w = int(fl_width(m_filter_input->label()));

        box->w(10 + ( (filter_label_w>file_label_w) ? filter_label_w : file_label_w) );

        int H = m_file_input->h()+m_filter_input->h()+12;
        if(H > o->h()) o->h(H);

        o->relayout();
        o->end();
    }

	layout_damage(FL_LAYOUT_XYWH);
}

char **Fl_File_Chooser::get_selected()
{
    if(!m_filebrowser->multi() || m_filebrowser->get_selection().count()<1)
        return 0;
 
	char **list = new char*[m_filebrowser->get_selection().size()+1];
	int files = 0;
    for(uint n=0; n<m_filebrowser->get_selection().size(); n++) {
        Fl_ListView_Item *w = m_filebrowser->get_selection()[n];
		Fl_String file = directory() + w->label(1);

		struct stat s;
		if(stat(file, &s)<0 || S_ISDIR(s.st_mode)) continue;

		list[files] = new char[file.length()+1];
		memcpy(list[files], file.c_str(), file.length()+1);
		files++;
    }
	list[files] = 0;
	return list;
}

void Fl_File_Chooser::get_selected(Fl_String_List &list)
{
    if(!m_filebrowser->multi() || m_filebrowser->get_selection().count()<1)
        return;
 
    for(uint n=0; n<m_filebrowser->get_selection().size(); n++) {
        Fl_ListView_Item *w = m_filebrowser->get_selection()[n];
		Fl_String file = directory() + w->label(1);

		struct stat s;
		if(stat(file, &s)<0 || S_ISDIR(s.st_mode)) continue;

		list.append(file);
    }
}

void Fl_File_Chooser::filters(const char *filters)
{
    unsigned n;
    for(n=0; n < (unsigned)m_filter_input->children(); n++) {
        free((char*)m_filter_input->child(n)->user_data());
    }
    m_filter_input->clear();

    m_filter_input->begin();

    Fl_String_List list;
    list.from_string(filters, ",");

    Fl_Item *i;
    for(n=0; n<list.size(); n+=2)
    {
        if(list.size() <= n+1) break;

        i = new Fl_Item();
        i->label(list[n].trim());
        i->user_data(strdup(list[n+1].trim()));
    }

    if(m_filter_input->children()==0) {
        i = new Fl_Item(_("All Files (*)"));
        i->user_data(strdup("*"));
    }

    i = (Fl_Item*)m_filter_input->child(0);
    m_filter_input->value(i->label().c_str());
    m_filter_input->item(i);

    m_filter_input->end();
    m_filter_input->redraw();
}

void Fl_File_Chooser::parse_dirs(const Fl_String &fp)
{	
	m_path_input->clear();
	Fl_Item *item=0;

	if(fp.empty() || !strcmp(fp, _("My Computer"))) {
		m_path_input->begin();
		m_path_input->add(_("My Computer"));
		m_path_input->value(fp.empty() ? _("My Computer") : fp.c_str());
		m_path_input->end();
		m_path_input->redraw();
		return;
	}

	m_path_input->begin();

	unsigned n=fp.length();
	while(n-->0) {
		char ch = fp.c_str()[n];
		if(ch == slash) {
			item = new Fl_Item(fp.sub_str(0, n+1));
		}
	}

	new Fl_Divider(0,10);
	m_path_input->add(_("My Computer"));

	m_path_input->end();
	m_path_input->value(m_path_input->child(0)->label());
	m_path_input->redraw();
}

void Fl_File_Chooser::directory(const Fl_String &path)
{
    if(mode() == _DIRECTORY)
        filebrowser()->showpolicy(Fl_Directory_DS::HIDE_FILES);
    if(strcmp(pattern(), ""))
        filebrowser()->pattern(pattern());

    m_preview_box->image_cache.clear();
    m_preview_box->update_preview("");

    if(!strcmp(path, _("My Computer")))
        filebrowser()->load("");
    else
        filebrowser()->load(path);

    parse_dirs(directory());

    if(mode()!=_DIRECTORY) {
        if(ok_button()) ok_button()->deactivate();
        if(!m_default_filename.empty()) {
            Fl_ListView_Item *selected=0;
            for(unsigned n=0; n<filebrowser()->children(); n++) {
                if(filebrowser()->child(n)->label(1) == m_default_filename) {
                    selected = filebrowser()->child(n);
                    break;
                }
            }
            if(selected) {
                filebrowser()->layout();
                file_input(m_default_filename);
                if(ok_button()) ok_button()->activate();
                filebrowser()->select_only(selected);
                filebrowser()->show_item(selected);
            }
        }
    } else {
        if(ok_button()) ok_button()->activate();
    }

    if(directory().empty()) m_up->deactivate();
    else m_up->activate();

    m_default_filename = "";
    filebrowser()->redraw();
}

Fl_String Fl_File_Chooser::new_dir()
{
    const char	*dir; 
    // Get a directory name from the user
    if ((dir = fl_input(_("New Directory?"))) == NULL)
        return false;

	Fl_String newdir;

    // Make it relative to the current directory as needed...
#ifdef _WIN32
    if(dir[1] != ':')
#else
    if(dir[0] != '/')
#endif /* _WIN32 || __EMX__ */
    {
		newdir = directory();
    }
	newdir += dir;

    // Create the directory; ignore EEXIST errors...
#ifdef _WIN32
    if(mkdir(newdir)!=0) {
#else
	if(mkdir(newdir, 0755)!=0) {
#endif
        if(errno != EEXIST) {
            fl_alert(_("Unable to create directory!"));
            return "";
        }
	}

    directory(newdir); // Show the new directory...
    return newdir;
}

void Fl_File_Chooser::up() 
{
    filebrowser()->up();
	if(directory().empty()) m_up->deactivate();
    else m_up->activate();
	parse_dirs(directory());
}

void Fl_File_Chooser::file_clicked(Fl_ListView_Item *i)
{
    if(ok_button()) ok_button()->activate();
    Fl_ListView_Item *item=0;

    if(m_filebrowser->multi())
    {
        if(m_filebrowser->get_selection().size() == 1) {
            item = (Fl_ListView_ItemExt *)m_filebrowser->item();
            if(item) m_file_input->value(item->label(1));
		} else if(m_filebrowser->get_selection().size() > 1) {
			Fl_String files;
	        int items=0;
		    for(uint n=0; n<m_filebrowser->get_selection().size(); n++) 
			{
				item = m_filebrowser->get_selection()[n];

				Fl_String full(directory() + item->label(1));
				struct stat s;
				if(stat(full, &s)<0 || S_ISDIR(s.st_mode)) continue;

				if(items > 4) {
					files += "....";
					break;
				}
				if(!item->label(1).empty()) {
					files += item->label(1);
					files += " ";
					items++;
				}
			}
            m_file_input->value(files);
        }
    }
    else
    {
        //D->fullpath((const char *)((Fl_File_ChooserItem *)w)->fullpath());
        m_file_input->value(i->label(1));
    }

    if(Fl::event_clicks() || Fl::event_key()==FL_Enter) {
		if(ok_button()) ok_button()->do_callback();
    } else {
        item = (Fl_ListView_ItemExt *)m_filebrowser->item();
        if(item && preview()) {
            Fl_String path(directory()+item->label(1));
            m_preview_box->update_preview(path);
        }
    }
}

void Fl_File_Chooser::folder_clicked(Fl_ListView_Item *i)
{
    if(ok_button()) ok_button()->activate();
    m_file_input->value("");

	if(Fl::event_clicks() || Fl::event_key()==FL_Enter) {
		Fl_String path(directory()+i->label(1));
#if 0//def _WIN32
		if(i->type()==Fl_FileItem::NETWORK)
			sprintf(tmp, "\\\\%s", i->label());
#endif
		directory(path);
	}
}

//CALLBACKS!!
void Fl_File_Chooser::cb_list(Fl_Widget *w, void *d)
{
    Fl_File_Browser *l = (Fl_File_Browser*)w;
    Fl_ListView_Item *item = (Fl_ListView_Item *)l->item();

#ifdef _WIN32
	// Lame way to prevent device status, if not clickking it..
	if(item->label(1)[1] == ':' && (!Fl::event_clicks() && Fl::event_key()!=FL_Enter))
		return; 
#endif

	if(item == l->up_item()) {
		if(Fl::event_clicks() || Fl::event_key()==FL_Enter) FD->up();
	} else if(item) {
		Fl_String path(FD->directory()+item->label(1));		

		if(access(path, 04)!=0) return;

		if(fl_is_dir(path)) FD->folder_clicked(item);
		else FD->file_clicked(item);
    }
}

void Fl_File_Chooser::get_filename(Fl_String path, Fl_String &buf)
{
    char check; int checkp;
#ifdef _WIN32
    check=':'; checkp=1;
#else
    check='/'; checkp=0;
#endif

    buf = fl_file_expand(path);

    if(buf[checkp]!=check && !directory().empty()
#if 0//ef _WIN32
		&& strncmp(buf.c_str(), "\\\\", 2) //Check for network path..
#endif
		) 
	{
		buf = directory();
		buf += path;
	}
}

void Fl_File_Chooser::get_filepath(Fl_String path, Fl_String &buf)
{	
    char check; int checkp;
#ifdef _WIN32
    check=':'; checkp=1;
#else
    check='/'; checkp=0;
#endif	
    
    buf = fl_file_expand(path);

    if(buf[checkp]!=check && !directory().empty())
    {
        buf = directory();
        buf += path;
    }

    int pos = buf.rpos(slash);
    if(pos>0) {
        pos++;
        buf.sub_delete(pos, buf.length()-pos);
    }

    if(fl_is_dir(buf)) {
        if(buf[buf.length()-1] != slash) buf += slash;
    }
    else if(fl_is_dir(path)) {
        buf = path;
        if(buf[buf.length()-1] != slash) buf += slash;
    } else
        buf.clear();
}

void Fl_File_Chooser::cb_location(Fl_Widget *w, void *d)
{
    Fl_Input_Browser *loc = (Fl_Input_Browser *)w;

    Fl_String filename;
    static Fl_String dirpath;

    if(!strcmp(loc->value(),"")) {
        if(FD->ok_button()) FD->ok_button()->deactivate();
        loc->hide_popup();
        return;
    }

    if(FD->mode()==_SAVE)
        if(FD->ok_button()) FD->ok_button()->activate();

    int key = Fl::event_key();

    if(key == FL_Enter) {

        if(!strcmp(loc->value(), "..")) {
            FD->cb_up(w, d);
            loc->value("");
            return;
        }

        filename = dirpath;
        filename += loc->value();

        if(fl_is_dir(filename)
#if 0//def _WIN32
           || !strncmp(filename, "\\\\", 2) //Check for network path..
#endif
          ) {
            FD->directory(filename);
            loc->value("");
        }
        else if(FD->mode()<=Fl_File_Chooser::_SAVE)  {
            if(!fl_is_dir(filename) && (FD->mode()==Fl_File_Chooser::_DEFAULT ? fl_file_exists(filename) : true)) {

                if(Fl::modal()==FD) {
                    if(FD->ok_button()) FD->ok_button()->do_callback();
                }
                else
                    FD->directory(dirpath);

            } else {
                if(FD->ok_button()) FD->ok_button()->deactivate();
                FD->clear_value();
            }
        }

        loc->hide_popup();

    } else {

        FD->get_filename(loc->value(), filename);
        FD->get_filepath(loc->value(), dirpath);

        normalize_path(filename);
        normalize_path(dirpath);

        if(FD->mode()!=Fl_File_Chooser::_SAVE && FD->ok_button()) {
            if(fl_file_exists(filename)) FD->ok_button()->activate();
            else FD->ok_button()->deactivate();
        }

        Fl_String pattern(loc->value());
        int pos = pattern.rpos('/');
        if(pos==-1) pos = pattern.rpos('\\');
        if(pos>=0) {
            pos++;
            pattern = pattern.sub_str(pos, pattern.length()-pos);
        }
        pattern += '*';

        loc->clear();

        if(!dirpath.empty()) 
		{
            loc->begin();

            bool match = false;

            struct dirent **files=0;
            int count = fl_filename_list(dirpath, &files);
            for(int n=0; n<count; n++) {
                char *file = files[n]->d_name;

                if(strcmp(file, ".") && strcmp(file, "..") && fl_file_match(file, pattern)) {

					Fl_String filen(dirpath + file);
                    if(FD->mode()==Fl_File_Chooser::_DIRECTORY && !fl_is_dir(filen)) {
                        continue;
                    }
                    Fl_Widget *w = new Fl_Item();
                    w->label(file);
                    match = true;
                }
                free(files[n]);
            }
            if(count>0 && files) free(files);

            loc->end();
            loc->item(0);
            if(match) {
                loc->popup();
            } else {
                loc->hide_popup();
            }
        } else {
			loc->hide_popup();
		}
    }
}

//////////////////////////////
// PREVIEW

void Fl_File_Chooser::preview(bool show)
{
	m_preview->value(show);

	if(!show) {
		m_preview_box->image_cache.clear();
		m_preview_box->update_preview("");

		m_preview_box->hide();

	} else {

		m_preview_box->show();
		
		Fl_ListView_Item *item = filebrowser()->item();
		if(item && !directory().empty()) {
			Fl_String path(directory()+item->label(1));
			m_preview_box->update_preview(path);
		}
	}

	filebrowser()->parent()->relayout(FL_LAYOUT_WH);
	redraw();
}

void Fl_File_Chooser::update_preview(const Fl_String filename) 
{
	m_preview_box->update_preview(filename);
}

int Fl_File_Chooser::handle(int e)
{
    if(e==FL_KEYUP && Fl::event_key()==FL_BackSpace) {
        if(Fl::focus()==filebrowser()) {
            cb_up(0, this);
            return 1;
        }
    }
    return Fl_Group::handle(e);
}

void Fl_File_Chooser::layout()
{
	if(preview()) {
		int W = int(w()*0.30f);
		m_preview_box->w(W);
	}
	Fl_Group::layout();
}

////////////////////////////
// WIN32 NETWORK

// BROKEN!!

#if 0//def _WIN32

// This sucks... I hate pure windoze programming...
bool Fl_File_Chooser::enum_netresources(Fl_Callback *cb, LPNETRESOURCE lpnr, DWORD scope)
{ 
	DWORD dwResult, dwResultEnum;
	HANDLE hEnum;
	DWORD cbBuffer = 16384;	// 16K is a good size
	DWORD cEntries = (DWORD)-1;	// enumerate all possible entries
	LPNETRESOURCE lpnrLocal;// pointer to enumerated structures
	DWORD i;
  
	// Call the WNetOpenEnum function to begin the enumeration.
	dwResult = WNetOpenEnum(scope,
							RESOURCETYPE_DISK,	// disk resources
							0,					// enumerate all resources
							lpnr,				// NULL first time the function is called
							&hEnum);			// handle to the resource

	if(dwResult != NO_ERROR) {  
		// Process errors with an application-defined error handler.
		//NetErrorHandler(hwnd, dwResult, (LPSTR)"WNetOpenEnum");
		return false;
	}

	lpnrLocal = new NETRESOURCE[cbBuffer];
	do {  
	    // Initialize the buffer.
		memset(lpnrLocal, 0, cbBuffer*sizeof(NETRESOURCE));

		// Call the WNetEnumResource function to continue the enumeration.
		dwResultEnum = WNetEnumResource(hEnum,      // resource handle
                                    &cEntries,  // defined locally as -1
                                    lpnrLocal,  // LPNETRESOURCE
                                    &cbBuffer); // buffer size

		// If the call succeeds, loop through the structures.
	    if (dwResultEnum == NO_ERROR) {
			for(i = 0; i < cEntries; i++) {
				// Call an application-defined function to
				// display the contents of the NETRESOURCE structures.
				cb(this, (void *)(&lpnrLocal[i]));
			}
		}
	    else if (dwResultEnum != ERROR_NO_MORE_ITEMS) // Process errors.
		{
			//NetErrorHandler(hwnd, dwResultEnum, (LPSTR)"WNetEnumResource");
			break;
		}
	
	} while(dwResultEnum != ERROR_NO_MORE_ITEMS);

	delete []lpnrLocal;
	dwResult = WNetCloseEnum(hEnum);
  
	if(dwResult != NO_ERROR) { 
		//NetErrorHandler(hwnd, dwResult, (LPSTR)"WNetCloseEnum");
		return false;
	}

	return true;
}

static void cb_add_netitem(Fl_Widget *w, void *d) {	
	((Fl_File_Chooser *)w)->add_netitem((LPNETRESOURCE)d);	
}

void Fl_File_Chooser::add_netitem(LPNETRESOURCE net)
{
	if(!net->lpRemoteName) return;
/*
	filebrowser()->begin();

	char *remote_name;
	
#ifdef UNICODE
	int len = wcslen(net->lpRemoteName);
	remote_name = (char*)malloc(len*5+1);
	fl_unicode2utf((unsigned short*)net->lpRemoteName, len, remote_name);
#else
	remote_name = net->lpRemoteName;
#endif

	char *tmp = strdup(remote_name);
	char *p = strrchr(tmp, '\\');
	tmp+=(p-tmp)+1;

	Fl_ListV *i = new Fl_FileItem(tmp, 0);
    i->type(Fl_FileItem::NETWORK);
	if(scope==RESOURCE_GLOBALNET)
		i->image(0, fold_pix);		
	else
		i->image(0, hd_pix);
	filebrowser()->end();

	free(tmp);
#ifdef UNICODE
	free(remote_name);
#endif*/
}

void Fl_File_Chooser::read_network(LPNETRESOURCE net)
{
	scope = RESOURCE_CONTEXT;
	if(net) scope = RESOURCE_GLOBALNET;		

	filebrowser()->clear();	
	enum_netresources(cb_add_netitem, net, scope);	
}

#endif

