#include "std_lib_facilities_5.h"
#include "Simple_window.h"
#include "Graph.h"
#include "FL/Fl_JPEG_Image.H"
#include "global.h"
#include "splashscreen.h"
#include "Difficulty_Count_Demo.h"
#include "pancakeOrder.h"
#include "initscore.h"
#include "pancakerenderdemo.h"
#include "GameOver_Screen.h"

void resetVariables() {
	continueForward = false;
	finished_game = false;
	initials_continue = false;
	continue_to_next_screen = false;
	orderCounter = 0;
	orderContinue = false;
	game_done = false;
	play_pressed = false;
	start_pressed = false;
	upperLimit = 9;
	lowerLimit = 2;
	input = -1;
	pancakeCount = input;
	isCount = true;
	gameOverTextInt = -1; // Number to determine tie, win, or lose
	AI *alexa;
	num_moves = 0;
	leftStack.clear();
	rightStack.clear();
	leftPancakeButtons.clear();
	rightPancakeButtons.clear();
}

int main() {
	try {
		if (H112 != 201708L) {
			error("Error: incorrect std_lib_facilities_5.h version ", H112);
		}

		win.callback(window_cb);

		while (!quit_pushed) {
			win.show();
			draw_splash();
			askUserForPancakeCount();
			intitialStateScreen();
			initialScoreScreen();
			playGame();
			gameOverScreen();
			resetVariables();
		}

		// Fl::run();

		return 0;
	}
	catch (exception &e)
	{
		cerr << "exception: " << e.what() << '\n';
		return 1;
	}
	catch (...)
	{
		cerr << "Some exception\n";
		return 2;
	}
}