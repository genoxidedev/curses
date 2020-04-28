# Curses
A small ASCII curses game I am programming for fun and also for learning C.

# Compilation
The game is written in C using the ncurses library all other
libraries should be included with gcc and clang.

The games code is written using Visual Studio Code.
I use(d) Cygwin64 and GCC for compiling.
Also tested compiling on Arch Linux with GCC.
The program should currently run on every machine that can run GCC and has a keyboard.
I haven't tested this on a 32bit machine yet though.
And I will not test this program on TempleOS.

A basic:
<code>gcc -o curses curses.c -lncurses</code>
should work well enough.
