#ifndef _FL_EVENTS_H_
#define _FL_EVENTS_H_

enum Fl_Event_Group {
    FL_MOUSE_EVENTS         = 0x100,
    FL_KEY_EVENTS           = 0x200,
    FL_FOCUS_EVENTS         = 0x400,
    FL_DND_EVENTS           = 0x800,
    FL_MENU_EVENTS          = 0x1000,
    FL_EDIT_EVENTS          = 0x2000,
    FL_BUTTON_EVENTS        = 0x4000,
    FL_WIDGET_EVENTS        = 0x8000,
    FL_LIST_EVENTS          = 0x10000,
    FL_DATA_EVENTS          = 0x20000,
    FL_WINDOW_EVENTS        = 0x40000,
    FL_DIALOG_EVENTS        = 0x80000
};

#define FL_PHYSICAL_EVENTS  FL_MOUSE_EVENTS|FL_KEY_EVENTS|FL_FOCUS_EVENTS|FL_DND_EVENTS
#define FL_LOGICAL_EVENTS   FL_MENU_EVENTS|FL_EDIT_EVENTS|FL_BUTTON_EVENTS|FL_LIST_EVENTS|FL_WIDGET_EVENTS|FL_DATA_EVENTS|FL_WINDOW_EVENTS|FL_DIALOG_EVENTS
#define FL_EVENTS_MASK      FL_PHYSICAL_EVENTS|FL_LOGICAL_EVENTS

enum Fl_Event_Types {
    FL_NO_EVENT             = 0,

    // (Physical) Mouse events 
    FL_MOUSE_PUSH           = FL_MOUSE_EVENTS + 1, 
    FL_MOUSE_RELEASE        = FL_MOUSE_EVENTS + 2, 
    FL_MOUSE_ENTER          = FL_MOUSE_EVENTS + 3, 
    FL_MOUSE_LEAVE          = FL_MOUSE_EVENTS + 4, 
    FL_MOUSE_DRAG           = FL_MOUSE_EVENTS + 5, 
    FL_MOUSE_MOVE           = FL_MOUSE_EVENTS + 6, 
    FL_MOUSE_WHEEL          = FL_MOUSE_EVENTS + 7,

    // (Physical) Keyboard 
    FL_KEY_DOWN             = FL_KEY_EVENTS + 1, 
    FL_KEY_UP               = FL_KEY_EVENTS + 2,
    FL_KEY_SHORTCUT         = FL_KEY_EVENTS + 3,

    // (Physical) Focus events
    FL_FOCUS_ASK            = FL_FOCUS_EVENTS + 1, 
    FL_FOCUS_RECEIVED       = FL_FOCUS_EVENTS + 2,
    FL_FOCUS_LOST           = FL_FOCUS_EVENTS + 2,

    // (Physical) Drag-n-Drop events 
    FL_DND_ENTER            = FL_DND_EVENTS + 1,
    FL_DND_DRAG             = FL_DND_EVENTS + 2,
    FL_DND_LEAVE            = FL_DND_EVENTS + 3,
    FL_DND_RELEASE          = FL_DND_EVENTS + 4,

    // (Logical) Edit commands 
    FL_EDIT_COPY            = FL_EDIT_EVENTS + 1,
    FL_EDIT_CUT             = FL_EDIT_EVENTS + 2,
    FL_EDIT_PASTE           = FL_EDIT_EVENTS + 3,
    FL_EDIT_DELETE          = FL_EDIT_EVENTS + 4,

    // (Logical) Menu commands
    FL_MENU_COMMAND         = FL_MENU_EVENTS + 1,

    // (Logical) Data modification commands
    FL_DATA_CHANGE          = FL_DATA_EVENTS + 1,
    FL_DATA_INSERT          = FL_DATA_EVENTS + 2,
    FL_DATA_DELETE          = FL_DATA_EVENTS + 3,
    FL_DATA_EDIT            = FL_DATA_EVENTS + 4,
    FL_DATA_REFRESH         = FL_DATA_EVENTS + 5,
    FL_DATA_SENT            = FL_DATA_EVENTS + 6,
    FL_DATA_RECEIVED        = FL_DATA_EVENTS + 7,
    FL_DATA_AVAILABLE       = FL_DATA_EVENTS + 8,
    FL_DATA_COMMAND         = FL_DATA_EVENTS + 9,

