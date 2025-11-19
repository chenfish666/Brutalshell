
#ifndef __BRUTALSHELL_WRAPPER_H__
#define __BRUTALSHELL_WRAPPER_H__

#include <termios.h>

#include <unistd.h>

extern struct termios origin;
extern int loglevel;
extern int logfd;

int connect_daemon( const char *restrict, int method, ... );
int send_daemon( int method, int fd, char *restrict, ssize_t );

int read_pty( void );
int set_pty( void ); /* raw pty */
void reset_pty( void );

void usage( const char *restrict );

void get_configure( int, char **, const char *restrict );

enum LOGLEVVELS {
	log_error,
	log_warning,
	log_normal,
	log_debug,
};

#endif
