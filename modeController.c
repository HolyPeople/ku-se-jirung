#include <stdio.h>
#include "conio.h"
#include "modeController.h"

extern MODE mode;

void modeController(  ) {

	currentTime = autoIncreaseTime(currentTime);
	if ( mode == TK_MODE )
		timekeeping_mode();
	else if ( mode == AL_MODE )
		alarm_mode();
	else
		stopwatch_mode();
}


Time* autoIncreaseTime(Time* currentTime) {
	
//	static clock_t p_clock = 0;
//	clock_t c_clock = clock();
	static struct timespec p_clock;
	struct timespec c_clock = { 0, 0 };
	
	static int start = 0;
	if ( start == 0 ) {
		clock_gettime( CLOCK_MONOTONIC, &p_clock );
        start = 1;
	}
	clock_gettime( CLOCK_MONOTONIC, &c_clock );

	time_t t = mktime(currentTime);

//	if (c_clock - p_clock >= CLOCKS_PER_SEC) {
	if ( ( c_clock.tv_sec * 1000000000 + c_clock.tv_nsec ) - ( p_clock.tv_sec * 1000000000 + p_clock.tv_nsec ) >= 1000000000 ) {
		/* In One Second */
		if (t == 4102412399)
		    t = 1546268399;
		t++; /* Increae one second */
//		p_clock = clock(); /* Assign current clock to p_clock */
		clock_gettime( CLOCK_MONOTONIC, &p_clock );

/*XXX*///gotoxy(0, 0);
/*XXX*///printf("%lu", t);
/*XXX*/
		printf("    \033[4m%04d\033[0m, %02d, %02d, %02d:%02d:%02d   %llu\r\n",
				currentTime->tm_year + 1900,
				currentTime->tm_mon + 1,
				currentTime->tm_mday,
				currentTime->tm_hour,
				currentTime->tm_min,
				currentTime->tm_sec,
				t
				);

	}

	return localtime(&t);
}	
