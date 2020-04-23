/*
 * boton.c
 *
 *  Created on: 20 abr. 2020
 *      Author: lucasml
 */
#include "debouncebutton.h"
#include "sapi.h"

void debounceinit(debouncebutton_t *pButton,gpioMap_t key){
	pButton->buttonpressed = FALSE;
	pButton->buttonstate = UP;
	pButton->key = key;
}

void debounceupdate(debouncebutton_t *pButton){
	switch(pButton->buttonstate){

	case UP:
		pButton->buttonpressed = FALSE;
		pButton->buttonreleased = TRUE;
		if(!gpioRead(pButton->key)){
			delayInit(&pButton->delayfsm,DEBOUNCE_DELAY);
			pButton->buttonstate = FALLING;
		}
	break;

	case FALLING:
		pButton->buttonpressed = FALSE;
		pButton->buttonreleased = TRUE;
		if(delayRead(&pButton->delayfsm)){
			if(!gpioRead(pButton->key)){
				pButton->buttonstate = DOWN;
			}
			else
			{
				pButton->buttonstate = UP;
			}
		}
	break;

	case DOWN:
		pButton->buttonpressed = TRUE;
		pButton->buttonreleased = FALSE;
		if(gpioRead(pButton->key)){
			delayInit(&pButton->delayfsm, DEBOUNCE_DELAY);
			pButton->buttonstate = RISING;
		}
	break;

	case RISING:
		pButton->buttonpressed = TRUE;
		pButton->buttonreleased = FALSE;
		if(delayRead(&pButton->delayfsm)){
			if(gpioRead(pButton->key)){
				pButton->buttonstate = UP;
			}
			else
			{
				pButton->buttonstate = DOWN;
			}
		}
	break;
}
}

