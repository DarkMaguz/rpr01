/*
 * TermIO.cpp
 *
 *  Created on: 14/12/2015
 *      Author: magnus
 */

#include <iostream>
#include <cstdio>
//#include <thread>
//#include <pthread.h>

using namespace std;

#include <termio.h>
#include <sys/time.h>

#include "TermIO.h"

TermIO::TermIO( KeyEventHandler keyPressed, KeyEventHandler keyReleased, void *data ) :
	m_keyPressed( false ),
	m_hasTermios( false ),
	m_keyPressedHandler( keyPressed ),
	m_keyReleasedHandler( keyReleased ),
	m_data( data )
{
}

TermIO::~TermIO()
{
	ResetTerm();
}

int TermIO::GetChar( void )
{
	
	struct timeval start, end;
	long mtime, seconds, useconds;
	
	//mttx.lock();
	SetupTerm();
	
	gettimeofday( &start, NULL );
	
	int c = fgetc( stdin );
	
	gettimeofday( &end, NULL );
	
	seconds = end.tv_sec - start.tv_sec;
	useconds = end.tv_usec - start.tv_usec;
	
	mtime = seconds * 1000 + useconds / 1000.0;
	
	ResetTerm();
	//mttx.unlock();
	
	if ( mtime < 100 ) // Vent i 100 millisekunder.
	{
		if ( !m_keyPressed )
		{
			//cout << "KeyPressed!" << endl;
			//thread (m_keyPressedHandler, c ).detach();
			m_keyPressedHandler( c, m_data );
			m_keyPressed = true;
		}
	}
	else
	{
		if ( m_keyPressed )
		{
			//cout << "KeyReleased!" << endl;
			//m_keyReleasedHandler( c );
			//thread ( m_keyReleasedHandler, c ).detach();
			m_keyReleasedHandler( c, m_data );
			m_keyPressed = false;
		}
	}
	
	//cout << "Elapsed time: " << mtime << " milliseconds!" << endl;
	
	return c;
	
}

void TermIO::SetupTerm( void )
{
	
	struct termios buf;
	
	// Lav en backup af terminalens oprindlige tilstand.
	if ( tcgetattr( fileno( stdin ), &m_termios ) < 0 )
		throw "Error: Raw mode failed!";
	
	buf = m_termios;
	
	// echo off, canonical mode off, extended input processing off, signal chars off
	buf.c_lflag &= ~( ECHO | ICANON | IEXTEN | ISIG );
	
	// no SIGINT on BREAK, CR-toNL off, input parity check off, don't strip the 8th bit on input, ouput flow control off
	buf.c_iflag &= ~( BRKINT | ICRNL | ISTRIP | IXON );
	
	// clear size bits, parity checking off
	buf.c_cflag &= ~( CSIZE | PARENB );
	
	// set 8 bits/char
	buf.c_cflag |= CS8;
	
	// output processing off
	buf.c_oflag &= ~( OPOST );
	
	buf.c_cc[VMIN] = 0; // Vent ikke på der kommer data.
	buf.c_cc[VTIME] = 2; // Vent i 200 milisekunder på data.
	
	if ( tcsetattr( fileno( stdin ), TCSAFLUSH, &buf ) < 0 )
		throw;
	
	m_hasTermios = true;
	
}

void TermIO::ResetTerm( void )
{
	
	if ( m_hasTermios )
		if ( tcsetattr( fileno( stdin ), TCSAFLUSH, &m_termios ) < 0 )
			throw "Error: Raw mode reset failed!";
	
}
