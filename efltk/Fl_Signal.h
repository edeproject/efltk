/*
 * $Id$
 *
 * Extended Fast Light Toolkit (EFLTK)
 * Copyright (C) 2002-2003 by EDE-Team
 * WWW: http://www.sourceforge.net/projects/ede
 *
 * Fast Light Toolkit (FLTK)
 * Copyright (C) 1998-2003 by Bill Spitzak and others.
 * WWW: http://www.fltk.org
 *
 * This library is distributed under the GNU LIBRARY GENERAL PUBLIC LICENSE
 * version 2. See COPYING for details.
 *
 * Author : Mikko Lahteenmaki
 * Email  : mikko@fltk.net
 *
 * Please report all bugs and problems to "efltk-bugs@fltk.net"
 *
 */

#ifndef _FL_SIGNAL_H_
#define _FL_SIGNAL_H_

#include <stdlib.h>

typedef struct Fl_Signal_Func_Struct {
    Fl_Signal_Callback *func;   //pointer to callback
    void *obj_ptr;              //pointer to receiver object
    int event;                  //event we accept
    Fl_Signal_Func_Struct *next;//pointer to next function in signal
} Fl_Signal_Func;

// Fl_Signal structure.
// Handles multiple callbacks.
typedef struct FL_API Fl_Signal_Struct
{
    Fl_Signal_Struct()  { first = 0; }
    ~Fl_Signal_Struct() { disconnect_all(); }

    // Remove all connected callbacks
    void disconnect_all() {
        for(Fl_Signal_Func *cb = first; cb;) { 
            Fl_Signal_Func *delcb=cb; cb = cb->next; free(delcb); 
        }
        first = 0;
    }
    
    // Connect callback 'func' with class object pointer 'obj_ptr'
    // If 'obj_ptr' is NULL, func is assumed to be normal (e)FLTK style callback function.
    // Called by FL_CONNECT_* macros internally.
    void connect(Fl_Signal_Callback *func, void *obj_ptr, int event=0) {
        Fl_Signal_Func *cb = (Fl_Signal_Func *)malloc(sizeof(Fl_Signal_Func));
        cb->next = first;       
        first = cb;
        cb->event   = event;
        cb->func    = func;
        cb->obj_ptr = obj_ptr;
    }

    // Disconnect callback 'func' with object pointer 'obj_ptr'
    void disconnect(Fl_Signal_Callback *func, void *obj_ptr, int event=0) {
        for(Fl_Signal_Func **p = &first; *p;) {
            Fl_Signal_Func *cb = *p;
            if(cb->func == func && cb->obj_ptr == obj_ptr) {
                *p = cb->next;
                free(cb);               
            } else {
                p = &(cb->next);
            }
        }
    }
    
    // Call all connected callbacks. 
    // That is - emit signal    
    int emit(int event, void *caller, void *user_data, void *opt_data) {
		int cnt = 0;
        for(Fl_Signal_Func *cb = first; cb; cb=cb->next) {
            if(cb->event!=event) continue;
			cnt++;
            //void *caller, void *user_data, int event, void *opt_data, void *receiver 
            if(cb->obj_ptr) cb->func(caller, user_data, event, opt_data, cb->obj_ptr);
            else            cb->func(caller, user_data, event, opt_data, 0);
        }
		return cnt; // return 0 if no event handlers were found
    }

private:
    Fl_Signal_Func *first;
} Fl_Signal;

// All slot types:
// void slot(CallerClass *caller, int event, type user_data, type opt_data)
// void slot(CallerClass *caller, int event, type opt_data)
// void slot(CallerClass *caller, type user_data, type opt_data)
// void slot(CallerClass *caller, type opt_data)
// void slot(CallerClass *caller, type user_data)
// void slot(CallerClass *caller, int event)
// void slot(CallerClass *caller)
// void slot()

//void slot(CallerClass *caller, int event, void *opt_data, void *user_data)
#define DEFSLOT_CEUO(CallerClass, ReceiverClass, CB, userdata_type, opt_type) \
static inline void cb_i_##CB(void *caller, void *user_data, int event, void *opt_data, void *receiver) { \
    ((ReceiverClass*)receiver)->CB((CallerClass*)caller, event, (userdata_type)user_data, (opt_type)opt_data); \
}

//void slot(CallerClass *caller, int event, void *opt_data)
#define DEFSLOT_CEO(CallerClass, ReceiverClass, CB, opt_type) \
static inline void cb_i_##CB(void *caller, void *, int event, void *opt_data, void *receiver) { \
    ((ReceiverClass*)receiver)->CB((CallerClass*)caller, event, (opt_type)opt_data); \
}

//void slot(CallerClass *caller, void *user_data, void *opt_data)
#define DEFSLOT_CUO(CallerClass, ReceiverClass, CB, userdata_type, opt_type) \
static inline void cb_i_##CB(void *caller, void *user_data, int, void *opt_data, void *receiver) { \
    ((ReceiverClass*)receiver)->CB((CallerClass*)caller, (userdata_type)user_data, (opt_type)opt_data); \
}

//void slot(CallerClass *caller, void *opt_data)
#define DEFSLOT_CO(CallerClass, ReceiverClass, CB, opt_type) \
static inline void cb_i_##CB(void *caller, void *, int, void *opt_data, void *receiver) { \
    ((ReceiverClass*)receiver)->CB((CallerClass*)caller, (opt_type)opt_data); \
}

//void slot(CallerClass *caller, void *user_data)
#define DEFSLOT_CU(CallerClass, ReceiverClass, CB, userdata_type) \
static inline void cb_i_##CB(void *caller, void *user_data, int, void *, void *receiver) { \
    ((ReceiverClass*)receiver)->CB((CallerClass*)caller, (userdata_type)user_data); \
}

//void slot(CallerClass *caller, int event)
#define DEFSLOT_CE(CallerClass, ReceiverClass, CB) \
static inline void cb_i_##CB(void *caller, void *, int event, void *, void *receiver) { \
    ((ReceiverClass*)receiver)->CB((CallerClass*)caller, event); \
}

//void slot(CallerClass *caller)
#define DEFSLOT_C(CallerClass, ReceiverClass, CB) \
static inline void cb_i_##CB(void *caller, void *, int, void *, void *receiver) { \
    ((ReceiverClass*)receiver)->CB((CallerClass*)caller); \
}

//void slot(CallerClass *caller)
#define DEFSLOT_O(CallerClass, ReceiverClass, CB, opt_type) \
static inline void cb_i_##CB(void *, void *, int, void *opt_data, void *receiver) { \
    ((ReceiverClass*)receiver)->CB((opt_type)opt_data); \
}

//void slot()
#define DEFSLOT(CallerClass, ReceiverClass, CB) \
static inline void cb_i_##CB(void *, void *, int, void *, void *receiver) { \
    ((ReceiverClass*)receiver)->CB(); \
}

// Member function slot
#define SLOT(Receiver, CB) Receiver, (Fl_Signal_Callback*)(Receiver)->cb_i_##CB

// Static function slot
#define STATIC_SLOT(CB) 0, (Fl_Signal_Callback*)CB

#endif
