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

EFLTK_TOPDIR=../
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

CPPFILES = demo.cpp sizes.cpp hello.cpp resizable.cpp scroll.cpp image.cpp file_chooser.cpp menubar.cpp \
	browser.cpp threads.cpp progress.cpp editor.cpp inactive.cpp checkers.cpp \
	valuators.cpp glpuzzle.cpp boxtype.cpp multi_image.cpp help.cpp mdi_test.cpp \
	resize.cpp tabs.cpp line_style.cpp doublebuffer.cpp subwindow.cpp \
	keyboard.cpp label.cpp layout.cpp arc.cpp ask.cpp button.cpp buttons.cpp \
	clock.cpp color_chooser.cpp cube.cpp cursor.cpp curve.cpp fast_slow.cpp \
	fonts.cpp fullscreen.cpp gl_overlay.cpp iconize.cpp input.cpp navigation.cpp \
	output.cpp overlay.cpp pack.cpp radio.cpp shape.cpp tile.cpp CubeMain.cpp CubeView.cpp \
	preferences.cpp image_manip.cpp listview.cpp listview_sort.cpp alphablend.cpp \
	thread_ball.cpp images.cpp image_loader.cpp tabs1.cpp tabs2.cpp \
	popup_window.cpp symbols.cpp calendar.cpp maskedinput.cpp bitmap.cpp utf8.cpp \
	dialog.cpp directory.cpp listview_ds.cpp xml_test.cpp xml_test2.cpp \
	exceptions.cpp layout2.cpp socket.cpp combobox.cpp labelwidth.cpp \
	labelwidth2.cpp button_groups.cpp date_time_widgets.cpp input_browser.cpp \
	split.cpp

ALL =   demo sizes hello resizable scroll image file_chooser menubar browser \
	threads progress editor inactive checkers valuators boxtype \
	multi_image help mdi_test resize tabs line_style doublebuffer subwindow \
	keyboard label layout arc ask button buttons clock color_chooser \
	cursor curve fast_slow fonts iconize input navigation input_browser \
	output overlay pack radio tile preferences image_manip labelwidth \
	labelwidth2 button_groups listview_sort date_time_widgets \
	listview alphablend thread_ball images image_loader layout2 split \
	tabs1 tabs2 popup_window symbols calendar maskedinput bitmap utf8 \
	dialog directory listview_ds xml_test xml_test2 exceptions socket combobox \
	glpuzzle cube fullscreen gl_overlay shape CubeView

all: demos

static:

shared:

demos: $(ALL)

programs: demos

# $(ALL): $(FLLIB) # only true for static library

# FLUID file rules
.fl.cpp .fl.h:
	$(EFLTK_BINDIR)/efluid -c $<

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

xml_test: xml_test.cpp $(FLXMLLIB) $(FLLIB)
	$(CXX) -I.. $(CXXFLAGS) $< $(FLXMLLIB) $(LDLIBS) -o $@

xml_test2: xml_test2.cpp $(FLXMLLIB) $(FLLIB)
	$(CXX) -I.. $(CXXFLAGS) $< $(FLXMLLIB) $(LDLIBS) -o $@
        
thread_ball: thread_ball.cpp $(FLIMAGESLIB) $(FLLIB)
	$(CXX) -I.. $(CXXFLAGS) $< $(IMAGELIBS) $(PNGLIBS) $(JPEGLIBS) $(THREADSLIBS) $(LDLIBS) -o $@

image_loader: image_loader.cpp $(FLIMAGESLIB) $(FLLIB)
	$(CXX) -I.. $(CXXFLAGS) $< $(IMAGELIBS) $(PNGLIBS) $(JPEGLIBS) $(LDLIBS) -o $@
        
images: images.cpp $(FLIMAGESLIB) $(FLLIB)
	$(CXX) -I.. $(CXXFLAGS) $< $(IMAGELIBS) $(PNGLIBS) $(JPEGLIBS) $(LDLIBS) -o $@

file_chooser: file_chooser.cpp $(FLCORELIB) $(FLUILIB)
	$(CXX) -I.. $(CXXFLAGS) $< $(LDLIBS) $(FLIMAGESLIB) $(PNGLIBS) $(JPEGLIBS) -o $@

help: help.cpp $(FLCORELIB) $(FLUILIB)
	$(CXX) -I.. $(CXXFLAGS) $< $(LDLIBS) $(FLIMAGESLIB) $(PNGLIBS) $(JPEGLIBS) -o $@

threads: threads.cpp $(FLCORELIB) $(FLUILIB)
	$(CXX) -I.. $(CXXFLAGS) $< $(LDLIBS) $(THREADSLIBS) -o $@

depend:
	$(MAKEDEPEND) -I.. $(CXXFLAGS) $(CPPFILES) > makedepend

clean:
	-@ rm -f $(ALL) *.exe jpeg_image *.o core *~ makedepend
	@touch makedepend

install:

install_static:

install_shared:

install_programs:

# include dependency files if it exist
ifeq (makedepend, $(wildcard makedepend))
include makedepend
endif

#
# End of "$Id$".
#
