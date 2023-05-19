#include "timer_interrupts.h"
#include "led.h"
#include "keyboard.h"
#include <LPC21xx.H>
#include "timer.h"
#include "servo.h"


/**********************************************/
enum KeyboardState {RELASED,BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};

void Delay(unsigned int uiWaitMs){
	
	unsigned int uiCounter;
	unsigned int uiCounter2;
	
	for(uiCounter=0; uiCounter<uiWaitMs; uiCounter++){
	  for(uiCounter2=0; uiCounter2<1496; uiCounter2++){}
	}	
}




int main (){
	int mainloop = 0;
	ServoInit(20);
	ServoGoTo(1000);
  KeyboardInit();
	while(1){
	 	Delay(100);
		switch(ReadButton()){
			case BUTTON_0:
				ServoCallib();
				break;			
			case BUTTON_1:
				ServoGoTo(50);
				break;
			case BUTTON_2:
				ServoGoTo(100);
				break;
			case BUTTON_3:
				ServoGoTo(150);
			break;
			case RELASED:
				break;
			default:{}
		}
	}
}

