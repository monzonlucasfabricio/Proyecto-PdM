/*
 * main.c
 *
 *  Created on: 20 abr. 2020
 *      Author: lucasml
 */

#include "sapi.h"
#include "MEF.h"
#include "debouncebutton.h"


int main(void){

	control_t quinta;

	boardInit();

	MEFinit(&quinta);

	while( true ){

		MEFupdate(&quinta);

	}

	return 0;
}



