#
# "$Id$"
#
# Library makefile for the Fast Light Tool Kit (FLTK).
#
# Copyright 1998 by Bill Spitzak and others.
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
# USA.
#
# Please report all bugs and problems to "fltk-bugs@easysw.com".
#

OUT_MAGIC := $(shell mkdir ../lib > /dev/null 2>&1 || :)

include ../makeinclude

################################################################

DSOCFLAGS += -DFL_LIBRARY
DSOCXXFLAGS += -DFL_LIBRARY

LIBNAME = libefltk
DSOLIBNAME = $(LIBNAME)
LIBRARY = ../lib/$(LIBNAME)
DSO = ../lib/$(LIBNAME)
DSONAME = $(LIBNAME)$(DSOEXT)

OBJECTS = $(CPPFILES:.cpp=.o) $(CFILES:.c=.o)

all: $(BUILDTARGETS)

static:
	$(MAKE) -C core static
	$(MAKE) -C widgets static
	$(MAKE) -C xutf static
	$(MAKE) $(LIBRARY)$(LIBEXT)
	$(MAKE) -C images static
	$(MAKE) -C opengl static

shared:
	$(MAKE) -C core shared
	$(MAKE) -C widgets shared
	$(MAKE) -C xutf shared
	$(MAKE) $(DSO)$(DSOEXT)
	$(MAKE) -C images shared
	$(MAKE) -C opengl shared

programs:

$(LIBRARY).a:
	@rm -f $@
	@echo $(LIBCOMMAND) $@ ...
	@$(LIBCOMMAND) $@ core/*.static.o widgets/*.static.o xutf/*.static.o
	@$(RANLIB) $@

$(DSO).so.2 $(DSO).sl.2: $(OBJECTS:.o=.shared.o)
	@rm -f $@
	@echo $(DSOCOMMAND) $(DSONAME) ...
	@$(DSOCOMMAND) $(DSONAME) core/*.shared.o widgets/*.shared.o xutf/*.shared.o $(DSOLIBS)
ifeq ($(HAVE_STRIP), 1) 
	@$(STRIP) $(DSONAME)
endif
	@mv $(DSONAME) $@

DLLIMPORTNAME = $(LIBNAME).2.dll$(LIBEXT)
$(DSO).2.dll: $(OBJECTS:.o=.shared.o)
	@-rm -f $@
	@echo $(DSOCOMMAND) $@ ...
	@$(DSOCOMMAND) $@ core/*.shared.o widgets/*.shared.o xutf/*.shared.o $(DSOLIBS)
	-mv $@.import ../lib/$(DLLIMPORTNAME)

clean:
	$(MAKE) -C core clean
	$(MAKE) -C widgets clean
	$(MAKE) -C xutf clean
	$(MAKE) -C images clean
	$(MAKE) -C opengl clean
	@rm -f *~ $(LIBRARY).*

depend:
	$(MAKE) -C core depend
	$(MAKE) -C widgets depend
	$(MAKE) -C xutf depend
	$(MAKE) -C images depend
	$(MAKE) -C opengl depend

################################################################

install: $(INSTALLTARGETS)

install_static: static
	@echo "Installing static libraries..."
	@mkdir -p $(libdir)
	@rm -f $(libdir)/$(LIBNAME)$(LIBEXT)
	@cp -f $(LIBRARY)$(LIBEXT) $(libdir)
	@-chmod 644 $(libdir)/$(LIBNAME)$(LIBEXT)

	$(MAKE) -C images install_static
	$(MAKE) -C opengl install_static

install_shared: shared
	@echo "Installing shared libraries..."
	@rm -f $(libdir)/$(DLLIMPORTNAME)
	@rm -f $(libdir)/$(DSOLIBNAME)$(DSOEXT)
	@if [ "$(DSOSHORTEXT)" ]; then rm -f $(libdir)/$(DSOLIBNAME)$(DSOSHORTEXT); fi
	@cp -f $(DSO)$(DSOEXT) $(libdir)
	@-chmod 755 $(libdir)/$(DSOLIBNAME)$(DSOEXT)
	@if [ "$(DSOSHORTEXT)" ]; then \
		ln -s $(DSOLIBNAME)$(DSOEXT) $(libdir)/$(DSOLIBNAME)$(DSOSHORTEXT); fi
	@if [ -f "../lib/$(DLLIMPORTNAME)" ]; then cp ../lib/$(DLLIMPORTNAME) $(libdir); fi

	$(MAKE) -C images install_shared
	$(MAKE) -C opengl install_shared

install_programs:

#
# End of "$Id$".
#
