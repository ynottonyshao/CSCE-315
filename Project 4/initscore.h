#include "std_lib_facilities_5.h"
#include "Simple_window.h"
#include "Graph.h"
#include "FL/Fl_JPEG_Image.H"
#include <vector>
#include <string>

// const int WINDOWX = 100;
// const int WINDOWY = 100;
// const int WINDOWWIDTH = 600;
// const int WINDOWHEIGHT = 600;
// const int LABELY = 50;
// const int LEFTLABELWIDTH = 38;
// const int RIGHTLABELWIDTH = 12;
// const int PANCAKEHEIGHT = 30;
// const int PANCAKESTARTY = 100;
// const int PANCAKEVERTICALGAP = 10;
// const int PANCAKELEFTX = WINDOWWIDTH / 3;
// const int PANCAKERIGHTX = WINDOWWIDTH * 2 / 3;
// const int PANCAKEUNITWIDTH = 10;
// const int PANCAKEBASEWIDTH = 30;

// Callback functions
void save_callback(Address a, Address b);
void continue_callback(Address a, Address b);

// Global Widgets
// Graph_lib::Window win(Point(WINDOWX, WINDOWY), WINDOWWIDTH, WINDOWHEIGHT, "Pancake Render Demo");
In_box get_initials(Point((WINDOWWIDTH / 2) + 35, (WINDOWHEIGHT / 6) + 50 + 25 * 5), 45, 20, "What are your initials? ");
Button sve_initials(Point((WINDOWWIDTH / 2) + 85, (WINDOWHEIGHT / 6) + 50 + 25 * 5), 45, 20, "Save", save_callback);
Button progress(Point((WINDOWWIDTH / 2) - 75, (WINDOWHEIGHT / 6) + 300), 150, 50, "Continue", continue_callback);
vector<Text *> textWidgets;

//Variables
string player_initials = "";
bool initials_continue = false;
bool continue_to_next_screen = false;

// Callback for save button
void save_callback(Address a, Address pw) {
	player_initials = get_initials.get_string();
	if (player_initials != "") {
		if (player_initials.size() > 3) {
			player_initials = player_initials.substr(0, 3);
		}

		initials_continue = true;
		// Remove the input and save button
		win.detach(get_initials);
		win.detach(sve_initials);
	}
}

// Callback for continue button
void continue_callback(Address a, Address pw) {
	continue_to_next_screen = true;
}

// reads initials and scores from disk and returns them as a 2D string vector
vector<vector<string>> readScores() {
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

void initialScoreScreen() {
	// Window dimensions
	int xBeg = WINDOWWIDTH / 3;
	int yBeg = WINDOWHEIGHT / 6;
	int xMid = WINDOWWIDTH / 2;

	// Gets the scores as a string array and the size of the array
	vector<vector<string>> allScores = readScores();
	// Print top score header
	Text topScores(Point(xMid - 120, yBeg), "Top scores:");
	topScores.set_font(FL_SCREEN);
	topScores.set_font_size(40);
	win.attach(topScores);

	// Print top scores loaded in from the file
	for (int i = 0; (i < (int)allScores.size()) && (i < 5); i++) {
		Text *score_initial = new Text(Point(xMid - 75, yBeg + 50 + 25 * i), allScores[i][0]);
		Text *score_val = new Text(Point(xMid + 55, yBeg + 50 + 25 * i), allScores[i][1]);

		score_initial->set_font(FL_SCREEN_BOLD);
		score_val->set_font(FL_SCREEN_BOLD);
		
		score_initial->set_font_size(20);
		score_val->set_font_size(20);
		
		textWidgets.push_back(score_initial);
		textWidgets.push_back(score_val);

		win.attach(*score_initial);
		win.attach(*score_val);
	}

	// Attach input and button that asks and saves the user initials
	win.attach(get_initials);
	win.attach(sve_initials);

	// Wait for initials save button to be pressed
	while (!initials_continue) {
		Fl::wait();
		Fl::redraw();
	}

	// prints the player's score with the top 5, in order
	Text playerName(Point(xMid - 75, yBeg + 50 + 25 * 5), player_initials);
	playerName.set_font(FL_HELVETICA_ITALIC);
	playerName.set_font_size(20);
	win.attach(playerName);

	// Attach continue button
	win.attach(progress);

	Fl::redraw();

	// Wait for continue button to be pressed
	while (!continue_to_next_screen) {
		Fl::wait();
		Fl::redraw();
	}

	win.detach(topScores);
	win.detach(playerName);
	win.detach(progress);
	for (int i = 0; i < textWidgets.size(); i++) {
		win.detach(*textWidgets[i]);
	}

	// Finished
	return;
}

/* int main() {
	try {
		if (H112 != 201708L) {
			error("Error: incorrect std_lib_facilities_5.h version ", H112);
		}
		initialScoreScreen();
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