#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>

#include "alarmController.h"
#include "conio.h"
#include "modeController.h"
#include "backLightController.h"

/* GLOBAL */
MODE mode = TK_MODE;
BUTTON btn = NONE;
extern BOOL tk_isSetting;
extern BOOL al_isSetting;

/* main function */
int main(int argc, char *argv[]) {
    time_t init_time = 1546268400; /* 2019.01.01 00:00:00 */
    currentTime = localtime(&init_time);
    changeTime = (Time*) malloc( sizeof( Time ) );
    pthread_t alarm_ctr;

    tk_isSetting = FALSE;
    al_isSetting = FALSE;


    system("clear");
    printf("\e[?25l");
    pthread_create(&alarm_ctr, NULL, ringAlarm, NULL);
    set_conio_terminal_mode();
    while (1) {
        btn = pushedButtonDector();
//        if ( btn)
//            printf("%d\r\n", btn);
        alarmController();
        backLightController();
        modeController();

    }
}
