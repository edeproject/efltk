#include <efltk/Fl_File_Dialog.h>
#include <efltk/Fl_Divider.h>
#include <efltk/Fl_Item.h>
#include <efltk/vsnprintf.h>
#include <efltk/fl_ask.h>
#include <efltk/fl_draw.h>
#include <efltk/fl_utf8.h>

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

static Fl_Image home_pix(datas_home);
static Fl_Image new_pix(datas_new);
static Fl_Image up_pix(datas_up);
static Fl_Image refresh_pix(datas_refresh);

static Fl_Image file_pix(datas_file);
static Fl_Image fold_pix(datas_filefolder);
#ifdef _WIN32
static Fl_Image cd_pix(datas_cd);
static Fl_Image flop_pix(datas_floppy);
static Fl_Image hd_pix(datas_harddisk);
#endif

////////////////////////////
// File Item functions

double get_file_size(uint size, char **prefix)
{
	*prefix=_("bytes");
	double s = (double)size;

	if(s>1024) {
		s /= 1024;
		*prefix=_("Kb");
	}
	if(s>1024) {
		s /= 1024;		
		*prefix=_("Mb");
	}
	return s;
}

#ifdef _WIN32

uint get_dev_size(uint64 size, char **prefix)
{
	*prefix=_("bytes");

	if(size>1024) {
		size /= 1024;
		*prefix=_("Kb");
	}
	if(size>1024) {
		size /= 1024;		
		*prefix=_("Mb");
	}
	return (uint)size;
}

#endif

static const char *types[] = {
    "Unknown",
	
    "File",
    "Dir",
    "Link",

    "CD-Rom",
    "Removable",
    "Local Disk",
    "Network Disk",
    "RAM Disk"
};

//////////////////////////
// File item class

Fl_FileItem::Fl_FileItem(const char *filename, Fl_FileAttr *a)
: Fl_ListView_Item(0, 0, 0, 0)
{
    strcpy(fname, filename?filename:_("Unknown"));
    label(0, fname);

    attr = a;
    if(!attr) return;

    const char *typestr=_(types[0]);

    char ptr[10];
    char *prefix = ptr;

    if(a->flags&FL_DEVICE) {
#ifdef _WIN32
        this->type(DEVICE);

        char nbuf[4];nbuf[0] = filename[0];nbuf[1]=':';nbuf[2]='\\';nbuf[3]='\0';
        uint type = GetDriveType(nbuf);
        if(type==DRIVE_CDROM) {
            typestr=_(types[4]);
		} else
        if(type==DRIVE_REMOVABLE) {
            typestr=_(types[5]);
		} else
        if(type==DRIVE_FIXED) {
            typestr=_(types[6]);
		} else
        if(type==DRIVE_REMOTE) {
            typestr=_(types[7]);
		} else
        if(type==DRIVE_RAMDISK) {
            typestr=_(types[8]);
		}

        label(1, typestr);

        uint s = 0;
        s = get_dev_size(a->capacity, &prefix);
        if(s>0) {
            sprintf(size, "%d %s", s, prefix);
            label(2, size);
        } else label(2,0);

        s = get_dev_size(a->free, &prefix);
        if(s>0) {
            sprintf(free, "%d %s", s, prefix);
            label(3, free);
        } else label(3,0);
		
		/*
		//TOO SLOW!!!
		char drivename[255];		
		if(GetVolumeInformation(
			filename,
			drivename,
			sizeof(drivename)-1,
			NULL, NULL, NULL, NULL, 0))
		{
			if(drivename[0])
				snprintf(fname, sizeof(fname)-1, "%s (%s)", filename, drivename);
		} 	
		*/
#endif
    } else {

        if(a->flags & FL_LINK) {
            this->type(DIR);
            typestr=_(types[3]);
        } else if(a->flags & FL_DIR) {
            this->type(DIR);
            typestr=_(types[2]);
        } else if(a->flags & FL_FILE) {
            this->type(FILE);
            typestr=_(types[1]);
        }

        double s = get_file_size(a->size, &prefix);

        if(s>0) {
            if(!strcmp(prefix, _("bytes")))
                sprintf(size, "%.0f %s", s, prefix);
            else
                sprintf(size, "%.1f %s", s, prefix);

            label(1, size);
        } else
            label(1, 0);

        label(2, typestr);

        label(3, a->time);
    }
}

Fl_FileItem::~Fl_FileItem()
{
    if(attr) delete attr;
}

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

///////////////////////////////
// Static select functions:

#define MODAL false
//#define MODAL true

static char **select_files(const char *path_, Filter **filters, const char *cap, int mode=0)
{
    Fl_File_Dialog d(Fl_File_Dialog::initial_w ,Fl_File_Dialog::initial_h , cap, mode);    

	const char *def_file=0;
    char read_path[FL_PATH_MAX]={0};

    if(path_ && fl_is_dir(path_))
        strncpy(read_path, path_, sizeof(read_path));
    else if(path_ && *path_ && strchr(path_, slash)) {
        int len=strlen(path_);
        while(len--) if(path_[len]==slash) break;
        if(len>0) {
            strncpy(read_path, path_, len);
			def_file = (path_+(len+1));
        }
    } else {
        getcwd(read_path, FL_PATH_MAX);
    }

	d.multi_selection(true);
	d.default_filename(def_file);
    d.filters(filters);
    d.read_dir(read_path);
    if(!d.exec(0, MODAL))
		return 0;

    char **tmp = 0;
    int len;

    tmp = d.get_selected();

    // Theres no selection, lets try to get filename from location box
    if(!tmp) {
        const char *file = d.location();
        char path[FL_PATH_MAX];
        if(d.get_filename(file, path)) {
            tmp = new char*[2];
            len = strlen(path)+1;
            tmp[0] = new char[len];
            strncpy(tmp[0], path, len);
            tmp[1] = 0;
            return tmp;
        }
    }

    return tmp;
}

