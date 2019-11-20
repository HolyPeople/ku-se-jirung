#include "conio.h"
#include "modeController.h"

/* GLOBAL */

extern MODE mode;
extern BUTTON btn;
extern pthread_t sw_thread;
Time al_time;			// global for display
BOOL al_isSetted;		// global for display
AL_CH al_toChange;		// global for display
BOOL al_isSetting;		// global for display

/* FUNCTION */

void alarm_onoff() {
	// al_isSetted: is alarm setted?

	al_isSetted =  ( al_isSetted + 1 ) % 2;
/*XXX*/ //printf( "alarm_onoff(): al_isSetted=%d\r\n", al_isSetted );
}

void switch_setting_alarm_time() {
	// toChange: select what to change
	// Hour -> Minute -> Hour
	// return: selected


	al_toChange = ( al_toChange + 1 ) % 2;
/*XXX*/ printf( "switch_setting_alarm_time(): tochange=%d\r\n", al_toChange );
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

void display_al(int month, int date, int hour, int minute) {
	gotoxy(0, 0);
	printf("   -----------\r\n");
	printf("    %c[1;100mAL %02dㆍ%02d%c[0;0m \r\n", 27, month, date, 27);
	printf("  -------------\r\n\r\n");
	if (al_isSetted) {
		if (al_isSetting) {
			if (al_toChange == AL_HOUR) {
				printf("  *   %c[1;101;4m%02d%c[1;101;24m:%02d%c[0;0m     \r\n\r\n", 27, hour, 27, minute, 27);
			}
			else printf("  *   %c[1;101;24m%02d:%c[1;101;4m%02d%c[0;0m     \r\n\r\n", 27, hour, 27, minute, 27);
		}
		else printf("  *   %c[1;101m%02d:%02d%c[0;0m     \r\n\r\n", 27, hour, minute, 27);
	}
	else {
		if (al_isSetting) {
			if (al_toChange == AL_HOUR) {
				printf("      %c[1;101;4m%02d%c[1;101;24m:%02d%c[0;0m     \r\n\r\n", 27, hour, 27, minute, 27);
			}
			else printf("      %c[1;101m%02d:%c[1;101;4m%02d%c[0;0m     \r\n\r\n", 27, hour, 27, minute, 27);
		}
		else printf("      %c[1;101m%02d:%02d%c[0;0m     \r\n\r\n", 27, hour, minute, 27);
	}
	printf("   -----------\r\n");
}

// if BUTTON-C pressed in TIME KEEPING MODE,	become ALARM MODE
// XXX DISPLAY PROCESS 2.2.13: Alarm

// XXX ASSUMPTION: BUTTON btn; MODE mode; are global
void alarm_mode() {
	// alarm: Alarm Time STORAGE
	// al_isSetted: is alarm setted?

	if ( mode != AL_MODE ) {
/*XXX*/ //printf( "alarm_mode(): Not Alarm Mode - RETURN\r\n" );
		return;
	}
	
	 display_al(currentTime->tm_mon + 1, currentTime->tm_mday, al_time.tm_hour, al_time.tm_min);

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
/*XXX*/ printf( "alarm_mode(): ALARM SETTING MODE BEGIN; toChange=%d\r\n", al_toChange );
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
