include ../makeinclude

DIRS = xml db

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
	@rm -rf $(includedir)/efltk
	@mkdir -p $(includedir)
	@mkdir -p $(includedir)/efltk

	@cp *.h  $(includedir)/efltk
	@chmod 644 $(includedir)/efltk/*
	@chmod 755 $(includedir)/efltk

	@for dir in $(DIRS); do\
        	(cd $$dir;$(MAKE) $(MFLAGS) install_headers) || break;\
	done

install_fltk_config:
	@echo "Installing efltk-config..."
	@mkdir -p $(bindir)
	@cp ../efltk-config $(bindir)

