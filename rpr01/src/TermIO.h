/*
 * TermIO.h
 *
 *  Created on: 14/12/2015
 *      Author: magnus
 */

#ifndef TERMIO_H_
#define TERMIO_H_

#include <termio.h>

typedef void (*KeyEventHandler)( int, void* );

class TermIO
{
	public:
		TermIO( KeyEventHandler keyPressed, KeyEventHandler keyReleased, void *data = NULL );
		virtual ~TermIO();
		//void SetupHandler( KeyPressHandler keyPressed, KeyPressHandler keyReleased  );
		
		int GetChar( void ); // Få input fra terminalen.
		
	private:
		void SetupTerm( void ); // Klargør terminalen.
		void ResetTerm( void ); // Set terminalen's attributer tilbage som de var før.
		
		termios m_termios;
		bool m_hasTermios;
		
		bool m_keyPressed;
		KeyEventHandler m_keyPressedHandler;
		KeyEventHandler m_keyReleasedHandler;
		void *m_data;
		
};

#endif /* TERMIO_H_ */
