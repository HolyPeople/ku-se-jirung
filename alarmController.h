#include <stdio.h>
#include <time.h>

#pragma once





struct tm_alarm {
	int tm_min;
	int tm_hour;
	int tm_second;

}AlarmTime;

int isRingAlarm;
unsigned int ringTime;
int trigger;


void ringOff();


void* ringAlarm(void* arg);

int check_Alarm_Time();





int alarmController( );
