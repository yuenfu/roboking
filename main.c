#include "roboking.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void get_main_structure(FILE *, struct stMainHeader *);
void view_main_structure(struct stMainHeader);

void get_file_structure(FILE *, struct stReadSubHeader *);
void view_file_structure(struct stReadSubHeader);

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
	
	struct stReadSubHeader file_header;
	get_file_structure(fp, &file_header);
	view_file_structure(file_header);	
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
