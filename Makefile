# variables
CXX = g++
MOC = /usr/lib/qt/bin/moc
PROGNAME = epong
BINDIR = bin
SRCDIR = src

# architecture variables
ARCH=`uname -m`

# compiler options
BASE_CFLAGS = -Wall -Wstrict-prototypes -Woverloaded-virtual -pipe -march=$(ARCH)
#CFLAGS = $(BASE_CFLAGS) -DDEBUG -g -gstabs+ -fno-default-inline
CFLAGS = $(BASE_CFLAGS) -DNDEBUG -O3 -finline-functions -fomit-frame-pointer -ffast-math -fno-common -funroll-loops -static
LD_FLAGS = -lqt-mt


# targets
all: nobin mainsrc
	mkdir $(BINDIR)
	mv $(SRCDIR)/$(PROGNAME) $(BINDIR)

nobin:
	rm -rf $(BINDIR)

mainsrc:
	$(MAKE) -C $(SRCDIR) CXX="$(CXX)" MOC="$(MOC)" PROGNAME="$(PROGNAME)" CFLAGS="$(CFLAGS)" LD_FLAGS="$(LD_FLAGS)"

fromdos:
	perl -pi -e 's/\r\n/\n/' AUTHORS COPYING ChangeLog
	$(MAKE) -C $(SRCDIR) $@

todos:
	perl -pi -e 's/\n/\r\n/' AUTHORS COPYING ChangeLog
	$(MAKE) -C $(SRCDIR) $@

strip: all
	strip -sv $(BINDIR)/$(PROGNAME)

clean: nobin
	$(MAKE) -C $(SRCDIR) PROGNAME="$(PROGNAME)" $@

install: strip
	@echo "not done"
