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
#include "GPIO.h"

using namespace std;

int main( int argc, char **argv )
{
	
	GPIO* gpio4 = new GPIO( "4" ); // Lav et nyt GPIO object med tilknytning til GPIO4(PIN 7) den røde LED
	
	cout << "Eksportere GPIO pins... ";
	cout.flush();
	gpio4->export_gpio(); // Eksporter GPIO4(PIN 7)
	cout << "Færdig!" << endl;
	
	cout << "Sætter GPIO pin retningen... ";
	cout.flush();
	gpio4->setdir_gpio( "out" ); // GPIO4(PIN 7) sat som output pin
	cout << "Færdig!" << endl;
	
	gpio4->setval_gpio( "1" ); // Tænd for de røde LED
	sleep( 3 );
	gpio4->setval_gpio( "0" ); // Sluk for de røde LED
	
	cout << "Afeksportere GPIO pins... ";
	cout.flush();
	gpio4->unexport_gpio(); //Afeksporter GPIO4(PIN 7)
	cout << "Færdig!" << endl;
	
	delete gpio4;
	
	cout << "Afslutter programmet..." << endl;
	
	return 0;
	
}