    // (Logical) Widget events 
    FL_WIDGET_ACTIVATE      = FL_WIDGET_EVENTS + 1,
    FL_WIDGET_DEACTIVATE    = FL_WIDGET_EVENTS + 2,
    FL_WIDGET_SHOW          = FL_WIDGET_EVENTS + 3,
    FL_WIDGET_HIDE          = FL_WIDGET_EVENTS + 4,

    // (Logical) Button events
    FL_BUTTON_DOWN          = FL_BUTTON_EVENTS + 1,
    FL_BUTTON_UP            = FL_BUTTON_EVENTS + 2,
    FL_BUTTON_PRESSED       = FL_BUTTON_EVENTS + 3,

    // (Logical) List events 
    FL_LIST_ITEM_ADDED      = FL_LIST_EVENTS + 1, 
    FL_LIST_ITEM_DELETED    = FL_LIST_EVENTS + 2,
    FL_LIST_ITEM_UPDATED    = FL_LIST_EVENTS + 3,
    FL_LIST_ITEM_SELECTED   = FL_LIST_EVENTS + 4,
    FL_LIST_PROGRESS        = FL_LIST_EVENTS + 5,

    // (Logical) Window events 
    FL_WINDOW_SHOW          = FL_WINDOW_EVENTS + 1,
    FL_WINDOW_CLOSE         = FL_WINDOW_EVENTS + 2,
    FL_WINDOW_DESTROY       = FL_WINDOW_EVENTS + 3,

    // (Logical) Dialog events
    FL_DIALOG_OK            = FL_DIALOG_EVENTS + 1,
    FL_DIALOG_CANCEL        = FL_DIALOG_EVENTS + 2,
    FL_DIALOG_HELP          = FL_DIALOG_EVENTS + 3,
    FL_DIALOG_BUTTON        = FL_DIALOG_EVENTS + 4
};

// Backward compatibility
#define FL_PUSH         FL_MOUSE_PUSH
#define FL_RELEASE      FL_MOUSE_RELEASE
#define FL_ENTER        FL_MOUSE_ENTER
#define FL_LEAVE        FL_MOUSE_LEAVE
#define FL_DRAG         FL_MOUSE_DRAG
#define FL_MOVE         FL_MOUSE_MOVE
#define FL_MOUSEWHEEL   FL_MOUSE_WHEEL

#define FL_FOCUS        FL_FOCUS_ASK
#define FL_UNFOCUS      FL_FOCUS_LOST

#define FL_COPY         FL_EDIT_COPY
#define FL_CUT          FL_EDIT_CUT
#define FL_PASTE        FL_EDIT_PASTE
#define FL_DELETE       FL_EDIT_DELETE

#define FL_WND_CLOSE    FL_WINDOW_CLOSE
#define FL_WND_DESTROY  FL_WINDOW_DESTROY

#define FL_KEYBOARD     FL_KEY_DOWN
#define FL_KEY          FL_KEY_DOWN
#define FL_KEYUP        FL_KEY_UP
#define FL_SHORTCUT     FL_KEY_SHORTCUT

#define FL_MENU_ITEM    FL_MENU_COMMAND

#define FL_SHOW         FL_WIDGET_SHOW
#define FL_HIDE         FL_WIDGET_HIDE

#define FL_UC_INSERT    FL_DATA_INSERT
#define FL_UC_DELETE    FL_DATA_DELETE
#define FL_UC_EDIT      FL_DATA_EDIT
#define FL_UC_REFRESH   FL_DATA_REFRESH

#define FL_ACTIVATE     FL_WIDGET_ACTIVATE
#define FL_DEACTIVATE   FL_WIDGET_DEACTIVATE

#define FL_DIALOG_BTN   FL_DIALOG_BUTTON

#endif
