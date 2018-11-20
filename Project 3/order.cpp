/* provided by Dr. Daugherity
* courses.cse.tamu.edu/daugher/misc/PPP/find_solution.h
* courses.cse.tamu.edu/daugher/misc/PPP/find_solution.o
*/

#include <ncurses.h>
#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "find_solution.h"

using namespace std;

// helper function to ensure the user enters a number not already used
bool isUnique(int element, vector<int> list) {
	int index = 0;
	while (index < list.size()) {
		if (list[index] == element) {
			return true;
		}
		index++;
	}
	return false;
}

void displayMinMoves(vector<int> pancakeStack, WINDOW *win) {
	mvwprintw(win, 17, 27, "Min number of moves to solve: ");
	vector<int> *result = find_solution(pancakeStack);
	string moves = to_string(result->size());
	mvwprintw(win, 17, 27+30, moves.c_str());
}

vector<int> userInitialize(vector<int> pancakeStack, int n) {
	WINDOW *win = newwin(40, 80, 0, 0);
	for (int i = 0; i < n; i++) {
		mvwprintw(win, 10, 32, "Enter a value: ");
		wrefresh(win);
		
		// convert char value to the real integer value
		int number = getch() - 48;
		
		// Display the number that the user input
		char charNum[10] = {(char) (number + 48)};
		mvwprintw(win, 10, 47, charNum);
		wrefresh(win);
		while (getch() != 10) {}

		// check to see if number is already there or not
		bool alreadyThere = false;
		alreadyThere = isUnique(number, pancakeStack);

		if (alreadyThere == true) {
			mvwprintw(win, 11, 25, "    Number is already used    ");
			wrefresh(win);
			i--;	// do not increase index
			continue;
		}
		else {
			if (number >= 1 && number <= n) {
				// mvwprintw(win, 10, 32, "               ");
				mvwprintw(win, 11, 25, "                               ");
				wrefresh(win);
				pancakeStack[i] = number;
			}
			else {
				mvwprintw(win, 11, 25, "Number must be between 1 and %d", n);
				wrefresh(win);
				i--;	// do not increase index
			}
		}

		// Display contents of pancake stack as user inputs pancakes
		mvwprintw(win, 14, 29, "Set up pancake stack:");
		wrefresh(win);
		for (int x = 0; x < pancakeStack.size(); x++) {
			int inside = pancakeStack[x] + 48;
			char forStack[10] =  {(char) inside};
			mvwprintw(win, 15, (2 * x) + 32, forStack);
			if (inside == 48) {
				// Hide the 0 values
				mvwprintw(win, 15, (2 * x) + 32, " ");
			}
			wrefresh(win);
		}
	}
	// display the minimum moves
	displayMinMoves(pancakeStack, win);
	wrefresh(win);
	return pancakeStack;
}

vector<int> userRandomize(vector<int> pancakeStack, int n) {
	WINDOW *win = newwin(40, 80, 0, 0);
	srand (time(NULL));
	for (int i = 0; i < n; i++) {
		pancakeStack[i] = i + 1;
	}
	for (int i = 0; i < n; i++) {
		int randomNumber = i + rand() % (n - i);
		swap(pancakeStack[i], pancakeStack[randomNumber]);
	}

	mvwprintw(win, 14, 27, "Randomized pancake stack:");
	for (int x = 0; x < n; x++) {
		int inside = pancakeStack[x] + 48;
		char forStack[10] =  {(char) inside};
		mvwprintw(win, 15, (2 * x) + 32, forStack);
		wrefresh(win);
	}
	// display the minimum moves
	displayMinMoves(pancakeStack, win);
	wrefresh(win);
	
	return pancakeStack;
}

vector<int> generateStack(int n) {
	initscr();
	noecho();
	curs_set(0);

	WINDOW *win = newwin(40, 80, 0, 0);
	box(win, 0, 0);
	wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	refresh();
	wrefresh(win);

	mvwprintw(win, 5, 27, "What order would you like?");
	mvwprintw(win, 6, 27, "    1. Own   2. Random");
	mvwprintw(win, 8, 32, "Choose 1 or 2: ");
	wrefresh(win);

	// cannot move on until user has chosen an appropriate option
	int order = getch();
	while(order != 49 && order != 50) {
		order = getch();
	}
	// Display the user's input choice
	char charOrder[10] = {(char) order};
	mvwprintw(win, 8, 47, charOrder);
	wrefresh(win);
	while (getch() != 10) {}

	vector<int> stack(n);
	if (order == 49) {	// ASCII for 1 is 49
		vector<int> user = userInitialize(stack, n);
		stack = user;
	}
	// unique random number generator
	else if (order == 50) {	// ASCII for 2 is 50
		vector<int> randomStack = userRandomize(stack, n);
		stack = randomStack;
	}

	mvwprintw(win, 19, 16, "Pancake stack is ready! Press ENTER to continue");
	wrefresh(win);
	while (getch() != 10) {}
	return stack;
	delwin(win);
	return stack;
}