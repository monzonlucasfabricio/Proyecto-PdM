/*
 * debounce.h
 *
 *  Created on: 20 abr. 2020
 *      Author: lucasml
 */

#ifndef MIS_PROYECTOS_PDM_DEBOUNCE_INC_DEBOUNCE_H_
#define MIS_PROYECTOS_PDM_DEBOUNCE_INC_DEBOUNCE_H_

#include "sapi.h"

#define DEBOUNCE_DELAY 40

typedef enum{
	UP,
	DOWN,
	FALLING,
	RISING,
}buttonstate_t;

typedef struct{
	bool_t buttonpressed;
	bool_t buttonreleased;
	buttonstate_t buttonstate;
	gpioMap_t key;
	delay_t delayfsm;
}debouncebutton_t;

debouncebutton_t pButton;

void debounceinit(debouncebutton_t *pButton,gpioMap_t key);
void debounceupdate(debouncebutton_t *pButton);


#endif /* MIS_PROYECTOS_PDM_DEBOUNCE_INC_DEBOUNCE_H_ */
