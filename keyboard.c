#include <LPC21xx.H>
#include "keyboard.h"
#define BUTTON0_bm 1<<4
#define BUTTON1_bm 1<<6
#define BUTTON2_bm 1<<5
#define BUTTON3_bm 1<<7

enum KeyboardState {RELASED,BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};

void KeyboardInit(void){
	IO0DIR = IO0DIR & (~( BUTTON0_bm | BUTTON1_bm | BUTTON2_bm | BUTTON3_bm));
}

enum KeyboardState ReadButton(){
	int PIN_TMP = IO0PIN;
	if((PIN_TMP&BUTTON0_bm) == 0){
		return BUTTON_0;
	}
	else if((PIN_TMP&BUTTON1_bm) == 0) {
		return BUTTON_1;
	}
	else if((PIN_TMP & BUTTON2_bm) == 0) {
		return BUTTON_2;
	}
	else if((PIN_TMP & BUTTON3_bm) == 0) {
		return BUTTON_3;
	}
		return RELASED;
}
