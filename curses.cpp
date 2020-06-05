#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstring>
#include <vector>
#include <ncurses.h>
#include <unistd.h>

using namespace std;

<<<<<<< HEAD:curses.cpp
int readFileInts(const char filename[], int value) {

    fstream saveFile(filename, std::ios_base::in);

    int a;
    int i = 0;
	vector<int> savedVars;

    for(i != a; saveFile >> a; i++)									// Tbh I didnt expect this to work on first try at all but it works :)!
        savedVars.insert(savedVars.begin() + i, i+1, a);			// Add values to vector

    return savedVars[value];										// Return requested integer only

}

// Function used for "jumping" mechanism. Basically a copy of the "move" mechanism in the main function.
=======
// Function used for "jumping" mechanism basically a copy of the "move" mechanism in the main function
>>>>>>> 94f4a725257c6faa8d75c72a7346a9577e5a46ea:curses.c
// except that this returns CurPosY and CurPosX and sets the Character at that position.
// More of a teleport right now.
void jump(int CurPosY, int CurPosX, int MaxY, int MaxX, int JmpPos[], FILE *map) {

	int PtrPosY = CurPosY;
	int PtrPosX = CurPosX;
	int Destination = 0;
<<<<<<< HEAD:curses.cpp
	char readFile;
=======
>>>>>>> 94f4a725257c6faa8d75c72a7346a9577e5a46ea:curses.c

	while(Destination != 10) {				// While input is not enter key

		clear();
		refresh();
		while((readFile=fgetc(map)) != EOF)
			printw("%c", readFile);
		fseek(map, 0, SEEK_SET);
		mvprintw(MaxY - 2, 0, "%dy %dx\n^%dy %dx", CurPosY, CurPosX, PtrPosY, PtrPosX);
		mvprintw(CurPosY, CurPosX, "@");
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

void clearscr() {

<<<<<<< HEAD:curses.cpp
	cout << "\e[1;1H\e[2J";
=======
	printf("\e[1;1H\e[2J");
>>>>>>> 94f4a725257c6faa8d75c72a7346a9577e5a46ea:curses.c

}

// Very primitive save function but good enough for a start. Writes Variables from savedVars array into file.
<<<<<<< HEAD:curses.cpp
void save(char savedVars[]) {
=======
void save(int save, char savedVars[]) {
>>>>>>> 94f4a725257c6faa8d75c72a7346a9577e5a46ea:curses.c

	clear();
	FILE *savefile;

	savefile = fopen("curses.sav", "w");
	printw("Saving.\n");
	fprintf(savefile, "%d\n%d", savedVars[0], savedVars[1]);
	fclose(savefile);


<<<<<<< HEAD:curses.cpp
}
=======
		printw("Loading.\n");
		//int Y = readFile("curses.sav", 0);
		//int X = readFile("curses.sav", 1);
		//printw("%d\n%d\n", Y, X);
		getch();
>>>>>>> 94f4a725257c6faa8d75c72a7346a9577e5a46ea:curses.c

int main(int argc, char *argv[]) {

	int Alive = 1;
	int MaxY;														// Maximum Screen Height
	int MaxX;														// Maximum Screen Width
	int JmpPos[2];													// Initializes Array used in jump function (0 = Y, 1 = X)
	char command[20];												// Used for VIM-like Commands
	char savedVars[2];												// Used for storing variables that are saved when calling save() function (Only positions currently)
	char mapFile[80];												// Used for getting maps (any format should work)
	FILE *map;														// Used for storing maps
	char readFile;													// Used for displaying maps;

<<<<<<< HEAD:curses.cpp
=======
int main() {

>>>>>>> 94f4a725257c6faa8d75c72a7346a9577e5a46ea:curses.c
	clearscr();
	cout << "\033[38;5;196mC\033[38;5;208mu\033[38;5;226mr\033[38;5;118ms\033[38;5;46me\033[38;5;48ms\n";
	sleep(1);

	initscr();
	cbreak();
	curs_set(0);
	getmaxyx(stdscr, MaxY, MaxX);
	int HalfY = MaxY / 2;
	int HalfX = MaxX / 2;
<<<<<<< HEAD:curses.cpp

	int CurPosY = readFileInts("curses.sav", 0);			// Stores horizontal cursor position
	int CurPosX = readFileInts("curses.sav", 1);			// Stores vertical cursor position

	if(CurPosY >= MaxY)
		CurPosY /= 2;
	if(CurPosX >= MaxX)
		CurPosX /= 2;


=======
	int CurPosY = 0;										// Stores horizontal cursor position
	int CurPosX = 0;										// Stores vertical cursor position
>>>>>>> 94f4a725257c6faa8d75c72a7346a9577e5a46ea:curses.c
	keypad(stdscr, TRUE);

	printw("This game is supposed to be played on standard 24x80 terminals\nthough most stuff still works in bigger terminals\n");
	printw("This game also makes partial use of vim-like keybindings\nuse :help for a list\n");
	printw("\nScreensize: %dy %dx\n", MaxY, MaxX);
	printw("Saved Positions: %dy %dx\n", CurPosY, CurPosX);
	printw("\nMap: ");
	scanw("%s", &mapFile);
<<<<<<< HEAD:curses.cpp
=======

	if((map = fopen(mapFile, "r")) != NULL) {							// Check if File exists to prevent Segfaults
		;
    } else
    	map = fopen("testmap", "r");

	clear();
	refresh();
	while(Alive) {
>>>>>>> 94f4a725257c6faa8d75c72a7346a9577e5a46ea:curses.c

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
		mvprintw(CurPosY, CurPosX, "@");
		savedVars[0] = CurPosY;
		savedVars[1] = CurPosX;

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
			jump(CurPosY, CurPosX, MaxY, MaxX, JmpPos, map);
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
			scanw("%s", &command);
			if(strcmp("w", command) == 0) {
				clear();
				save(savedVars);
				*command = ' ';
				getch();
			} else if(strcmp("q", command) == 0) {
				clear();
				endwin();
				clearscr();
				return 0;
			} else if(strcmp("wq", command) == 0) {
				clear();
				save(savedVars);
				endwin();
				clearscr();
				return 0;
			} else if(strcmp("curpos", command) == 0) {
				printw("%dy %dx", CurPosY, CurPosX);
				*command = ' ';
				getch();
			} else if(strcmp("help", command) == 0) {

				clear();
				mvprintw(0, (MaxX - strlen("VIM-Like keybindings - Help")) / 2, "VIM-Like keybindings - Help");
				mvprintw(1, (MaxX - strlen("===========================")) / 2, "===========================");
				mvprintw(3, 0, "help - Shows this page");
				mvprintw(4, 0, "curpos - Shows current Position of the Character");
				mvprintw(5, 0, "w - Saves game without exiting");
				mvprintw(6, 0, "q - Exits game without saving");
				mvprintw(7, 0, "wq - Saves and exits game");
				mvprintw(MaxY - 1, (MaxX - strlen("For game keybindings press h")) / 2, "For game keybindings press h");
				*command = ' ';
				getch();

			} else {
				*command = ' ';
				continue;
			}

		} else
			continue;

<<<<<<< HEAD:curses.cpp
    }


	printw("Presumably you died. The End.\n");
	getch();
	endwin();
	cout << "Map played: " << mapFile << endl;
	return 0;

}
=======
	}

	clearscr();
	printw("Presumably you died. The End.\n");
	getch();
	endwin();

}
>>>>>>> 94f4a725257c6faa8d75c72a7346a9577e5a46ea:curses.c
