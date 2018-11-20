#include "std_lib_facilities_5.h"
#include "Simple_window.h"
#include "Graph.h"
#include "FL/Fl_JPEG_Image.H"
#include <vector>
#include <string>
#include <cmath>
#include "unistd.h"

using namespace Graph_lib;

Text game_title(Point((WINDOWWIDTH / 2)-165, 90), "Pancake Flipper");
Text team_name(Point((WINDOWWIDTH / 2)-90, 155), "Aunt Jemima: Team 31");
bool start_pressed = false; 
bool play_pressed = false;
vector<string> names = {"Jalen Perkins", "Joseph Santana", "Sidney Shaw", "Marshall Pickett", "Connor Smith", "Tony Shao"};
vector<Text* > member_ptrs;

//Callback function
void start_callback(Address a, Address b);
void play_game(Address a, Address b);


void print_instructions() {
	win.detach(game_title);
	win.detach(team_name);

	Button play_button(Point((WINDOWWIDTH / 2)-85, 500), 155, 50, "PLAY", play_game);
	win.attach(play_button);
	Text line1(Point((WINDOWWIDTH / 2)-170, 155), "Welcome to Pancake Flipper, the pancake sorting game.");
	Text line2(Point((WINDOWWIDTH/2)-170, 180), "The rules are simple. Each player has a stack of pancakes.");
	Text line3(Point((WINDOWWIDTH/2)-170, 205), "The goal is get the stack into order");
	Text line4(Point((WINDOWWIDTH/2)-170, 230), "(from smallest on top to largest on bottom) by repeatedly");
	Text line5(Point((WINDOWWIDTH/2)-170, 255), "flipping over a top partial stack of some number of pancakes.");
	Text line6(Point((WINDOWWIDTH/2)-170, 280), "The winner is the player who gets the stack into order");
	Text line7(Point((WINDOWWIDTH/2)-170, 305), "in the smallest amount of moves possible.");
	Text line8(Point((WINDOWWIDTH/2)-80, 330), "Press PLAY to begin.");

	win.attach(line1);
	win.attach(line2);
	win.attach(line3);
	win.attach(line4);
	win.attach(line5);
	win.attach(line6);
	win.attach(line7);
	win.attach(line8);

	while(!play_pressed) {
		Fl::wait();
		Fl::redraw();
	}

	win.detach(line1);
	win.detach(line2);
	win.detach(line3);
	win.detach(line4);
	win.detach(line5);
	win.detach(line6);
	win.detach(line7);
	win.detach(line8);

	if(play_pressed) {
		win.detach(play_button);
	}
}

void start_callback(Address a, Address pw) {
	start_pressed = true;
	for(int i = 0; i < member_ptrs.size(); i++) {
		win.detach(*member_ptrs[i]);
	}
	print_instructions();
}

void play_game(Address a, Address pw) {
	play_pressed = true;
	win.hide();
}

void start_fn() {
	Button start_button(Point((WINDOWWIDTH / 2)-85, 500), 155, 50, "START", start_callback);
	win.attach(start_button);

	while (!start_pressed) {
		Fl::wait();
		Fl::redraw();
	}

	win.detach(start_button);
}

void draw_splash() {
	int xMid = WINDOWWIDTH / 2;
	game_title.set_font(FL_COURIER);
	game_title.set_font_size(40);

	team_name.set_font(FL_COURIER);
	team_name.set_font_size(15);

	int label_x = xMid-55;
	int label_y = 175;
	for (int i = 0; i < names.size(); i++) {
		Text* member = new Text(Point(label_x, label_y), names[i]);
		member->set_font(FL_COURIER);
		member->set_font_size(10);
		label_y += 20;
		win.attach(*member);
		member_ptrs.push_back(member);
	}
	win.attach(game_title);
	win.attach(team_name);

	start_fn();
}