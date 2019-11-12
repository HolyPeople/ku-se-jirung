#include <stdio.h>
#include "conio.h"
#include "modeController.h"

/* main function */
int main(int argc, char *argv[]) {
	
	currentTime = (Time*)malloc(sizeof(Time));
	currentTime->tm_sec = 0;
	currentTime->tm_min = 0;
	currentTime->tm_hour = 0;
	currentTime->tm_mday = 0;
	currentTime->tm_mon = 1;
	currentTime->tm_year = 119;
	int key = 0;
    set_conio_terminal_mode();
	while (1) {
		if (key = pushedButtonDector())
			printf("%d\r\n", key);
		modeController();
	}
}
