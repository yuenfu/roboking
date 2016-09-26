#pragma once
struct stMainHeader
{
	unsigned int unRevision;
	unsigned int unFirmwareSize;
	unsigned int unChecksum;
	unsigned char szPartNumber[0x10];
};

struct stReadSubHeader
{
	unsigned int unDataSize;
	unsigned short unPathLength;
	unsigned short unFlag;
};

