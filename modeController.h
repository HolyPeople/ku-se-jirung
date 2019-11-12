#pragma once
#include <time.h>
#include <stdlib.h>

typedef struct tm Time;
Time* currentTime;


void modeController();

Time* autoIncreaseTime(Time* currentTime);

