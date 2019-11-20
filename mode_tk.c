#include "conio.h"
#include "modeController.h"

extern MODE mode;
extern BUTTON btn;
extern Time* currentTime;
W_CH tk_toChange;	// global for display
BOOL tk_isSetting;	// global for display

void switch_setting_time( ) {
	// toChange: select what to change
	// Second -> Hour -> Minute -> Year -> Month -> Day -> Second

	tk_toChange =  ( tk_toChange + 1 ) % 6;
/*XXX*/ printf( "switch_setting_time(): tochange=%d\r\n", tk_toChange );
}

void manual_incease_time( ) {
	// currentTime: Current Time tm STORAGE
	// toChange: what to change

	int year = 0;	// for OPT
	int day = 0;	// for day++

	switch ( tk_toChange ) {
		case W_SEC:
			currentTime->tm_sec = ( currentTime->tm_sec + 1 ) % 60;
			break;
		case W_HOUR:
			currentTime->tm_hour = ( currentTime->tm_hour + 1 ) % 24;
			break;
		case W_MIN:
			currentTime->tm_min = ( currentTime->tm_min + 1 ) % 60;
			break;
		case W_YEAR:
			currentTime->tm_year++;
			if ( currentTime->tm_year > 199 )	// year > 2099
				currentTime->tm_year = 119;	// year := 2019
			break;
		case W_MONTH:
			currentTime->tm_mon = ( currentTime->tm_mon + 1 ) % 12;
			break;
		case W_DAY:
			day = currentTime->tm_mday + 1;

			switch( currentTime->tm_mon ) {
				case 0:
				case 2:
				case 4:
				case 6:
				case 7:
				case 9:
				case 11:
					if ( day > 31 )
						currentTime->tm_mday = 1;
					else
						currentTime->tm_mday = day;
					break;
				case 1:
					year = currentTime->tm_year;
					if ( ( !( year % 4 ) && ( year % 100 ) ) || !( year % 400 ) ) {
						if ( day > 29 )
							currentTime->tm_mday = 1;
						else
							currentTime->tm_mday = day;
					}
					else {
						if ( day > 28 )
							currentTime->tm_mday = 1;
						else
							currentTime->tm_mday = day;
					}
					break;
				default:
						if ( day > 30 )
							currentTime->tm_mday = 1;
						else
							currentTime->tm_mday = day;
			}
	}
/*XXX*/ printf( "manual_increase_time(): Time=%d/%d/%d %d:%d:%d\r\n", currentTime->tm_year+1900, currentTime->tm_mon+1, currentTime->tm_mday, currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec );
}



// if BUTTON-C pressed in STOPWATCH MODE,	become TIME KEEPING MODE
// XXX DISPLAY PROCESS 2.2.2: Time Keeping

// XXX ASSUMPTION: BUTTON btn; MODE mode; are global
void timekeeping_mode( ) {
	// currentTime: Current Time Storage
	
	if ( mode != TK_MODE ) {
/*XXX*/ printf( "timekeeping_mode(): Not Timekeeping Mode - RETURN\r\n" );
                return;
	}

	if ( tk_isSetting == FALSE ) {
		// if BUTTON-C pressed in TIME KEEPING MODE,	goto ALARM MODE
		if ( btn == C ) {
			mode = ( mode + 1 ) % 3;
/*XXX*/ printf( "timekeeping_mode(): Mode Change - AL; RETURN\r\n" );
			btn = NONE;
                        return;
                }

		// if BUTTON-B pressed in TIME KEEPING MODE, DO NOTHING

		// if BUTTON-A pressed in TIME KEEPING MODE,	become TIME SETTING MODE
		if ( btn == A ) {
			tk_isSetting = ( tk_isSetting + 1 ) % 2;
			tk_toChange = W_SEC;
/*XXX*/ printf( "timekeeping_mode(): TIME SETTING MODE BEGIN; toChange=%d\r\n", tk_toChange );
		}
		// XXX DISPLAY - PROCESS 2.2.3: struct tm Setting ( toChange )
	}

	/***********************
	 * △ Time Keeping Mode *
	 * ▽ Time Setting Mode *
	 ***********************/

	else {
		// if BUTTON-C pressed in TIME SETTING MODE,	XXX PROCESS 2.2.4: Switch Setting Time XXX
		if ( btn == C ) {
			switch_setting_time();
		}

		// if BUTTON-B pressed in TIME SETTING MODE,	XXX PROCESS 2.2.5: Manual Increase Time XXX
		if ( btn == B ) {
			manual_incease_time();
		}

		// if BUTTON-A pressed in TIME SETTING MODE,	return to TIME KEEPING MODE
		if ( btn == A ) {
			tk_isSetting = ( tk_isSetting + 1 ) % 2;
/*XXX*/ printf( "timekeeping_mode(): TIME SETTING MODE END; toChange=%d\r\n", tk_toChange );
			// XXX DISPLAY - PROCESS 2.2.2: Time Keeping ( currentTime )
		}
	}

	btn = NONE;
}
