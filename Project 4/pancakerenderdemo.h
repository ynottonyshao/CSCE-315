#include "AI.h"
#include "FL/Fl_JPEG_Image.H"
#include "GUI.h"
#include "Graph.h"
#include "Point.h"
#include "Window.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

// #undef string
// #undef vector

// Print vector
void printv(vector<int> pancake) {
	for(auto i = pancake.begin(); i != pancake.end(); ++i) {
		cout << *i << " ";
	}
	cout << endl;
}

using namespace Graph_lib;

// const int WINDOWX			= 100;
// const int WINDOWY			= 100;
// const int WINDOWWIDTH		= 600;
// const int WINDOWHEIGHT		= 600;
// const int LABELY				= 50;
// const int LEFTLABELWIDTH		= 38;
// const int RIGHTLABELWIDTH	= 12;
// const int PANCAKEHEIGHT		= 30;
// const int PANCAKESTARTY		= 100;
// const int PANCAKEVERTICALGAP	= 10;
// const int PANCAKELEFTX		= WINDOWWIDTH / 3;
// const int PANCAKERIGHTX		= WINDOWWIDTH * 2 / 3;
// const int PANCAKEUNITWIDTH	= 10;
// const int PANCAKEBASEWIDTH	= 30;

// Graph_lib::Window win(Point(WINDOWX, WINDOWY), WINDOWWIDTH, WINDOWHEIGHT, "Pancake Render Demo");
vector<int> leftStack;
vector<int> rightStack;
vector<Button*> leftPancakeButtons;
vector<Button*> rightPancakeButtons;
int gameOverTextInt = -1; // Number to determine tie, win, or lose
bool game_done = false;
bool players_turn = true;
AI* alexa;
int num_moves;

bool checkWinner() {
	if(isSorted(leftStack) && isSorted(rightStack)) {
		gameOverTextInt = 0;
	}
	else if(isSorted(leftStack)) {
		gameOverTextInt = 1;
	}
	else if(isSorted(rightStack)) {
		gameOverTextInt = 2;
	}

	if (gameOverTextInt != -1) {
		for(auto i : leftPancakeButtons) {
			win.detach(*i);
			delete i;
		}
		for(auto i : rightPancakeButtons) {
			win.detach(*i);
			delete i;
		}
		Fl::redraw();
		game_done = true;
		return true;
	}
	return false;
}

void flip(vector<int>& stack, int position) {
	vector<int> top;
	for(long unsigned int i = 0; i < position; i++) {
		top.push_back(stack[i]);
	}
	vector<int> bottom;
	for(long unsigned int i = position; i < stack.size(); i++) {
		bottom.push_back(stack[i]);
	}
	reverse(top.begin(), top.end());
	top.insert(top.end(), bottom.begin(), bottom.end());
	stack = top;
}

void blink(int position, bool human) {
	if(human) {
		for(int j = 0; j < position; j++) {
			win.detach(*leftPancakeButtons[j]);
		}
		Fl::redraw();
		Fl::wait(0);
		usleep(500 * 1000);
		for(int j = 0; j < position; j++) {
			win.attach(*leftPancakeButtons[j]);
		}
		Fl::redraw();
		Fl::wait(0);
		usleep(500 * 1000);
	}
	else {
		for (int j = 0; j < position; j++) {
			win.detach(*rightPancakeButtons[j]);
		}
		Fl::redraw();
		Fl::wait(0);
		usleep(500 * 1000);
		for(int j = 0; j < position; j++) {
			win.attach(*rightPancakeButtons[j]);
		}
		Fl::redraw();
		Fl::wait(0);
		usleep(500 * 1000);
	}
}

void drawPancakeStacks();

void flipStackAI(int position) {
	for(int i = 0; i < 3; i++) {
		blink(position, false);
	}
	flip(rightStack, position);
	drawPancakeStacks();

	// Call back would give control back to user
	checkWinner();
}

void flipStackPlayer(int position) {
	if (!players_turn) {
		return;
	}
	players_turn = false;

	for (int i = 0; i < 3; i++) {
		blink(position, true);
	}
	flip(leftStack, position);
	drawPancakeStacks();
	num_moves++;

	// Get AI move and make move
	alexa->playTurn();
	flipStackAI(alexa->move_flipped + 1);
	rightStack = alexa->pancakes;

	players_turn = true;
}

void cb1(Address, Address) { flipStackPlayer(2); }
void cb2(Address, Address) { flipStackPlayer(3); }
void cb3(Address, Address) { flipStackPlayer(4); }
void cb4(Address, Address) { flipStackPlayer(5); }
void cb5(Address, Address) { flipStackPlayer(6); }
void cb6(Address, Address) { flipStackPlayer(7); }
void cb7(Address, Address) { flipStackPlayer(8); }
void cb8(Address, Address) { flipStackPlayer(9); }
void cb9(Address, Address) { flipStackPlayer(10); }

void drawPancakeStacks() {
	for (auto i : leftPancakeButtons) {
		win.detach(*i);
		delete i;
	}
	leftPancakeButtons.clear();
	for (int i = 0; i < leftStack.size(); i++) {
		vector<Callback> cb{NULL, cb1, cb2, cb3, cb4, cb5, cb6, cb7, cb8, cb9};
		int width = PANCAKEBASEWIDTH + leftStack[i] * PANCAKEUNITWIDTH;
		Button* pancake = new Button(Point(PANCAKELEFTX - width / 2, PANCAKESTARTY + (PANCAKEHEIGHT + PANCAKEVERTICALGAP) * i), width, PANCAKEHEIGHT, to_string(leftStack[i]), cb[i]);
		leftPancakeButtons.push_back(pancake);
		win.attach(*pancake);
	}
	for (auto i : rightPancakeButtons) {
		win.detach(*i);
		delete i;
	}
	rightPancakeButtons.clear();
	for (int i = 0; i < rightStack.size(); i++) {
		int width = PANCAKEBASEWIDTH + rightStack[i] * PANCAKEUNITWIDTH;
		Button* pancake = new Button(Point(PANCAKERIGHTX - width / 2, PANCAKESTARTY + (PANCAKEHEIGHT + PANCAKEVERTICALGAP) * i), width, PANCAKEHEIGHT, to_string(rightStack[i]), NULL);
		rightPancakeButtons.push_back(pancake);
		win.attach(*pancake);
	}
}

void playGame() {
	printv(initialPancakeOrder);
	leftStack = initialPancakeOrder;
	rightStack = initialPancakeOrder;
	alexa = new AI(rightStack, difficulty);
	Text humanLabel(Point(PANCAKELEFTX - LEFTLABELWIDTH / 2, LABELY), "Human");
	Text aiLabel(Point(PANCAKERIGHTX - RIGHTLABELWIDTH / 2, LABELY), "AI");
	win.attach(humanLabel);
	win.attach(aiLabel);
	drawPancakeStacks();

	while (!game_done) {
		Fl::wait();
		Fl::redraw();
	}

	win.detach(humanLabel);
	win.detach(aiLabel);
}
