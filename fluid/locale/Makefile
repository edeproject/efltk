include ../../makeinclude

PROG = fluid
CWD = locale
MSGFMT = msgfmt
SUB_DIRS = 
FILES_PO:=fi.po
FILES_MO:=$(FILES_PO:.po=.mo)

LOCALEDIR = $(prefix)/share/locale

all: mo-files

mo-files: $(FILES_MO)

install_static: install

install_shared: install

install: 
	$(MAKE) all
	for f in *.mo ; do \
		mkdir -p $(INSTALL_PREFIX)$(LOCALEDIR)/`basename $$f .mo`/LC_MESSAGES ; \
		cp -f $$f $(INSTALL_PREFIX)$(LOCALEDIR)/`basename $$f .mo`/LC_MESSAGES/$(PROG).mo ; done

%.mo: %.po
	$(MSGFMT) -f -o $@ $<

clean:
	@$(RM) $(FILES_MO)
	@$(RM) *~

depend:

