/*
 * CSolidSBCStringConverter.cpp
 *
 *  Created on: 13.09.2011
 *      Author: Moritz Wagner
 */

#include "CSolidSBCStringConverter.h"

#include <iconv.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define CONVERTER_ZERO_PAD_SIZE      4
#define CONVERTER_REALLOC_BLOCK_SIZE 16

CSolidSBCStringConverter g_cStringConverter;

CSolidSBCStringConverter* CSolidSBCStringConverter::GetInstance(void)
{
	return &g_cStringConverter;
}

CSolidSBCStringConverter::CSolidSBCStringConverter(void)
{
}

CSolidSBCStringConverter::~CSolidSBCStringConverter(void)
{
}

bool CSolidSBCStringConverter::ConvertToUTF16LE(const std::string& sInput, char** ppszOutput, int* pnOutputSize, const char* pszInputEncoding) const
{
	return Convert(sInput.c_str(),strlen(sInput.c_str())+1,pszInputEncoding,ppszOutput,pnOutputSize,"UTF16LE");
}

bool CSolidSBCStringConverter::ConvertToUTF8(const char* pszInput, const int nInputSize, std::string& sOutput, const char* pszInputEncoding) const
{
	char* pszOutput = 0;
	int nOutputSize = 0;
	bool bSuccess = Convert(pszInput,nInputSize,pszInputEncoding,&pszOutput,&nOutputSize,"UTF8");
	if(bSuccess)
		sOutput = pszOutput;
	if(pszOutput)
		free(pszOutput);
	return bSuccess;
}

bool CSolidSBCStringConverter::Convert(const char* pszInput, const int nInputSize, const char* pszInputEncoding, char** ppszOutput, int* pnOutputSize, const char* pszOutputEncoding) const
{
	*ppszOutput   = 0;
	*pnOutputSize = 0;

	iconv_t h_iconv = (iconv_t)-1;
	if ((h_iconv = iconv_open(pszOutputEncoding,pszInputEncoding)) == (iconv_t)-1){
		return false;}

	char* pszInputBuffer    = new char[nInputSize];
	char* pszInputBufferPos = pszInputBuffer;
	memcpy(pszInputBuffer,pszInput,nInputSize);
	size_t nInputBytesLeft    = (size_t)nInputSize;

	char*  pszOutputBuffer    = (char*)malloc(nInputSize);
	char*  pszOutputBufferPos = pszOutputBuffer;
	size_t  nOutputBufferSize = nInputSize;
	size_t  nOutputBytesLeft  = nInputSize;

	bool bBreak = false;
	size_t nTotalConverted = 0;
	while(nInputBytesLeft && !bBreak)
	{
		size_t nBytesConverted = 0;
		if ( (nBytesConverted = iconv(h_iconv, &pszInputBufferPos, &nInputBytesLeft, &pszOutputBufferPos, &nOutputBytesLeft)) == (size_t)-1 )
		{
			switch(errno)
			{
			case E2BIG:
				{
					int nOffSet        = pszOutputBufferPos - pszOutputBuffer;
					pszOutputBuffer    = ResizeOutputBuffer(pszOutputBuffer, &nOutputBufferSize, CONVERTER_REALLOC_BLOCK_SIZE);
					pszOutputBufferPos = &pszOutputBuffer[nOffSet/*-nOutputBytesLeft*/];
					nOutputBytesLeft  += CONVERTER_REALLOC_BLOCK_SIZE;
				}
				break;

			case EINVAL:
				if (nInputBytesLeft == 1){
					bBreak = true;
					break;
				}

			case EILSEQ:
			default:
				if(pszOutputBuffer)
					free(pszOutputBuffer);
				*ppszOutput   = 0;
				*pnOutputSize = 0;
				delete [] pszInputBuffer;
				return false;
			}
		}
		else
		{
			nTotalConverted++;
		}
	}
	iconv_close(h_iconv);

	if((nOutputBufferSize - nOutputBytesLeft) <= 0)
	{
		if(pszOutputBuffer)
			free(pszOutputBuffer);
		*ppszOutput   = 0;
		*pnOutputSize = 0;
		delete [] pszInputBuffer;
		return false;
	}
	else if( nOutputBytesLeft < CONVERTER_ZERO_PAD_SIZE )
	{
		//resizing while already pad with zeros, so we dont need to set them here
		pszOutputBuffer = ResizeOutputBuffer(pszOutputBuffer, &nOutputBufferSize, CONVERTER_ZERO_PAD_SIZE - nOutputBytesLeft, true);
	}

	*ppszOutput   = pszOutputBuffer;
	*pnOutputSize = nOutputBufferSize - nOutputBytesLeft;

	delete [] pszInputBuffer;
	return true;
}

char* CSolidSBCStringConverter::ResizeOutputBuffer(char* pszOutput, size_t* pnOutputSize, const size_t nAddSize, const bool bZeroNewMemory) const
{
	if(nAddSize <= 0)
		return false;

	pszOutput = (char*)realloc(pszOutput,(*pnOutputSize) + nAddSize);
	if(bZeroNewMemory)
		memset(&pszOutput[(*pnOutputSize)],0,nAddSize);
	*pnOutputSize += nAddSize;
	return pszOutput;
}
