#include <ncurses.h>
#include "color.h"

void InitColors () {
	// black
	init_pair (BkBk, COLOR_BLACK, COLOR_BLACK);
	init_pair (BkR, COLOR_BLACK, COLOR_RED);
	init_pair (BkG, COLOR_BLACK, COLOR_GREEN);
	init_pair (BkY, COLOR_BLACK, COLOR_YELLOW);
	init_pair (BkBl, COLOR_BLACK, COLOR_BLUE);
	init_pair (BkM, COLOR_BLACK, COLOR_MAGENTA);
	init_pair (BkC, COLOR_BLACK, COLOR_CYAN);
	init_pair (BkW, COLOR_BLACK, COLOR_WHITE);
	// red
	init_pair (RBk, COLOR_RED, COLOR_BLACK);
	init_pair (RR, COLOR_RED, COLOR_RED);
	init_pair (RG, COLOR_RED, COLOR_GREEN);
	init_pair (RY, COLOR_RED, COLOR_YELLOW);
	init_pair (RBl, COLOR_RED, COLOR_BLUE);
	init_pair (RM, COLOR_RED, COLOR_MAGENTA);
	init_pair (RC, COLOR_RED, COLOR_CYAN);
	init_pair (RW, COLOR_RED, COLOR_WHITE);
	// green
	init_pair (GBk, COLOR_GREEN, COLOR_BLACK);
	init_pair (GR, COLOR_GREEN, COLOR_RED);
	init_pair (GG, COLOR_GREEN, COLOR_GREEN);
	init_pair (GY, COLOR_GREEN, COLOR_YELLOW);
	init_pair (GBl, COLOR_GREEN, COLOR_BLUE);
	init_pair (GM, COLOR_GREEN, COLOR_MAGENTA);
	init_pair (GC, COLOR_GREEN, COLOR_CYAN);
	init_pair (GW, COLOR_GREEN, COLOR_WHITE);
	// yellow
	init_pair (YBk, COLOR_YELLOW, COLOR_BLACK);
	init_pair (YR, COLOR_YELLOW, COLOR_RED);
	init_pair (YG, COLOR_YELLOW, COLOR_GREEN);
	init_pair (YY, COLOR_YELLOW, COLOR_YELLOW);
	init_pair (YBl, COLOR_YELLOW, COLOR_BLUE);
	init_pair (YM, COLOR_YELLOW, COLOR_MAGENTA);
	init_pair (YC, COLOR_YELLOW, COLOR_CYAN);
	init_pair (YW, COLOR_YELLOW, COLOR_WHITE);
	// blue
	init_pair (BlBk, COLOR_BLUE, COLOR_BLACK);
	init_pair (BlR, COLOR_BLUE, COLOR_RED);
	init_pair (BlG, COLOR_BLUE, COLOR_GREEN);
	init_pair (BlY, COLOR_BLUE, COLOR_YELLOW);
	init_pair (BlBl, COLOR_BLUE, COLOR_BLUE);
	init_pair (BlM, COLOR_BLUE, COLOR_MAGENTA);
	init_pair (BlC, COLOR_BLUE, COLOR_CYAN);
	init_pair (BlW, COLOR_BLUE, COLOR_WHITE);
	// magenta
	init_pair (MBk, COLOR_MAGENTA, COLOR_BLACK);
	init_pair (MR, COLOR_MAGENTA, COLOR_RED);
	init_pair (MG, COLOR_MAGENTA, COLOR_GREEN);
	init_pair (MY, COLOR_MAGENTA, COLOR_YELLOW);
	init_pair (MBl, COLOR_MAGENTA, COLOR_BLUE);
	init_pair (MM, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair (MC, COLOR_MAGENTA, COLOR_CYAN);
	init_pair (MW, COLOR_MAGENTA, COLOR_WHITE);
	// cyan
	init_pair (CBk, COLOR_CYAN, COLOR_BLACK);
	init_pair (CR, COLOR_CYAN, COLOR_RED);
	init_pair (CG, COLOR_CYAN, COLOR_GREEN);
	init_pair (CY, COLOR_CYAN, COLOR_YELLOW);
	init_pair (CBl, COLOR_CYAN, COLOR_BLUE);
	init_pair (CM, COLOR_CYAN, COLOR_MAGENTA);
	init_pair (CC, COLOR_CYAN, COLOR_CYAN);
	init_pair (CW, COLOR_CYAN, COLOR_WHITE);
	// white
	init_pair (WBk, COLOR_WHITE, COLOR_BLACK);
	init_pair (WR, COLOR_WHITE, COLOR_RED);
	init_pair (WG, COLOR_WHITE, COLOR_GREEN);
	init_pair (WY, COLOR_WHITE, COLOR_YELLOW);
	init_pair (WBl, COLOR_WHITE, COLOR_BLUE);
	init_pair (WM, COLOR_WHITE, COLOR_MAGENTA);
	init_pair (WC, COLOR_WHITE, COLOR_CYAN);
	init_pair (WW, COLOR_WHITE, COLOR_WHITE);
}

void TestColors () {
	int i;
	
	for (i = BkBk; i <= WW; i++) {
		attron (COLOR_PAIR (i));
		addch ('U');
		refresh ();
	}
}