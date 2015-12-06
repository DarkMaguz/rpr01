/*
 ============================================================================
 Name        : rpr01.cpp
 Author      : me
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C++,
 ============================================================================
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
	gpio.SetAsOutput( pin ); // GPIO4(PIN 7) sat som output pin
	cout << "Færdig!" << endl;
	
	gpio.SetHigh( pin ); // Tænd for de røde LED
	sleep( 1 );
	gpio.SetLow( pin ); // Sluk for de røde LED
	
	cout << "Færdig!" << endl;
	cout << "Afslutter programmet..." << endl;
	
	return 0;
	
}
