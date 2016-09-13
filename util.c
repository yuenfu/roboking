#include "util.h"

void create_sub_directories(char * path)
{
	char buf[PATH_MAX];
	char * p_buf = buf;
	strcpy(buf, path);
	while( *p_buf )
	{
		if(*p_buf == '/')
		{
			*p_buf = '\x00';
			if( access(buf, F_OK) != 0 )
			{
				mkdir(buf, 0777);
			}
			*p_buf = '/';
		}
		p_buf++;
	}	
	
	if( access(buf, F_OK) != 0 )
	{
		mkdir(buf, 0777);
	}
}

int str_ascii(char * buf)
{
	while( *buf )
	{
		if( *buf < 0x20 || *buf >= 0x7f )
		{
			return 0;
		}

		buf++;
	}
	return 1;
}
