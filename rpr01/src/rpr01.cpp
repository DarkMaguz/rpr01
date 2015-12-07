/*
 * rpr01.cpp
 *
 *  Created on: 07/12/2015
 *      Author: magnus
 */

#include <iostream>
#include <unistd.h>
#include <ncurses.h>

#include "RaspPiGPIO.h"

using namespace std;

//#include <SDL2/SDL.h>
//#include <stdio.h>

int main( int argc, char **argv )
{
	
//	SDL_Event event;
//	bool quit = false;
//	
//	/* Initialise SDL */
//	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
//	{
//		fprintf( stderr, "Could not initialise SDL: %s\n", SDL_GetError() );
//		exit( -1 );
//	}
//	
//	/* Poll for events. SDL_PollEvent() returns 0 when there are no  */
//	/* more events on the event queue, our while loop will exit when */
//	/* that occurs.                                                  */
//	while ( SDL_WaitEvent( &event ) )
//	{
//		/* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
//		switch ( event.key.keysym.sym )
//		{
//			case SDLK_ESCAPE:
//				printf( "Escape key press detected\n" );
//				break;
//			default:
//				printf( "aKey press detected\n" );
//				break;
//		}
//		switch ( event.type )
//		{
//			case SDL_KEYDOWN:
//				printf( "Key press detected\n" );
//				//quit = true;
//				switch ( event.key.keysym.sym )
//				{
//					case SDLK_UP:
//						std::cout << "Up pressed" << std::endl;
//						break;
//					case SDLK_DOWN:
//						std::cout << "Down pressed" << std::endl;
//						break;
//					case SDLK_LEFT:
//						std::cout << "Left pressed" << std::endl;
//						break;
//					case SDLK_RIGHT:
//						std::cout << "Right pressed" << std::endl;
//						break;
//				}
//				break;
//			case SDL_KEYUP:
//				printf( "Key release detected\n" );
//				//quit = true;
//				switch ( event.key.keysym.sym )
//				{
//					case SDLK_UP:
//						std::cout << "Up released" << std::endl;
//						break;
//					case SDLK_DOWN:
//						std::cout << "Down released" << std::endl;
//						break;
//					case SDLK_LEFT:
//						std::cout << "Left released" << std::endl;
//						break;
//					case SDLK_RIGHT:
//						std::cout << "Right released" << std::endl;
//						break;
//				}
//				break;
//			case SDL_QUIT:
//				std::cout << "Quit event..." << std::endl;
//				quit = true;
//				break;
//			default:
//				cout << "event.type: " << event.type << endl;
//				std::cout << "Some event..." << std::endl;
//				break;
//		}
//		SDL_Delay( 100 );
//		
//		if ( quit )
//			break;
//		
//	}
//	
//	SDL_Quit();
	
	initscr();
	raw();
	keypad( stdscr, TRUE );
	noecho();
	int c;
	printw( "Press any key or ESC to exit..." );
	while ( ( c= getch() ) )
	{
		switch ( c )
		{
			case 27:
				printw( "ESCAPE" );
				break;
			case KEY_UP:
				printw( "UP" );
				break;
			case KEY_DOWN:
				printw( "DOWN" );
				break;
			case KEY_LEFT:
				printw( "LEFT" );
				break;
			case KEY_RIGHT:
				printw( "RIGHT" );
				break;
			default:
				mvprintw( 24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c );
				refresh();
				break;
		}
		
		if ( c == 27 )
			break;
		
		/*move( 10, 0 );
		printw( "Keycode: %d, char: %c\n", c, c );
		move( 0, 0 );
		printw( "Press any key or ESC to exit..." );
		refresh();*/
	}
	
	endwin();
	
//	RaspPiGPIO gpio; // Lav et nyt GPIO object.
//	
//	int pin1 = 17;
//	
//	gpio.SetAsOutput( pin1 );
//	//gpio.SetAsOutput( pin2 );
//	
//	gpio.SetHigh( pin1 );
//	
//	sleep( 5 );
//	
//	gpio.SetLow( pin1 );
	
	return 0;
	
}


