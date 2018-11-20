# makefile

CC = g++-8.2.0
CFLAGS = -std=c++2a -Wall -Wextra -pedantic -fsanitize=address,undefined,pointer-compare,pointer-subtract -fstack-clash-protection -g -fno-omit-frame-pointer
LIBS = -lncurses++ -lmenu -lpanel -lform -lutil -lncurses

main: main.cpp
	$(CC) $(CFLAGS) main.cpp find_solution.o $(LIBS)
