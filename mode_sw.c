#include "conio.h"
#include "modeController.h"

/* GLOBAL */

pthread_t sw_thread;		// global for thread
sw_Time sw_time;		// global for thread
BOOL sw_isWork = FALSE;		// global for thread
pthread_mutex_t sw_mtx = PTHREAD_MUTEX_INITIALIZER;
sw_Time sw_lap;			// global for display
BOOL sw_isLap = FALSE;		// global for display
extern MODE mode;
extern BUTTON btn;
extern BOOL al_isSetted; // Add for Display by harheem
extern Time* changeTime;
extern int idle;
char light = 0;

/* FUNCTION */

void *sw_increase( void* arg ) {
	// thread handler
	stopwatch_reset();

	struct timespec from;
	struct timespec now;

	clock_gettime( CLOCK_MONOTONIC, &from );

/*XXX*/ //printf( "sw_increase(): INCREASING START\r\n" );
	while ( 1 ) {
		if ( sw_isWork == TRUE ) {
			// XXX PROCESS 2.2.9: Stopwatch Measurement XXX
			// TODO FIXME increase
			clock_gettime( CLOCK_MONOTONIC, &now );
			if ( ( now.tv_sec * 1000000000 + now.tv_nsec ) - ( from.tv_sec * 1000000000 + from.tv_nsec ) >= 10000000 ) {
				pthread_mutex_lock( &sw_mtx );
				sw_time.centi++;
/*XXX*/	//printf( "sw_increase(): %d:%d:%d\r\n", sw_time.min, sw_time.sec, sw_time.centi );
		
				if ( sw_time.centi >= 100 ) {
					sw_time.centi -= 100;
					sw_time.sec++;

					if ( sw_time.sec >= 60 ) {
						sw_time.sec -= 60;
						sw_time.min++;
					}
				}
				pthread_mutex_unlock( &sw_mtx );
				clock_gettime( CLOCK_MONOTONIC, &from );
			}
		}
		if ( mode != SW_MODE )
			break;
	}
/*XXX*/ //printf( "sw_increase(): INCREASING FINISH\r\n" );
}

void record_laptime( ) {
	// sw_time: increasing stopwatch time
	// sw_lap: laptime for display
	// sw_isLap: is laptime on display?
	
	sw_isLap = TRUE;
	pthread_mutex_lock( &sw_mtx );
        memcpy( &sw_lap, &sw_time, sizeof( sw_Time ) );
	pthread_mutex_unlock( &sw_mtx );
/*XXX*/// printf( "record_laptime(): Lap=%d:%d:%d\r\n", sw_lap.min, sw_lap.sec, sw_lap.centi );
}

void stopwatch_reset( ) {
	// sw_time: increasing stopwatch time TO RESET

	pthread_mutex_lock( &sw_mtx );
        sw_time.min = 0;
        sw_time.sec = 0;
        sw_time.centi = 0;
		//Add LabTime Initialization by harheem
		sw_lap.centi = 0;
		sw_lap.min = 0;
		sw_lap.sec = 0;
	pthread_mutex_unlock( &sw_mtx );
/*XXX*/ //printf( "stopwatch_reset()\r\n" );
}


void display_sw(int hour, int minute, int sw_miniute, int sw_second, int sw_microsecond) {
	gotoxy(0, 0);
	printf("   -----------\r\n");
	printf("    %c[%dmST %02d:%02d%c[0;0m \r\n", 27, light, hour, minute, 27);
	printf("  -------------\r\n\r\n");
	if (al_isSetted) printf("  *  %c[%dm%02d'%02d\"%02d%c[0;0m \r\n\r\n", 27, light, sw_miniute, sw_second, sw_microsecond, 27);
	else printf("     %c[%dm%02d'%02d\"%02d%c[0;0m \r\n\r\n", 27, light, sw_miniute, sw_second, sw_microsecond, 27);
	printf("   -----------\r\n");
}


// if BUTTON-C pressed in ALARM MODE,    become STOPWATCH MODE
// XXX DISPLAY PROCESS 2.2.7: Stopwatch Mode

// XXX ASSUMPTION: BUTTON btn; MODE mode; are global
void stopwatch_mode( ) {
	// sw_time: increasing stopwatch time
	// sw_lap: laptime for display
	// sw_isLap: is laptime on display? -> global for display
	// sw_isWork: is stopwatch work?
	// sw_thread: thread for increment
	
	if ( mode != SW_MODE ) {
/*XXX*/ //printf( "stopwatch_mode(): Not Stopwatch Mode - RETURN\r\n" );
        return;
	}

	//if LabTime is Not 00'00"00 -> Display LabTime by harheem
	if (idle == 1) light = 33;
	else light = 0;
	if (sw_isLap == TRUE) display_sw(currentTime->tm_hour, currentTime->tm_min, sw_lap.min, sw_lap.sec, sw_lap.centi);
	else display_sw(currentTime->tm_hour, currentTime->tm_min, sw_time.min, sw_time.sec, sw_time.centi);

	// if BUTTON-C pressed && !sw_isWork,	goto TIME KEEPING MODE
	if ( btn == C && sw_isWork == FALSE ) {
/*XXX*/ //printf( "stopwatch_mode(): Mode Change - TK; RETURN\r\n" );
		mode = ( mode + 1 ) % 3;
		return;
	}

	// if BUTTON-C pressed && sw_isWork,	DO NOTHING

	if ( btn == B ) {
		if ( sw_isLap == FALSE ) {
			// if BUTTON-B pressed && !sw_isLab	sw_isWork: T -> F -> T
			sw_isWork = ( sw_isWork + 1 ) % 2;
/*XXX*/ //printf( "stopwatch_mode(): isWork=%d\r\n", sw_isWork );
		}
		else {
			// if BUTTON-B pressed && sw_isLab	show sw_time
			sw_isLap = FALSE;
/*XXX*/ //printf( "stopwatch_mode(): isWork=%d; isLap=%d\r\n", sw_isWork, sw_isLap );
		}
	}

	if ( btn == A ) {
		if ( sw_isWork == TRUE ) {
			// if BUTTON-A pressed && sw_isWork,	XXX PROCESS 2.2.11: Record Laptime XXX
			record_laptime( );
		}
		else {
			// if BUTTON-A pressed in STOPWATCH MODE when ( sw_work == FALSE ),	XXX PROCESS 2.2.8: Stopwatch Reset XXX
			stopwatch_reset( );
		}
	}

	btn = NONE;
}
