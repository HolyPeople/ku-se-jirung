#include <stdio.h>
#include <stdlib.h>

#include "conio.h"
#include "modeController.h"

/* GLOBAL */
MODE mode = TK_MODE;
BUTTON btn = NONE;

/* main function */
int main(int argc, char *argv[]) {	
	time_t init_time = 1546268400; /* 2019.01.01 00:00:00 */
	currentTime = localtime(&init_time); 
    
	Time alarmTime = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        BOOL alarmSet = FALSE;

	MODE mode = TK_MODE;


	system("clear");

	set_conio_terminal_mode();
	while (1) {
		if ( btn = pushedButtonDector())
			printf("%d\r\n", btn);
		modeController( );
	}
}
