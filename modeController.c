#include <stdio.h>
#include "conio.h"
#include "modeController.h"

extern MODE mode;

void modeController( Time* alarmTime, BOOL* alarmSet, sw_Time* swLap, BOOL* sw_isLap ) {

	currentTime = autoIncreaseTime(currentTime);

	if ( mode == TK_MODE )
		timekeeping_mode();
	else if ( mode == AL_MODE )
		alarm_mode();
	else
		stopwatch_mode();
}


Time* autoIncreaseTime(Time* currentTime) {
	
	static clock_t p_clock = 0;
	clock_t c_clock = clock();
	time_t t = mktime(currentTime);

	if (c_clock - p_clock >= CLOCKS_PER_SEC) {
		/* In One Second */
		t++; /* Increae one second */
		p_clock = clock(); /* Assign current clock to p_clock */
		
//		gotoxy(0, 0);
		printf("%lu", t);
		printf("    \033[4m%04d\033[0m, %02d, %02d, %02d:%02d:%02d \r\n",
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
