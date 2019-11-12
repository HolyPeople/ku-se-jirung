#include <stdio.h>
#include "conio.h"


/* main function */
int main(int argc, char *argv[])
{
	int key = 0;
    set_conio_terminal_mode();
	while (1) {
    	if (kbhit()) {
   			key = getKey();
			printf("%d\r\n", key);
			if (key == 'q')
				break;
		}
	}
}
