#include "servo.h"
#include "led.h"
#include <LPC21xx.H>
#include "timer_interrupts.h"

#define Dedector_bm (1<<10)


enum DetectorState {ACTIVE, INACTIVE};
enum ServoState {CALLIB, IDLE, IN_PROGRESS};
struct Servo {
	enum ServoState eState; 
	unsigned int uiCurrentPosition; 
	unsigned int uiDesiredPosition;
};
struct Servo sServo;


void DetectorInit(){
	IO0DIR = IO0DIR&(~Dedector_bm);
}

enum DetectorState eReadDetector(){
		if((IO0PIN&Dedector_bm) == 0){
			return ACTIVE;
		}
		else{
			return INACTIVE;
		}
}

void vAutomat(){
	switch(sServo.eState){
			case IDLE:
					if(sServo.uiCurrentPosition != sServo.uiDesiredPosition){
						sServo.eState = IN_PROGRESS;
					}
					break;
				
				case IN_PROGRESS:
					if(sServo.uiCurrentPosition < sServo.uiDesiredPosition){
						LedStepRight();
						sServo.uiCurrentPosition++;
					}
					else if(sServo.uiCurrentPosition > sServo.uiDesiredPosition){
						LedStepLeft();
						sServo.uiCurrentPosition--;
					}
					else{
						sServo.eState = IDLE;
					}
					break;
			case CALLIB:
				if (eReadDetector() == ACTIVE){
					sServo.eState = IDLE;
					sServo.uiCurrentPosition=0;
					sServo.uiDesiredPosition=0;
				}
				else{
					LedStepLeft();
				}
				break;
		}
}


void ServoInit(unsigned int uiServoFrequency){
		sServo.eState = CALLIB;
	  LedInit();
	  DetectorInit();
		Timer0Interrupts_Init(1000000/uiServoFrequency,&vAutomat);
}

void ServoCallib(void){
	sServo.eState = CALLIB;
}

void ServoGoTo(unsigned int uiPosition){
	sServo.uiDesiredPosition=uiPosition;
}
