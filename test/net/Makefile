#
# "$Id$"
#

include ../../makeinclude

CPPFILES = ftp_connect.cpp imap_connect.cpp
ALL = ftp_connect imap_connect

all: demos

static:

shared:

demos: $(ALL)

programs: demos

# NET programs needing special "help"...
ftp_connect: ftp_connect.cpp $(FLNETLIB) $(FLLIB)
	$(CXX) -I../.. $(CXXFLAGS) $<  $(FLNETLIB) $(LDLIBS) -o $@

imap_connect: imap_connect.cpp  $(FLNETLIB) $(FLLIB)
	$(CXX) -I../.. $(CXXFLAGS) $<  $(FLNETLIB) $(LDLIBS) -o $@

depend:
	$(MAKEDEPEND) -I.. $(CXXFLAGS) $(CPPFILES) > makedepend

clean:
	@ rm -f $(ALL) *.exe *.o core *~ makedepend
	@touch makedepend

install:

install_static:

install_shared:

install_programs:

# include dependency files if it exist
ifeq (makedepend, $(wildcard makedepend))
include makedepend
endif
