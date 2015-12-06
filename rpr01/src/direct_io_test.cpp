/*
 * direct_io_test.cpp
 *
 *  Created on: 05/12/2015
 *      Author: magnus
 */

//
//  How to access GPIO registers from C-code on the Raspberry-Pi
//  Example program
//  15-January-2012
//  Dom and Gert
//  Revised: 15-Feb-2013

#define PI_VERSION 2

// Access from ARM Running Linux
#if PI_VERSION == 1
#define BCM2708_PERI_BASE 0x20000000
#elif PI_VERSION == 2
#define BCM2708_PERI_BASE 0x3F000000
#endif

#define GPIO_BASE (BCM2708_PERI_BASE + 0x200000) // GPIO controller

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

int mem_fd;
void *gpio_map;

// I/O access
volatile unsigned *gpio;

// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

#define GPIO_SET *(gpio+7) // sets bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio+10) // clears bits which are 1 ignores bits which are 0

#define GET_GPIO(g) (*(gpio+13)&(1<<g)) // 0 if LOW, (1<<g) if HIGH

#define GPIO_PULL *(gpio+37) // Pull up/pull down
#define GPIO_PULLCLK0 *(gpio+38) // Pull up/pull down clock

void setup_io();

void printButton( int g )
{
	if ( GET_GPIO( g ) ) // !=0 <-> bit is 1 <- port is HIGH=3.3V
		printf( "Button pressed!\n" );
	else
		// port is LOW=0V
		printf( "Button released!\n" );
}

int main( int argc, char **argv )
{
	
	// Set up gpi pointer for direct register access
	setup_io();
	
	/************************************************************************\
  * You are about to change the GPIO settings of your computer.          *
	 * Mess this up and it will stop working!                               *
	 * It might be a good idea to 'sync' before running this program        *
	 * so at least you still have your code changes written to the SD-card! *
	 \************************************************************************/

	int g = 4;
	// Set GPIO pin 4 to output
	INP_GPIO( g ); // must use INP_GPIO before we can use OUT_GPIO
	OUT_GPIO( g );
	
	for ( int i = 0; i < 3; i++ )
	{
		GPIO_SET = 1 << g;
		sleep( 1 );
		GPIO_CLR = 1 << g;
		sleep( 1 );
	}
	
	return 0;
	
}

// Set up a memory regions to access GPIO
void setup_io()
{
	// open /dev/mem
	if ( ( mem_fd = open( "/dev/mem", O_RDWR | O_SYNC ) ) < 0 )
	{
		printf( "can't open /dev/mem \n" );
		exit( -1 );
	}
	
	// mmap GPIO
	gpio_map = mmap(
	NULL, 										//Any adddress in our space will do
	BLOCK_SIZE,							//Map length
	PROT_READ | PROT_WRITE, 	// Enable reading & writting to mapped memory
	MAP_SHARED, 						//Shared with other processes
	mem_fd, 									//File to map
	GPIO_BASE 								//Offset to GPIO peripheral
	);
	
	close( mem_fd ); //No need to keep mem_fd open after mmap
	
	if ( gpio_map == MAP_FAILED )
	{
		printf( "mmap error %d\n", (int)gpio_map ); //errno also set!
		exit( -1 );
	}
	
	// Always use volatile pointer!
	gpio = (volatile unsigned *)gpio_map;
	
}
