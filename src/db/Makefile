include ../../makeinclude

CPPFILES = \
	Fl_Database.cpp \
	Fl_Query.cpp \
	Fl_Params.cpp 

CFILES =

LIBNAME = libefltk
DSOLIBNAME = $(LIBNAME)
LIBRARY = ../lib/$(LIBNAME)
DSO = ../lib/$(LIBNAME)
DSONAME = $(LIBNAME)$(DSOEXT)

OBJECTS = $(CPPFILES:.cpp=.o) $(CFILES:.c=.o)
STATIC_OBJECTS = $(OBJECTS:.o=.static.o)
SHARED_OBJECTS = $(OBJECTS:.o=.shared.o)

all: $(BUILDTARGETS)

static: $(LIBRARY)$(LIBEXT)

shared: $(DSO)$(DSOEXT)

programs:

$(LIBRARY).a: $(STATIC_OBJECTS)

$(DSO).so.2 $(DSO).sl.2: $(SHARED_OBJECTS)

DLLIMPORTNAME = $(LIBNAME).2.dll$(LIBEXT)
$(DSO).2.dll: $(SHARED_OBJECTS)

clean :
	@rm -f *.o *~ makedepend
	@touch makedepend

depend:
	$(MAKEDEPEND) -I../.. $(CXXFLAGS) $(CPPFILES) $(CFILES) > makedepend
	sed -e "s'\.o'\.shared\.o'" makedepend > foo
	cat foo >> makedepend
	rm foo

# include dependency files if it exist
ifeq (makedepend, $(wildcard makedepend))
include makedepend
endif
