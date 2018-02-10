#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main( int argc, char *argv[])
{
	int fd;

	const int BUF_size = 4096;
	char buf[BUF_size];
	
	char char_status[260] = {0};
	char *ptr, *end;

	size_t result;
	int cnt;

	assert( argc == 2 || argc == 3 );

	if( argc == 2 )
	{
		fd = 0;
	}
	else if( argc == 3 )
	{
		fd = open( argv[2], O_RDONLY);
		if( fd < 0 )
		{
			write( 1, "error\n", sizeof("error\n"));
			return 0;
		}
	}

	for( ptr = argv[1]; *ptr; ptr++)
		char_status[ (int) *ptr] = 1;

	cnt = 0;
	while( (result = read( fd, buf, BUF_size)) )
	{
		ptr = buf;
		end = buf + result;
		for( ; ptr != end; ptr++)
		{
			if( *ptr == '\n' )
			{
				printf("%d\n", cnt);
				cnt = 0;
			}
			else
			{
				cnt += char_status[*ptr];
			}
		}
	}
	close(fd);
	return 0;
}

