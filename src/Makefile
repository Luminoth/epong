# variables
OBJDIR = obj
MOCDIR = moc

OBJECTS = $(OBJDIR)/main.o \
          $(OBJDIR)/Game.o \
          $(OBJDIR)/GLWidget.o \
          $(OBJDIR)/MainWindow.o \
          $(OBJDIR)/Paddle.o \
          $(OBJDIR)/Ball.o
OBJMOC = $(OBJDIR)/Moc_MainWindow.o \
         $(OBJDIR)/Moc_GLWidget.o \
         $(OBJDIR)/Moc_Game.o

INCLUDE = -I/usr/lib/qt/include
LIB = -L/usr/lib/qt/lib


# targets
all: $(PROGNAME)

$(PROGNAME): $(OBJDIR) $(MOCDIR) $(OBJECTS) $(OBJMOC)
	$(CXX) -o $@ $(OBJECTS) $(OBJMOC) $(LIB) $(LD_FLAGS)

$(OBJDIR):
	mkdir $(OBJDIR)

$(MOCDIR):
	mkdir $(MOCDIR)

fromdos:
	perl -pi -e 's/\r\n/\n/' *.cpp *.h

todos:
	perl -pi -e 's/\n/\r\n/' *.cpp *.h

ctags:
	ctags *.h *.cpp

strip: all
	strip -sv $(PROGNAME)

clean:
	-rm -rf $(OBJDIR) $(MOCDIR) *.o $(PROGNAME) core a.out *.log tags


# dependancies
$(OBJDIR)/main.o: main.cpp main.h Game.h MainWindow.h Shared.h
	$(CXX) -o $@ $(INCLUDE) $(CFLAGS) -c $<

$(OBJDIR)/Game.o: Game.cpp Game.h GLWidget.h Paddle.h Ball.h Shared.h main.h
	$(CXX) -o $@ $(INCLUDE) $(CFLAGS) -c $<

$(OBJDIR)/GLWidget.o: GLWidget.cpp GLWidget.h Game.h Paddle.h Ball.h Shared.h
	$(CXX) -o $@ $(INCLUDE) $(CFLAGS) -c $<

$(OBJDIR)/MainWindow.o: MainWindow.cpp MainWindow.h Game.h Shared.h
	$(CXX) -o $@ $(INCLUDE) $(CFLAGS) -c $<

$(OBJDIR)/Paddle.o: Paddle.cpp Paddle.h
	$(CXX) -o $@ $(INCLUDE) $(CFLAGS) -c $<

$(OBJDIR)/Ball.o: Ball.cpp Ball.h Shared.h
	$(CXX) -o $@ $(INCLUDE) $(CFLAGS) -c $<


# moc dependancies
$(OBJDIR)/Moc_MainWindow.o: $(MOCDIR)/Moc_MainWindow.cpp MainWindow.h
	$(CXX) -o $@ $(INCLUDE) $(CFLAGS) -c $<

$(MOCDIR)/Moc_MainWindow.cpp: MainWindow.h
	$(MOC) -o $@ $<

$(OBJDIR)/Moc_GLWidget.o: $(MOCDIR)/Moc_GLWidget.cpp GLWidget.h
	$(CXX) -o $@ $(INCLUDE) $(CFLAGS) -c $<

$(MOCDIR)/Moc_GLWidget.cpp: GLWidget.h
	$(MOC) -o $@ $<

$(OBJDIR)/Moc_Game.o: $(MOCDIR)/Moc_Game.cpp Game.h
	$(CXX) -o $@ $(INCLUDE) $(CFLAGS) -c $<

$(MOCDIR)/Moc_Game.cpp: Game.h
	$(MOC) -o $@ $<
