
#include "wrapper.h"
#include <termios.h>
#include <unistd.h>

void reset_pty( void ){
	tcsetattr( STDIN_FILENO, TCSAFLUSH, &origin );
}
