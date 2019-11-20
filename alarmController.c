#include <unistd.h>
#include <pthread.h>
#include "conio.h"
#include "modeController.h"
#include "alarmController.h"

extern BUTTON btn;
extern Time al_time;                   // global for display
extern BOOL al_isSetted;               // global for display


void ringOff() {
    isRingAlarm = 0;
}

void *ringAlarm(void* args) {
    struct timespec now, from;
    printf("ringAlarm() : is Created!\r\n");
    while (1) {
        clock_gettime( CLOCK_MONOTONIC, &from);
        if (isRingAlarm)
            system("echo -e '\a'");
        while (isRingAlarm) {
            clock_gettime( CLOCK_MONOTONIC, &now );
            if ( ( now.tv_sec * 1000000000 + now.tv_nsec )
                 - ( from.tv_sec * 1000000000 + from.tv_nsec ) >= 1000000000 ) {
                system("echo -e '\a'");
                printf("ringAlarm() : ring\r\n");
                clock_gettime( CLOCK_MONOTONIC, &from );
            }
        }
    }
}

int check_Alarm_Time(){

    if (al_isSetted == TRUE
            && (al_time.tm_min== currentTime->tm_min && al_time.tm_hour== currentTime->tm_hour && 0 == currentTime->tm_sec ))
        return 1;
    else
        return 0;
}

int alarmController( ) {

    if (!isRingAlarm && check_Alarm_Time()) {
        printf("alarmController() : change isRingAlarm%d\r\n", isRingAlarm);
        isRingAlarm = 1;
    }


    if( isRingAlarm && ((btn ==1 || btn == 2 || btn == 3 || btn == 4)||(currentTime->tm_sec >= 5))) {
        ringOff();
        isRingAlarm = 0;
        btn = NONE;
    }

}
