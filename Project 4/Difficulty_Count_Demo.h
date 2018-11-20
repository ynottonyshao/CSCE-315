#include "FL/Fl_JPEG_Image.H"
#include "GUI.h"
#include "Graph.h"
#include "Point.h"
#include "Window.h"
#include <iostream>
#include <string>
#include <vector>

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

// Graph_lib::Window win(Point(WINDOWX, WINDOWY), WINDOWWIDTH, WINDOWHEIGHT, "Pancake Count & Difficulty Demo");

// Difficulty stuff
Text inputValidation(Point(PANCAKELEFTX - LEFTLABELWIDTH / 2, 65), "");
In_box difficultyInbox(Point(PANCAKELEFTX - LEFTLABELWIDTH / 2, 75), 50, 50, "Difficulty: ");
Out_box difficultyOutbox(Point(PANCAKELEFTX - LEFTLABELWIDTH / 2, 75), 50, 50, "Difficulty Chosen: ");
Text difficultyQuestionLabel(Point(PANCAKELEFTX - LEFTLABELWIDTH / 2, 50), "What difficulty would you like to play on?");
int difficulty = -1;
// Count stuff
In_box countInbox(Point(PANCAKELEFTX - LEFTLABELWIDTH / 2, 75), 50, 50, "Pancake Count");
Out_box countOutbox(Point(PANCAKELEFTX - LEFTLABELWIDTH / 2, 75), 50, 50, "Pancake Count Chosen: ");
Text pancakeQuestionLabel(Point(PANCAKELEFTX - LEFTLABELWIDTH / 2, 50), "How many pancakes would you like to play with?");
// Button showDifficultyPage();
// Button closeDifficultyPage();
void CleanScreen();

// Shared stuff

int upperLimit = 9;
int lowerLimit = 2;
int input = -1;
int pancakeCount = input;
bool isCount = true;
bool continueForward = false;

void checkInput(Address, Address pw);
void RemoveCountInbox();
void ShowDifficulty(Address, Address pw);
void DetachAll(Address, Address pw);
Button getCount(Point(PANCAKELEFTX - LEFTLABELWIDTH / 2, 250), 75, 50, "Confirm", checkInput);
Button getDifficulty(Point(PANCAKELEFTX - LEFTLABELWIDTH / 2, 250), 75, 50, "Confirm", checkInput);

void checkInput(Address, Address pw)
{
	string countString;
	if (isCount) {
		countString = countInbox.get_string();
	}
	else {
		countString = difficultyInbox.get_string();
	}

	if (countString.length() > 1 || countString.length() == 0) {
		input = -1;
	}
	else {
		char countCharacter = countString[0];
		if (isdigit(countCharacter)) {
			input = countCharacter - '0';
			if (!(input <= upperLimit && input >= lowerLimit)) {
				input = -1;
			}
			else {
				if (isCount) {
					RemoveCountInbox();
				}
				else {
					CleanScreen();
				}
			}
		}
	}
}

Button showDifficultyPage(Point(PANCAKELEFTX - LEFTLABELWIDTH / 2, 250), 75, 50, "Continue", ShowDifficulty);
Button closeDifficultyPage(Point(PANCAKELEFTX - LEFTLABELWIDTH / 2, 250), 75, 50, "Continue", DetachAll);

void DetachAll(Address, Address pw) {
	win.detach(difficultyOutbox);
	win.detach(closeDifficultyPage);
	win.detach(difficultyQuestionLabel);
	win.detach(inputValidation);
	Fl::redraw();
	continueForward = true;
}

void ShowDifficulty(Address, Address pw) {
	isCount = false;
	win.detach(pancakeQuestionLabel);
	win.detach(countOutbox);
	win.detach(showDifficultyPage);

	lowerLimit = 1;
	upperLimit = pancakeCount;

	inputValidation.set_label("Input must be between 1 and " + to_string(pancakeCount));
	// win.attach(inputValidation);
	win.attach(difficultyQuestionLabel);
	win.attach(getDifficulty);
	win.attach(difficultyInbox);
	Fl::redraw();
}

void RemoveCountInbox() {
	win.attach(countOutbox);
	countOutbox.put(to_string(input));
	pancakeCount = input;
	win.attach(showDifficultyPage);
	win.detach(getCount);
	win.detach(countInbox);
	Fl::redraw();
}

void CleanScreen() {
	win.attach(difficultyOutbox);
	win.attach(closeDifficultyPage);
	difficultyOutbox.put(to_string(input));
	difficulty = input;
	// win.attach(showDifficultyPage);
	win.detach(difficultyInbox);
	win.detach(getDifficulty);
	Fl::redraw();
}

void askUserForPancakeCount() {
	inputValidation.set_label("Input must be between 2 and 9.");
	win.attach(inputValidation);
	win.attach(pancakeQuestionLabel);
	win.attach(countInbox);
	// win.attach(countOutbox);
	win.attach(getCount);
	// win.attach(showDifficultyPage);

	win.show();
	Fl::redraw();

	while (!continueForward)
	{
		Fl::wait();
		Fl::redraw();
	}

	// win.show();
	// Fl::run();
}

/* int main() {
	try {
		if (H112 != 201708L) {
			error("Error: incorrect std_lib_facilities_5.h version ", H112);
		}
		askUserForPancakeCount();
		return 0;
	}
	catch (exception& e) {
		cerr << "exception: " << e.what() << '\n';
		return 1;
	}
	catch (...) {
		cerr << "Some exception\n";
		return 2;
	}
} */