#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int diff = 9;	// dummy diff, the depth of the minimax tree is no more than diff

// flips everything "above" the pancake including the pancake itself
vector<int> flipPancakes(vector<int> stack, int position) {
	if (position > 0 && position <= stack.size()) {
		for (int i = 0; i < position/2; i++) {
			swap(stack[i], stack[position - i - 1]);
		}
	}
	return stack;
}

// sortedness is the number of reversals
int sortedness(vector<int> checkSort) {
	int reversals = 0;
	// count for number of reversals
	for (int i = 2; i < checkSort.size(); i++) {
		// start with 0 < top pancake
		if (i == 2 && checkSort[i - 2] > 0 && checkSort[i - 2] > checkSort[i - 1]) {
			reversals++;
			continue;
		}
		else if (checkSort[i - 2] > checkSort[i - 1] && checkSort[i - 1] < checkSort[i]) {
			reversals++;
		}
		else if (checkSort[i - 2] < checkSort[i - 1] && checkSort[i - 1] > checkSort[i]) {
			reversals++;
		}
	}
	return reversals;
}

// minimax function considers all possible ways the stack can go
int minimax(vector<int> pancakeStack, int depth, int last) {
	// terminating condition, leaf node is reached (or the end is sorted)
	if (sortedness(pancakeStack) == 0 || depth == diff) {
		return sortedness(pancakeStack) + depth;
	}
	int optimum = pancakeStack.size();
	for (int i = 2; i < pancakeStack.size() + 1; i++) {
		if (last != i) {
			pancakeStack = flipPancakes(pancakeStack, i);
			// find minimum attainable value by calling minimax recursively
			optimum = min(optimum, minimax(pancakeStack, depth + 1, i));
			pancakeStack = flipPancakes(pancakeStack, i);
		}
	}
	return optimum;
}

int bestMove(vector<int> pancake) {
	int track = 10;
	int best;
	
	for (int i = 2; i < pancake.size() + 1; i++) {
		// make permutation of flips
		pancake = flipPancakes(pancake, i);
		int move = minimax(pancake, 0, 0);
		pancake = flipPancakes(pancake, i);	// retain original stack for permutation

		// if value of the current move is less than the best move, update the best
		if (move < track) {
			track = move;
			best = i;
		}
	}
	// cout << "The best move is to flip the top " << best << " pancakes." << endl;
	return best;
}

// int main() {
// 	vector<int> pancakes{6, 4, 5, 2, 3, 1};
// 	// vector<int> pancakes{4, 2, 3, 1};
// 	while (true) {
// 		for (int i = 0; i < pancakes.size(); i++) {
// 			cout << pancakes[i] << " ";
// 		}
// 		cout << endl << endl;
		
// 		// determine and make next best move
// 		int best_move = bestMove(pancakes);
// 		cout << "The best move is to flip the top " << best_move << " pancakes" << endl;
// 		cout << "Pancake chosen: " << pancakes[best_move - 1] << endl;
// 		// flip the pancakes
// 		pancakes = flipPancakes(pancakes, best_move);

// 		if (sortedness(pancakes) == 0) {
// 			break;
// 		}
// 	}
// 	for (int i = 0; i < pancakes.size(); i++) {
// 		cout << pancakes[i] << " ";
// 	}
// 	cout << endl;
// 	cout << "AI has sorted the pancake stack" << endl;
// 	return 1;
// }