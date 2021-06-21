#pragma once

#include "nclr.h"

#define NCGR_TYPE_INVALID	0
#define NCGR_TYPE_NCGR		1
#define NCGR_TYPE_HUDSON	2
#define NCGR_TYPE_HUDSON2	3
#define NCGR_TYPE_NCBR      4
#define NCGR_TYPE_BIN       5

extern LPCWSTR characterFormatNames[];

typedef struct NCGR_{
	OBJECT_HEADER header;
	int nTiles;
	int tilesX;
	int tilesY;
	int mapping;
	int nBits;
	int tileWidth;
	BYTE **tiles;
} NCGR;

int calculateWidth(int nTiles);

int ncgrIsValidHudson(LPBYTE buffer, int size);

int ncgrIsValidBin(LPBYTE buffer, int size);

int ncgrGetTile(NCGR * ncgr, NCLR * nclr, int x, int y, DWORD * out, int previewPalette, BOOL drawChecker);

int ncgrReadFile(NCGR *ncgr, LPCWSTR path);

void ncgrWrite(NCGR * ncgr, LPWSTR name);

void ncgrCreate(DWORD * blocks, int nBlocks, int nBits, LPWSTR name, int fmt);