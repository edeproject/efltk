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

# * essai.theme removed from default list because it requires -ljpeg
#   and breaks the build on some platforms
THEMES = \
	essai.theme \

################################################################

include ../makeinclude

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

clean :
	-@ rm -f *.shared.o $(LIBRARY)$(LIBEXT) $(THEMES) core *~ makedepend
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

include makedepend

#
# End of "$Id$".
#
