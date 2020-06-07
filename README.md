# Curses
A small ASCII curses game I am programming for fun and also for learning C.
<br>Now in C++ because of reasons.

# Compilation
The game is written in C++ using the ncurses library. All other
libraries should be included with gcc and clang.
<br>The games code is written using Sublime Text 3.
<br>I use(d) Cygwin64 and GCC for compiling.
<br>Also tested compiling on Arch Linux with GCC.
<br>The program should currently run on every machine that can run GCC and has a keyboard I think.
<br>I haven't tested this on a 32bit machine yet though.
<br>Also probably won't work on MS-DOS.
<br>And I will not test this program on TempleOS.

A basic:
<br><code>g++ -o curses curses.c -lncurses</code>
<br>should work well enough.
<br>Though I do include a very simple Makefile so running <code>make</code> is sufficient.
