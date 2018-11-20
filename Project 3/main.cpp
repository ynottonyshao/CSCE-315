/* provided by Dr. Daugherity
* courses.cse.tamu.edu/daugher/misc/PPP/find_solution.h
* courses.cse.tamu.edu/daugher/misc/PPP/find_solution.o
*/

#include <ncurses.h>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include "game_over.cpp"
#include "splash_screen.cpp"
#include "animated_splash_screen.cpp"
#include "order.cpp"
#include "pancake_renderer.cpp"
#include "ai.cpp"

using namespace std;

int main() {

	bool play = true;
	while(play) {
		initscr();
	  	noecho();
	  	curs_set(0);

	  	// start splash screen
		animatedSplashScreenMain();
	  	// instructions();
	  	string user = displayStartTopScores();

	  	int n = get_pancakes();
		int diff = get_difficulty(n);

		vector<int> leftStack = generateStack(n);
		vector<int> rightStack = leftStack;
		
		bool game_over = false;
		int game_result = 0;
		
		while(!game_over) {
			//user flips their stack
			int flipLevel = drawPancakeStacks(leftStack,rightStack, -1) + 1;
			flipStack(leftStack, flipLevel);
			writePancakeStacks(leftStack, rightStack);
			//AI flips their stack
			int aiFlipLevel = bestMove(rightStack);
			drawPancakeStacks(leftStack, rightStack, aiFlipLevel);
			flipStack(rightStack, aiFlipLevel);
			game_result = detectGameOver(leftStack, rightStack);
			if(game_result != -1) {
				game_over = true;
			}
		}

	  	// display score
	  	int finalScore = calculateScore(game_result, n, diff);
	  	int g = displayGameOver(user, finalScore, game_result);

	  	//if user presses ENTER, play again
	  	if (g == 113) {
	  		play = false;
	  	}
	}
  	
  	endwin();
  	return 0;
}
