#include "conio.h"

void reset_terminal_mode() {
    tcsetattr(0, TCSANOW, &orig_termios);
}

void set_conio_terminal_mode() {
    struct termios new_termios;

    tcgetattr(0, &orig_termios);
    memcpy(&new_termios, &orig_termios, sizeof(new_termios));

    atexit(reset_terminal_mode);
    cfmakeraw(&new_termios);
    tcsetattr(0, TCSANOW, &new_termios);
}

int kbhit() {
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

int getch() {
    int r;
    unsigned char c;
    if ((r = read(0, &c, sizeof(c))) < 0) {
        return r;
    } else {
        return c;
    }
}


/* getKeyCode */
int getKey() {
	int ch = 0;
	if ((ch = getch()) == 0xE0)
		ch += getch();
	return ch;
}

int pushedButtonDector() {
	int key = 0;
	int res = 0;
	if(kbhit()) {
		key = getKey();
		if ('A' <= key && key <= 'D')
			res = key;
		else if ('a' <= key && key <= 'd')
			res = key - 32;
		else if (key == 27) /* ESC KEY INPUT */
			exit(0);
	}
	return res;
}

