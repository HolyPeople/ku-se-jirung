#pragma once
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

/* sturcture */

typedef struct tm Time;
Time* currentTime;
Time* changeTime;

typedef enum _MODE {
        TK_MODE, AL_MODE, SW_MODE
} MODE;

typedef enum alarmChange {
        AL_HOUR, AL_MIN
} AL_CH;

typedef enum watchChange {
        W_SEC, W_HOUR, W_MIN, W_YEAR, W_MONTH, W_DAY
} W_CH;

typedef enum boolean {
        FALSE, TRUE
} BOOL;

typedef struct time_sw {
        int min;
        int sec;
        int centi;      // centi-sec
} sw_Time;


/* function */

void modeController( );

Time* autoIncreaseTime(Time* currentTime);

void time_switch( Time* dst, Time* src );

/* function in mode_tk.c */
void timekeeping_mode( );
// C: goto ALARM MODE
// B: DO NOTHING
// A: TIME KEEPING MODE -> TIME SETTING MODE
/***********************
 * △ Time Keeping Mode *
 * ▽ Time Setting Mode *
 ***********************/
void switch_setting_time( W_CH* toChange );     // C: 2.2.4
void manual_incease_time( W_CH toChange );       // B: 2.2.5
// A: TIME SETTING MODE -> TIME KEEPING MODE

/* function in mode_sw.c */
void stopwatch_mode( );
// C( !sw_work ): goto TIME KEEPING MODE
// C( sw_work ): DO NOTHING
void *sw_increase( void* sw_arg );      // for SW THREAD: sw_work: 2.2.9
// B( !sw_lap ): WORK or STOP
// B( sw_lap ): SHOW sw_time; sw_lap := FALSE
void record_laptime( ); // A( sw_work ): 2.2.11
void stopwatch_reset( );        // A( !sw_work ): 2.2.8

/* function in mode_al.c */
void alarm_mode( );
// C: goto STOPWATCH MODE
void alarm_onoff( );    // B: 2.2.16
// A: ALARM MODE -> ALARM SETTING MODE
/************************
 * △ Alarm Mode         *
 * ▽ Alarm Setting Mode *
 ************************/
void switch_setting_alarm_time( AL_CH* toChange ); // C: 2.2.14
void increase_alarm_time( AL_CH toChange );     // B: 2.2.15
// A: ALARM SETTING MODE -> ALARM MODE