static char *select_file(const char *path_, Filter **filters, const char *cap, int mode=0)
{
    Fl_File_Dialog d(Fl_File_Dialog::initial_w ,Fl_File_Dialog::initial_h , cap, mode);

	const char *def_file=0;
    char read_path[FL_PATH_MAX]={0};

    if(path_ && fl_is_dir(path_))
        strncpy(read_path, path_, sizeof(read_path));
    else if(path_ && *path_ && strchr(path_, slash)) {
        int len=strlen(path_);
        while(len--) if(path_[len]==slash) break;
        if(len>0) {
            strncpy(read_path, path_, len);
			def_file = (path_+(len+1));
        }
    } else {
        getcwd(read_path, FL_PATH_MAX);
    }

	d.default_filename(def_file);
    d.filters(filters);
    d.read_dir(read_path);
    if(!d.exec(0, MODAL))
		return 0;

    char *ret = 0;
    int len = 0;

    char path[FL_PATH_MAX];
    if(d.get_filename(d.location(), path)) {
        len = strlen(path)+1;
        ret = new char[len];
        strncpy(ret, path, len);
        return ret;
    }

	return 0;
}

////////////////////////
// Global select functions:

char **fl_select_files(const char *path_, char *filters, const char *cap)
{
    const char *caption = cap;
    if(!caption) caption=_("Choose Files:");

    Filter **f = Fl_File_Dialog::build_filters(filters);

    char **files = select_files(path_, f, caption);
    if(f) {
        for(int n=0; f[n]; n++) delete f[n];
        delete []f;
    }
    return files;
}

char *fl_select_file(const char *path_, char *filters, const char *cap)
{
    const char *caption = cap;
    if(!caption) caption=_("Choose File:");

    Filter **f = Fl_File_Dialog::build_filters(filters);

    char *file = select_file(path_, f, caption, Fl_File_Dialog::DEFAULT);
    if(f) {
        for(int n=0; f[n]; n++) delete f[n];
        delete []f;
    }
    return file;
}

char *fl_select_dir(const char *path_, const char *cap)
{
    const char *caption = cap;
    if(!caption) caption=_("Choose Directory:");

    char *dir = select_file(path_, 0, caption, Fl_File_Dialog::DIRECTORY);
    return dir;
}

char *fl_save_file(const char *path_, char *filters, const char *cap)
{
    const char *caption = cap;
    if(!caption) caption=_("Save File:");

    Filter **f = Fl_File_Dialog::build_filters(filters);

    char *file = select_file(path_, f, caption, Fl_File_Dialog::SAVE);
    if(f) {
        for(int n=0; f[n]; n++) delete f[n];
        delete []f;
    }
    return file;
}

class PreviewBox : public Fl_Widget
{
public:
    PreviewBox(int x, int y, int w, int h) : Fl_Widget(x,y,w,h,0) { color(FL_WHITE); }
    void draw() {
        if(!(damage()&(FL_DAMAGE_ALL|FL_DAMAGE_EXPOSE))) return;

        int X=0,Y=0,W=w(),H=h();
        box()->inset(X,Y,W,H);

        if(image()) {
            draw_frame();
            fl_push_clip(X,Y,W,H);

            Fl_Image *im = image();

            W=im->width();
            H=im->height();
            int pbw = w() - 10;
            int pbh = h() - 10;
            if(W > pbw || H > pbh) {
                W = pbw;
                H = W * im->height() / im->width();
                if(H > pbh) {
                    H = pbh;
                    W = H * im->width() / im->height();
                }
            }
            X=(w()/2)-W/2;
            Y=(h()/2)-H/2;
            if(X<5) X=5;
            if(Y<5) Y=5;

            im->mask_type(MASK_NONE);
            im->draw(X,Y,W,H,FL_ALIGN_SCALE);

            fl_clip_out(X,Y,W,H);

            X=0,Y=0,W=w(),H=h();
            box()->inset(X,Y,W,H);

            fl_color(color());
            fl_rectf(X,Y,W,H);

            fl_pop_clip();

        } else {

            draw_box();

            if(w()<=120) label_size(8);
            else if(w()>120) label_size(10);
            else if(w()>180) label_size(12);
            else if(w()>250) label_size(14);

            if(label()[0]=='?'&&label()[1]=='\0') label_size(96);

            draw_label(X, Y, W, H, align());
        }
    }
};

///////////////////////////
// FILE DIALOG CLASS

#define FD ((Fl_File_Dialog *)d)

int Fl_File_Dialog::initial_w = 400;//370;
int Fl_File_Dialog::initial_h = 350;//320;
bool Fl_File_Dialog::initial_preview = false;

char *normalize_path(const char *path, char *buf)
{
#ifdef _WIN32
    strncpy(buf, path, FL_PATH_MAX);
	char *d = buf;
	for(; *d; d++) if(*d=='/') *d='\\'; //Convert slashes..

#else

    char ch=0;
    int cnt=0;
    char *ptr = buf;
    while((ch=*path++))
    {
        if(ch==slash) cnt++; else cnt=0;
        if(cnt==2) {
            cnt=0;
            continue;
        }
        *ptr++ = ch;
    }
    *ptr++ = '\0';    
#endif
	return buf;
}

void cb_file_dialog(Fl_Widget *w, void *d)
{
    ((Fl_File_Dialog*)d)->close(CLOSE_CANCEL);
}

Fl_File_Dialog::Fl_File_Dialog(int w, int h, const char *label, int mode)
: FileDialogType(w, h, label)
{
    callback(cb_file_dialog, this);
    image_cache.size(10);
    image_cache.autodelete(true);

    mode_ = mode;
    make_group(w, h);
    init();
}

