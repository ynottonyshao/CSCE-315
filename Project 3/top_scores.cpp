#include <ncurses.h>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
using namespace std;

// debug
void print(multimap<int, string> scores) {
	multimap<int, string>::iterator it;

	for(it = scores.begin(); it != scores.end(); it++) {
		cout << it->first << " " << it->second << endl;
	}
}

// read from "topScores.txt" file
multimap<int, string> readFromFile() {
	int tempScore;
	string tempUsername;
	multimap<int, string> scores;
	scores.clear();

	ifstream inputFile("topScores.txt");
	while(inputFile >> tempScore >> tempUsername) {
		scores.insert(pair<int,string> (tempScore, tempUsername));
	}

	inputFile.close();
	return scores;
}

// write to "topScores.txt" file
void writeToFile(multimap<int, string> scores) {
	ofstream outputFile("topScores.txt");
	multimap<int, string>::iterator it;

	for(it = scores.begin(); it != scores.end(); it++) {
		outputFile << it->first << " " << it->second << endl;
	}

	outputFile.close();
}

// check for duplicate username and score
bool duplicateScore(int score, string username, multimap<int, string> scores) {
	multimap<int, string>::iterator it;

	for(it = scores.begin(); it != scores.end(); it++) {
		if(it->first == score && it->second == username) {
			return true;
		}
	}
	return false;
}


// input the current score when the game ends
void inputScore(string username, int score) {
	// read from file
	multimap<int, string> scores = readFromFile();

	// insert
	if(!duplicateScore(score, username, scores)) {
		scores.insert(pair<int,string> (score, username));
	}

	// write to file
	writeToFile(scores);
}

// display top five
void displayTopFive(WINDOW *win, multimap<int, string> scores, int start) {

	mvwprintw(win, start, 0, "TOP SCORES");
	//multimap<int, string>::iterator it = scores.begin();
	int count = 1;

	if(scores.size() < 5) {
		for (auto it = scores.rbegin(); it != scores.rend(); ++it) {
	        std::string s = std::to_string(it->first);
			char const *score = s.c_str();
			char const *user = (it->second).c_str();
			mvwprintw(win, start + count, 0, user);
			mvwprintw(win, start + count, (string(user)).size(), ":");
			mvwprintw(win, start + count, (string(user)).size()+2, score);
			count++;
	    }
	}
	else {
		auto it = scores.rbegin();
		for (int i=0; i < 5; i++) {
	        std::string s = std::to_string(it->first);
			char const *score = s.c_str();
			char const *user = (it->second).c_str();
			mvwprintw(win, start + count, 0, user);
			mvwprintw(win, start + count, (string(user)).size(), ":");
			mvwprintw(win, start + count, (string(user)).size()+2, score);
			count++;
			++it;
	    }
	}
}

string inputUserInitials(WINDOW *win) {
	stringstream ss;
	mvwprintw(win, 0, 0, "Enter initials: ");
	wrefresh(win);
	ss << (char)getchar() << ' ' << (char)getchar();
	string c1, c2;
	ss >> c2 >> c1;
	string initials = c2 + c1;

	return initials;
}

//display top 5 scores with user's name
string displayStartTopScores() {

	WINDOW *win = newwin(40, 80, 0, 0);
	box(win, 0, 0);
	wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	refresh();
	wrefresh(win);

	// enter initials
	string initials = inputUserInitials(win);

	// display initials
	mvwprintw(win, 0, 17, initials.c_str());

	// read from file
	multimap<int, string> scores = readFromFile();

	// display top five
	displayTopFive(win, scores, 2);

	// display current username
	int count = scores.size();
	if(count > 5) {
		count = 5;
	}
	mvwprintw(win, count+3, 0, initials.c_str());
	mvwprintw(win, count+3, 3, ":");
	mvwprintw(win, count+3, 5, "0");
	
	mvwprintw(win, count+5, 0, "Please press ENTER to choose the number of pancakes");

	// refresh
	wrefresh(win);
  	wattron(win, A_BLINK);
	while(10 != getch()) {
  	}
  	delwin(win);

  	return initials;
}

// int main() {

// 	//test
// 	inputScore("sarah", 1);
// 	inputScore("john", 2);
// 	inputScore("sarah", 5);
// 	inputScore("john", 3);
// 	inputScore("sarah", 11);

// 	// start display
// 		initscr();
//   	noecho();
//   	curs_set(0);
//   	WINDOW *win = newwin(40, 80, 0, 0);
//   	box(win, 0, 0);
//   	wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
//   	refresh();
//   	wrefresh(win);

//   	// display scores
//   	displayStartTopScores(win);
//   	endwin();
  	
//   	return 0;
// }