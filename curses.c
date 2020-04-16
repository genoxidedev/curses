#include <ncurses.h>
#include <string.h>

int main() {

	int Alive = 1;
	int MaxY;
	int MaxX;
	char *command;
	initscr();
	cbreak();
	curs_set(0);
	getmaxyx(stdscr, MaxY, MaxX);
	int HalfY = MaxY / 2;
	int HalfX = MaxX / 2;
	int CurposY = HalfY;
	int CurposX = HalfX;
	keypad(stdscr, TRUE);

	printw("This game is supposed to be played on standard 24x80 terminals\nthough basic stuff still works in bigger terminals\n");
	printw("This game also makes partial use of vim-like keybindings\nuse :help for a list\n");
	printw("\nScreensize: %dy %dx\n", MaxY, MaxX);
	getch();
	clear();
	refresh();
	while(Alive) {

		getmaxyx(stdscr, MaxY, MaxX);
		HalfY = MaxY / 2;
		HalfX = MaxX / 2;
		clear();
		refresh();
		noecho();
		printw("%dy %dx\n", CurposY, CurposX);
		mvprintw(CurposY, CurposX, "@");
		
		int Action = getch();
		if(Action == KEY_LEFT) {							// Key: left arrow, decreases x pos by 1
			CurposX -= 1;
			if(CurposX <= -1)								// This makes the character go to the other side of the screen when he hits the "wall"
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
		} else if(Action == 58) {							// Key: ':', vim like commands
			mvprintw(MaxY - 1, 0, ":");
			echo();
			getstr(command);
			if(strcmp("q", command) == 0) {
				clear();
				endwin();
				return 0;
			} else if(strcmp("help", command) == 0) {
				clear();
				mvprintw(0, (MaxX - strlen("VIM-Like keybindings - Help")) / 2, "VIM-Like keybindings - Help");
				mvprintw(1, (MaxX - strlen("===========================")) / 2, "===========================");
				mvprintw(3, 0, "help - shows this page");
				mvprintw(4, 0, "q - Exits game without any messages");
				mvprintw(MaxY - 1, (MaxX - strlen("For game keybindings press h")) / 2, "For game keybindings press h");
				getch();
			} else
				continue;

		} else if(Action == 410) {							// Key: back key (android, termux)
			clear();
			printw("Why not play this on your pc instead of your phone\n");
			getch();
			continue;

		} else
			continue;

	}
	
	clear();
	printw("Presumably you died. The End.\n");
	getch();
	endwin();
	
}
