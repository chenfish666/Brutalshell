
#include "wrapper.h"

#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>
#include <alloca.h>
#include <limits.h>

#ifndef BUFLEN
#define BUFLEN 256
#endif

#ifndef BSH_CONFIGPATH
#define BSH_CONFIGPATH "/etc/brutalshell/config.conf"
#endif

struct config get_configure( int argc, char **restrict argv ){

	static const char *arg_default[] = { "/bin/sh", NULL };

	register struct config cfg = {};

	register int fd;

	register char *restrict cfg_path = BSH_CONFIGPATH;
	register char *buf;
	register ssize_t rlen;

	register char *restrict cfg_home;

	cfg.logfd = logfd = STDERR_FILENO;

	if ( argc < 2 ){
		cfg.argv = (void *)arg_default;
		memset( cfg.argv, 0, sizeof( *cfg.argv ) * 2 );
		*cfg.argv = "/bin/sh";
	} else {

		if ( !strcmp( "c", *( argv + 1 ) ) && argc > 2 ){
			cfg_path = *( argv + 2 );
			cfg.argv = argv + 3;
		} else if ( !strcmp( "?", *( argv + 1 ) ) ){
			usage( *argv );
			return cfg;
		}else{
			cfg.argv = argv + 1;
		}

		fd = open( cfg_path, O_RDONLY );
		if ( fd < 0 ){

			if ( ( fd = open( getenv( "BSH_CFG" ), O_RDONLY ) ) < 0 ){

				cfg.desc = getenv( "HOME" );
				if ( !cfg.desc ){
					return cfg;
				}
				cfg_home = malloc( PATH_MAX );
				memset( cfg_home, 0, PATH_MAX );
				cfg.desc = strcpy( cfg_home, cfg.desc );
				strncpy( cfg.desc, "/.config/bsh/config.conf", PATH_MAX - strlen( cfg_home ) - 1 );

				cfg.desc = NULL;

				fd = open( cfg_home, O_RDONLY );
				free( cfg_home );
				if ( fd < 0 ){
					return cfg;
				}

			}
		}

		buf = malloc( BUFLEN );

		while ( ( rlen = read( fd, buf, BUFLEN ) ) > 0 ){
			/* parse configs */
		}

		free( buf );

		close( fd );
	}

	return cfg;

}
