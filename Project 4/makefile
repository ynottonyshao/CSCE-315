# makefile

PROG = gui1
CC = g++-8.2.0
CPPFLAGS = -std=c++2a
LIBS = -lfltk -lfltk_images -lX11 -ljpeg
OBJS = main.o Graph.o GUI.o Simple_window.o Window.o

$(PROG) : $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) -o $(PROG) $(OBJS)

Graph.o: Graph.h
	$(CC) $(CFLAGS) $(LIBS) -c Graph.cpp

GUI.o: GUI.h
	$(CC) $(CFLAGS) $(LIBS) -c GUI.cpp

Simple_window.o: Simple_window.h
	$(CC) $(CFLAGS) $(LIBS) -c Simple_window.cpp

Window.o: Window.cpp Window.h
	$(CC) $(CFLAGS) $(LIBS) -c Window.cpp

main.o: std_lib_facilities_5.h global.h splashscreen.h Difficulty_Count_Demo.h pancakeOrder.h initscore.h pancakerenderdemo.h GameOver_Screen.h
	$(CC) $(CFLAGS) $(LIBS) -c main.cpp

clean:
	rm -rf $(OBJS)