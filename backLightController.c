#include "modeController.h"
#include "alarmController.h"
#include "backLightController.h"


int back_lighting = 0;

void backLightController(int btn){
	 	
	if(isRingAlarm == 0 && btn ==4){
        back_lighting = 1;
		BackLightTime.tm_sec = currentTime->tm_sec;
		backLight();//FIXME: 이렇게 안 할 수 없을까?
	}	

  	if(back_lighting == 1 && currentTime->tm_sec - BackLightTime.tm_sec == 2){
                lightOff();
        back_lighting = 0;
        }
}

void backLight(){
    back_lighting = 1;
}

void lightOff(){
    back_lighting = 0;
}

