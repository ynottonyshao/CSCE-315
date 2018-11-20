#include <ncurses.h>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <time.h>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

using namespace std;

//This function draws a single pancake on a given window.
void drawSinglePancake(WINDOW* win, int x, int y, int size) {
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

int getFlipLocation(WINDOW* win, int stack_size) {
  int position = 0;
  
  mvwprintw(win, 2 + position * 3, 38, "<--");
  wrefresh(win);
  char str = getch();
  while(10 != str) {
    if('w' == str) {
      if(position != 0) {
        mvwprintw(win, 2 + position * 3, 38, "   ");
        position--;
      }
    }
    else if('s' == str) {
      if(position < stack_size-1) {
        mvwprintw(win, 2 + position * 3, 38, "   ");
        position++;
      }
    }
    else if('\033' == str) {
      getch();
      switch(getch()) {
        case 'A':
          if(position != 0) {
            mvwprintw(win, 2 + position * 3, 38, "   ");
            position--;
          }
          break;
        case 'B':
          if(position < stack_size-1) {
            mvwprintw(win, 2 + position * 3, 38, "   ");
            position++;
          }
          break;
        default:
          mvwprintw(win, stack_size * 3 + 3, 25, "Please press W, S, UP, or DOWN");
          break;
      }
    }
    else {
      mvwprintw(win, stack_size * 3 + 3, 25, "Please press W, S, UP, or DOWN");
    }
    mvwprintw(win, 2 + position * 3, 38, "<--");
    wrefresh(win);
    str = getch();
  }

  return position;
}

//This function flips a pancake stack at a given position.
void flipStack(vector<int>& stack, long unsigned int position) {
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

WINDOW* writePancakeStacks(vector<int> leftStack, vector<int> rightStack) {
  WINDOW* win = newwin(40,80, 0, 0);
  mvwprintw(win, 0, 21, "HUMAN");
  mvwprintw(win, 0, 56, "AI");
  for(int i = 0; i < leftStack.size(); i++)
    drawSinglePancake(win, 0, i, leftStack[i]);
  for(int i = 0; i < rightStack.size(); i++)
    drawSinglePancake(win, 1, i, rightStack[i]);
  wrefresh(win);

  return win;
}

void erasePancakeStacks(vector<int> leftStack, vector<int> rightStack, int flipLevel, bool isUserStack) {
  WINDOW* win = newwin(40,80, 0, 0);
  mvwprintw(win, 0, 21, "HUMAN");
  mvwprintw(win, 0, 56, "AI");
  if(isUserStack) {
    for(int i = flipLevel + 1; i < leftStack.size(); i++)
      drawSinglePancake(win, 0, i, leftStack[i]);
    for(int i = 0; i < rightStack.size(); i++)
      drawSinglePancake(win, 1, i, rightStack[i]);
  }
  else {
    for(int i = 0; i < leftStack.size(); i++)
      drawSinglePancake(win, 0, i, leftStack[i]);
    for(int i = flipLevel; i < rightStack.size(); i++)
      drawSinglePancake(win, 1, i, rightStack[i]);
  }
  wrefresh(win);
  delwin(win);
}

void erasePancakeStacks(vector<int> leftStack, vector<int> rightStack, int flipLevel) {
  erasePancakeStacks(leftStack, rightStack, flipLevel, true);
}

//This function draws two pancake stacks on a given window.
int drawPancakeStacks(vector<int> leftStack, vector<int> rightStack, int aiStackChange) {
  if(aiStackChange == -1) {
    WINDOW* win = writePancakeStacks(leftStack, rightStack);
    int i = getFlipLocation(win, leftStack.size());
    delwin(win);
    erasePancakeStacks(leftStack, rightStack, i);
    this_thread::sleep_for (chrono::seconds(1));
    win = writePancakeStacks(leftStack, rightStack);
    delwin(win);
    this_thread::sleep_for (chrono::seconds(1));
    erasePancakeStacks(leftStack, rightStack, i);
    this_thread::sleep_for (chrono::seconds(1));
    // }
  return i;
  }
  else {
    erasePancakeStacks(leftStack, rightStack, aiStackChange, false);
    this_thread::sleep_for (chrono::seconds(1));
    WINDOW* win = writePancakeStacks(leftStack, rightStack);
    delwin(win);
    this_thread::sleep_for (chrono::seconds(1));
    erasePancakeStacks(leftStack, rightStack, aiStackChange, false);
    this_thread::sleep_for (chrono::seconds(1));
    return 0;
  }
  
}


// int main(int argc, char const* argv[]) {
//   initscr();
//   noecho();
//   curs_set(0);
//   WINDOW* win = newwin(40, 80, 0, 0);
//   box(win, 0, 0);
//   wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
//   refresh();
//   wrefresh(win);
//   vector<int> leftStack;
//   leftStack.push_back(6);
//   leftStack.push_back(4);
//   leftStack.push_back(5);
//   leftStack.push_back(2);
//   leftStack.push_back(3);
//   leftStack.push_back(1);
//   vector<int> rightStack;
//   rightStack.push_back(6);
//   rightStack.push_back(4);
//   rightStack.push_back(5);
//   rightStack.push_back(2);
//   rightStack.push_back(3);
//   rightStack.push_back(1);
//   int flipLevel = drawPancakeStacks(leftStack, rightStack) + 1;
//   flipStack(leftStack, flipLevel);

//   drawPancakeStacks(leftStack, rightStack);
//   endwin();
//   return 0;
// }