Fl_File_Dialog::Fl_File_Dialog(int x, int y, int w, int h, const char *label, int mode)
	: FileDialogType(x, y, w, h, label)
{
    callback(cb_file_dialog, this);
    image_cache.size(10);
    image_cache.autodelete(true);

    mode_ = mode;
    make_group(w, h);
    init();
}

Fl_File_Dialog::~Fl_File_Dialog()
{
	image_cache.clear();
}

Filter **Fl_File_Dialog::build_filters(char *ptr)
{
    if(!ptr)  return 0;

    Filter **filters = new Filter*[1];
    char **split = fl_split(ptr, ",", 32);
    int filter_cnt=0;
    for(int n=0; split[n]; n+=2)
    {
        if(!split[n+1]) break;

        char *name = fl_trim(split[n]);
        char *pattern = fl_trim(split[n+1]);

        Filter *filter = new Filter;
        filter->type_str = strdup(name);
        filter->pattern  = strdup(pattern);
        filters[filter_cnt] = filter;
        
        filter_cnt++;
		filters = (Filter **)realloc(filters, sizeof(Filter*) * (filter_cnt+1));
    }

    if(filter_cnt==0) { delete []filters; filters=0; }
    else filters[filter_cnt] = 0;

    fl_freev(split);	

    return filters;
}

void Fl_File_Dialog::make_group(int w, int h)
{	
    {
        Fl_Group* o = new Fl_Group(5, 5, w-10, 35);
        //o->box(FL_THIN_UP_BOX);

        up_ = new Fl_Highlight_Button(5, 5, 25, 25);
        up_->image(up_pix);
        home_ = new Fl_Highlight_Button(35, 5, 25, 25);
        home_->image(home_pix);
        refresh_ = new Fl_Highlight_Button(65, 5, 25, 25);
        refresh_->image(refresh_pix);
        new_folder_ = new Fl_Highlight_Button(95, 5, 25, 25);
        new_folder_->image(new_pix);

        path_ = new Fl_Input_Browser(125, 5, w-140, 25);
        path_->type(Fl_Input_Browser::NONEDITABLE);
        path_->end();

        Fl_Group::current()->resizable(path_);

        o->end();
    } //end top

    {
        Fl_Group* o = new Fl_Group(5, 45, w-10, h-130);
        o->box(FL_FLAT_BOX);
        int W=o->w(), H=o->h();

        listview_ = new Fl_ListView(0, 0, W-5, H);
        listview_->add_column(_("File"));
        listview_->add_column(_("Size"),80);
        listview_->add_column(_("Type"),80);
        listview_->add_column(_("Modified"),120);
        listview_->column_flags(0,FL_ALIGN_LEFT);
        listview_->column_flags(1,FL_ALIGN_LEFT);
        listview_->column_flags(2,FL_ALIGN_LEFT);
        listview_->column_flags(3,FL_ALIGN_LEFT);
        listview_->end();

        preview_ = new PreviewBox(0, 0, 0, 0);
        preview_->label(preview_text);
        preview_->hide();
        preview_->box(FL_THIN_DOWN_BOX);
        preview_info_ = new Fl_Box(0, 0, 0, 0);
        preview_info_->label(preview_info);
        preview_info_->hide();
        preview_info_->box(FL_FLAT_BOX);
        preview_info_->label_size(10);
        preview_info_->label_font(FL_HELVETICA);
        preview_info_->align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_LEFT|FL_ALIGN_TOP);

        o->resizable(o);
        o->end();
        resizable(o);

        // Outside of group
        preview_but_ = new Fl_Check_Button(5, 45+H, W, 18, _("Show Preview"));
        preview_but_->text_size(10);
        preview_but_->value(Fl_File_Dialog::initial_preview);
        if(mode()==DIRECTORY) preview_but_->deactivate();
    }

    {
        Fl_Group* o = new Fl_Group(5, h-65, w-10, 30);

        //location_ = new Fl_FileInput(55, 0, w-120, 25, "Location:");
        location_ = new Fl_Input_Browser(60, 0, w-130, 23, _("Location:"));
        location_->maxh(200);
        location_->callback(cb_location, this);
        location_->when(FL_WHEN_CHANGED | FL_WHEN_ENTER_KEY_ALWAYS);
        location_->end();

        Fl_Group::current()->resizable(location_);

        ok_ = new Fl_Return_Button(w-65, 0, 55, 23, _("OK"));
        //ok_->deactivate();
        ok_->shortcut(0xff0d);

        o->end();
    } //loc, ok

    {
        Fl_Group* o = new Fl_Group(5, h-35, w-10, 30);

        filter_ = new Fl_Input_Browser(60, 0, w-130, 23, _("Filter:"));
        filter_->type(Fl_Input_Browser::NONEDITABLE);
        filter_->end();

        Fl_Group::current()->resizable(filter_);

        cancel_ = new Fl_Button(w-65, 0, 55, 23, _("&Cancel"));

        o->end();
    }

    preview(Fl_File_Dialog::initial_preview);
}

char **Fl_File_Dialog::get_selected()
{
    if(!listview_->multi() || listview_->get_selection().count()<=1)
        return 0;

    char **tmp = (char **)malloc(sizeof(char *));

    int sel = 0;
    Fl_FileItem *w=0;
    for(uint n=0; n<listview_->get_selection().size(); n++) {
        w = (Fl_FileItem *)listview_->get_selection()[n];
        if(w->type()==Fl_FileItem::DEVICE) continue;

        tmp = (char **)realloc(tmp, (sel+1)*sizeof(char *)+sizeof(char *));
        char filepath[FL_PATH_MAX];
        snprintf(filepath, sizeof(filepath)-1, "%s%c%s", fullpath(), slash, w->label());
        tmp[sel] = strdup(filepath);
        sel++;
    }

    if(sel==0) {
        delete []tmp;
        return 0;
    }

    tmp[sel] = 0; //make sure last item in list is 0
    return tmp;
}

