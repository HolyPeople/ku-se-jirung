#include <stdio.h>
#include <stdlib.h>

#include "conio.h"
#include "modeController.h"

/* main function */
int main(int argc, char *argv[]) {	
	time_t init_time = 1546268400; /* 2019.01.01 00:00:00 */
	currentTime = localtime(&init_time); 
	int key = 0;
    
	system("clear");

	set_conio_terminal_mode();
	while (1) {
		if (key = pushedButtonDector())
			printf("%d\r\n", key);
		modeController();
	}
}
