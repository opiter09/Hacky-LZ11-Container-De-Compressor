#pragma once

#define COMPRESSION_NONE             0
#define COMPRESSION_LZ77             1
#define COMPRESSION_LZ11             2
#define COMPRESSION_LZ11_COMP_HEADER 3
#define COMPRESSION_HUFFMAN_4        4
#define COMPRESSION_HUFFMAN_8        5

/*
* char * lz77Decompress(char * buffer, int size, int * uncompressedSize)
*
* Returns a pointer to the uncompressed data.
*
* Returns:
*  NULL if the call failed
*  the pointer to the uncompressed data if the call was successful
*/
char *lz77decompress(char *buffer, int size, int *uncompressedSize);


/*
* char * lz77Compress(char * buffer, int size, int * compressedSize)
*
* Returns a pointer to a buffer containing the compressed data.
*
* Returns:
*  NULL if the call failed
*  the pointer to the compressed data if the call was successful
*/
char *lz77compress(char *buffer, int size, int *compressedSize);


/*
* int lz77IsCompressed(char * buffer, unsigned size)
*
* Determines whether the input buffer contains valid lz77 compressed data.
*
* Returns:
*  0 if the buffer does not contain valid lz77 compressed data
*  1 if the buffer does contain valid lz77 compressed data
*/
int lz77IsCompressed(char *buffer, unsigned size);

int getCompressionType(char *buffer, int size);

char *decompress(char *buffer, int size, int *uncompressedSize);

char *compress(char *buffer, int size, int compression, int *compressedSize);

char *lz11CompHeaderCompress(char *buffer, int size, int *compressedSize);