void Fl_File_Dialog::close(bool cancel)
{
	if(!cancel) set_value();
    location_->hide_popup();
    hide();
}

void Fl_File_Dialog::init()
{
	fullpath_ = 0;
	default_filename_ = 0;
	size_range(300, 200);

	up_->callback(cb_up, this);
	home_->callback(cb_home, this);
	refresh_->callback(cb_refresh, this);
	new_folder_->callback(cb_new, this);

	//listview_->text_background(FL_WHITE);
	listview_->callback(cb_list, this);
	preview_but_->callback(cb_preview, this);
		
	filter_->add(_("All Files (*)"));
	filter_->value(_("All Files (*)"));
	filter_->callback(cb_filter, this);

	path_->callback(cb_dirc, this);

	cancel_->callback(cb_cancel, this);
	ok_->callback(cb_ok, this);
}

void Fl_File_Dialog::filters(Filter **filters)
{
    filter_->clear();
    filter_->begin();
    Fl_Item *i;

    if(!filters) {
        static Filter tmp;
        tmp.pattern = "*"; tmp.type_str = _("All Files (*)");
        _cur_filter = &tmp;

        i = new Fl_Item();
        i->copy_label(tmp.type_str);
        i->user_data(&tmp);

    } else {

        _cur_filter = filters[0];
        for(Filter *f=*filters++; f!=0; f=*filters++)
        {
            char tmp[128];
            sprintf(tmp, "%s",f->type_str);
            i = new Fl_Item();
            i->copy_label(tmp);
            i->user_data(f);
        }
    }

    filter_->value(filter_->child(0)->label());
    filter_->end();
    filter_->redraw();
}

#ifndef _WIN32

void Fl_File_Dialog::parse_dirs(const char *fp)
{
    path_->clear();
    Fl_Item *item=0;

    if(!fp || !strcmp(fp, _("My Computer")) || !strcmp(fp, _("My Home"))) {
        path_->begin();
        //path_->add("My Computer");
        path_->add(_("My Home"));
        path_->value(path_->child(0)->label());
        path_->end();
        path_->redraw();
        return;
    }

    int i;
    char buf[FL_PATH_MAX];
    char *ptr = normalize_path(fp, buf);

    path_->begin();

    i = strlen(ptr)-1;
    while(i--) {
        if(ptr[i] == slash) {
            item = new Fl_Item();
            item->copy_label(ptr);
            ptr[i] = '\0';
        }
    }
    item = new Fl_Item();
    item->copy_label("/");

    new Fl_Divider(0,10);
    //path_->add("My Computer");
    path_->add(_("My Home"));

    path_->end();
    path_->value(path_->child(0)->label());
    path_->redraw();
}

#else

void Fl_File_Dialog::parse_dirs(const char *fp)
{	
	path_->clear();
	Fl_Item *item=0;

	if(!fp || !*fp || !strcmp(fp, _("My Computer")) || !strcmp(fp, _("My Network"))) {
		path_->begin();
		path_->add(_("My Computer"));
		path_->add(_("My Network"));
		path_->value(fp?fp:_("My Computer"));
		path_->end();
		path_->redraw();
		return;
	}

	int i;

	char *_tmp = strdup(fp);
	char *ptr = _tmp;

	path_->begin();
	
	i = strlen(ptr)-1;
	while(i--) {
		if(ptr[i] == slash) {			
			item = new Fl_Item();
			item->copy_label(ptr);
			// Do not add last '\' if we have network path_ (only win32) 
			if(i==1&&ptr[0]=='\\'&&ptr[1]=='\\') { ptr[i] = '\0'; break; }
			ptr[i] = '\0';
		}
	}
	
	// Do not add '\\' at the end of list
	if(fp[0]!='\\' && fp[1]!='\\') {
		item = new Fl_Item();
		item->copy_label(ptr);  
	}

	new Fl_Divider(0,10);
	path_->add(_("My Computer"));
	path_->add(_("My Network"));

	path_->end();
	path_->value(path_->child(0)->label());
	path_->redraw();
		
	delete []_tmp;	
}

#endif

