#
# "$Id$"
#
# FLTK-plugin makefile for the Fast Light Tool Kit (FLTK).
#
# Copyright 1998-1999 by Bill Spitzak and others.
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
 include $(EFLTK_TOPDIR)/MinGW/makeinclude
else
 include $(EFLTK_TOPDIR)/makeinclude
endif

THEMES = \
	essai.theme \
	motif.theme \
        eblue.theme

################################################################

all : $(BUILDTARGETS)

static: $(LIBRARY)$(LIBEXT)

shared: $(THEMES)

programs:

$(LIBRARY).a: $(OBJECTS)
	@rm -f $@
	$(LIBCOMMAND) $@ $(OBJECTS)
	$(RANLIB) $@

ESSAI_OBJ = essai.shared.o
essai.theme : $(ESSAI_OBJ)
	$(THEMECOMMAND) $@ $(ESSAI_OBJ) $(DSOLIBS)

EBLUE_OBJ = eblue.shared.o
eblue.theme : $(EBLUE_OBJ)
	$(THEMECOMMAND) $@ $(EBLUE_OBJ) $(DSOLIBS)

MOTIF_OBJ = motif.shared.o
motif.theme : $(MOTIF_OBJ)
	$(THEMECOMMAND) $@ $(MOTIF_OBJ) $(DSOLIBS)

clean :
	-@ rm -f *.o $(LIBRARY)$(LIBEXT) $(THEMES) core *~ makedepend
	@touch makedepend

install : $(INSTALLTARGETS)

install_static:
# it would be nice if this built .o versions of the themes

install_shared:
	@echo "Installing themes..."
	@-mkdir -p $(libdir)/fltk
	@cp -f $(THEMES) $(libdir)/fltk

install_programs:

depend:

# include dependency files if it exist
ifeq (makedepend, $(wildcard makedepend))
include makedepend
endif

#
# End of "$Id$".
#
