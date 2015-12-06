/*
 * RpIO.cpp
 *
 *  Created on: 06/12/2015
 *      Author: magnus
 */

#include <iostream>

#include "RpIO.h"
#include "GPIO.h"

RpIO::RpIO( int gpioPin ) :
	m_gpioPin( gpioPin )
{
}

RpIO::~RpIO()
{
}

GPIO& RpIO::getGPIO( void )
{
	static GPIO gpio;
	return gpio;
}