void Fl_File_Dialog::read_dir(const char *_path)
{
    Fl_FileItem *selected=0;
    image_cache.clear();
    update_preview(0);

    char read_path[FL_PATH_MAX];
    if(_path && *_path) {
        normalize_path(_path, read_path);
    } else {
        read_path[0] = '\0';
    }

#ifndef _WIN32
    if(!*read_path) {
        strncpy(read_path, "/", sizeof(read_path));
        _path = "/";
        ok_->deactivate();
    }
    if(!strcmp(read_path, _("My Home"))) {
        char *home = fl_get_homedir();
        strncpy(read_path, home, FL_PATH_MAX);
        delete []home;
        _path = read_path;
    }
    parse_dirs(read_path);
#else
    parse_dirs(read_path);
    bool get_drives = false;
    bool read_net = false; LPNETRESOURCE netres=0;
	
    if(!*read_path || !strcmp(read_path, _("My Computer")))
    {
        get_drives = true;
        _path=0;
    } else
    if(!strcmp(read_path, _("My Network"))) {
        read_net = true;
        _path=0;
    } else
    if(read_path[0]=='\\' && read_path[1]=='\\') {		
		
		// Remove trailing slash...
		if(read_path[strlen(read_path)-1]=='\\') read_path[strlen(read_path)-1] = '\0'; 

        char *p = strchr((char *)(read_path+2), '\\');
        if(!p) {
		    //Network path, w/o share name. Try to read all shares
            NETRESOURCE net;
            memset(&net, 0, sizeof(net));
            net.lpRemoteName = strdup(read_path);
            netres = &net;
            read_net = true;
        }
    }
    if(mode_!=Fl_File_Dialog::DIRECTORY || (mode_==Fl_File_Dialog::DIRECTORY && !fullpath_))
        ok_->deactivate();	
#endif
    fullpath(_path);

    if(!fullpath_) up_->deactivate();
    else up_->activate();

    location_->value("");

    listview_->yposition(0);
    listview_->column_width(0, -1);
    listview_->clear();
    listview_->begin();

#ifdef _WIN32
    if(get_drives)
    {
        listview_->column_name(1, _("Type"));
        listview_->column_name(2, _("Capacity"));
        listview_->column_name(3, _("Free Space"));
        DWORD drvs = GetLogicalDrives();
        char drive[4];
        Fl_FileItem *it;
        for(int i = 'A'; i <= 'Z'; i++, drvs >>= 1) {
            if(drvs & 1) {
                sprintf(drive, "%c:", i);
                it = new Fl_FileItem(drive, fl_file_attr(drive));
                it->image(0, hd_pix);
            }
        }
    }
    else if(read_net) {
        up_->activate();
        read_network(netres);
    }
    else
#endif
    {
        listview_->column_name(1, _("Size"));
        listview_->column_name(2, _("Type"));
        listview_->column_name(3, _("Modified"));
        char filename[FL_PATH_MAX];
        struct dirent **files;
        int count = fl_filename_list(fullpath(), &files);
        int n = 0;

        if(count>0)
        {
            for(n=0; n<count; n++)
            {
                if(strcmp(files[n]->d_name, ".") != 0 && strcmp(files[n]->d_name, "..") != 0)
                {
                    snprintf(filename, sizeof(filename)-1, "%s%c%s", fullpath(), slash, files[n]->d_name);
                    Fl_FileAttr *attr = fl_file_attr(filename);

#ifndef _WIN32
                    if(attr->flags & FL_LINK) {
                        char tmp[FL_PATH_MAX] = {0};
                        if(readlink(filename, tmp, sizeof(tmp)))
                            if(fl_is_dir(tmp)) attr->flags |= FL_DIR;
                    }
#endif

                    if(attr->flags & FL_DIR) {
                        Fl_FileItem *it = new Fl_FileItem(files[n]->d_name, attr);
                        it->image(&fold_pix);
                        free(files[n]);
                        files[n] = 0;
                    } else
                        delete attr;
                }
            }

            for(n=0; n<count; n++)
            {
                if(files[n] && (strcmp(files[n]->d_name, ".") && strcmp(files[n]->d_name, "..") != 0) && mode() != Fl_File_Dialog::DIRECTORY)
                {
                    bool sel = false;
                    snprintf(filename, sizeof(filename)-1, "%s%c%s", fullpath(), slash, files[n]->d_name);
                    Fl_FileAttr *attr = fl_file_attr(filename);
                    if(!(attr->flags & FL_DIR)) {
                        Fl_FileItem *item=0;
                        if(default_filename_) sel = !strcmp(default_filename_, files[n]->d_name);
                        if(_cur_filter) {
                            if(fl_file_match(filename, _cur_filter->pattern))
                                item = new Fl_FileItem(files[n]->d_name, attr);
                        } else {
                            item = new Fl_FileItem(files[n]->d_name, attr);
                        }
                        if(item) {
                            item->image(&file_pix);
                            item->type(Fl_FileItem::FILE);
                            if(sel) {
                                selected = item;
                            }
                        }
                    } else
                        delete attr;
                }
                if(files[n]) free(files[n]);
            }
            free(files);
        }
    }

    listview_->end();
    listview_->layout();

    if(listview_->column_width(0) > int(listview_->w()/1.5)) {
        listview_->column_width(0, int(listview_->w()/1.5));
        listview_->relayout();
    }
    if(listview_->column_width(0) <= 0) {
        listview_->column_width(0, 50);
        listview_->relayout();
    }

    if(mode()!=DIRECTORY) {		
        ok_->deactivate();
        if(selected) {
            listview_->select_only(selected);
            listview_->show_item(selected);
        }
        if(default_filename_) {
            location(default_filename_);
            ok_->activate();
		}
    } else {
        ok_->activate();
    }

    default_filename_ = 0;
    listview_->redraw();
}

bool Fl_File_Dialog::new_dir()
{
    const char	*dir;		// New directory name
    char pathname[FL_PATH_MAX];	// Full path_ of directory

    // Get a directory name from the user
    if ((dir = fl_input(_("New Directory?"))) == NULL)
        return false;

    // Make it relative to the current directory as needed...
#ifdef _WIN32
    if(dir[1] == '\\' && dir[2] != ':')
#else
    if(dir[0] == '/')
#endif /* _WIN32 || __EMX__ */
    {
        strncpy(pathname, dir, sizeof(pathname) - 1);
        pathname[sizeof(pathname) - 1] = '\0';
    }
    else
        snprintf(pathname, sizeof(pathname)-1, "%s%c%s", fullpath(), slash, dir);

    // Create the directory; ignore EEXIST errors...
#ifdef _WIN32
    if(mkdir(pathname)!=0)
#else
    if(mkdir(pathname, 0755)!=0)
#endif
        if(errno != EEXIST) {
            fl_alert(_("Unable to create directory!"));
            return false;
        }


    read_dir(pathname); // Show the new directory...

    return true;
}

