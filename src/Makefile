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

EFLTK_TOPDIR=..
OS_NAME := $(shell uname -s | sed "s/\//-/" | sed "s/_/-/" | sed "s/-.*//g")
ifeq ($(OS_NAME), MINGW32)
  OS_NAME = WIN32
endif

ifneq ($(MAKEINCLUDE_INCLUDED), 1)
 ifeq ($(OS_NAME), WIN32)
  include $(EFLTK_TOPDIR)/MinGW/makeinclude
 else
  include $(EFLTK_TOPDIR)/makeinclude
 endif
endif

OUT_MAGIC := $(shell mkdir $(EFLTK_TOPDIR)/lib > /dev/null 2>&1 || :)

################################################################

FLDIRS = core widgets db 
DIRS = xml images opengl net

LIBNAME = libefltk
DSOLIBNAME = $(LIBNAME)
LIBRARY = $(EFLTK_TOPDIR)/lib/$(LIBNAME)
DSO = $(EFLTK_TOPDIR)/lib/$(LIBNAME)
DSONAME = $(LIBNAME)$(DSOEXT)

all: $(BUILDTARGETS)

static:
	@rm -f $(LIBRARY)$(LIBEXT)
	@for dir in $(FLDIRS); do\
        	if test ! -f $$dir/makedepend; then touch $$dir/makedepend; fi;\
        	(cd $$dir;$(MAKE) $(MFLAGS) static) || exit;\
	done	
	$(MAKE) $(LIBRARY)$(LIBEXT)
	@for dir in $(DIRS); do\
        	if test ! -f $$dir/makedepend; then touch $$dir/makedepend; fi;\
        	(cd $$dir;$(MAKE) $(MFLAGS) static) || exit;\
	done	

shared:
	@rm -f $(LIBRARY)$(DSOEXT)
	@for dir in $(FLDIRS); do\
        	if test ! -f $$dir/makedepend; then touch $$dir/makedepend; fi;\
        	(cd $$dir;$(MAKE) $(MFLAGS) shared) || exit;\
	done	
	$(MAKE) $(DSO)$(DSOEXT)
	@for dir in $(DIRS); do\
        	if test ! -f $$dir/makedepend; then touch $$dir/makedepend; fi;\
        	(cd $$dir;$(MAKE) $(MFLAGS) shared) || exit;\
	done

programs:

STATIC_OBJECTS = core/*.static.o widgets/*.static.o db/*.static.o
SHARED_OBJECTS = core/*.shared.o widgets/*.shared.o db/*.shared.o

$(LIBRARY).a:
	@echo $(LIBCOMMAND) $@ ...
	@$(LIBCOMMAND) $@ $(STATIC_OBJECTS)
	@$(RANLIB) $@

$(DSO).so.$(FL_API_VERSION) $(DSO).sl.2:
	@rm -f $@
	@echo $(DSOCOMMAND) $(DSONAME) ...
	@$(DSOCOMMAND) $(DSONAME) $(SHARED_OBJECTS) $(DSOLIBS)
ifneq ($(STRIP), ) 
	@$(STRIP) $(DSONAME)
endif
	@mv $(DSONAME) $@

DLLIMPORTNAME = $(LIBNAME).2.0.dll$(LIBEXT)
$(DSO).$(FL_API_VERSION).dll:
	@-rm -f $@
	@echo $(DSOCOMMAND) $@ ...
	@$(DSOCOMMAND) $@ $(SHARED_OBJECTS) $(DSOLIBS)
	@mv $@.import $(EFLTK_TOPDIR)/lib/$(DLLIMPORTNAME)

clean:
	@for dir in $(DIRS) $(FLDIRS); do\
        	if test ! -f $$dir/makedepend; then touch $$dir/makedepend; fi;\
        	(cd $$dir;$(MAKE) $(MFLAGS) clean) || exit;\
	done
	@rm -f *~ $(LIBRARY).*

depend:
	@for dir in $(DIRS) $(FLDIRS); do\
        	if test ! -f $$dir/makedepend; then touch $$dir/makedepend; fi;\
        	(cd $$dir;$(MAKE) $(MFLAGS) depend) || exit;\
	done

################################################################

install: $(INSTALLTARGETS)

install_static: static
	@echo "Installing static libraries..."
	@mkdir -p $(libdir)
	@rm -f $(libdir)/$(LIBNAME)$(LIBEXT)
	@cp -f $(LIBRARY)$(LIBEXT) $(libdir)
	@chmod 644 $(libdir)/$(LIBNAME)$(LIBEXT)
	@for dir in $(DIRS) $(FLDIRS); do\
        	if test ! -f $$dir/makedepend; then touch $$dir/makedepend; fi;\
        	(cd $$dir;$(MAKE) $(MFLAGS) install_static) || exit;\
	done

install_shared: shared
	@echo "Installing shared libraries..."
	@rm -f $(libdir)/$(DLLIMPORTNAME)
	@rm -f $(libdir)/$(DSOLIBNAME)$(DSOEXT)
	@rm -f $(libdir)/$(DSOLIBNAME)$(DSOSHORTEXT)

	@cp -f $(DSO)$(DSOEXT) $(libdir)
	@chmod 755 $(libdir)/$(DSOLIBNAME)$(DSOEXT)

	@if [ "$(DSOSHORTEXT)" ]; then ln -s $(DSOLIBNAME)$(DSOEXT) $(libdir)/$(DSOLIBNAME)$(DSOSHORTEXT); fi
	@if [ -f "$(EFLTK_TOPDIR)/lib/$(DLLIMPORTNAME)" ]; then cp -f $(EFLTK_TOPDIR)/lib/$(DLLIMPORTNAME) $(libdir); fi
	@for dir in $(DIRS) $(FLDIRS); do\
        	if test ! -f $$dir/makedepend; then touch $$dir/makedepend; fi;\
        	(cd $$dir;$(MAKE) $(MFLAGS) install_shared) || exit;\
	done
 
install_programs:

#
# End of "$Id$".
#
