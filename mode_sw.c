#include "conio.h"
#include "modeController.h"

/* GLOBAL */

pthread_t sw_thread;		// global for thread
sw_Time sw_time;		// global for thread
BOOL sw_isWork = FALSE;		// global for thread
sw_Time sw_lap;			// global for display
BOOL sw_isLap = FALSE;		// global for display
extern MODE mode;
extern BUTTON btn;

/* FUNCTION */

void *sw_increase( void* arg ) {
	// thread handler
	
        static clock_t a_clock =0;//To check clock_per_sec/100;
	clock_t cu_clock = clock();// To check 
	sw_time.min = 0; 
	sw_time.sec = 0;
	sw_time.centi = 0;

/*XXX*/// printf( "sw_increase(): INCREASING START\n" );
while ( 1 ) {
                if ( sw_isWork == TRUE ) {
                        // XXX PROCESS 2.2.9: Stopwatch Measurement XXX
                        // TODO increase
                if(cu_clock - a_clock >= CLOCKS_PER_SEC/100) {
                        sw_time.centi ++;
                        a_clock = clock();
                }
                if(sw_time.centi=100){
                        sw_time.centi = 0;
                        sw_time.sec++;
                }
                if(sw_time.sec=60){
                        sw_time.sec = 0;
                        sw_time.min++;
                }
                
                }
                if ( mode != SW_MODE )
                        break;
        }
/*XXX*/// printf( "sw_increase(): INCREASING FINISH\n" );
}

void record_laptime( ) {
	// sw_time: increasing stopwatch time
	// sw_lap: laptime for display
	// sw_isLap: is laptime on display?
	
	sw_isLap = TRUE;
        memcpy( &sw_lap, &sw_time, sizeof( sw_Time ) );
/*XXX*/// printf( "record_laptime(): Lap=%d:%d:%d\n", sw_lap.min, sw_lap.sec, sw_lap.centi );
}

void stopwatch_reset( ) {
	// sw_time: increasing stopwatch time TO RESET

        sw_time.min = 0;
        sw_time.sec = 0;
        sw_time.centi = 0;
/*XXX*/// printf( "stopwatch_reset()\n" );
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
/*XXX*/// printf( "stopwatch_mode(): Not Stopwatch Mode - RETURN\n" );
                return;
	}

	// if BUTTON-C pressed && !sw_isWork,	goto TIME KEEPING MODE
	if ( btn == C && sw_isWork == FALSE ) {
/*XXX*/// printf( "stopwatch_mode(): Mode Change - TK; RETURN\n" );
		mode = ( mode + 1 ) % 3;
		return;
	}

	// if BUTTON-C pressed && sw_isWork,	DO NOTHING

	if ( btn == B ) {
		if ( sw_isLap == FALSE ) {
			// if BUTTON-B pressed && !sw_isLab	sw_isWork: T -> F -> T
			sw_isWork = ( sw_isWork + 1 ) % 2;
/*XXX*/// printf( "stopwatch_mode(): isWork=%d\n", sw_isWork );
		}
		else {
			// if BUTTON-B pressed && sw_isLab	show sw_time
			sw_isLap = FALSE;
/*XXX*/// printf( "stopwatch_mode(): isWork=%d; isLap=%d\n", sw_isWork, sw_isLap );
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
