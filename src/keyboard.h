#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h> // for usleep
#endif

void sleep_ms(int milliseconds) { // cross-platform sleep function
#ifdef WIN32
	Sleep(milliseconds);
#else
	if (milliseconds >= 1000)
		sleep(milliseconds / 1000);
	usleep((milliseconds % 1000) * 1000);
#endif
}

#include <pthread.h> // Multithreading
#include <stdio.h>
#include <stdlib.h>  // for atexit()
#include <termios.h> // For changing terminal mode

struct termios original;

void enableRAWMode();
void disableRAWMode();

void enableRAWMode() {
	struct termios raw;
	tcgetattr(STDIN_FILENO, &raw); // Save the state of the terminal to struct raw
	// STDIN_FILENO is from <stdlib.h>
	// tcgetattr() from <termios.h>
	tcgetattr(STDIN_FILENO, &original);
	atexit(&disableRAWMode); // Revert to canonical mode when exiting the program
	// atext() from <stdlib.h>
	raw.c_lflag &=
		~(ECHO | ICANON); // Turn off canonical mode
	// Turn off ECHO mode so that keyboard is not
	// printing to terminal
	// ICANON and ECHO is bitflag. ~ is binary NOT operator

	tcsetattr(STDIN_FILENO, TCSAFLUSH,
		&raw); // Set the terminal to be in raw mode
	// tcsetattr() from <termios.h>
}

void disableRAWMode() {
	tcsetattr(STDIN_FILENO, TCSAFLUSH,
		&original); // Set terminal to original state
}