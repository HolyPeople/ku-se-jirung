#include "watch_ctrl.h"

/* GLOBAL */

extern MODE mode;
extern BUTTON btn;
extern pthread_t sw_thread;
Time al_time;			// global for display
BOOL al_isSetted;		// global for display

/* FUNCTION */

void alarm_onoff() {
	// al_isSetted: is alarm setted?

	al_isSetted =  ( al_isSetted + 1 ) % 2;
/*XXX*/// printf( "alarm_onoff(): al_isSetted=%d\n", al_isSetted );
}

void switch_setting_alarm_time( AL_CH* toChange ) {
	// toChange: select what to change
	// Hour -> Minute -> Hour
	// return: selected

	*toChange = ( *toChange + 1 ) % 2;
/*XXX*/// printf( "switch_setting_alarm_time(): tochange=%d\n", *toChange );
}

void increase_alarm_time( AL_CH toChange ) {
	// alarm: Alarm Time STORAGE
	// toChange: what to change

	switch( toChange ) {
		case AL_HOUR:
			al_time.tm_hour = ( al_time.tm_hour + 1 ) % 24;
			break;
		case AL_MIN:
			al_time.tm_min = ( al_time.tm_min + 1 ) % 60;
			break;
	}
/*XXX*/// printf( "increase_alarm_time(): Alarm=%d:%d\n", al_time.tm_hour, al_time.tm_min );
}



// if BUTTON-C pressed in TIME KEEPING MODE,	become ALARM MODE
// XXX DISPLAY PROCESS 2.2.13: Alarm

// XXX ASSUMPTION: BUTTON btn; MODE mode; are global
void alarm_mode() {
	// alarm: Alarm Time STORAGE
	// al_isSetted: is alarm setted?

	/* STATIC */
	static AL_CH toChange = AL_HOUR;	// what to change
	static BOOL isSetting = FALSE;	// is alarm setting mode? ( or alarm mode )


	if ( mode != AL_MODE ) {
/*XXX*/// printf( "alarm_mode(): Not Alarm Mode - RETURN\n" );
		return;
	}

	if ( isSetting == FALSE ) {
		// if BUTTON-C pressed in ALARM MODE,	goto STOPWATCH MODE
		if ( btn == C ) {
	                mode = ( mode + 1 ) % 3;
			pthread_create( &sw_thread, NULL, sw_increase, NULL );
/*XXX*/// printf( "alarm_mode(): Mode Change - SW; RETURN\n" );
			btn = NONE;
        	        return;
        	}

		// if BUTTON-B pressed in ALARM MODE,	XXX PROCESS 2.2.16: Alarm On/Off XXX
		if ( btn == B ) {
			alarm_onoff();
		}

		// if BUTTON-A pressed in ALARM MODE,	become ALARM SETTING MODE
		if ( btn == A ) {
			isSetting = ( isSetting + 1 ) % 2;
			toChange = AL_HOUR;
/*XXX*/// printf( "alarm_mode(): ALARM SETTING MODE BEGIN; toChange=%d\n", toChange );
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
			switch_setting_alarm_time( &toChange );
		}

		// if BUTTON-B pressed in ALARM SETTING MODE,	XXX PROCESS 2.2.15: Increase Alarm Time XXX
		if ( btn == B )	{
			increase_alarm_time( toChange );
		}

		// if BUTTON-A pressed in ALARM SETTING MODE,	become ALARM MODE
		if ( btn == A ) {
			isSetting = ( isSetting + 1 ) % 2;
			// XXX DISPLAY PROCESS 2.2.13: Alarm
/*XXX*/// printf( "alarm_mode(): ALARM MODE BEGIN\n" );
		}
	}

	btn = NONE;
}
