#include <ncurses.h>
#include <string.h>
#include <stdlib.h>


// Function used for "jumping" mechanism basically a copy of the "move" mechanism in the main function
// except that this returns CurPosY and CurPosX and sets the Character at that position.
// Will expand this later with limitations if this game ever becomes something playable (a game)
// so you can't jump infinitely and stuff.
// I am currently realizing how fucked up returning multiple values is. Kinda missing C# right now.
// Forget that last sentence I figured it out. I am now in love with Arrays.
int jump(int CurPosY, int CurPosX, int MaxY, int MaxX, int JmpPos[]) {

	int PtrPosY = CurPosY;
	int PtrPosX = CurPosX;
	int Destination = 1;

	while(Destination != 10) {

		clear();
		refresh();
		printw("%dy %dx\n^%dy %dx", CurPosY, CurPosX, PtrPosY, PtrPosX);
		mvprintw(CurPosY, CurPosX, "@");
		mvprintw(PtrPosY, PtrPosX, "V");
		Destination = getch();

		if(Destination == KEY_LEFT) {
			PtrPosX -= 1;
			if(PtrPosX <= -1)
				PtrPosX += MaxX;
		} else if(Destination == KEY_RIGHT) {
			PtrPosX += 1;
			if(PtrPosX >= MaxX)
				PtrPosX -= MaxX;
		} else if(Destination == KEY_DOWN) {
			PtrPosY += 1;
			if(PtrPosY >= MaxY)
				PtrPosY -= MaxY;
		} else if(Destination == KEY_UP) {
			PtrPosY -= 1;
			if(PtrPosY <= -1)
				PtrPosY += MaxY;
		}

	}
	JmpPos[0] = PtrPosY;
	JmpPos[1] = PtrPosX;

	return 0;

}

int main() {

	int Alive = 1;											// If this is 0 the program ends
	int MaxY;												// Maximum Screen Height
	int MaxX;												// Maximum Screen Width
	int JmpPos[2];											// Initializes Array used in jump function (0 = Y, 1 = X)
	char *command;											// Used for VIM-like Commands
	initscr();
	cbreak();
	curs_set(0);
	getmaxyx(stdscr, MaxY, MaxX);
	int HalfY = MaxY / 2;
	int HalfX = MaxX / 2;
	int CurPosY = HalfY;
	int CurPosX = HalfX;
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
		printw("%dy %dx\n", CurPosY, CurPosX);
		mvprintw(CurPosY, CurPosX, "@");
		
		int Action = getch();
		if(Action == KEY_LEFT) {							// Key: left arrow, decreases x pos by 1
			CurPosX -= 1;
			if(CurPosX <= -1)								// This makes the character go to the other side of the screen when he hits the "wall"
				CurPosX += MaxX;
			continue;
		} else if(Action == KEY_RIGHT) {					// Key: right arrow, increases x pos by 1
			CurPosX += 1;
			if(CurPosX >= MaxX)
				CurPosX -= MaxX;
			continue;
		} else if(Action == KEY_DOWN) {						// Key: down arrow, decreases y pos by 1
			CurPosY += 1;
			if(CurPosY >= MaxY)
				CurPosY -= MaxY;
			continue;
		} else if(Action == KEY_UP) {						// Key: up arrow, increases y pos by 1
			CurPosY -= 1;
			if(CurPosY <= -1)
				CurPosY += MaxY;
			continue;
		} else if(Action == ' ') {
			jump(CurPosY, CurPosX, MaxY, MaxX, JmpPos);
			CurPosY = JmpPos[0];
			CurPosX = JmpPos[1];
			continue;
		} else if(Action == 114) {							// Key: r, to reset character position to middle of screen
			CurPosY = HalfY;
			CurPosX = HalfX;
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
