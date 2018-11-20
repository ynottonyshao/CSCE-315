#include <algorithm>
#include <iostream>
#include <ncurses.h>
#include <string>
#include <thread>
#include <unistd.h>
#include <vector>
using namespace std;

//This function checks for user input without blocking the program execution.
int kbhit() {
  struct timeval tv = {0L, 0L};
  fd_set         fds;
  FD_ZERO(&fds);
  FD_SET(0, &fds);
  return select(1, &fds, NULL, NULL, &tv);
}

//This function draws a single pancake on a given window.
void animateSinglePancake(WINDOW* win, int x, int y, int size) {
  int innerwidth = 2 * size - 1;
  int adjustedx  = x * 20 + 9 + (x + 1) * 14 - size;
  int adjustedy  = y * 3 + 1;
  mvwprintw(win, adjustedy, adjustedx, "+");
  for(int i = 0; i < innerwidth; i++)
    mvwprintw(win, adjustedy, adjustedx + 1 + i, "-");
  mvwprintw(win, adjustedy, adjustedx + 1 + innerwidth, "+");
  mvwprintw(win, adjustedy + 1, adjustedx, "|");
  mvwprintw(win, adjustedy + 1, adjustedx + 1 + innerwidth / 2, to_string(size).c_str());
  mvwprintw(win, adjustedy + 1, adjustedx + 1 + innerwidth, "|");
  mvwprintw(win, adjustedy + 2, adjustedx, "+");
  for(int i = 0; i < innerwidth; i++)
    mvwprintw(win, adjustedy + 2, adjustedx + 1 + i, "-");
  mvwprintw(win, adjustedy + 2, adjustedx + 1 + innerwidth, "+");
  wrefresh(win);
}

//This function draws two pancake stacks on a given window.
void animatePancakeStacks(WINDOW* win, vector<int> leftStack, vector<int> rightStack) {
  int height = 3 * ((leftStack.size() > rightStack.size()) ? leftStack.size() : rightStack.size()) + 1;
  for(int i = 0; i < height; i++)
    for(int j = 0; j < 80; j++)
      mvwprintw(win, i, j, " ");
  mvwprintw(win, 0, 21, "HUMAN");
  mvwprintw(win, 0, 56, "AI");
  for(long unsigned int i = 0; i < leftStack.size(); i++)
    animateSinglePancake(win, 0, i, leftStack[i]);
  for(long unsigned int i = 0; i < rightStack.size(); i++)
    animateSinglePancake(win, 1, i, rightStack[i]);
}

//This function flips a pancake stack at a given position.
void flipAnimatedStack(vector<int>& stack, long unsigned int position) {
  if(position > 0 and position <= stack.size()) {
    vector<int> top;
    for(long unsigned int i = 0; i < position; i++)
      top.push_back(stack[i]);
    vector<int> bottom;
    for(long unsigned int i = position; i < stack.size(); i++)
      bottom.push_back(stack[i]);
    reverse(top.begin(), top.end());
    top.insert(top.end(), bottom.begin(), bottom.end());
    stack = top;
  }
}

//This function generates two randomized pancake stacks of size n.
void randomizeStacks(vector<int>& leftStack, vector<int>& rightStack, int n) {
  for(int i = 0; i < n; i++)
    while(true) {
      int test = (rand() % n) + 1;
      if(find(leftStack.begin(), leftStack.end(), test) == leftStack.end()) {
        leftStack.push_back(test);
        break;
      }
    }
  for(int i = 0; i < n; i++)
    while(true) {
      int test = (rand() % n) + 1;
      if(find(rightStack.begin(), rightStack.end(), test) == rightStack.end()) {
        rightStack.push_back(test);
        break;
      }
    }
}

//This function prints a splash screen to a given window.
void splashScreen(WINDOW* win) {
  mvwprintw(win, 20, 14, "    ____  ___    _   ___________    __ __ ___________");
  mvwprintw(win, 21, 14, "   / __ \\/   |  / | / / ____/   |  / //_// ____/ ___/");
  mvwprintw(win, 22, 14, "  / /_/ / /| | /  |/ / /   / /| | / ,<  / __/  \\__ \\");
  mvwprintw(win, 23, 14, " / ____/ ___ |/ /|  / /___/ ___ |/ /| |/ /___ ___/ /");
  mvwprintw(win, 24, 14, "/_/   /_/  |_/_/ |_/\\____/_/  |_/_/ |_/_____//____/");
  mvwprintw(win, 26, 30, "Team #42 - The Flippers");
  mvwprintw(win, 27, 9, "Anthony Shao, Sidney Shaw, Suvedh Srikanth, Maria Theresia Tyas");
  wrefresh(win);
  wattron(win, A_BLINK);
  mvwprintw(win, 30, 30, "Press ENTER to start");
  wattroff(win, A_BLINK);
  wrefresh(win);
}

//This function creates a new window and prints the splash screen and displays an animated demo of the game being played.
void animatedSplashScreen() {
  WINDOW* win = newwin(40, 80, 0, 0);
  box(win, 0, 0);
  wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  refresh();
  wrefresh(win);
  splashScreen(win);
  int n = 6;
  vector<int> leftStack, rightStack;
  randomizeStacks(leftStack, rightStack, n);
  animatePancakeStacks(win, leftStack, rightStack);
  splashScreen(win);
  while(true) {
    while(!kbhit()) {
      flipAnimatedStack(leftStack, (rand() % (n - 1)) + 2);
      flipAnimatedStack(rightStack, (rand() % (n - 1)) + 2);
      animatePancakeStacks(win, leftStack, rightStack);
      usleep(1000 * 300);
    }
    if(getch() == 10)
      break;
  }
  delwin(win);
}

//This function creates a new window and prints the instructions to the screen.
void animatedInstructions() {
  WINDOW* win = newwin(40, 80, 0, 0);
  box(win, 0, 0);
  wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  refresh();
  wrefresh(win);
  mvwprintw(win, 0, 34, "Instructions:");
  mvwprintw(win, 2, 1, "Use the arrow keys or WASD to select a pancake on the left side of the screen.");
  mvwprintw(win, 3, 13, "Press ENTER to flip the stack at the selected pancake.");
  wrefresh(win);
  wattron(win, A_BLINK);
  mvwprintw(win, 30, 30, "Press ENTER to start");
  wattroff(win, A_BLINK);
  wrefresh(win);
  while(getch() != 10) {
  }
  delwin(win);
}

int animatedSplashScreenMain() {
  initscr();
  noecho();
  curs_set(0);
  animatedSplashScreen();
  animatedInstructions();
  endwin();
  return 0;
}
