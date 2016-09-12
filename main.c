#include "roboking.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	if( argc < 2 )
	{
		printf("[+] Usage : %s update.dat", argv[0]);
		return 0;
	}
	
	FILE * fp = fopen(argv[1], "rb");
	if( !fp )
	{
		printf("[+] File Error : %s", argv[1]);
		return 0;
	}

}
