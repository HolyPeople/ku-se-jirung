#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

typedef enum _BUTTON {
	NONE = 0, A, B, C, D
}BUTTON;

struct termios orig_termios;

void reset_terminal_mode();
void set_conio_terminal_mode();
int kbhit();
int getch();
int getKey();
BUTTON pushedButtonDector();
