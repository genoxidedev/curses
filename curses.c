#include <ncurses.h>
#include <string.h>

int main() {

	int Alive = 1;
	int MaxY;
	int MaxX;
	initscr();
	curs_set(0);
	getmaxyx(stdscr, MaxY, MaxX);
	int HalfY = MaxY / 2;
	int HalfX = MaxX / 2;
	int CurposY = HalfY;
	int CurposX = HalfX;

	printw("Screensize: %dy %dx\n", MaxY, MaxX);
	getch();
	clear();
	refresh();
	keypad(stdscr, TRUE);
	while(Alive) {

		getmaxyx(stdscr, MaxY, MaxX);
		HalfY = MaxY / 2;
		HalfX = MaxX / 2;
		clear();
		refresh();
		printw("%dy %dx\n", CurposY, CurposX);
		mvprintw(CurposY, CurposX, "@");
		mvprintw(0, (MaxX - strlen("Press F12 to die.")) / 2, "Press F12 to die.");
		
		int Action = getch();
		if(Action == KEY_LEFT) {							// Key: left arrow, decreases x pos by 1
			CurposX -= 1;
			if(CurposX <= -1)
				CurposX += MaxX;
			continue;
		} else if(Action == KEY_RIGHT) {					// Key: right arrow, increases x pos by 1
			CurposX += 1;
			if(CurposX >= MaxX)
				CurposX -= MaxX;
			continue;
		} else if(Action == KEY_DOWN) {						// Key: down arrow, decreases y pos by 1
			CurposY += 1;
			if(CurposY >= MaxY)
				CurposY -= MaxY;
			continue;
		} else if(Action == KEY_UP) {						// Key: up arrow, increases y pos by 1
			CurposY -= 1;
			if(CurposY <= -1)
				CurposY += MaxY;
			continue;
		} else if(Action == 114) {							// Key: r, to reset character position to middle of screen
			CurposY = HalfY;
			CurposX = HalfX;
			continue;
		} else if(Action == 410) {							// Key: back key (android)
			clear();
			printw("Why not play this on your pc instead of your phone\n");
			getch();
		} else if(Action == KEY_F(12))						// Key: F12, kills character immediately, ending the game
			Alive = 0;
		else
			continue;

	}
	
	clear();
	printw("Presumably you died. The End.\n");
	getch();
	endwin();
	
}
