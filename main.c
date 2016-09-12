#include "roboking.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void get_main_structure(FILE *, struct stMainHeader *);
void view_main_structure(struct stMainHeader);

void get_file_structure(FILE *, struct stReadSubHeader *);
void view_file_structure(struct stReadSubHeader);

void get_file_name(FILE *,unsigned char *, int);

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

	struct stMainHeader main_header;
	get_main_structure(fp, &main_header);
	view_main_structure(main_header);
	printf("\n");

	while( !feof(fp) )
	{
		struct stReadSubHeader file_header;
		get_file_structure(fp, &file_header);
		view_file_structure(file_header);
		
		unsigned char * file_name = (unsigned char *)malloc(sizeof(unsigned char) * file_header.unPathLength);
		get_file_name(fp, file_name, file_header.unPathLength);
		printf("%s", file_name);
		printf("\n");
		return -1;
	}
}

void get_file_name(FILE * fp, unsigned char * name, int size)
{
	int i;

	if( fp )
	{
		fread(name, 1, size, fp);
	}

	for (i = 0; i < size; i++)
	{
		if (name[i] >= 0x80)
		{
			name[i] = (-1 - name[i]) & 0xff;
		}
		else
		{
			name[i] = (name[i] + -0x80) & 0xff;
		}
	}
	name[i] = '\x00';
}

void get_main_structure(FILE * fp, struct stMainHeader * main_header)
{
	if( fp )
	{
		fread(main_header, 1, sizeof(struct stMainHeader), fp); 	
	}
}

void view_main_structure(struct stMainHeader header)
{
	printf("Revision : 0x%x\n", header.unRevision);
	printf("FirmwareSize : 0x%x\n", header.unFirmwareSize);
	printf("Checksum : 0x%x\n", header.unChecksum);
	printf("szPartNumber : ");
	for (int i = 0; ((unsigned char)header.szPartNumber[i]) != '\x00'; i++)
	{
		printf("%c", header.szPartNumber[i]);
	}
	printf("\n");
}

void get_file_structure(FILE *fp, struct stReadSubHeader * file_header)
{
	if( fp )
	{
		fread(file_header, 1, sizeof(struct stReadSubHeader), fp);
	}
}

void view_file_structure(struct stReadSubHeader header)
{
	printf("Data Size : 0x%x\n", header.unDataSize);
	printf("Path Length : 0x%x\n", header.unPathLength);
	printf("Flag : 0x%x\n", header.unFlag);
}
