/*
 * RpIO.h
 *
 *  Created on: 06/12/2015
 *      Author: magnus
 */

#ifndef RPIO_H_
#define RPIO_H_

#include "RaspPiGPIO.h"

class RpIO
{
	public:
		RpIO( int gpioPin );
		virtual ~RpIO();
		
	private:
		RaspPiGPIO& getGPIO( void );
		
		int m_gpioPin;
		
};

#endif /* RPIO_H_ */
