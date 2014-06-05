#include "wins.h"

// Global WINDOWS, PANELS, MENU, etc
MENU *menu = NULL;
WINDOW *menuWindow = NULL;
PANEL *menuPanel = NULL;

WINDOW *helpWindow = NULL;
PANEL *helpPanel = NULL;


void InitWins () {
// HELP
	helpPanel = CreateBoxedTitledWindow (HELP_HEIGHT, HELP_WIDTH, 0, 0, "HELP");
	hide_panel (helpPanel);
	helpWindow = panel_window (helpPanel);

	wbkgd (helpWindow, COLOR_PAIR (WBl));

	// the subtitles
	const char *subtitles[] = {
		"Nmos commands (basic hotkeys)",
		"Navigation",
		"Mosaic editing"
	};
	// the hotkeys
	const char *hotkeys[] = {
		"F1", "F10", "^Q",
		"Arrow Keys", "^D", "^B", "Page Up/Page Down", "Home/End",
		"F2", "^S", "^O", "^R", "^C/^X", "^V", "Tab"
	};
	// and how many are there for each subtitle
	int n_hotkeys[] = {3, 5, 7};
	// what the hotkeys do
	const char *explanations[] = {
		"show this helpWindow window", "show the menu", "quit Nmos",
		"move through the mosaic", "change the moving direction after input (default direction)", "toggle box selection mode", "previous/next mosaic", "move to first/last character (in the default direction)",
		"new mosaic", "save mosaic", "load mosaic", "resize mosaic", "copy/cut selection", "paste selection", "show the attribute table"
	};
	
	// aux counters; only 'i' gets reseted at 0, as it counts until n_hotkeys ends
	int sub, hot, i, line = 1;
	// for each subtitle
	for (sub = hot = 0; sub < 3; sub++, line++) {
		// write subtitle
		wattron (helpWindow, A_BOLD | A_UNDERLINE);
		mvwaddstr (helpWindow, line, 1, subtitles[sub]);
		wattroff (helpWindow, A_UNDERLINE);
		line++;
		// write rest =P
		for (i = 0; i < n_hotkeys[sub]; i++, hot++) {
			mvwaddstr (helpWindow, line++, 1, hotkeys[hot]);
			waddstr (helpWindow, ": ");
			wattroff (helpWindow, A_BOLD);
			waddstr (helpWindow, explanations[hot]);
			wattron (helpWindow, A_BOLD);
		}
	}

	wstandend (helpWindow);	
	// HUD explanation
	mvwaddch (helpWindow, HELP_HEIGHT - 1, 0, ACS_ULCORNER);
	waddch (helpWindow, ACS_HLINE); waddch (helpWindow, ACS_HLINE);
	waddstr (helpWindow, " Nmos basic hotkeys ");
	waddch (helpWindow, ACS_HLINE); waddch (helpWindow, ACS_HLINE); waddch (helpWindow, ACS_HLINE); waddch (helpWindow, ACS_URCORNER);
	wclrtoeol (helpWindow);
	
	int aux = COLS - 44;
	mvwaddch (helpWindow, HELP_HEIGHT - 1, 29, ACS_ULCORNER);
	for (i = 0; i < aux; i++) {
		wechochar (helpWindow, ACS_HLINE);
	}
	waddch (helpWindow, ACS_URCORNER);
	mvwaddstr (helpWindow, HELP_HEIGHT - 1, 22 + (aux / 2), " message area ");
	
	mvwaddch (helpWindow, HELP_HEIGHT - 1, HELP_WIDTH - 11, ACS_ULCORNER);
	waddstr (helpWindow, "position");
	waddch (helpWindow, ACS_URCORNER); waddch (helpWindow, ACS_VLINE);
	mvwaddstr (helpWindow, HELP_HEIGHT - 2, HELP_WIDTH - 18, "default direction");
	waddch (helpWindow, ACS_URCORNER);
	
	wrefresh (helpWindow);
// END HELP

// MENU
	menuPanel = CreateBoxedTitledWindow (MENU_HEIGHT, MENU_WIDTH, LINES - MENU_HEIGHT - 1, 0, "MENU");		// the panel for the menu's window
	hide_panel (menuPanel);
	menuWindow = panel_window (menuPanel);	// window for the menu
	
	ITEM **items;
	
	const int num_items = 6;
	const char *choice_titles[] = {	// 
		"Help",
		"New Image",
		"Save Image",
		"Load Image",
		"Resize Image",
		"Exit Mosaic"
	};
	const char *choice_description[] = {
		"F1",
		"F2",
		"^S",
		"^O",
		"^R",
		"^Q"
	};
	static const int choices[] = {
		KEY_F(1),
		KEY_F(2),
		KEY_CTRL_S,
		KEY_CTRL_O,
		KEY_CTRL_R,
		KEY_CTRL_Q
	};
	// create the items
	items = (ITEM**) calloc (num_items + 1, sizeof (ITEM*));
	for (i = 0; i < num_items; i++) {
		items[i] = new_item (choice_titles[i], choice_description[i]);
		set_item_userptr (items[i], (void*) &choices[i]);
	}
	
	// create the menu
	menu = new_menu (items);
	// options: cycle and don't show description, mark...
	menu_opts_off (menu, O_NONCYCLIC);
	set_menu_mark (menu, "");

	// menu's windows
	set_menu_win (menu, menuWindow);
	set_menu_sub (menu, derwin (menuWindow, MENU_HEIGHT - 2, MENU_WIDTH - 2, 1, 1));
	
	post_menu (menu);
// END MENU
}



