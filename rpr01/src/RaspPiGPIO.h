/*
 * GPIO.h
 *
 *  Created on: 06/12/2015
 *      Author: magnus
 */

#ifndef RASPPIGPIO_H_
#define RASPPIGPIO_H_

class RaspPiGPIO
{
	public:
		RaspPiGPIO();
		virtual ~RaspPiGPIO();
		
		void SetAsInput( const int &pin );
		void SetAsOutput( const int &pin );
		void SetAsAlterateFunction( const int &pin, const int &alt );
		void SetHigh( const int &pin ); // ON
		void SetLow( const int &pin ); // OFF
		bool GetValue( const int &pin ) const;
		
	private:
		// File descriptor.
		int m_mem_fd;
		
		// I/O access.
		volatile unsigned *m_gpio;
		//volatile unsigned *m_pwm;
		
};

#endif /* RASPPIGPIO_H_ */
