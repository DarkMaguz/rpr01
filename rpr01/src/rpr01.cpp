/*
 * rpr01.cpp
 *
 *  Created on: 07/12/2015
 *      Author: magnus
 */

#include <iostream>

using namespace std;

#include "RaspPiGPIO.h"
#include "TermIO.h"

void KeyPressed( int c, void *data )
{
	
	RaspPiGPIO *gpio = (RaspPiGPIO *)data;
	
	cout  << "Start: ";
	
	switch ( c )
	{
		case 'w': // Kør frem.
			gpio->SetHigh( 17 );
			gpio->SetHigh( 22 );
			cout << "kør frem.";
			break;
		case 's': // Kør tilbage.
			gpio->SetHigh( 18 );
			gpio->SetHigh( 23 );
			cout << "kør tilbage.";
			break;
		case 'a': // Drej til venstre.
			gpio->SetHigh( 18 );
			gpio->SetHigh( 22 );
			cout << "drej til venstre.";
			break;
		case 'd': // Drej til højre.
			gpio->SetHigh( 17 );
			gpio->SetHigh( 23 );
			cout << "drej til højre.";
			break;
			
		default:
			break;
	}
	
	cout << endl;
	
}

void keyReleased( int c, void *data )
{
	
	RaspPiGPIO *gpio = (RaspPiGPIO *)data;
	
	// Efter som vi ikke ved hvilken motor der gør hvad LIGE NU, så slukker vi bare for alle udgange.
	gpio->SetLow( 17 ); // Venstre motor 1.
	gpio->SetLow( 18 ); // Venstre motor 2.
	gpio->SetLow( 22 ); // Højre motor 1.
	gpio->SetLow( 23 ); // Højre motor 2.
	
	cout  << "Stop" << endl;
	
}

int main( int argc, char **argv )
{
	
	RaspPiGPIO gpio; // Lav et nyt GPIO object.
	
	gpio.SetAsOutput( 17 );
	gpio.SetAsOutput( 18 );
	gpio.SetAsOutput( 22 );
	gpio.SetAsOutput( 23 );
	
	TermIO tio( &KeyPressed, &keyReleased, (void *)&gpio );
	
	while ( 1 )
	{
		
		int c = tio.GetChar();
		
		if ( c == 27 )
			break;
		
	}
	
	return 0;
	
}


