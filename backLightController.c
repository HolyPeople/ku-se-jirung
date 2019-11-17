#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "modeController.h"
#include "alarmController.h"
#include "BackLightController.h"


int idle = 0; 

void backLightController(int btn){
	 	

	if(isRingAlarm == 0 && btn ==4){
		idle = 1;
		BackLightTime.tm_sec = currentTime->tm_sec;
		backLight();//이렇게 안 할 수 없을까?
	}	

	

  	if(idle == 1 && currentTime->tm_sec - BackLightTime.tm_sec == 2){
                lightOff();
		idle = 0;
        }
	
}



void backLight(){
	 printf("%c[1;33m", 27);
}


void lightOff(){

printf("%c[0m\n",27);

}

