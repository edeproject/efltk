include ../../makeinclude

CPPFILES = \
	Fl_Database.cpp \
	Fl_Query.cpp \
	Fl_Params.cpp 

################################################################

DSOCFLAGS += -DFL_LIBRARY
DSOCXXFLAGS += -DFL_LIBRARY

LIBNAME = libefltk_db
DSOLIBNAME = $(LIBNAME)
LIBRARY = ../../lib/$(LIBNAME)
DSO = ../../lib/$(LIBNAME)
DSONAME = $(LIBNAME)$(DSOEXT)

OBJECTS = $(CPPFILES:.cpp=.o) $(CFILES:.c=.o)
STATIC_OBJECTS = $(OBJECTS:.o=.static.o)
SHARED_OBJECTS = $(OBJECTS:.o=.shared.o)

all: $(BUILDTARGETS)

static: $(LIBRARY)$(LIBEXT)

shared: $(DSO)$(DSOEXT)

programs:

$(LIBRARY).a: $(STATIC_OBJECTS)
	@rm -f $@
	@echo $(LIBCOMMAND) $@ ...
	@$(LIBCOMMAND) $@ $(STATIC_OBJECTS)
	@$(RANLIB) $@

$(DSO).so.2 $(DSO).sl.2: $(SHARED_OBJECTS)
	@rm -f $@
	@echo $(DSOCOMMAND) $(DSONAME) ...
	@$(DSOCOMMAND) $(DSONAME) $(SHARED_OBJECTS) $(DSOLIBS)
ifeq ($(HAVE_STRIP), 1) 
	@$(STRIP) $(DSONAME)
endif
	@mv $(DSONAME) $@

DLLIMPORTNAME = $(LIBNAME).2.dll$(LIBEXT)
$(DSO).2.dll: $(SHARED_OBJECTS)
	@-rm -f $@
	@echo $(DSOCOMMAND) $@ ...
	@$(DSOCOMMAND) $@ $(SHARED_OBJECTS) $(DSOLIBS)
	@-mv $@.import ../lib/$(DLLIMPORTNAME)

clean:
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

################################################################

install: $(INSTALLTARGETS)

install_static: static
	@echo "Installing static DB library..."
	@mkdir -p $(libdir)
	@rm -f $(libdir)/$(LIBNAME)$(LIBEXT)
	@cp -f $(LIBRARY)$(LIBEXT) $(libdir)
	@-chmod 644 $(libdir)/$(LIBNAME)$(LIBEXT)

install_shared: shared
	@echo "Installing shared DB library..."
	@rm -f $(libdir)/$(DLLIMPORTNAME)
	@rm -f $(libdir)/$(DSOLIBNAME)$(DSOEXT)
	@if [ "$(DSOSHORTEXT)" ]; then rm -f $(libdir)/$(DSOLIBNAME)$(DSOSHORTEXT); fi
	@cp -f $(DSO)$(DSOEXT) $(libdir)
	@-chmod 755 $(libdir)/$(DSOLIBNAME)$(DSOEXT)
	@if [ "$(DSOSHORTEXT)" ]; then \
		ln -s $(DSOLIBNAME)$(DSOEXT) $(libdir)/$(DSOLIBNAME)$(DSOSHORTEXT); fi
	@if [ -f "../../lib/$(DLLIMPORTNAME)" ]; then cp ../../lib/$(DLLIMPORTNAME) $(libdir); fi

install_programs:
	@echo "There are no programms to be installed"

###
# $Id$
#
