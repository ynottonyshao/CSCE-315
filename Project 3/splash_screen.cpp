#include <iostream>
#include <ncurses.h>
#include <string>
// #include "animated_splash_screen.cpp"

using namespace std;

void oldSplashScreen() {
  WINDOW *win = newwin(40, 80, 0, 0);
  box(win, 0, 0);
  wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  refresh();
  wrefresh(win);
  mvwprintw(win, 0, 14, "    ____  ___    _   ___________    __ __ ___________");
  mvwprintw(win, 1, 14, "   / __ \\/   |  / | / / ____/   |  / //_// ____/ ___/");
  mvwprintw(win, 2, 14, "  / /_/ / /| | /  |/ / /   / /| | / ,<  / __/  \\__ \\");
  mvwprintw(win, 3, 14, " / ____/ ___ |/ /|  / /___/ ___ |/ /| |/ /___ ___/ /");
  mvwprintw(win, 4, 14, "/_/   /_/  |_/_/ |_/\\____/_/  |_/_/ |_/_____//____/");
  mvwprintw(win, 6, 30, "Team #42 - The Flippers");
  mvwprintw(win, 7, 9, "Anthony Shao, Sidney Shaw, Suvedh Srikanth, Maria Theresia Tyas");
  wrefresh(win);
  wattron(win, A_BLINK);
  mvwprintw(win, 10, 30, "Press ENTER to start");
  wattroff(win, A_BLINK);
  wrefresh(win);
  while(10 != getch()) {
  }
  delwin(win);
}

void instructions() {
  WINDOW *win = newwin(40, 80, 0, 0);
  box(win, 0, 0);
  wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  refresh();
  wrefresh(win);
  mvwprintw(win, 0, 34, "Instructions:");
  mvwprintw(win, 2, 1, "Use the arrow keys or WASD to select a pancake on the left side of the screen.");
  mvwprintw(win, 3, 13, "Press ENTER to flip the stack at the selected pancake.");
  wrefresh(win);
  wattron(win, A_BLINK);
  mvwprintw(win, 10, 30, "Press ENTER to start");
  wattroff(win, A_BLINK);
  wrefresh(win);
  while(10 != getch()) {
  }
  delwin(win);
}

int get_pancakes() {
  bool err = false;
  int num;
  WINDOW *win = newwin(40, 80, 0, 0);
  while(true) {
    box(win, 0, 0);
    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    refresh();
    wrefresh(win);
    if(err) {
      mvwprintw(win, 3, 24, "Error: please enter a number 1-9");
    }
    mvwprintw(win, 9, 20, "Enter the number of pancakes (1-9):");
    wrefresh(win);
    int str = getch();
    char input[10] = "";
    input[0] = (char)str;
    mvwprintw(win, 9, 56, input);
    num = (int) (str - '0');
    if(num < 1 || num > 9) {
      err = true;
      win = newwin(40, 80, 0, 0);
    }
    else {
      break;
    }
  }

  wrefresh(win);
  while(10 != getch()) {
  }
  delwin(win);
  return num;
}

int get_difficulty(int num) {
  bool err = false;
  WINDOW *win = newwin(40, 80, 0, 0);
  int diff;
  while(true) {
    box(win, 0, 0);
    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    refresh();
    wrefresh(win);
    string inp = "Error: please enter a number 1-%d";
    if(err) {
      mvwprintw(win, 3, 24, inp.c_str(), num);
    }
    string inp2 = "Enter the difficulty level (1-%d):";
    mvwprintw(win, 9, 20, inp2.c_str(), num);
    wrefresh(win);
    int str = getch();
    string output = "";
    output += str;
    mvwprintw(win, 9, 56, output.c_str());
    diff = str - '0';
    if(diff < 1 || diff > num) {
      err = true;
      win = newwin(40, 80, 0, 0);
    }
    else {
      break;
    }
  }

  wrefresh(win);
  while(10 != getch()) {
  }
  delwin(win);
  return diff;
}

// int main(int argc, char const *argv[]) {
void startscreen() {
  initscr();
  noecho();
  curs_set(0);
  // splashScreen();
  
  instructions();
  // int num = get_pancakes();
  // int diff = get_difficulty(num);
  endwin();
  // cout << "num is " << num << endl;
  // cout << "diff is " << diff << endl;
  // return 0;
}