void Fl_File_Dialog::file_clicked(Fl_FileItem *i)
{
    ok_->activate();
    Fl_ListView_Item *item=0;

    if(listview_->type()&Fl_ListView::MULTI_SELECTION)
    {
        files[0] = '\0';
        int tot=0;
        int items=0;
        for(uint n=0; n<listview_->get_selection().size(); n++) {
            item = (Fl_ListView_Item*)listview_->get_selection()[n];
            if(items > 5) {
                strcat(files, "....");
                break;
            }
            if(item->label()) {
                int len = strlen(item->label());
                tot += len+2;

                if(tot>4090) {
                    strcat(files, "....");
                    break;
                }

                char tmp[1024];
                sprintf(tmp, "\"%s\" ", item->label());
                strcat(files, tmp);
                items++;
            }
        }

        if(items==1) {
            item = (Fl_ListView_Item *)listview_->item();
            if(item) location_->value(item->label());
        } else if(items>1) {
            location_->value(files);
        }
    }
    else
    {
        //D->fullpath((const char *)((Fl_File_DialogItem *)w)->fullpath());
        location_->value(i->label());
    }

    if(Fl::event_clicks())
        close(CLOSE_OK);
    else {
        item = (Fl_ListView_Item *)listview_->item();
        if(item && preview()) {
            char tmp[FL_PATH_MAX];
            snprintf(tmp, sizeof(tmp)-1, "%s%c%s", fullpath(), slash, item->label());
            update_preview(tmp);
        }
    }
}

void Fl_File_Dialog::folder_clicked(Fl_FileItem *i)
{
    ok_->activate();
    location_->value("");

    if(Fl::event_clicks()) {
        char tmp[FL_PATH_MAX];

        if(fullpath()) {
            if(!strcmp(fullpath(), "/"))
                sprintf(tmp, "%s%s", fullpath(), i->label());
            else
                sprintf(tmp, "%s%c%s", fullpath(), slash, i->label());
        }
#ifdef _WIN32
        else if(i->type()==Fl_FileItem::NETWORK)
            sprintf(tmp, "\\\\%s", i->label());
#endif
        else
            sprintf(tmp, "%s", i->label());

#ifndef _WIN32
        if(i->attr->flags & FL_LINK) {
            int len=0;
            if((len=readlink(tmp, tmp, sizeof(tmp)))) tmp[len] = '\0';
            else return;
        }
#endif
        read_dir(tmp);
    }
}


//CALLBACKS!!
void Fl_File_Dialog::cb_list(Fl_Widget *w, void *d)
{
    Fl_ListView *l = (Fl_ListView *)w;
    Fl_FileItem *i = (Fl_FileItem *)l->item();

    if(i) {
        if(i->type()>=Fl_FileItem::DIR)
            FD->folder_clicked(i);
        else
            FD->file_clicked(i);

    }
}

void Fl_File_Dialog::cb_ok(Fl_Widget *, void *d) 
{
    if(!strcmp(FD->location_->value(), ".")) return;
    if(!strcmp(FD->location_->value(), "..")) {
        cb_up(0, d);
        return;
    }

    Fl_FileItem *i = (Fl_FileItem *)FD->listview()->item();
    char file[FL_PATH_MAX];

    if(FD->mode()==SAVE) {
        if(strlen(FD->location())>0) {
            FD->close(CLOSE_OK);
            return;
        }
    }

    if(FD->mode()==DIRECTORY) {
        // Complete dirpath with selected item
        /*if(i && i->type()==Fl_FileItem::DIR) {
            if(FD->get_filename(i->label(), file))
                FD->fullpath(file);
        }*/
        if(FD->fullpath()) { FD->close(CLOSE_OK); return; }
    }

    if(i && i->type()>=Fl_FileItem::DIR) {
        // Open directory
        Fl::event_clicks(1);
        FD->folder_clicked(i);
        return;
    }

    if(FD->get_filename(FD->location_->value(), file)) {

        if(fl_is_dir(file)) {

            // Change directory
            FD->read_dir(file);

        } else {

            if(FD->mode()==SAVE) {
                FD->close(CLOSE_OK);
                return;
            }
            else if(FD->mode()==DEFAULT && fl_file_exists(file)) {
                FD->close(CLOSE_OK);
                return;
            }
        }
    }

    if(i && FD->listview()->multi()) {
        FD->close(CLOSE_OK);
    }
}

void Fl_File_Dialog::cb_cancel(Fl_Widget *, void *d) {
	FD->close(CLOSE_CANCEL);
}

void Fl_File_Dialog::cb_new(Fl_Widget *, void *d) {
	FD->new_dir();
}

void Fl_File_Dialog::cb_home(Fl_Widget *, void *d) {
	char *p = fl_get_homedir();
	FD->read_dir(p);
	delete []p;
}

void Fl_File_Dialog::cb_refresh(Fl_Widget *, void *d) {
	FD->read_dir( FD->fullpath() );
}


void Fl_File_Dialog::cb_up(Fl_Widget *, void *d) 
{
    if(!FD->fullpath()) {
        FD->read_dir(0);
        return;
    }

    char *buf = strdup( FD->fullpath() );

    char *slash_ = strrchr(buf, slash);

    if(slash_) {
        *slash_ = '\0';
#ifdef _WIN32
        if(*(slash_-1)=='\\')
            FD->read_dir(_("My Network"));
        else
#endif
            FD->read_dir(buf);
    } else {
        FD->read_dir(0);
    }
    delete []buf;
}

void Fl_File_Dialog::cb_dirc(Fl_Widget *w, void *d) {
	const char *dir = ((Fl_Input_Browser *)w)->value();
	if(dir && *dir)
		FD->read_dir(dir);
}

