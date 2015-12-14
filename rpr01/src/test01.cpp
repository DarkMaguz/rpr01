/*
 * test01.cpp
 *
 *  Created on: 07/12/2015
 *      Author: magnus
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <termio.h>
#include <sys/time.h>
#include <unistd.h>
#include <ctime>

using namespace std;

static struct termios save_termios;
static int term_saved;

int tty_raw( int fd )
{
	/* RAW! mode */
	struct termios buf;
	
	if ( tcgetattr( fd, &save_termios ) < 0 ) /* get the original state */
		return -1;
	
	buf = save_termios;
	
	buf.c_lflag &= ~( ECHO | ICANON | IEXTEN | ISIG );
	/* echo off, canonical mode off, extended input
	 processing off, signal chars off */

	buf.c_iflag &= ~( BRKINT | ICRNL | ISTRIP | IXON );
	/* no SIGINT on BREAK, CR-toNL off, input parity
	 check off, don't strip the 8th bit on input,
	 ouput flow control off */

	buf.c_cflag &= ~( CSIZE | PARENB );
	/* clear size bits, parity checking off */

	buf.c_cflag |= CS8;
	/* set 8 bits/char */

	buf.c_oflag &= ~( OPOST );
	/* output processing off */

	buf.c_cc[VMIN] = 0; /* 1 byte at a time */
	buf.c_cc[VTIME] = 2; /* no timer on input */
	
	if ( tcsetattr( fd, TCSAFLUSH, &buf ) < 0 )
		return -1;
	
	term_saved = 1;
	
	return 0;
}

int tty_reset( int fd )
{
	/* set it to normal! */
	if ( term_saved )
		if ( tcsetattr( fd, TCSAFLUSH, &save_termios ) < 0 )
			return -1;
	
	return 0;
}

int getch( void )
{
	
	static int keyPressed = 0;
	
	struct timeval start, end;
	
	long mtime, seconds, useconds;
	
	if ( tty_raw( fileno(stdin) ) )
	{
		std::cout << "Error: Raw mode failed!" << std::endl;
		return -1;
	}
	
	gettimeofday( &start, NULL );
	
	int c = fgetc( stdin );
	
	gettimeofday( &end, NULL );
	
	seconds = end.tv_sec - start.tv_sec;
	useconds = end.tv_usec - start.tv_usec;
	
	mtime = seconds * 1000 + useconds / 1000.0;
	
	if ( tty_reset( fileno(stdin) ) )
	{
		std::cout << "Error: Raw mode reset failed!" << std::endl;
		return -1;
	}
	
	if ( mtime < 100 ) // Vent i 100 millisekunder.
	{
		if ( !keyPressed )
		{
			cout << "KeyPressed!" << endl;
			keyPressed++;
		}
	}
	else
	{
		if ( keyPressed )
		{
			cout << "KeyReleased!" << endl;
			keyPressed--;
		}
	}
	
	//cout << "Elapsed time: " << mtime << " milliseconds!" << endl;
	
	return c;
	
}

int main( int argc, char **argv )
{
	
	std::cout << "Press a key..." << std::endl;
	
	int i = 0;
	
	while ( 1 )
	{
		
		int c = getch();
		
		std::cout << "You pressed: " << c  << std::endl;
		
		if ( c == 27 )
			break;
		
		i++;
		
	}
	
	std::cout << "You pressed a key " << i  << " times." << std::endl;
	
	return 0;
	
}

