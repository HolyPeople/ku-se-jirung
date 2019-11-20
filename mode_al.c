#include "conio.h"
#include "modeController.h"

/* GLOBAL */

extern MODE mode;
extern BUTTON btn;
extern pthread_t sw_thread;
Time al_time;			// global for display
BOOL al_isSet;		// global for display
AL_CH al_toChange;		// global for display
BOOL al_isSetting;		// global for display
extern int back_lighting;
extern int light;

/* FUNCTION */

void alarm_onoff() {
	// al_isSet: is alarm setted?

	al_isSet = (al_isSet + 1 ) % 2;
/*XXX*/ //printf( "alarm_onoff(): al_isSet=%d\r\n", al_isSet );
}

void switch_setting_alarm_time() {
	// toChange: select what to change
	// Hour -> Minute -> Hour
	// return: selected


	al_toChange = ( al_toChange + 1 ) % 2;
/*XXX*/ //printf( "switch_setting_alarm_time(): tochange=%d\r\n", al_toChange );
}

void increase_alarm_time() {
	// alarm: Alarm Time STORAGE
	// toChange: what to change

	switch( al_toChange ) {
		case AL_HOUR:
			al_time.tm_hour = ( al_time.tm_hour + 1 ) % 24;
			break;
		case AL_MIN:
			al_time.tm_min = ( al_time.tm_min + 1 ) % 60;
			break;
	}
/*XXX*/ //printf( "increase_alarm_time(): Alarm=%d:%d\r\n", al_time.tm_hour, al_time.tm_min );
}

void display_al() {
	gotoxy(0, 0);
	printf("   -----------\r\n");
	printf("    %c[%dmAL %02d-%02d%c[0m \r\n", 27, light, currentTime->tm_mon + 1, currentTime->tm_mday, 27);
	printf("  -------------\r\n\r\n");
	if (al_isSet) {
		if (al_isSetting) {
			if (al_toChange == AL_HOUR) {
				printf("  *   %c[%d;4m%02d%c[%d;24m:%02d%c[0;0m     \r\n\r\n", 27, light, al_time.tm_hour, 27, light, al_time.tm_min, 27);
			}
			else printf("  *   %c[%d;24m%02d:%c[%d;4m%02d%c[0;0m     \r\n\r\n", 27, light, al_time.tm_hour, 27, light, al_time.tm_min, 27);
		}
		else printf("  *   %c[%dm%02d:%02d%c[0m     \r\n\r\n", 27, light, al_time.tm_hour, al_time.tm_min, 27);
}
	else {
		if (al_isSetting) {
			if (al_toChange == AL_HOUR) {
				printf("      %c[%d;4m%02d%c[%d;24m:%02d%c[0;0m     \r\n\r\n", 27, light, al_time.tm_hour, 27, light, al_time.tm_min, 27);
			}
			else printf("      %c[%d;24m%02d:%c[%d;4m%02d%c[0;0m     \r\n\r\n", 27, light, al_time.tm_hour, 27, light, al_time.tm_min, 27);
		}
		else printf("      %c[%dm%02d:%02d%c[0m     \r\n\r\n", 27, light, al_time.tm_hour, al_time.tm_min, 27);
	}
	printf("   -----------\r\n");
}

// if BUTTON-C pressed in TIME KEEPING MODE,	become ALARM MODE
// XXX DISPLAY PROCESS 2.2.13: Alarm

// XXX ASSUMPTION: BUTTON btn; MODE mode; are global
void alarm_mode() {
	// alarm: Alarm Time STORAGE
	// al_isSet: is alarm setted?

	if ( mode != AL_MODE ) {
/*XXX*/ //printf( "alarm_mode(): Not Alarm Mode - RETURN\r\n" );
		return;
	}

	if (back_lighting == 1) light = 33;
	else light = 0;
	display_al();

	if ( al_isSetting == FALSE ) {
		// if BUTTON-C pressed in ALARM MODE,	goto STOPWATCH MODE
		if ( btn == C ) {
	                mode = ( mode + 1 ) % 3;
			pthread_create( &sw_thread, NULL, sw_increase, NULL );
/*XXX*/ //printf( "alarm_mode(): Mode Change - SW; RETURN\r\n" );
			btn = NONE;
        	        return;
        	}

		// if BUTTON-B pressed in ALARM MODE,	XXX PROCESS 2.2.16: Alarm On/Off XXX
		if ( btn == B ) {
			alarm_onoff();
		}

		// if BUTTON-A pressed in ALARM MODE,	become ALARM SETTING MODE
		if ( btn == A ) {
			al_isSetting = ( al_isSetting + 1 ) % 2;
			al_toChange = AL_HOUR;
/*XXX*/ //printf( "alarm_mode(): ALARM SETTING MODE BEGIN; toChange=%d\r\n", al_toChange );
		}
		// XXX DISPLAY - PROCESS 2.2.12: Alarm Setting ( toChange )
	}

	/************************
	 * △ Alarm Mode         *
	 * ▽ Alarm Setting Mode *
	 ************************/

	else {
		// if BUTTON-C pressed in ALARM SETTING MODE,	XXX PROCESS 2.2.14: Switch Setting Alarm Time XXX
		if ( btn == C )	{
			switch_setting_alarm_time();
		}

		// if BUTTON-B pressed in ALARM SETTING MODE,	XXX PROCESS 2.2.15: Increase Alarm Time XXX
		if ( btn == B )	{
			increase_alarm_time();
		}

		// if BUTTON-A pressed in ALARM SETTING MODE,	become ALARM MODE
		if ( btn == A ) {
			al_isSetting = ( al_isSetting + 1 ) % 2;
			// XXX DISPLAY PROCESS 2.2.13: Alarm
/*XXX*/ //printf( "alarm_mode(): ALARM MODE BEGIN\r\n" );
		}
	}

	btn = NONE;
}