void Fl_File_Dialog::cb_filter(Fl_Widget *w, void *d)
{
	Fl_File_Dialog *D = (Fl_File_Dialog *)w->user_data();
	
	Filter *F = (Filter *)((Fl_Input_Browser *)w)->item()->user_data();	

	D->set_filter(F);
	D->read_dir(D->fullpath());	
}

void Fl_File_Dialog::cb_preview(Fl_Widget *w, void *d)
{
    FD->preview(bool(w->value()==1));
}

char *Fl_File_Dialog::get_filename(const char *path, char *buf)
{
    char check; int checkp;
#ifdef _WIN32
    check=':'; checkp=1;
#else
    check='/'; checkp=0;
#endif
    char tmp[FL_PATH_MAX];
    if(fl_file_expand(tmp, path)) path = tmp;

    if(path[checkp]==check || !fullpath() 
#ifdef _WIN32
		|| !strncmp(path, "//", 2) //Check for network path..
#endif
		)
        snprintf(buf, FL_PATH_MAX, "%s", path);
    else if(fullpath()[strlen(fullpath())-1]==slash)
        snprintf(buf, FL_PATH_MAX, "%s%s", fullpath(), path);
    else
        snprintf(buf, FL_PATH_MAX, "%s%c%s", fullpath(), slash, path);

    return buf;
}

char *Fl_File_Dialog::get_filepath(const char *path, char *buf)
{	
    char check; int checkp;
#ifdef _WIN32
    check=':'; checkp=1;
#else
    check='/'; checkp=0;
#endif	

    char tmp_path[FL_PATH_MAX];
    if(path && path[checkp]!=check && fullpath())
	{
		strncpy(tmp_path, fullpath(), FL_PATH_MAX);
        if(tmp_path[strlen(tmp_path)-1]!=slash && path[0]!=slash) { 
			char sl[2] = { slash, '\0' }; strcat(tmp_path, sl); 
		}
        strcat(tmp_path, path);
        path = tmp_path;
    }
    char tmp[FL_PATH_MAX];
    if(fl_file_expand(tmp, path)) path = tmp;

    char *p = strrchr(path, slash);
    if(p) {
        const char *ptr = path;
        char *bufptr = buf;
        int len=0;
        while(ptr<=p) {
            *bufptr++ = *ptr++;
            len++;
        }
        *bufptr++ = '\0';

        if(fl_is_dir(buf) || (len<=3&&buf[1]==':')) {
            return buf;
        }
    }

    if(fl_is_dir(path)) {
        snprintf(buf, FL_PATH_MAX, "%s", path);
        return buf;
    }

    return 0;
}

