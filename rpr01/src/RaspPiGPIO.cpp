/*
 * GPIO.cpp
 *
 *  Created on: 06/12/2015
 *      Author: magnus
 */

#include "RaspPiGPIO.h"

#define PI_VERSION 2

// Access from ARM Running Linux
#if PI_VERSION == 1
#define BCM2708_PERI_BASE 0x20000000
#elif PI_VERSION == 2
#define BCM2708_PERI_BASE 0x3F000000
#endif

#define CLOCK_BASE (BCM2708_PERI_BASE + 0x00101000)
#define GPIO_BASE (BCM2708_PERI_BASE + 0x00200000) // GPIO controller
#define GPIO_PWM (BCM2708_PERI_BASE + 0x0020C000)

#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <iostream>

using namespace std;

RaspPiGPIO::RaspPiGPIO()
{
	
	// Åben /dev/mem.
	if ( ( m_mem_fd = open( "/dev/mem", O_RDWR | O_SYNC ) ) < 0 )
	{
		cout << "Kan ikke åbne \"/dev/mem\", har du de rigtige rettighedder?" << endl;
		exit( -1 );
	}
	
	// Access memory map to the GPIO.
	m_gpio = (volatile unsigned *)mmap(
	NULL, 											//Any adddress in our space will do
	BLOCK_SIZE,								//Map length
	PROT_READ | PROT_WRITE, 	// Enable reading & writting to mapped memory
	MAP_SHARED, 							//Shared with other processes
	m_mem_fd, 									//File to map
	GPIO_BASE 								//Offset to GPIO peripheral
	);
	
	// Test for failure.
	if ( m_gpio == MAP_FAILED )
	{
		perror( "mmap faild to access memory map to the GPIO: " );
		exit( -1 );
	}
	
//	// Access memory map to the PWM.
//	m_pwm = (volatile unsigned *)mmap(
//	NULL, 											//Any adddress in our space will do
//	BLOCK_SIZE,								//Map length
//	PROT_READ | PROT_WRITE, 	// Enable reading & writting to mapped memory
//	MAP_SHARED, 							//Shared with other processes
//	m_mem_fd, 									//File to map
//	GPIO_PWM 								//Offset to GPIO PWM peripheral
//	);
//	
//	// Test for failure.
//	if ( m_pwm == MAP_FAILED )
//	{
//		perror( "mmap faild to access memory map to the PWM: " );
//		exit( -1 );
//	}
	
}

RaspPiGPIO::~RaspPiGPIO()
{
	
	// Ryd alle GPIO's.
	// TODO Find en måde og nulstille alle ind/ud og deres respektive værdier.
	// Find ud af om det overhoved er noget vi bør bekymer os om.
	
	// Unmap I/O access.
	munmap( (void *)m_gpio, BLOCK_SIZE );
	//munmap( (unsigned *)m_pwm, BLOCK_SIZE );
	
	// Close /dev/mem file descriptor.
	close( m_mem_fd );
	
}

// #define INP_GPIO(g) *(gpio         + ((g)/10)) &= ~(7<<(((g)%10)*3))
// #define INP_GPIO(g) *(gpio.addr + ((g)/10)) &= ~(7<<(((g)%10)*3))
void RaspPiGPIO::SetAsInput( const int &pin )
{
	*( m_gpio + ( pin / 10 ) ) &= ~( 7 << ( ( pin % 10 ) * 3 ) );
}

// #define OUT_GPIO(g) *(gpio           + ((g)/10)) |=  (1<<(((g)%10)*3))
// #define OUT_GPIO(g)   *(gpio.addr + ((g)/10)) |=  (1<<(((g)%10)*3))
void RaspPiGPIO::SetAsOutput( const int &pin )
{
	// First we have to clear the register so we are sure that all 3 bits are zero.
	SetAsInput( pin );
	*( m_gpio + ( pin / 10 ) ) |= ( 1 << ( ( pin % 10 ) * 3 ) );
}

// #define SET_GPIO_ALT(g,a) *(gpio.addr + (((g)/10))) |= (((a)<=3?(a) + 4:(a)==4?3:2)<<(((g)%10)*3))
void RaspPiGPIO::SetAsAlterateFunction( const int &pin, const int &alt )
{
	// First we have to clear the register so we are sure that all 3 bits are zero.
	SetAsInput( pin );
	*( m_gpio + ( pin / 10 ) ) |= ( ( alt <= 3 ? alt + 4 : alt == 4 ? 3 : 2  ) << ( ( pin % 10 ) * 3 ) );
}

int RaspPiGPIO::GetState( const int &pin ) const
{
	
	int r = *( m_gpio + ( pin / 10 ) );
	
	for ( int j = 0; j < 10; j++ )
	{
		for ( int i = 0; i < 3; i++ )
		{
			std::cout << (r % 2); 
			r /= 2;
		}
		std::cout << "*";
	}
	
	std::cout << (r % 2); 
	r /= 2;
	std::cout << (r % 2); 
	
	std::cout << "\n";
	
	return r;
}

// *(gpio.addr + 7) = 1 << pin
void RaspPiGPIO::SetHigh( const int &pin )
{
	*( m_gpio + 7 ) = 1 << pin;
}

void RaspPiGPIO::SetLow( const int &pin )
{
	*( m_gpio + 10 ) = 1 << pin;
}

// #define GPIO_READ(g)  *(gpio.addr + 13) &= (1<<(g))
bool RaspPiGPIO::GetValue( const int &pin ) const
{
	return *( m_gpio + 13 ) & ( 1 << pin );
}