WINDOW *CreateHud () {
	WINDOW *win = subwin (stdscr, 1, COLS, LINES - 1, 0);

	wattron (win, A_BOLD);
	waddstr (win, "F1: ");
	wattroff (win, A_BOLD);
	waddstr (win, "Help ");
	wattron (win, A_BOLD);
	waddstr (win, "F10: ");
	wattroff (win, A_BOLD);
	waddstr (win, "Menu ");
	wattron (win, A_BOLD);
	waddstr (win, "^Q: ");
	wattroff (win, A_BOLD);
	waddstr (win, "Quit");
	
	wrefresh (win);
	return win;
}


void UpdateHud (WINDOW *hud, Cursor cur, Direction dir) {
	int c;
	switch (dir) {
		case UP: c = ACS_UARROW; break;
		case DOWN: c = ACS_DARROW; break;
		case LEFT: c = ACS_LARROW; break;
		case RIGHT: c = ACS_RARROW; break;
	}

	mvwprintw (hud, 0, COLS - 11, "%dx%d", cur.y, cur.x);
	wclrtoeol (hud);
	mvwaddch (hud, 0, COLS - 1, c);
	wrefresh (hud);
	move (cur.y, cur.x);
}


int PrintHud (WINDOW *hud, const char *message) {
	mvwaddch (hud, 0, 29, ACS_DIAMOND);
	waddstr (hud, message);
	wrefresh (hud);
	int c = getch ();
	wmove (hud, 0, 29);
	wclrtoeol (hud);
	wrefresh (hud);
	
	return c;
}


/* Displays the help (in a created window and panel, for going back to the normal field after) */
void Help () {
	curs_set (0);	// don't display the cursor, pliz

	show_panel (helpPanel);
// writes the help window, wait for some key to be pressed and delete the help window
	update_panels ();
	doupdate ();
	getch ();
	
	hide_panel (helpPanel);
	doupdate ();
	
	curs_set (1);	// and back with the cursor
}


int Menu () {
	// display the menu
	show_panel (menuPanel);
	update_panels ();
	doupdate ();
	
	// get the chosen option
	int c = GetChosenOption (menu);

	hide_panel (menuPanel);
	doupdate ();

	return c;
}


int GetChosenOption (MENU *menu) {
	int c;
	
	menu_driver (menu, REQ_FIRST_ITEM);
	wrefresh (menuWindow);
	// drives through the menu options
	while (c != ' ') {
		c = getch ();
		switch (c) {
			case ' ':
				break;

			case KEY_F(10):
				return 0;

			case KEY_DOWN:
				menu_driver (menu, REQ_DOWN_ITEM);
				break;

			case KEY_UP:
				menu_driver (menu, REQ_UP_ITEM);
				break;
				
			case KEY_HOME:
				menu_driver (menu, REQ_FIRST_ITEM);
				break;
				
			case KEY_END:
				menu_driver (menu, REQ_LAST_ITEM);
				break;

			default:
				if (menu_driver (menu, c) == E_NO_MATCH)
					menu_driver (menu, REQ_LAST_ITEM);
				c = ' ';
		}
		// refreshes the menu window
		wrefresh (menu_win (menu));
	}
	
	return *(int*) (item_userptr (current_item (menu)));
}


int AttrTable (MOSIMG *current, Cursor cur) {
	WINDOW *table;
	PANEL *up;

	table = newwin (12, HELP_WIDTH, 0, 0);
	up = new_panel (table);
	update_panels ();
	doupdate ();
	
	//box (table, 0, 0);
	wbkgd (table, COLOR_PAIR (BkW));
	wrefresh (table);
	
	getch ();

	werase (table);
	wrefresh (table);
	del_panel (up);
	delwin (table);
	
	return 0;
}


PANEL *CreateBoxedTitledWindow (int nlines, int ncols, int begin_y, int begin_x, const char *title) {
	WINDOW *win = newwin (nlines, ncols, begin_y, begin_x);
	PANEL *panel = new_panel (win);

	box (win, 0, 0);
	
	int length = strlen (title);
	int title_begin = (ncols - length)/2;
	mvwaddstr (win, 0, title_begin, title);
	mvwaddch (win, 0, title_begin - 1, ' ');
	mvwaddch (win, 0, title_begin + length, ' ');
	
	return panel;
}


void DeletePanel (PANEL *pan) {
	WINDOW *win = panel_window (pan);
	
	werase (win);
	wrefresh (win);
	del_panel (pan);
	delwin (win);
}


void DestroyWins () {
// HELP
	if (helpPanel != NULL)
		DeletePanel (helpPanel);
	
// MENU
	if (menu != NULL) {
		unpost_menu (menu);
		free_menu (menu);

		int i;
		ITEM **items = menu_items (menu);
		for (i = 0; i < item_count (menu); i++)
			free_item (items[i]);
		free (items);
		
		DeletePanel (menuPanel);
	}
}
