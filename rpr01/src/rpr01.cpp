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
	
	gpio.SetAsOutput( 17 );
	gpio.SetAsOutput( 18 );
	
	gpio.SetHigh( 17 );
	
	sleep( 2 );
	
	gpio.SetLow( 17 );
	
	return 0;
	
}
