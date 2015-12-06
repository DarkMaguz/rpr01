/*
 * GPIO.h
 *
 *  Created on: 06/12/2015
 *      Author: magnus
 */

#ifndef RASPPIGPIO_H_
#define RASPPIGPIO_H_

// Raspberry Pi 2 pins.
enum Pins
{
	
	PIN3 = 2,
	PIN5 = 3,
	PIN7 = 4,
	PIN8 = 14,
	PIN10 = 15,
	PIN11 = 17,
	PIN12 = 18,
	PIN13 = 27,
	PIN15 = 22,
	PIN16 = 23,
	PIN18 = 24,
	PIN19 = 10,
	PIN21 = 9,
	PIN22 = 25,
	PIN23 = 11,
	PIN24 = 8,
	PIN26 = 7
	
};

class RaspPiGPIO
{
	public:
		RaspPiGPIO();
		virtual ~RaspPiGPIO();

		void SetAsInput( const int &pin );
		void SetAsOutput( const int &pin );
		void SetAsAlterateFunction( const int &pin, const int &alt );
		int GetState( const int &pin ) const;
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
