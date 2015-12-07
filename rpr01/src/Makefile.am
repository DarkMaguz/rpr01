bin_PROGRAMS = rpr01 direct test01

rpr01_SOURCES = rpr01.cpp RaspPiGPIO.cpp
rpr01_CPPFLAGS = -D_GNU_SOURCE
# -D_GNU_SOURCE
rpr01_LDADD = -lncurses -ltinfo
# -lSDL2
# -lncurses -ltinfo

direct_SOURCES = direct_io_test.cpp
direct_CPPFLAGS = -fpermissive

test01_SOURCES = test01.cpp
test01_CPPFLAGS =