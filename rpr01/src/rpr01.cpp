/*
 * blink.cpp
 *
 *  Created on: 07/12/2015
 *      Author: magnus
 */

#include <iostream>
#include <unistd.h>

#include "RaspPiGPIO.h"

using namespace std;

int main( int argc, char **argv )
{
	
	RaspPiGPIO gpio; // Lav et nyt GPIO object.
	
	int pin1 = 18;
	
	gpio.SetAsOutput( pin1 );
	//gpio.SetAsOutput( pin2 );
	
	gpio.SetHigh( pin1 );
	
	sleep( 5 );
	
	gpio.SetLow( pin1 );
	
	return 0;
	
}
