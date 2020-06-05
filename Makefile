all:
	g++ -o curses curses.cpp -lncurses
	./curses curses.sav

clean:
	rm -f curses 
