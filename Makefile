all:
	g++ -o curses curses.cpp -lncurses
	./curses testmap

clean:
	rm -f curses