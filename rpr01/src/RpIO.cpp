/*
 * RpIO.cpp
 *
 *  Created on: 06/12/2015
 *      Author: magnus
 */

#include <RaspPiGPIO.h>
#include <iostream>

#include "RpIO.h"

RpIO::RpIO( int gpioPin ) :
	m_gpioPin( gpioPin )
{
}

RpIO::~RpIO()
{
}

RaspPiGPIO& RpIO::getGPIO( void )
{
	static RaspPiGPIO gpio;
	return gpio;
}
