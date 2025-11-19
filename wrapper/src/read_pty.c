
#include "wrapper.h"
#include <termios.h>
#include <unistd.h>

int read_pty( void ){

	return tcgetattr( STDIN_FILENO, &origin );

}
