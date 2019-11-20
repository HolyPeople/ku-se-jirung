#include "conio.h"
#include "modeController.h"

extern MODE mode;
extern BUTTON btn;
extern Time* currentTime;
extern BOOL al_isSetted; // Add for Display by harheem
W_CH tk_toChange;	// global for display
BOOL tk_isSetting;	// global for display
extern Time* changeTime;
char day[][3] = { "SU", "MO", "TU", "WE", "TH", "FR", "SA" };

void switch_setting_time( ) {
	// toChange: select what to change
	// Second -> Hour -> Minute -> Year -> Month -> Day -> Second

	tk_toChange =  ( tk_toChange + 1 ) % 6;
/*XXX*/ //printf( "switch_setting_time(): tochange=%d\r\n", tk_toChange );
}

void manual_incease_time( ) {
	// currentTime: Current Time tm STORAGE
	// toChange: what to change

	int year = 0;	// for OPT
	int day = 0;	// for day++

	switch ( tk_toChange ) {
		case W_SEC:
			changeTime->tm_sec = ( changeTime->tm_sec + 1 ) % 60;
			break;
		case W_HOUR:
			changeTime->tm_hour = ( changeTime->tm_hour + 1 ) % 24;
			break;
		case W_MIN:
			changeTime->tm_min = ( changeTime->tm_min + 1 ) % 60;
			break;
		case W_YEAR:
			changeTime->tm_year++;
			if ( changeTime->tm_year > 199 )	// year > 2099
				changeTime->tm_year = 119;	// year := 2019
			break;
		case W_MONTH:
			changeTime->tm_mon = ( changeTime->tm_mon + 1 ) % 12;
			break;
		case W_DAY:
			day = changeTime->tm_mday + 1;

			switch( changeTime->tm_mon ) {
				case 0:
				case 2:
				case 4:
				case 6:
				case 7:
				case 9:
				case 11:
					if ( day > 31 )
						changeTime->tm_mday = 1;
					else
						changeTime->tm_mday = day;
					break;
				case 1:
					year = changeTime->tm_year;
					if ( ( !( year % 4 ) && ( year % 100 ) ) || !( year % 400 ) ) {
						if ( day > 29 )
							changeTime->tm_mday = 1;
						else
							changeTime->tm_mday = day;
					}
					else {
						if ( day > 28 )
							changeTime->tm_mday = 1;
						else
							changeTime->tm_mday = day;
					}
					break;
				default:
						if ( day > 30 )
							changeTime->tm_mday = 1;
						else
							changeTime->tm_mday = day;
			}
	}
/*XXX*/ //printf( "manual_increase_time(): Time=%d/%d/%d %d:%d:%d\r\n", changeTime->tm_year+1900, changeTime->tm_mon+1, changeTime->tm_mday, changeTime->tm_hour, changeTime->tm_min, changeTime->tm_sec );
}


//W_SEC, W_HOUR, W_MIN, W_YEAR, W_MONTH, W_DAY

