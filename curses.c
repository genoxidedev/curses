#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


// Reads a specific line of a file, still returns wrong numbers so not in use currently
int readLine(char fileName[], int lineNumber) {

	FILE *file = fopen(fileName, "r");
	int count = 0;
    char line[256];
    while(fgets(line, sizeof(line), file) != NULL) {

        if(count == lineNumber) {
			char *test = NULL;
            printf("%s\n", line);
			printf("%ld\n", strtol(line, &test, 10));
        } else {
            count++;
        }

    }
	fclose(file);
	return atoi(line);

}

// Function used for "jumping" mechanism basically a copy of the "move" mechanism in the main function
// except that this returns CurPosY and CurPosX and sets the Character at that position.
void jump(int CurPosY, int CurPosX, int MaxY, int MaxX, int JmpPos[]) {

	int PtrPosY = CurPosY;
	int PtrPosX = CurPosX;
	int Destination;

	while(Destination != 10) {				// While input is not enter key

		clear();
		refresh();
		printw("%dy %dx\n^%dy %dx", CurPosY, CurPosX, PtrPosY, PtrPosX);
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
	
	printf("\e[1;1H\e[2J");

}

// Very primitive save function but good enough for a start. Writes Variables from savedVars array into file.
void save(int save, char savedVars[]) {
	
	clear();
	FILE *savefile;

	if(save == 1) {

		savefile = fopen("curses.sav", "w");
		printw("Saving.\n");
		fprintf(savefile, "%d\n%d", savedVars[0], savedVars[1]);
		fclose(savefile);

	} else if(save == 0) {

		printw("Loading.\n");
		int Y = readLine("curses.sav", 0);
		int X = readLine("curses.sav", 1);
		printw("%d\n%d\n", Y, X);
		getch();

	}

}

int main() {
	
	clearscr();
	printf("\033[38;5;196mC\033[38;5;208mu\033[38;5;226mr\033[38;5;118ms\033[38;5;46me\033[38;5;48ms\n");
	sleep(1);

	int Alive = 1;											// If this is 0 the program ends
	int MaxY;												// Maximum Screen Height
	int MaxX;												// Maximum Screen Width
	int JmpPos[2];											// Initializes Array used in jump function (0 = Y, 1 = X)
	char command[20];										// Used for VIM-like Commands
	char savedVars[2];										// Used for storing variables that are saved when calling save() function (Only positions currently)
	char mapFile[80];										// Used for getting maps (any format should work)
	FILE *map;												// Used for storing maps
	char readFile;											// Used for displaying maps
	initscr();
	cbreak();
	curs_set(0);
	getmaxyx(stdscr, MaxY, MaxX);
	int HalfY = MaxY / 2;
	int HalfX = MaxX / 2;
	int CurPosY = HalfY;
	int CurPosX = HalfX;
	keypad(stdscr, TRUE);

	printw("This game is supposed to be played on standard 24x80 terminals\nthough most stuff still works in bigger terminals\n");
	printw("This game also makes partial use of vim-like keybindings\nuse :help for a list\n");
	printw("\nScreensize: %dy %dx\n", MaxY, MaxX);
	printw("\nMap: ");
	scanw("%s", &mapFile);
	map = fopen(mapFile, "r");
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
			scanw("%s", &command);
			if(strcmp("w", command) == 0) {
				clear();
				save(1, savedVars);
				*command = ' ';
				getch();
			} else if(strcmp("q", command) == 0) {
				clear();
				endwin();
				clearscr();
				return 0;
			} else if(strcmp("wq", command) == 0) {
				clear();
				save(1, savedVars);
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

		} else if(Action == 410) {							// Key: back key (android, termux), also resize in console window (windows, cygwin64)
			
			if(getenv("ANDROID_ROOT") == NULL && getenv("ANDROID_DATA") == NULL)
				continue;
			clear();
			printw("Why not play this on your PC instead of your phone\n");
			printw("Or anything that has a physical keyboard\n");
			getch();
			continue;

		} else
			continue;

	}
	
	clearscr();
	printw("Presumably you died. The End.\n");
	getch();
	endwin();
	
}
