#
# "$Id$"
#

include ../../makeinclude

ifneq ($(UNIXODBCLIB), )
# Add ODBC, if not disabled..
ODBCCPP = database.cpp
ODBC = db_odbc
endif

ifneq ($(MYSQLCONFIG), )
# Add MySQL, if not disabled..
MYSQLCPP = database.cpp
MYSQL = db_mysql
endif

CPPFILES = $(ODBCCPP)
ALL = $(ODBC) $(MYSQL)

all: demos

static:

shared:

demos: $(ALL)

programs: demos

$(ODBC): $(ODBCCPP)
	$(CXX) -DODBC_DRIVER -I../.. $(CXXFLAGS) $< $(FLLIB) $(ODBCLIBS) $(LDLIBS) -o $@

$(MYSQL): $(MYSQLCPP)
	$(CXX) -DMYSQL_DRIVER $(MYSQLFLAGS) -I../.. $(CXXFLAGS) $< $(FLLIB) $(MYSQLLIBS_) $(LDLIBS) -o $@
 
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
