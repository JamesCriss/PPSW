#include <LPC21xx.H>
#include "led.h"

#define LED0_bm 1<<16
#define LED1_bm 1<<17
#define LED2_bm 1<<18
#define LED3_bm 1<<19

static unsigned int uiLedLocation = 0;
enum LedDirection {LEFT, RIGHT};

void LedOn(unsigned char ucLedIndeks){
	IO1CLR = LED0_bm | LED1_bm | LED2_bm | LED3_bm;
	switch (ucLedIndeks){
		case 0:
			IO1SET = LED0_bm;
		  break;
		case 1:
			IO1SET = LED1_bm;
			break;
		case 2:
			IO1SET = LED2_bm;
			break;
		case 3:
			IO1SET = LED3_bm;
			break;
	}
}


void LedStep(enum LedDirection Direction){
	if(Direction == RIGHT){
	uiLedLocation = (uiLedLocation-1)%4;
	}
	else if (Direction == LEFT){
		uiLedLocation = (uiLedLocation+1)%4;
	}
	LedOn(uiLedLocation);
}


void LedInit(void){
	IO1DIR = IO1DIR | LED0_bm | LED1_bm | LED2_bm | LED3_bm ;
	IO1SET = LED0_bm;
}

void LedStepRight(void){
	LedStep(RIGHT);
}

void LedStepLeft(void){
	LedStep(LEFT);
}
