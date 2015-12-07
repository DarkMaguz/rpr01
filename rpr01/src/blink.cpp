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
	
	RaspPiGPIO gpio; // Lav et nyt GPIO object med tilknytning til GPIO4(PIN 7) den røde LED
	const int pin = 4;
	
	cout << "Sætter GPIO pin retningen... ";
	cout.flush();
	cout << gpio.GetState( 4 ) << endl;
	gpio.SetAsOutput( pin ); // GPIO4(PIN 7) sat som output pin
	cout << "Færdig!" << endl;
	
	cout << gpio.GetState( 4 ) << endl;
	
	gpio.SetHigh( pin ); // Tænd for de røde LED
	cout << gpio.GetState( 4 ) << endl;
	sleep( 1 );
	gpio.SetLow( pin ); // Sluk for de røde LED
	cout << gpio.GetState( 4 ) << endl;
	
	cout << "Færdig!" << endl;
	cout << "Afslutter programmet..." << endl;
	
	return 0;
	
}


