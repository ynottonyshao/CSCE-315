#include "std_lib_facilities_5.h"
#include "Simple_window.h"
#include "Graph.h"
#include "FL/Fl_JPEG_Image.H"
#include <vector>
#include <string>
#include <cmath>

using namespace Graph_lib;
using namespace std;

// const int WINDOWX			= 100;
// const int WINDOWY			= 100;
// const int WINDOWWIDTH		= 600;
// const int WINDOWHEIGHT		= 600;
// const int LABELY				= 50;
// const int LEFTLABELWIDTH		= 38;
// const int RIGHTLABELWIDTH	= 12;

// Callback functions
void quit_callback(Address a, Address b);
void again_callback(Address a, Address b);

// Global Widgets
// Graph_lib::Window win(Point(WINDOWX, WINDOWY), WINDOWWIDTH, WINDOWHEIGHT, "Pancake Render Demo");
Button quit_game(Point((WINDOWWIDTH / 2) - 135, WINDOWHEIGHT - 240), 125, 30, "No (Quit)", quit_callback);
Button play_again(Point((WINDOWWIDTH / 2) + 15, WINDOWHEIGHT - 240), 125, 30, "Yes, play again!", again_callback);

bool quit_pushed = false;
bool finished_game = false;

// Callback for quit button
void quit_callback(Address a, Address pw) {
	quit_pushed = true;
	finished_game = true;
}

// Callback for play again button
void again_callback(Address a, Address pw) {
	finished_game = true;
}

// Reads initials and scores from disk and returns them as a 2D string vector
vector<vector<string>> readScores2() {
	ifstream in("score");
	int i = 0;
	string temp;
	vector<vector<string>> scores;
	while (in >> temp) {
		scores.push_back(vector<string>(2));
		scores[i][0] = temp;
		in >> temp;
		scores[i++][1] = temp;
	}
	return scores;
}

// Calculates the users score
int calcFinalScore() {
	int score = 0;
	switch (gameOverTextInt) {
		case 1: // User wins
			score = 2 * num_moves * (difficulty + 1);
			break;
		case 0: // Tie game
			score = num_moves * (difficulty + 1);
			break;
		case 2: // AI wins
			score = num_moves;
			break;
		default:
			break;
	}
	return score;
}

// Adds the players score and sorts it with the top 5 scores
vector<vector<string>> sortScores(vector<vector<string>> scores) {
	scores.push_back(vector<string>(2));

	scores[scores.size()-1][0] = player_initials.substr(0,3);
	scores[scores.size()-1][1] = to_string(calcFinalScore());

	string temp;
	for (int i = 0; i < (int)scores.size()-1; i++) {
		if (stoi(scores[scores.size()-1][1]) > stoi(scores[i][1])) {
			temp = scores.back()[0];
			scores[scores.size()-1][0] = scores[i][0];
			scores[i][0] = temp;

			temp = scores.back()[1];
			scores[scores.size()-1][1] = scores[i][1];
			scores[i][1] = temp;
		}
	}
	return scores;
}

void gameOverScreen() {
	// Window dimension
	int xMid = WINDOWWIDTH / 2;

	// Display "GAME OVER" header
	Text game_over(Point(xMid - 90, 90), "GAME OVER");
	game_over.set_font(FL_SCREEN);
	game_over.set_font_size(30);
	win.attach(game_over);

	// Display "Top Scores" header
	Text top_scores(Point(xMid - 52, 125), "Top Scores");
	top_scores.set_font(FL_SCREEN);
	top_scores.set_font_size(20);
	win.attach(top_scores);

	// Gets the scores as an array and the size of the array
	vector<vector<string>> allScores = readScores2();
	allScores = sortScores(allScores);
	ofstream out("score");
	for (int i = 0; (i < (int)allScores.size()) && (i < 5); i++) {
		out << allScores[i][0] << endl << allScores[i][1] << endl;
	}

	// Display the top scores loaded in from the file
	int label_x = xMid - 65;
	int label_y = 150;
	for (int i = 0; (i < (int)allScores.size()) && (i < 5); i++) {
		Text *score_initial = new Text(Point(label_x + 20, label_y), allScores[i][0]);
		Text *score_val = new Text(Point(label_x + 80, label_y), allScores[i][1]);

		score_initial->set_font(FL_SCREEN_BOLD);
		score_val->set_font(FL_SCREEN_BOLD);

		score_initial->set_font_size(15);
		score_val->set_font_size(15);

		textWidgets.push_back(score_initial);
		textWidgets.push_back(score_val);

		win.attach(*score_initial);
		win.attach(*score_val);
		label_y += 25;
	}

	// Display player's score
	Text your_score(Point(xMid - 70, 280), "Your score is: ");
	your_score.set_font(FL_COURIER);
	your_score.set_font_size(12);
	win.attach(your_score);

	int score = calcFinalScore();
	string score_string = to_string(score);
	Text display_score(Point(xMid + 35, 280), score_string);
	display_score.set_font(FL_COURIER);
	display_score.set_font_size(18);
	win.attach(display_score);

	// Display whether the play tied, won, or lost
	string gameOverText = "";
	int text_position = 0;
	if (gameOverTextInt == 0) {
		gameOverText = "Congratulations, you equalled the AI!";
		text_position = 140;
	}
	else if (gameOverTextInt == 1) {
		gameOverText = "WOW! You beat the AI!!!";
		text_position = 95;
	}
	else if (gameOverTextInt == 2) {
		gameOverText = "The AI beat you...";
		text_position = 65;
	}
	Text TieWinLose(Point(xMid - text_position, 315), gameOverText);
	TieWinLose.set_font(FL_SCREEN);
	TieWinLose.set_font_size(15);
	win.attach(TieWinLose);

	// Display asking user to continue or quit
	Text next_instruction(Point(xMid - 110, 345), "Would you like to play again?");
	next_instruction.set_font(FL_SCREEN);
	next_instruction.set_font_size(15);
	win.attach(next_instruction);

	// Attach buttons for quit or play again
	win.attach(quit_game);
	win.attach(play_again);

	Fl::redraw();

	// Wait for quit button to be pressed
	while (!finished_game) {
		Fl::wait();
		Fl::redraw();
	}

	// Detach everything to avoid segmentation fault
	win.detach(game_over);
	win.detach(top_scores);
	for (int i = 0; i < textWidgets.size(); i++) {
		win.detach(*textWidgets[i]);
	}
	win.detach(your_score);
	win.detach(display_score);
	win.detach(TieWinLose);
	win.detach(next_instruction);
	win.detach(quit_game);
	win.detach(play_again);

	return;

	/* win.show();
	Fl::run(); */
}

/* int main() {
	try {
		if (H112 != 201708L) {
			error("Error: incorrect std_lib_facilities_5.h version ", H112);
		}
		gameOverScreen();
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