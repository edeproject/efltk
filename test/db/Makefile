#
# "$Id$"
#

include ../../makeinclude

ifneq ($(UNIXODBCLIB), )
# Add ODBC, if not disabled..
ODBCCPP = db_odbc.cpp
ODBC = db_odbc
endif

CPPFILES = $(ODBCCPP)
ALL = $(ODBC)

all: demos

static:

shared:

demos: $(ALL)

programs: demos

# DB programs needing special "help"...
db_odbc: db_odbc.cpp $(FLODBCLIB) $(FLLIB)
	$(CXX) -I../.. $(CXXFLAGS) $< $(ODBCLIBS) $(LDLIBS) -o $@

depend:
	$(MAKEDEPEND) -I.. $(CXXFLAGS) $(CPPFILES) > makedepend

clean:
	@ rm -f $(ALL) *.exe *.o core *~ makedepend
	@touch makedepend

regenerate:
	@echo "Generating tests.."
	@sed -e "s'__DRIVER__'Fl_ODBC_Database'g" db_test_template.cpp > db_odbc.cpp;

install:

install_static:

install_shared:

install_programs:

# include dependency files if it exist
ifeq (makedepend, $(wildcard makedepend))
include makedepend
endif
