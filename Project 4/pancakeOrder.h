#include "FL/Fl_JPEG_Image.H"
#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities_5.h"
#include <algorithm>
#include <string>
#include <vector>

// const int WINDOWX = 100;
// const int WINDOWY = 100;
// const int WINDOWWIDTH = 600;
// const int WINDOWHEIGHT = 600;
// const int LABELY = 50;
// const int LEFTLABELWIDTH = 38;
// const int RIGHTLABELWIDTH = 12;
// const int PANCAKEHEIGHT = 30;
// const int PANCAKESTARTY = 100;
// const int PANCAKEVERTICALGAP = 10;
// const int PANCAKELEFTX = WINDOWWIDTH / 3;
// const int PANCAKERIGHTX = WINDOWWIDTH * 2 / 3;
// const int PANCAKEUNITWIDTH = 10;
// const int PANCAKEBASEWIDTH = 30;
// Graph_lib::Window win(Point(WINDOWX, WINDOWY), WINDOWWIDTH, WINDOWHEIGHT, "Pancake Render Demo");

// Function declarations
void cb_confirm(Address, Address pw);
void updatePancakeOrder(Address, Address pw);
void continueToScoreScreen(Address, Address pw);

// Widgets
Text label1(Point(WINDOWWIDTH / 3, WINDOWHEIGHT / 4 - 15), "Please enter the order of pancakes");
Text label1a(Point(WINDOWWIDTH / 3, WINDOWHEIGHT / 4), "one at a time");
Text label2(Point(WINDOWWIDTH / 3, WINDOWHEIGHT / 4 + 15), "");
Text label3(Point(WINDOWWIDTH / 3, WINDOWHEIGHT / 4 + 30), "-OR-");
Text label4(Point(WINDOWWIDTH / 3, WINDOWHEIGHT / 4 + 45), "Press 0 for random order");
In_box order_inbox(Point(WINDOWWIDTH / 3, WINDOWHEIGHT / 4 + 60), 50, 50, "Enter pancake number: ");
Out_box order_outbox(Point(WINDOWWIDTH / 3, WINDOWHEIGHT / 4 + 200), 200, 50, "Pancake order: ");
Button order_confirm(Point(WINDOWWIDTH / 3 + 115, WINDOWHEIGHT / 4 + 60), 75, 50, "Confirm", updatePancakeOrder);
Button order_continue(Point(WINDOWWIDTH / 2 - 75, WINDOWHEIGHT / 4 + 300), 150, 50, "Continue", continueToScoreScreen);

// variables
vector<int> initialPancakeOrder;
int orderCounter = 0;
int numPancakes;
int remainingPancakes;
string pancakeOrder_string = "";
bool orderContinue = false;

// seed random generator
// std::srand(std::time(0));

bool isSorted(vector<int> pancakes) {
	return is_sorted(pancakes.begin(), pancakes.end());
}

bool isInVector(int c, vector<int> orderState) {
	int size = orderState.size();
	for (auto i = 0; i < size; ++i) {
		if (c == orderState[i]) {
			return true;
		}
	}
	return false;
}

void continueToScoreScreen(Address, Address pw) {
	win.detach(label1);
	win.detach(label1a);
	win.detach(label2);
	win.detach(label3);
	win.detach(label4);
	win.detach(order_inbox);
	win.detach(order_outbox);
	win.detach(order_confirm);
	win.detach(order_continue);
	orderContinue = true;
}

string vectorOrderToString() {
	string orderOfPancakes = "";
	// create the string of the order to print
	int size = initialPancakeOrder.size();
	for (int i = 0; i < size; ++i) {
		orderOfPancakes += to_string(initialPancakeOrder[i]);
		orderOfPancakes += ", ";
	}
	return orderOfPancakes;
}

void shuffleVector(int numPancakes) {
	// clear order if user had already started entering numbers
	if (initialPancakeOrder.size() > 0) {
		initialPancakeOrder.clear();
	}

	// push all numbers in initialPancakeOrder and shuffle
	for (int i = 1; i <= numPancakes; ++i) {
		initialPancakeOrder.push_back(i);
	}

	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(initialPancakeOrder.begin(), initialPancakeOrder.end(), g);
}

void updatePancakeOrder(Address, Address pw) {
	//int number = order_inbox.get_int();
	string number_s = order_inbox.get_string();
	int number = atoi(number_s.c_str());
	if(number > 0 && number <= numPancakes && !isInVector(number, initialPancakeOrder)) {
		initialPancakeOrder.push_back(number);
		pancakeOrder_string += to_string(number);
		pancakeOrder_string += ", ";
		++orderCounter;
		order_outbox.put(pancakeOrder_string);
		Fl::redraw();
	}
	else if(number == 0) {
		shuffleVector(numPancakes);
		while(isSorted(initialPancakeOrder)) {
			shuffleVector(numPancakes);
		}
		pancakeOrder_string = vectorOrderToString();
		order_outbox.put(pancakeOrder_string);
		orderCounter = numPancakes; // end while loop
	}
}

void intitialStateScreen() {
	numPancakes = pancakeCount;
	initialPancakeOrder.clear();
	pancakeOrder_string = "";
	string enterPancakeNums = "Enter each pancake number from 1 to " + to_string(numPancakes);
	label2.set_label(enterPancakeNums.c_str());

	win.attach(label1);
	win.attach(label1a);
	win.attach(label2);
	win.attach(label3);
	win.attach(label4);

	win.attach(order_inbox);
	win.attach(order_outbox);
	win.attach(order_confirm);

	win.show();
	Fl::redraw();

	while(orderCounter != numPancakes) {
		Fl::wait();
		Fl::redraw();
	}

	win.attach(order_continue);
	Fl::redraw();

	while(!orderContinue) {
		Fl::wait();
		Fl::redraw();
	}
}

/* int main() {
	try {
		if (H112 != 201708L) {
			error("Error: incorrect std_lib_facilities_5.h version ", H112);
		}
		intitialStateScreen();
		return 0;
	}
	catch (exception& e) {
		cerr << "exception: " << e.what() << '\n';
		return 1;
	}
	catch (...) {
		cerr << "Some exception\n";
		return 2;
	}
} */