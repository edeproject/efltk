include ../makeinclude

all:

static:

shared:

install_static: install

install_shared: install

install_programs: install

depend:

clean:
	@rm -rf *~

install: install_headers install_fltk_config

install_headers:
	@echo "Installing include files..."
	@mkdir -p $(includedir)
	@rm -rf $(includedir)/efltk
	@mkdir -p $(includedir)/efltk
	@mkdir -p $(includedir)/efltk/xml
	@cp *.h  $(includedir)/efltk
	@cp xml/*.h  $(includedir)/efltk/xml
        @chmod 755 $(includedir)/efltk
        @chmod 755 $(includedir)/efltk/xml
	@chmod 644 $(includedir)/efltk/*
	@chmod 644 $(includedir)/efltk/xml/*

install_fltk_config:
	@echo "Installing efltk-config..."
	@mkdir -p $(bindir)
	@cp ../efltk-config $(bindir)

