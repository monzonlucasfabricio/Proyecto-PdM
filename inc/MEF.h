/*
 * main.h
 *
 *  Created on: 20 abr. 2020
 *      Author: lucasml
 */

#ifndef MIS_PROYECTOS_PDM_TPFINAL_INC_MEF_H_
#define MIS_PROYECTOS_PDM_TPFINAL_INC_MEF_H_

#include "sapi.h"

#define DELAY_PUMP 2000

typedef enum{
	RIEGO,
	TANQUE,
	MANUAL,
	APAGADO
}state_t;

typedef struct{
	state_t state;
	delay_t delayfsm;
	gpioMap_t Vriego;
	gpioMap_t Vtanque;
	gpioMap_t Pump;
}control_t;


void MEFinit(control_t *controlstate);
void MEFupdate(control_t *controlstate);


#endif /* MIS_PROYECTOS_PDM_TPFINAL_INC_MEF_H_ */
