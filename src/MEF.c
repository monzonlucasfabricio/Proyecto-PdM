/*
 * MEF.c
 *
 *  Created on: 20 abr. 2020
 *      Author: lucasml
 */

#include "sapi.h"
#include "MEF.h"
#include "debouncebutton.h"

static void apagadoInit(control_t *MEF);
static void riegoInit(control_t *MEF);
static void tanqueInit(control_t *MEF);
static void manualInit(control_t *MEF);

static void apagado(control_t *MEF);
static void riego(control_t *MEF);
static void tanque(control_t *MEF);
static void manual(control_t *MEF);

//Definicion de teclas con antirebote

debouncebutton_t tecla1;
debouncebutton_t tecla2;
debouncebutton_t tecla3;
debouncebutton_t tecla4;

void MEFinit(control_t *controlstate){

	//Inicio la maquina en estado APAGADO
	apagadoInit(controlstate);

	//Inicializo las teclas con antirebote
	debounceinit(&tecla1,TEC1);
	debounceinit(&tecla2,TEC2);
	debounceinit(&tecla3,TEC3);
	debounceinit(&tecla4,TEC4);

}

void MEFupdate(control_t *controlstate){

	//Checkeo las teclas
	debounceupdate(&tecla1);
	debounceupdate(&tecla2);
	debounceupdate(&tecla3);
	debounceupdate(&tecla4);

	switch(controlstate -> state){

	case APAGADO:{

		apagado(controlstate);

	}
	break;

	case RIEGO:{

		riego(controlstate);

	}
	break;

	case TANQUE:{

		tanque(controlstate);

	}
	break;

	case MANUAL:{

		manual(controlstate);

	}
	break;
	}
}


static void apagadoInit(control_t *MEF){
	MEF -> state = APAGADO;
}

static void riegoInit(control_t *MEF){
	MEF -> state = RIEGO;
	delayInit(&MEF -> delayfsm, DELAY_PUMP);
}

static void tanqueInit(control_t *MEF){
	MEF -> state = TANQUE;
	delayInit(&MEF -> delayfsm, DELAY_PUMP);
}

static void manualInit(control_t *MEF){
	MEF -> state = MANUAL;
}

static void apagado(control_t *MEF){

	MEF -> Vriego = FALSE;
	MEF -> Vtanque = FALSE;
	MEF -> Pump = FALSE;

	gpioWrite(LED1, MEF -> Vriego );
	gpioWrite(LED2, MEF -> Vtanque);
	gpioWrite(LED3, MEF -> Pump);
	gpioWrite(LEDB, OFF);

	if(tecla1.buttonpressed || tecla2.buttonpressed){
		riegoInit(MEF);
	}

	if(tecla3.buttonpressed){
		tanqueInit(MEF);
	}

	if(tecla4.buttonpressed){
		manualInit(MEF);
	}
}

static void riego(control_t *MEF){

	MEF -> Vriego = TRUE;
	MEF -> Vtanque = FALSE;

	if(delayRead(&MEF -> delayfsm)){
		MEF -> Pump = TRUE;
	}

	gpioWrite(LED1, MEF -> Vriego );
	gpioWrite(LED2, MEF -> Vtanque);
	gpioWrite(LED3, MEF -> Pump);
	gpioWrite(LEDB, OFF);

	if(tecla1.buttonpressed || tecla2.buttonpressed){
		MEF -> state = RIEGO;

		if(tecla4.buttonpressed){
			manualInit(MEF);
		}
	}
	else{
		apagadoInit(MEF);
	}
}

static void tanque(control_t *MEF){

	MEF -> Vriego = FALSE;
	MEF -> Vtanque = TRUE;

	if(delayRead(&MEF -> delayfsm)){
		MEF -> Pump = TRUE;
	}

	gpioWrite(LED1, MEF -> Vriego );
	gpioWrite(LED2, MEF -> Vtanque);
	gpioWrite(LED3, MEF -> Pump);
	gpioWrite(LEDB, OFF);

	if(tecla3.buttonpressed !=0 ){
		MEF -> state = TANQUE;

		if(tecla4.buttonpressed){
			MEF -> state = MANUAL;
		}
	}
	else{
		MEF -> state = APAGADO;
	}
}

static void manual(control_t *MEF){

	MEF -> Pump = FALSE;
	MEF -> Vriego = FALSE;
	MEF -> Vtanque = FALSE;

	gpioWrite(LED1, MEF -> Vriego );
	gpioWrite(LED2, MEF -> Vtanque);
	gpioWrite(LED3, MEF -> Pump);
	gpioWrite(LEDB, ON);

	if(tecla2.buttonpressed || tecla3.buttonpressed){
		gpioWrite(LED1, tecla2.buttonpressed);
		gpioWrite(LED2, tecla3.buttonpressed);
	}

	if(tecla1.buttonpressed){
		MEF -> state = APAGADO;
	}

}
