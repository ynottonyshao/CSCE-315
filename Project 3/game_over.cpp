#include <ncurses.h>
#include <string>
#include <vector>
#include "top_scores.cpp"
using namespace std;

int detectGameOver(vector<int> leftStack, vector<int> rightStack) {
	int i = 1;
	bool playerWon = true;
	while(i <= leftStack.size() && playerWon) {
		if(i != leftStack[i-1]) {
			playerWon = false;
		}
		i++;
	}
	bool aiWon = true;
	i = 1;
	while(i <= leftStack.size() && aiWon) {
		if(i != rightStack[i-1]) {
			aiWon = false;
		}
		i++;
	}
	if(playerWon && aiWon) {
		return 2;
	}
	else if (playerWon) {
		return 3;
	}
	else if(aiWon) {
		return 1;
	}
	else {
		return -1;
	}
}

int calculateScore(int c, int n, int diff) {
	
	int score = 0;

	// AI stack is sorted but human's stack is not
	if(c == 1) {
		score = n;
	}
	// both stacks are sorted
	else if(c == 2) {
		score = n*(diff + 1);
	}
	// human stack is sorted but AI stack is not
	else if(c == 3) {
		score = 2*n*(diff + 1);
	}

	return score;
}

void printSucessMessage(int y, int c, WINDOW *win) {
	string message = "";
	// AI stack is sorted but human's stack is not
	if(c == 1) {
		message = "The AI beat you!";
	}
	// both stacks are sorted
	else if(c == 2) {
		message = "Congratulations, you equalled the AI!";
	}
	// human stack is sorted but AI stack is not
	else if(c == 3) {
		message = "Wow! You beat the AI!!";
	}
	mvwprintw(win, y, 0, message.c_str());
}

void displayCurrentScore(string username, int score, WINDOW *win, int y) {
	string s = to_string(score);
	//char const *score = s.c_str();
	char const *user = username.c_str();
	string message = ", your score is: ";
	mvwprintw(win, y, 0, user);
	mvwprintw(win, y, 2, ", your score is: ");
	mvwprintw(win, y, 20, s.c_str());
}

int displayGameOver(string username, int score, int c) {
	WINDOW *win = newwin(40, 80, 0, 0);
	box(win, 0, 0);
	wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	refresh();
	wrefresh(win);
	// title
	mvwprintw(win, 0, 0, " ________  ________  _____ ______   _______");
	mvwprintw(win, 1, 0, "|\\   ____\\|\\   __  \\|\\   _ \\  _   \\|\\  ___ \\");
	mvwprintw(win, 2, 0, "\\ \\  \\___|\\ \\  \\|\\  \\ \\  \\\\__\\ \\  \\ \\   __/|");
	mvwprintw(win, 3, 0, " \\ \\  \\  __\\ \\   __  \\ \\  \\|__| \\  \\ \\  \\_|/");
	mvwprintw(win, 4, 0, "  \\ \\  \\|\\  \\ \\  \\ \\  \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\");
	mvwprintw(win, 5, 0, "   \\ \\_______\\ \\__\\ \\__\\ \\__\\    \\ \\__\\ \\_______\\");
	mvwprintw(win, 6, 0, "    \\|_______|\\|__|\\|__|\\|__|     \\|__|\\|_______|");
	mvwprintw(win, 7, 0, " ________  ___      ___ _______   ________");
	mvwprintw(win, 8, 0, "|\\   __  \\|\\  \\    /  /|\\  ___ \\ |\\   __  \\");
	mvwprintw(win, 9, 0, "\\ \\  \\|\\  \\ \\  \\  /  / | \\   __/|\\ \\  \\|\\  \\");
	mvwprintw(win, 10, 0, " \\ \\  \\\\\\  \\ \\  \\/  / / \\ \\  \\_|/_\\ \\   _  _\\");
	mvwprintw(win, 11, 0, "  \\ \\  \\\\\\  \\ \\    / /   \\ \\  \\_|\\ \\ \\  \\  \\|");
	mvwprintw(win, 12, 0, "   \\ \\_______\\ \\__/ /     \\ \\_______\\ \\__\\\\\\ _\\");
	mvwprintw(win, 13, 0, "    \\|_______|\\|__|/       \\|_______|\\|__|\\|__|");

	// update score
	inputScore(username, score);
	// read from file
	multimap<int, string> scores = readFromFile();
	// display top five scores
	displayTopFive(win, scores, 15);

	int count = scores.size();
	if(count > 5) {
		count = 5;
	}

	// display current score
	displayCurrentScore(username, score, win, count+17);

	printSucessMessage(count+19, c, win);
	mvwprintw(win, count+21, 0, "Press \"ENTER\" to play again or \"q\" to quit");

	// refresh
	wrefresh(win);
  	wattron(win, A_BLINK);
  	int g = getch();
	while(113 != g && 10 != g) {
		g = getch();
  	}

  	return g;
}