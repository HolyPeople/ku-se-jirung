#include <stdio.h>
#include "conio.h"
#include "modeController.h"

void modeController() {

	currentTime = autoIncreaseTime(currentTime);

}

Time* autoIncreaseTime(Time* currentTime) {
	
	static clock_t p_clock = 0;
	clock_t c_clock = clock();
	time_t t = mktime(currentTime);

	if (c_clock - p_clock >= CLOCKS_PER_SEC) {
		/* In One Second */
		t++; /* Increae one second */
		p_clock = clock(); /* Assign current clock to p_clock */
		
		gotoxy(0, 0);
		printf("%llu", t);
		printf("    %d, %d, %d, %d:%d:%d \r\n",
				currentTime->tm_year + 1900,
				currentTime->tm_mon + 1,
				currentTime->tm_mday,
				currentTime->tm_hour,
				currentTime->tm_min,
				currentTime->tm_sec
				);
	}

	return localtime(&t);
}	
