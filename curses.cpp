#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstring>
#include <vector>
#include <ncurses.h>
#include <unistd.h>

using namespace std;

// Reads integers from given file and returns the requested Integer
int readFileInts(const char filename[], int requestedInt) {

    fstream saveFile(filename, ios_base::in);

    int a;
    int i = 0;
	vector<int> savedVars;

    for(i != a; saveFile >> a; i++)									// Tbh I didnt expect this to work on first try at all but it works :)!
        savedVars.insert(savedVars.begin() + i, i+1, a);			// Add values to vector

    return savedVars[requestedInt];									// Return requested integer only

}

// Function used for "jumping" mechanism. Basically a copy of the "move" mechanism in the main function.
// except that this returns CurPosY and CurPosX and sets the Character at that position.
// More of a teleport right now.
void jump(int CurPos[], int MaxY, int MaxX, int JmpPos[], FILE *map) {

	int PtrPosY = CurPos[0];
	int PtrPosX = CurPos[1];
	int Destination = 0;
	char readFile;

	while(Destination != 10) {				// While input is not enter key

		clear();
		refresh();
		while((readFile=fgetc(map)) != EOF)
			printw("%c", readFile);
		fseek(map, 0, SEEK_SET);
		mvprintw(MaxY - 2, 0, "%dy %dx\n^%dy %dx", CurPos[0], CurPos[1], PtrPosY, PtrPosX);
		mvprintw(CurPos[0], CurPos[1], "@");
		mvprintw(PtrPosY - 1, PtrPosX, "|");
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

}

// Clears default terminal (The one that you started curses with)
void clearscr() {

	cout << "\e[1;1H\e[2J";

}



// Very primitive save function but good enough for a start. Writes Variables from savedVars array into file.
void save(char savedVars[]) {

	FILE *savefile;

	savefile = fopen("curses.sav", "w");
	fprintf(savefile, "%d\n%d", savedVars[0], savedVars[1]);
	fclose(savefile);
	printw("Saved");


}

int vim(char *command, char savedVars[], int CurPos[]) {

	int MaxY;
	int MaxX;
	getmaxyx(stdscr, MaxY, MaxX);

	char loadValues[20];

	if(strcmp("w", command) == 0) {
		save(savedVars);
		getch();
	} else if(strcmp("q", command) == 0) {
		clear();
		endwin();
		clearscr();
		return 69;
	} else if(strcmp("q!", command) == 0) {
		exit(0);
	} else if(strcmp("wq", command) == 0) {
		clear();
		save(savedVars);
		endwin();
		clearscr();
		return 69;
	} else if(strcmp("curpos", command) == 0) {
		printw("%dy %dx", CurPos[0], CurPos[1]);
		getch();
	} else if(strcmp("savedVars", command) == 0) {				// This looks so bad

		clear();
		mvprintw(0, (MaxX - strlen("Saved Variables in curses.sav")) / 2, "Saved Variables in curses.sav");
		mvprintw(1, (MaxX - strlen("=============================")) / 2, "=============================");
		mvprintw(2, 0, "Value      |	Saved value(s)	  |	Current value(s)");
		mvprintw(3, 0, "-----------------------------------------------------------");

		mvprintw(4, 0, "CurPos 	   |                      |");
		mvprintw(4, 20, "%dy %dx", readFileInts("curses.sav", 0), readFileInts("curses.sav", 1));
		mvprintw(4, 44, "%dy %dx", CurPos[0], CurPos[1]);

		mvprintw(MaxY - 2, (MaxX - strlen("Load a Value?[y/n] ")) / 2, "Load a Value?[y/n] ");
		int loadValue = getch();
		if(loadValue == 121) {

			mvprintw(MaxY - 1, (MaxX - strlen("Which Value? ")) / 2, "Which Value? ");
			scanw("%s", &loadValues);
			if(strcmp("CurPos", loadValues) == 0) {
				CurPos[0] = readFileInts("curses.sav", 0);
				CurPos[1] = readFileInts("curses.sav", 1);
			} else
				;

		} else
			;

	} else if(strcmp("help", command) == 0) {

		clear();
		mvprintw(0, (MaxX - strlen("VIM-Like keybindings - Help")) / 2, "VIM-Like keybindings - Help");
		mvprintw(1, (MaxX - strlen("===========================")) / 2, "===========================");
		mvprintw(3, 0, "help - Shows this page");
		mvprintw(4, 0, "curpos - Shows current Position of the Character");
		mvprintw(5, 0, "savedVars - Shows all saved Values / Variables (can also load Values)");
		mvprintw(6, 0, "w - Saves game without exiting");
		mvprintw(7, 0, "q - Exits game without saving");
		mvprintw(8, 0, "q! - Exits game without cleanup / stack unwinding (use only when necessary!)");
		mvprintw(9, 0, "wq - Saves and exits game");
		mvprintw(MaxY - 1, (MaxX - strlen("For game keybindings press h")) / 2, "For game keybindings press h");
		getch();

	}

	return 0;

}

int main(int argc, char *argv[]) {

	int Alive = 1;
	int MaxY;														// Maximum Screen Height
	int MaxX;														// Maximum Screen Width
	int JmpPos[2];													// Initializes Array used in jump function (0 = Y, 1 = X)
	int CurPos[2];													// Stores Positions of Cursor (0 = Y, 1 = X)

	char command[20];												// Used for VIM-like Commands
	char savedVars[2];												// Used for storing variables that are saved when calling save() function (Only positions currently)
	char mapFile[80];												// Used for getting maps (any format should work)
	char readFile;													// Used for displaying maps;

	FILE *map;														// Used for storing maps

	clearscr();
	cout << "\033[38;5;196mC\033[38;5;208mu\033[38;5;226mr\033[38;5;118ms\033[38;5;46me\033[38;5;48ms\n";
	sleep(1);

	initscr();
	cbreak();
	curs_set(0);
	getmaxyx(stdscr, MaxY, MaxX);
	int HalfY = MaxY / 2;
	int HalfX = MaxX / 2;

	CurPos[0] = readFileInts("curses.sav", 0);			// Stores horizontal cursor position
	CurPos[1] = readFileInts("curses.sav", 1);			// Stores vertical cursor position

	if(CurPos[0] >= MaxY)
		CurPos[0] /= 2;
	if(CurPos[1] >= MaxX)
		CurPos[1] /= 2;


	keypad(stdscr, TRUE);

	printw("This game is supposed to be played on standard 24x80 terminals\nthough most stuff still works in bigger terminals\n");
	printw("This game also makes partial use of vim-like keybindings\nuse :help for a list\n");
	printw("\nScreensize: %dy %dx\n", MaxY, MaxX);
	printw("Saved Positions: %dy %dx\n", CurPos[0], CurPos[1]);
	printw("\nMap: ");
	scanw("%s", &mapFile);

	if((map = fopen(mapFile, "r")) != NULL)					// Check if File exists to prevent Segfaults
		;
    else
    	map = fopen("testmap", "r");

    clear();
    refresh();

    while(Alive) {

    	getmaxyx(stdscr, MaxY, MaxX);
		HalfY = MaxY / 2;
		HalfX = MaxX / 2;
		clear();
		refresh();
		noecho();
		while((readFile=fgetc(map)) != EOF)
			printw("%c", readFile);
		fseek(map, 0, SEEK_SET);
		mvprintw(CurPos[0], CurPos[1], "@");
		savedVars[0] = CurPos[0];
		savedVars[1] = CurPos[1];

		int Action = getch();
		if(Action == KEY_LEFT) {							// Key: left arrow, decreases x pos by 1
			CurPos[1] -= 1;
			if(CurPos[1] <= -1)								// This makes the character go to the other side of the screen when he hits the "wall"
				CurPos[1] += MaxX;
			continue;
		} else if(Action == KEY_RIGHT) {					// Key: right arrow, increases x pos by 1
			CurPos[1] += 1;
			if(CurPos[1] >= MaxX)
				CurPos[1] -= MaxX;
			continue;
		} else if(Action == KEY_DOWN) {						// Key: down arrow, decreases y pos by 1
			CurPos[0] += 1;
			if(CurPos[0] >= MaxY)
				CurPos[0] -= MaxY;
			continue;
		} else if(Action == KEY_UP) {						// Key: up arrow, increases y pos by 1
			CurPos[0] -= 1;
			if(CurPos[0] <= -1)
				CurPos[0] += MaxY;
			continue;
		} else if(Action == ' ') {
			jump(CurPos, MaxY, MaxX, JmpPos, map);
			CurPos[0] = JmpPos[0];
			CurPos[1] = JmpPos[1];
			continue;
		} else if(Action == 114) {							// Key: r, to reset character position to middle of screen
			CurPos[0] = HalfY;
			CurPos[1] = HalfX;
			continue;
		} else if(Action == 104) {

			clear();
			mvprintw(0, (MaxX - strlen("Keybindings")) / 2, "Keybindings");
			mvprintw(1, (MaxX - strlen("===========")) / 2, "===========");
			mvprintw(3, 0, "' ' - Initiates Jump Function");
			mvprintw(4, 0, "r - Resets Cursor to center of terminal");
			mvprintw(5, 0, ": - Opens up prompt for Vim like commands");
			mvprintw(MaxY - 1, (MaxX - strlen("Press any button to continue.")) / 2, "Press any button to continue.");
			getch();

		} else if(Action == 58) {							// Key: ':', vim like commands

			mvprintw(MaxY - 1, 0, ":");
			echo();
			scanw("%s", &command);
			if(vim(command, savedVars, CurPos) == 69)
				return 0;
			memset(command, 0, 20);

		} else
			continue;

    }

	printw("Presumably you died. The End.\n");
	getch();
	endwin();
	cout << "Map played: " << mapFile << endl;
	return 0;

}