void Fl_File_Dialog::cb_location(Fl_Widget *w, void *d)
{
    Fl_Input_Browser *loc = (Fl_Input_Browser *)w;

    char tmp[FL_PATH_MAX] = {0};
    char tmp2[FL_PATH_MAX]= {0};

    if(!strcmp(loc->value(),"")) {
        FD->ok_->deactivate();
        loc->hide_popup();
        return;
    }

    if(FD->mode()==SAVE)
        FD->ok_->activate();

	int key = Fl::event_key();

    if(key == FL_Enter) {

        if(!strcmp(loc->value(), "..")) {
            FD->cb_up(w, d);
            return;
        }

        FD->get_filename(loc->value(), tmp);

        if(fl_is_dir(tmp)
#ifdef _WIN32
			|| !strncmp(tmp, "//", 2) //Check for network path..
#endif
			) {
            FD->read_dir(tmp);
        } else if(FD->mode()<=Fl_File_Dialog::SAVE) {
            if(!fl_is_dir(tmp) && (FD->mode()==Fl_File_Dialog::DEFAULT?fl_file_exists(tmp):true)) {
                FD->ok_->activate();
				FD->close(false);
                //FD->location_->hide_popup();
                //FD->ok_->do_callback();
                return;
            } else {
                FD->ok_->deactivate();
                FD->clear_value();
            }
        }

        loc->hide_popup();

    } else if(Fl::compose(key)) {		

        char *filename = FD->get_filename(loc->value(), tmp);
        char *dirpath = FD->get_filepath(loc->value(), tmp2);
        int dirpath_len = dirpath?strlen(dirpath):0;

        if(FD->mode()!=Fl_File_Dialog::SAVE) {
            if(fl_file_exists(tmp)) FD->ok_->activate();
            else FD->ok_->deactivate();
        }

        char pattern[64];
        char *p = strrchr(filename, slash);
        if(p) {
            p++;
            strcpy(pattern, p);
            strcat(pattern, "*");
        } else {
            strcpy(pattern, filename);
            strcpy(pattern, "*");
        }

        loc->clear();
        if(dirpath) 
		{
            loc->begin();

            bool match = false;

            struct dirent **files=0;
            int count = fl_filename_list(dirpath, &files);
            char filen[FL_PATH_MAX];
            for(int n=0; n<count; n++) {
                char *file = files[n]->d_name;

                if(strcmp(file, ".") && strcmp(file, "..") && fl_file_match(file, pattern)) {

                    if(file[0]==slash)
                        snprintf(filen, sizeof(filen)-1, "%s", file);
                    else if(dirpath[dirpath_len-1]==slash)
                        snprintf(filen, sizeof(filen)-1, "%s%s", dirpath, file);
                    else
                        snprintf(filen, sizeof(filen)-1, "%s%c%s", dirpath, slash, file);

                    if(FD->mode()==Fl_File_Dialog::DIRECTORY && !fl_is_dir(filen)) {
                        continue;
                    }
                    Fl_Widget *w = new Fl_Item(filen);
                    w->copy_label(filen);
                    match = true;
                }
                free(files[n]);
            }
            if(files) free(files);

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

void Fl_File_Dialog::preview(bool show)
{
	preview_on = show;

	int W=listview_->parent()->w(), H=listview_->parent()->h();
	
	if(!show) {
		image_cache.clear();
		preview_->image(0);
		preview_text[0] = '\0';
		preview_info[0] = '\0';

		preview_->hide();
		preview_info_->hide();

		listview_->w(W);
		listview_->relayout();
		listview_->parent()->init_sizes();

	} else {

		int prev_h = (int)(H*0.65);
		int prev_w = (int)(W*0.30);

		listview_->w(W-prev_w);
		preview_->resize(W-prev_w+5, 0, prev_w-5, prev_h);
		preview_info_->resize(W-prev_w+5, preview_->h(), prev_w-5, H-preview_->h());
		
		listview_->relayout();
		listview_->parent()->init_sizes();
		
		preview_->show();
		preview_info_->show();	
		
		Fl_ListView_Item *item = (Fl_ListView_Item *)listview_->item();
		if(item && item->label() && fullpath()) {
			char tmp[FL_PATH_MAX];
			snprintf(tmp, sizeof(tmp)-1, "%s%c%s", fullpath(), slash, item->label());
			update_preview(tmp);
		}
	}

	listview_->parent()->redraw();
}

void Fl_File_Dialog::update_preview(const char *filename)
{
	preview_->image(0);
	preview_text[0] = '\0';
	preview_info[0] = '\0';

	if(!filename) {
		preview_->redraw();
		preview_info_->redraw();
		return;
	}

	bool loaded = false;

	if(fl_file_match(filename, "*.{gif|bmp|xpm|png|jpg|jpeg}")) {
		
		Fl_Image *im = 0;
		
		im = image_cache.get(filename);
		if(!im) {
			// Not in cache
			cursor(FL_CURSOR_WAIT);
			Fl::check();
			im= Fl_Image::read(filename);
		}

		if(im) {		
			
                    if(im->format()->Amask) {
                        // If image has alpha pixel, blend it to preview box backgroud
                        Fl_Image *blended = im->back_blend(preview_->color());
                        delete im;
                        im = blended;
                    }

                    snprintf(preview_info, sizeof(preview_info)-1,
                             "%s\n\n%s %d x %d\n%s %s",
                             ((Fl_ListView_Item *)listview()->item())->label(),
                             _("Size:"),
                             im->width(), im->height(),
                              _("File Size:"),
                             ((Fl_ListView_Item *)listview()->item())->label(1));

                    im->system_convert();
                    image_cache.add(im, filename);
                    preview_->image(im);
                    preview_->redraw();
                    loaded = true;
                }

	} else {

		cursor(FL_CURSOR_WAIT);
		Fl::check();

		FILE *fp;
		int	 bytes;
		char *ptr;

		fp = fl_fopen(filename, "rb");
		if (fp != NULL) {
			// Try reading the first 1k of data for a label...
			bytes = fread(preview_text, 1, sizeof(preview_text) - 1, fp);
			preview_text[bytes] = '\0';
			fclose(fp);
			loaded = true;
		} else {
			// Assume we can't read any data...
			preview_text[0] = '\0';
		}		

		// Scan the buffer for printable chars...
		for(ptr = preview_text; *ptr && (isprint(*ptr) || isspace(*ptr)); ptr ++);

		if(*ptr || ptr == preview_text) {			
			loaded = false;
		} else {
			snprintf(preview_info, sizeof(preview_info)-1, 
				"%s\n\n%s %s",
                                 ((Fl_ListView_Item *)listview()->item())->label(),
                                 _("File Size:"),
				((Fl_ListView_Item *)listview()->item())->label(1));

			// remove '\r' from text EOL
			for(ptr = preview_text; *ptr; ptr++) if(*ptr=='\r') *ptr=' ';

			preview_->align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_LEFT|FL_ALIGN_TOP);
			preview_->label_font(FL_COURIER);
		}
	}

	if(!loaded) {
		preview_text[0] = '?'; 
		preview_text[1] = '\0';
		preview_->align(FL_ALIGN_CLIP);
		preview_->label_font(FL_TIMES);
	}
	
	preview_->redraw();
	preview_info_->redraw();
	
	cursor(FL_CURSOR_DEFAULT);
	Fl::check();
}

int Fl_File_Dialog::handle(int e)
{
    if(e==FL_KEYUP && Fl::event_key()==FL_BackSpace) {
        if(Fl::focus()==listview_) {
            cb_up(0, this);
            return 1;
        }
    }
    return Fl_Window::handle(e);
}

////////////////////////////
// WIN32 NETWORK

#ifdef _WIN32

// This sucks... I hate pure windoze programming...
bool Fl_File_Dialog::enum_netresources(Fl_Callback *cb, LPNETRESOURCE lpnr, DWORD scope)
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
	((Fl_File_Dialog *)w)->add_netitem((LPNETRESOURCE)d);	
}

void Fl_File_Dialog::add_netitem(LPNETRESOURCE net)
{
	if(!net->lpRemoteName) return;

	listview_->begin();

	char *tmp = strdup(net->lpRemoteName);
	char *p = strrchr(tmp, '\\');
	tmp+=(p-tmp)+1;

	Fl_FileItem *i = new Fl_FileItem(tmp, 0);
        i->type(Fl_FileItem::NETWORK);
	if(scope==RESOURCE_GLOBALNET)
		i->image(0, fold_pix);		
	else
		i->image(0, hd_pix);
	listview_->end();
}

void Fl_File_Dialog::read_network(LPNETRESOURCE net)
{
	scope = RESOURCE_CONTEXT;
	if(net) scope = RESOURCE_GLOBALNET;		

	listview_->clear();	
	enum_netresources(cb_add_netitem, net, scope);	
}

#endif

