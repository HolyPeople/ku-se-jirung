#include <stdio.h>
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
		printf("%llu\r\n", t);
	}

	return localtime(&t);
}	
