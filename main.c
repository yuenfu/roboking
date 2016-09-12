#include "roboking.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void get_main_structure(FILE *, struct stMainHeader *);
void view_main_structure(struct stMainHeader);

void get_file_structure(FILE *, struct stReadSubHeader *);
void view_file_structure(struct stReadSubHeader);

void get_file_name(FILE *,unsigned char *, int);
void get_file_data(FILE *,unsigned char *, int);

int main(int argc, char **argv)
{
	if( argc < 3 )
	{
		printf("[+] Usage : %s ./update.dat ./result_directory", argv[0]);
		return 0;
	}
	
	FILE * fp = fopen(argv[1], "rb");
	if( !fp )
	{
		printf("[+] File Error : %s", argv[1]);
		return 0;
	}

	int res = mkdir(argv[2], 0777);
	if( res == -1 )
	{
		printf("[+] Directory Error : %s", argv[2]);
		return 0;
	}

	struct stMainHeader main_header;
	get_main_structure(fp, &main_header);
	view_main_structure(main_header);
	printf("\n");
	
	int count = 0;
	do
	{
		count += 1;
		struct stReadSubHeader file_header;
		get_file_structure(fp, &file_header);
		file_header.unDataSize = (file_header.unDataSize == 0xffffffff) ? 0 : file_header.unDataSize;

		unsigned char * file_name = (unsigned char *)malloc(sizeof(unsigned char) * file_header.unPathLength);
		get_file_name(fp, file_name, file_header.unPathLength);
		
		unsigned char * file_data = (unsigned char *)malloc(sizeof(unsigned char) * file_header.unDataSize);
		get_file_data(fp, file_data, file_header.unDataSize);
		
		FILE * dest_fp;	
		unsigned char dest_name[100];
		if ( file_header.unDataSize == 0 )
		{
			printf("[DIR] %s\n", file_name);
		}
		else
		{
			printf("%s\n", file_name);
		}

	}while( !feof(fp) );

	printf("[*] File Count : %d\n", count);
	printf("[*] File Size : 0x%lx \n", ftell(fp));

	fclose(fp);
}

void get_file_data(FILE* fp, unsigned char *data, int size)
{
	if( fp )
	{
		fread(data, 1, size, fp);
	}
	for(int i=0;i<size;i++)
	{
		if( data[i] < 0x80 )
		{
			data[i] = (data[i] + -128) & 0xff;
		}
		else
		{
			data[i] = (-1 - data[i])  & 0xff;
		}
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
