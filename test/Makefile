#
# "$Id$"
#
# Test/example program makefile for the Fast Light Tool Kit (FLTK).
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

CPPFILES = demo.cpp hello.cpp resizable.cpp scroll.cpp image.cpp file_chooser.cpp menubar.cpp \
	   browser.cpp threads.cpp progress.cpp editor.cpp inactive.cpp checkers.cpp \
           valuators.cpp glpuzzle.cpp boxtype.cpp multi_image.cpp help.cpp mdi_test.cpp \
           resize.cpp tabs.cpp line_style.cpp doublebuffer.cpp subwindow.cpp \
           keyboard.cpp label.cpp layout.cpp arc.cpp ask.cpp button.cpp buttons.cpp \
           clock.cpp color_chooser.cpp cube.cpp cursor.cpp curve.cpp fast_slow.cpp \
           fonts.cpp fullscreen.cpp gl_overlay.cpp iconize.cpp input.cpp navigation.cpp \
           output.cpp overlay.cpp pack.cpp radio.cpp shape.cpp tile.cpp CubeMain.cpp CubeView.cpp

ALL =   demo hello resizable scroll image file_chooser menubar browser \
	threads progress editor inactive checkers valuators glpuzzle boxtype \
        multi_image help mdi_test resize tabs line_style doublebuffer subwindow \
        keyboard label layout arc ask button buttons clock color_chooser cube \
        cursor curve fast_slow fonts fullscreen gl_overlay iconize input navigation \
        output overlay pack radio shape tile CubeView

all: demos

static:

shared:

demos: $(ALL)

programs: demos

include ../makeinclude

# $(ALL): $(FLLIB) # only true for static library

# FLUID file rules
.fl.cpp .fl.h:
	../fluid/efluid -c $<

# Other programs needing special "help"...
CubeView: CubeMain.o CubeView.o CubeViewUI.o $(FLGLLIB) $(FLCORELIB) $(FLUILIB)
	$(CXX) -I.. $(CXXFLAGS) CubeMain.o CubeView.o CubeViewUI.o $(GLDLIBS) $(LDLIBS) -o $@
CubeMain.o: CubeViewUI.h CubeView.h
CubeView.o: CubeView.h

glpuzzle: glpuzzle.cpp $(FLUILIB) $(FLGLLIB) $(FLCORELIB)
	$(CXX) -I.. $(CXXFLAGS) $< $(GLDLIBS) $(LDLIBS) -o $@
cube: cube.cpp $(FLGLLIB) $(FLCORELIB) $(FLUILIB)
	$(CXX) -I.. $(CXXFLAGS) $< $(GLDLIBS) $(LDLIBS) -o $@
fullscreen: fullscreen.cpp $(FLGLLIB) $(FLCORELIB) $(FLUILIB)
	$(CXX) -I.. $(CXXFLAGS) $< $(GLDLIBS) $(LDLIBS) -o $@
gl_overlay: gl_overlay.cpp $(FLGLLIB) $(FLCORELIB) $(FLUILIB)
	$(CXX) -I.. $(CXXFLAGS) $< $(GLDLIBS) $(LDLIBS) -o $@
mandelbrot: mandelbrot.cpp mandelbrot_ui.cpp

shape: shape.cpp $(FLGLLIB) $(FLCORELIB) $(FLUILIB)
	$(CXX) -I.. $(CXXFLAGS) $< $(GLDLIBS) $(LDLIBS) -o $@

image_file: image_file.cpp $(FLIMAGESLIB) $(FLLIB)
	$(CXX) -I.. $(CXXFLAGS) $< $(IMAGELIBS) $(PNGLIBS) $(JPEGLIBS) $(LDLIBS) -o $@

file_chooser: file_chooser.cpp $(FLCORELIB) $(FLUILIB)
	$(CXX) -I.. $(CXXFLAGS) $< $(LDLIBS) $(FLIMAGESLIB) $(PNGLIBS) $(JPEGLIBS) -o $@

help: help.cpp $(FLCORELIB) $(FLUILIB)
	$(CXX) -I.. $(CXXFLAGS) $< $(LDLIBS) $(FLIMAGESLIB) $(PNGLIBS) $(JPEGLIBS) -o $@

threads: threads.cpp $(FLCORELIB) $(FLUILIB)
	$(CXX) -I.. $(CXXFLAGS) $< $(LDLIBS) $(THREADSLIBS) -o $@

# If you have libjpeg installed, you might want to try this test program:

jpeg_image: jpeg_image.cpp
	$(CXX) -I.. $(CXXFLAGS) -I../../../local/jpeg-6b -L../../../local/jpeg-6b jpeg_image.cpp -L../lib -lfltk $(LDLIBS) $(IMAGELIBS) -lXext -o $@

depend:
	$(MAKEDEPEND) -I.. $(CXXFLAGS) $(CPPFILES) > makedepend

include makedepend

clean:
	-@ rm -f $(ALL) *.exe jpeg_image *.o core *~ makedepend
	@touch makedepend

install:

install_static:

install_shared:

install_programs:

#
# End of "$Id$".
#
