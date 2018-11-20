#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
using namespace std;

int diff = 4;
int maxdepth = 9;

vector<int> flipCakes(vector<int> pancake, int i) {
	i--;
	int temp, start = 0;
	while (start < i) {
		temp = pancake[start];
		pancake[start] = pancake[i];
		pancake[i] = temp;
		start++;
		i--;
	}
	return pancake;
}

// Calculates the sortedness advantage
int evaluate(vector<int> pancake) {
	int reversals = 0;
	for (int i = 1; i < pancake.size(); i++) {
		if (pancake[i - 1] > pancake[i]) {
			reversals++;
			// cout << pancake[i - 1] << " " << pancake[i] << endl;
		}
	}
	return reversals;
}

// Checks if the pancake stack is sorted
bool isMovesLeft(vector<int> pancake) {
	return evaluate(pancake) != 0;
}

// Determines all possibles moves
int minimax(vector<int> pancake, int depth, int lastmove = 0) {
	int score = evaluate(pancake);

	if (score == 0) {
		return score + depth;
	}

	if (depth == maxdepth) {
		return score + depth;
	}

	int best = pancake.size();
	//For every flipCakes option
	for (int i = 2; i < pancake.size() + 1; i++) {
		if (lastmove != i) {
			// Make move
			pancake = flipCakes(pancake, i);
			// Call minimax with new tree
			best = min(best, minimax(pancake, depth + 1, i));
			//Reverse move
			pancake = flipCakes(pancake, i);
		}
	}
	return best;
}

// Finds the best move returned from the minimax tree
int findBestMove(vector<int> pancake) {
	int bestVal = 100;
	int bestMove;
	for (int i = 2; i < pancake.size() + 1; i++) {
		// Make move
		pancake = flipCakes(pancake, i);
		// Call minimax with new tree
		int moveVal = minimax(pancake, 0);
		//Reverse move
		pancake = flipCakes(pancake, i);

		if (moveVal < bestVal) {
			bestMove = i;
			bestVal = moveVal;
		}
		//Randomly decied which move to take
		else if (moveVal == bestVal && rand() % 2) {
			srand(time(NULL));
			bestMove = i;
			bestVal = moveVal;
		}
	}
	// cout << "best move is " << bestMove << endl;
	return bestMove;
}

class AI {
	public:
		vector<int> pancakes;
		int diff;
		bool hasWon;
		int n;
		int move_flipped;
		
		AI(vector<int> p, int d) {
			this->pancakes = p;
			this->diff = d;
			maxdepth = d;
			this->hasWon = false;
			this->n = 0;
			this->move_flipped = 0;
		}
		
		void playTurn() {
			int move = findBestMove(pancakes);
			move_flipped = move-1;
			pancakes = flipCakes(pancakes, move);
			n++;
			if (evaluate(pancakes) == 0) {
				hasWon = true;
			}
		}
};

int findNumMoves(vector<int> vect) {
	AI walt(vect, diff);
	int i = 0;
	while (!walt.hasWon) {
		walt.playTurn();
		i++;
	}
	return i;
}
