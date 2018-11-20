#include <vector>
#include <iostream>
#include "find_solution.h"
using namespace std;

int main(){
	vector<int> pancakes{4,1,2,3};
	vector<int> *result = find_solution(pancakes);
	cout << result->size() << endl;
	delete result;
}