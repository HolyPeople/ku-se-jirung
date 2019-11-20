#include <stdio.h>
#include <time.h>

#pragma once

int isRingAlarm;


void ringOff();

void *ringAlarm(void* args);

int check_Alarm_Time();

int alarmController( );
