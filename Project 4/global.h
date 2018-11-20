#include "std_lib_facilities_5.h"
#include "Simple_window.h"

// Global constants
const int WINDOWX			= 100;
const int WINDOWY			= 100;
const int WINDOWWIDTH		= 600;
const int WINDOWHEIGHT		= 600;
const int LABELY			= 50;
const int LEFTLABELWIDTH	= 38;
const int RIGHTLABELWIDTH	= 12;
const int PANCAKEHEIGHT = 30;
const int PANCAKESTARTY = 100;
const int PANCAKEVERTICALGAP = 10;
const int PANCAKELEFTX = WINDOWWIDTH / 3;
const int PANCAKERIGHTX = WINDOWWIDTH * 2 / 3;
const int PANCAKEUNITWIDTH = 10;
const int PANCAKEBASEWIDTH = 30;

const string title = "Pancake Flipper";

Graph_lib::Window win(Point(WINDOWX, WINDOWY), WINDOWWIDTH, WINDOWHEIGHT, title);

void window_cb(Fl_Widget *widget, void *) {
	Fl_Window *window = (Fl_Window *)widget;
	window->hide();
	exit(0);
};

