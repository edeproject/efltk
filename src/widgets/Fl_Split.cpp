#include <efltk/Fl_Split.h>
#include <efltk/fl_draw.h>
#include <efltk/Fl.h>

Fl_Split::Fl_Split(Fl_Widget * _ref_,int layout_size)
    :Fl_Box("",layout_size,(FlagsEnum)_ref_->layout_align()),ref_(_ref_)
{
    box(FL_UP_BOX);
    // dir_ is set to 1 when the splitter is vertical and is set to 0 when horizontal
    dir_=(layout_align()&(FL_ALIGN_LEFT|FL_ALIGN_RIGHT));
}
    
int Fl_Split::handle(int ev)
{
    static int ox=0,oy=0; // old x and y
    static int dragging=0;// dragging flag
    int nx=Fl::event_x(); // current x
    int ny=Fl::event_y(); // current y
    int dx,dy;
    Fl_Widget * client=NULL;
    switch (ev){
        //// When the mouse enters, change the cursor, so the user sees what he can do
        case FL_ENTER:
            fl_cursor((dir_)?FL_CURSOR_WE:FL_CURSOR_NS);
            return 1;
        //// When the mouse leaves, reset the cursor
        case FL_LEAVE:
            fl_cursor(FL_CURSOR_DEFAULT);
            return 1;
        case FL_PUSH:
            fl_cursor(FL_CURSOR_HAND);
            ox=nx;oy=ny;
            dragging=1;
            return 1;
        case FL_RELEASE:
            fl_cursor(FL_CURSOR_DEFAULT);
            dragging=0;
            return 1;
        case FL_MOVE:
        case FL_DRAG:
            if (dragging){
                dx=nx-ox;
                dy=ny-oy;
                int nw=ref_->w(); // These will be the new width and
                int nh=ref_->h(); // height of the widget
                // find the client widget
                for(int i=0;i<parent()->children();i++){
                    Fl_Widget * c=parent()->child(i);
                    if (c->layout_align()&FL_ALIGN_CLIENT){
                        client=c;
                        break;
                    }
                }
                if (client){
                    // we must check that the client should not
                    // have negative sizes
                    int cw=client->w();
                    int ch=client->h();
                    switch (layout_align()){
                        case FL_ALIGN_TOP:    if (ch-dy<0) dy=ch; break;
                        case FL_ALIGN_BOTTOM: if (ch+dy<0) dy=-ch; break;
                        case FL_ALIGN_LEFT:   if (cw-dx<0) dx=cw; break;
                        case FL_ALIGN_RIGHT:  if (cw+dx<0) dx=-cw; break;
                    }
                }
                // na dnow finally resize the widget
                if (dir_){ // vertical
                    if (layout_align()&FL_ALIGN_LEFT){
                        nw+=dx;
                    } else {
                        nw-=dx;
                    }
                    if (nw<0) nw=0;
                } else { // horizontal
                    if (layout_align()&FL_ALIGN_TOP){
                        nh+=dy;
                    } else {
                        nh-=dy;
                    }
                    if (nh<0) nh=0;
                }
                ref_->size(nw,nh);
                parent()->redraw();
            }
            return 1;
    }
    return Fl_Box::handle(ev);
}

