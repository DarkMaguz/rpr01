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
			//gpio->SetHigh( 22 );
			cout << "kør frem.";
			break;
		case 's': // Kør tilbage.
			gpio->SetHigh( 18 );
			//gpio->SetHigh( 23 );
			cout << "kør tilbage.";
			break;
		case 'a': // Drej til venstre.
			cout << "drej til venstre.";
			break;
		case 'd': // Drej til højre.
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
	
	// Efter som vi ikke ved hvilken motor der gør hvad så lukker vi bare for alle udgange.
	gpio->SetLow( 17 );
	gpio->SetLow( 18 );
	gpio->SetLow( 22 );
	gpio->SetLow( 23 );
	
	cout  << "Stop" << endl;
	
}

int main( int argc, char **argv )
{
	
	RaspPiGPIO gpio; // Lav et nyt GPIO object.
	
	TermIO tio( &KeyPressed, &keyReleased, (void *)&gpio );
	
	while ( 1 )
	{
		
		int c = tio.GetChar();
		
		if ( c == 27 )
			break;
		
	}
	
	return 0;
	
}


