#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include "conio.h"
#include "modeController.h"
#include "alarmController.h"

#if !(WIN32)
#define Beep(x,y)
#endif


extern BUTTON btn;
extern Time al_time;                   // global for display
extern BOOL al_isSetted;               // global for display


void ringOff() {
        isRingAlarm = 0;
	
}


void* ringAlarm(void* arg) {
	
        isRingAlarm = 1;
	Beep(523,100);
	//is need delete thread??
 	       
}

int check_Alarm_Time(){

 	if(al_isSetted == FALSE) return 0;
	


	else if (al_time.tm_min== currentTime->tm_min && al_time.tm_hour== currentTime->tm_hour && 0 == currentTime->tm_sec )
			
	{
		trigger = 1;
		return trigger;
	}

}





int alarmController( ) {

	//Beep때문에 쓰레드를 쓰려고 합니다.
	pthread_t p_thread[1];
	

	check_Alarm_Time();
	
	
	if(trigger == 1) pthread_create(&p_thread[0], NULL, ringAlarm,NULL);

	else {
		ringOff();

	}




	if((btn ==1 || btn == 2 || btn == 3 || btn == 4)||(currentTime->tm_sec >= 5))
        {
                trigger = 0;
        }






}
