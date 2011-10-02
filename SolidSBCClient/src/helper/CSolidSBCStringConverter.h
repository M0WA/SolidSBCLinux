/*
 * CSolidSBCStringConverter.h
 *
 *  Created on: 13.09.2011
 *      Author: Moritz Wagner
 */

#ifndef CSOLIDSBCSTRINGCONVERTER_H_
#define CSOLIDSBCSTRINGCONVERTER_H_

#include <string>
#include <iconv.h>

class CSolidSBCStringConverter
{
public:
	CSolidSBCStringConverter(void);
	~CSolidSBCStringConverter(void);

	bool ConvertToUTF16LE(const std::string& sInput, char** ppszOutput, int* pnOutputSize, const char* pszInputEncoding = "UTF8") const;
	bool ConvertToUTF8   (const char* pszInput, const int nInputSize, std::string& sOutput, const char* pszInputEncoding = "UTF16LE") const;

	static CSolidSBCStringConverter* GetInstance(void);

private:
	bool Convert(const char* pszInput, const int nInputSize, const char* pszInputEncoding, char** ppszOutput, int* pnOutputSize, const char* pszOutputEncoding) const;
	char* ResizeOutputBuffer(char* pszOutput, size_t* pnOutputSize, const size_t nAddSize, const bool bZeroNewMemory = true) const;
};

#endif /* CSOLIDSBCSTRINGCONVERTER_H_ */