void display_tk(int month, int date, int hour, int minute, int second) {
	gotoxy(0, 0);
	printf("   -----------\r\n");
	if (tk_isSetting) {
		if (tk_toChange == W_MONTH) {
			printf("    %c[1;100m%s %c[1;100;4m%02d%c[1;100;24mㆍ%02d%c[0;0;24m \r\n", 27, day[currentTime->tm_wday], 27, month, 27, date, 27);
		}
		else if(tk_toChange == W_DAY) printf("    %c[1;100m%s %02dㆍ%c[1;100;4m%02d%c[0;0;24m \r\n", 27, day[currentTime->tm_wday], month, 27, date, 27);
		else printf("    %c[1;100m%s %02dㆍ%02d%c[0;0m \r\n", 27, day[currentTime->tm_wday], month, date, 27);
	}
	else printf("    %c[1;100m%s %02dㆍ%02d%c[0;0m \r\n", 27, day[currentTime->tm_wday], month, date, 27);
	printf("  -------------\r\n\r\n");
	if (al_isSetted) {
		if (tk_isSetting) {
			if (tk_toChange == W_SEC) {
				printf("  *  %c[1;101;24m%02d:%02d %c[1;101;4m%02d%c[0;0;24m \r\n\r\n", 27, hour, minute, 27, second, 27);
			}
			else if (tk_toChange == W_HOUR) {
				printf("  *  %c[1;101;4m%02d%c[1;101;24m:%02d %02d%c[0;0;24m \r\n\r\n", 27, hour, 27, minute, second, 27);
			}
			else if (tk_toChange == W_MIN) {
				printf("  *  %c[1;101m%02d:%c[1;101;4m%02d%c[1;101;24m %02d%c[0;0;24m \r\n\r\n", 27, hour, 27, minute, 27, second, 27);
			}
			else printf("  *  %c[1;101m%02d:%02d %02d%c[0;0m \r\n\r\n", 27, hour, minute, second, 27);
		}
		else printf("  *  %c[1;101m%02d:%02d %02d%c[0;0m \r\n\r\n", 27, hour, minute, second, 27);
	}
	else {
		if (tk_isSetting) {
			if (tk_toChange == W_SEC) {
				printf("     %c[1;101;24m%02d:%02d %c[1;101;4m%02d%c[0;0;24m \r\n\r\n", 27, hour, minute, 27, second, 27);
			}
			else if (tk_toChange == W_HOUR) {
				printf("     %c[1;101;4m%02d%c[1;101;24m:%02d %02d%c[0;0;24m \r\n\r\n", 27, hour, 27, minute, second, 27);
			}
			else if (tk_toChange == W_MIN) {
				printf("     %c[1;101m%02d:%c[1;101;4m%02d%c[1;101;24m %02d%c[0;0;24m \r\n\r\n", 27, hour, 27, minute, 27, second, 27);
			}
			else printf("     %c[1;101m%02d:%02d %02d%c[0;0m \r\n\r\n", 27, hour, minute, second, 27);
		}
		else printf("     %c[1;101m%02d:%02d %02d%c[0;0m \r\n\r\n", 27, hour, minute, second, 27);
	}
	printf("   -----------\r\n");
}



// if BUTTON-C pressed in STOPWATCH MODE,	become TIME KEEPING MODE
// XXX DISPLAY PROCESS 2.2.2: Time Keeping

// XXX ASSUMPTION: BUTTON btn; MODE mode; are global
void timekeeping_mode( ) {
	// currentTime: Current Time Storage
	
	if ( mode != TK_MODE ) {
/*XXX*/ //printf( "timekeeping_mode(): Not Timekeeping Mode - RETURN\r\n" );
                return;
	}

	if (tk_isSetting == TRUE) display_tk(changeTime->tm_mon + 1, changeTime->tm_mday, changeTime->tm_hour, changeTime->tm_min, changeTime->tm_sec);
	else display_tk(currentTime->tm_mon + 1, currentTime->tm_mday, currentTime->tm_hour, currentTime->tm_min, currentTime->tm_sec);


	if ( tk_isSetting == FALSE ) {
		// if BUTTON-C pressed in TIME KEEPING MODE,	goto ALARM MODE
		if ( btn == C ) {
			mode = ( mode + 1 ) % 3;
/*XXX*/ //printf( "timekeeping_mode(): Mode Change - AL; RETURN\r\n" );
			btn = NONE;
                        return;
                }

		// if BUTTON-B pressed in TIME KEEPING MODE, DO NOTHING

		// if BUTTON-A pressed in TIME KEEPING MODE,	become TIME SETTING MODE
		if ( btn == A ) {
			time_switch( changeTime, currentTime );
			tk_isSetting = ( tk_isSetting + 1 ) % 2;
			tk_toChange = W_SEC;
/*XXX*/ //printf( "timekeeping_mode(): TIME SETTING MODE BEGIN; toChange=%d\r\n", tk_toChange );
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
			time_switch(currentTime, changeTime);
		}

		// if BUTTON-A pressed in TIME SETTING MODE,	return to TIME KEEPING MODE
		if ( btn == A ) {
			time_switch( currentTime, changeTime );
			tk_isSetting = ( tk_isSetting + 1 ) % 2;
/*XXX*/ //printf( "timekeeping_mode(): TIME SETTING MODE END; toChange=%d\r\n", tk_toChange );
			// XXX DISPLAY - PROCESS 2.2.2: Time Keeping ( currentTime )
		}
	}

	btn = NONE;
}


void time_switch( Time* dst, Time* src ) {
	memcpy( dst, src, sizeof( Time ) );
}
