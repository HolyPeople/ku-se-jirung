#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/wait.h>
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

    Time alarmTime = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    BOOL alarmSet = FALSE;

    MODE mode = TK_MODE;

    tk_isSetting = FALSE;
    al_isSetting = FALSE;


    system("clear");
    pthread_create(&alarm_ctr, NULL, ringAlarm, NULL);
    set_conio_terminal_mode();
    while (1) {
        if ( btn = pushedButtonDector())
            printf("%d\r\n", btn);
        alarmController();
        backLightController(btn);
        modeController();

    }
}
