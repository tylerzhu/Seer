#include "File.h"
#include <cstdarg>
// support for Load
#include <sys/stat.h>


void Seer::File::Initialize()
{
	ms_pkDirectories = new std::vector<std::string>;
}

void Seer::File::Terminate()
{
	delete ms_pkDirectories;
	ms_pkDirectories = nullptr;
}


const char* Seer::File::GetPath(const char* acFilename, int eMode)
{
	if (!ms_pkDirectories)
	{
		Initialize();
	}

	for (int i = 0; i < (int)ms_pkDirectories->size(); i++)
	{
		const char* acDecorated = GetPath(
			(*ms_pkDirectories)[i].c_str(), acFilename);
		if (!acDecorated)
		{
			return nullptr;
		}

		FILE* pkFile;
		if (eMode == SM_READ)
		{
			pkFile = Fopen(acDecorated, "r");
		}
		else if (eMode == SM_WRITE)
		{
			pkFile = Fopen(acDecorated, "w");
		}
		else // eMode == SM_READ_WRITE
		{
			pkFile = Fopen(acDecorated, "r+");
		}

		if (pkFile)
		{
			Fclose(pkFile);
			return acDecorated;
		}
	}
	return nullptr;
}

const char* Seer::File::GetPath(const char* acDirectory, const char* acFilename)
{
	size_t uiDLength = strlen(acDirectory);
	size_t uiFLength = strlen(acFilename);
	if (uiDLength + uiFLength + 1 <= SYSTEM_MAX_PATH)
	{
		strcpy_s(ms_acPath, SYSTEM_MAX_PATH, acDirectory);
		strcat_s(ms_acPath, SYSTEM_MAX_PATH, acFilename);
		return ms_acPath;
	}
	return 0;
}

FILE* Seer::File::Fopen(const char* acFilename, const char* acMode)
{
	return fopen(acFilename, acMode);
}

int Seer::File::Fprintf(FILE* pkFile, const char* acFormat, ...)
{
	if (!pkFile || !acFormat)
	{
		return -1;
	}

	va_list acArgs;
	va_start(acArgs, acFormat);
	int iNumWritten = vfprintf(pkFile, acFormat, acArgs);
	va_end(acArgs);
	return iNumWritten;
}

int Seer::File::Fclose(FILE* pkFile)
{
	return fclose(pkFile);
}

bool Seer::File::Load(const char* acFilename, char*& racBuffer, int& riSize)
{
	struct stat kStat;
	if (stat(acFilename, &kStat) != 0)
	{
		// file does not exist
		racBuffer = nullptr;
		riSize = 0;
		return false;
	}

	FILE* pkFile = Fopen(acFilename, "rb");
	if (!pkFile)
	{
		racBuffer = nullptr;
		riSize = 0;
		return false;
	}

	riSize = kStat.st_size;
	racBuffer = new char[riSize];
	int iRead = (int)fread(racBuffer, sizeof(char), riSize, pkFile);
	if (Fclose(pkFile) != 0 || iRead != riSize)
	{
		delete[] racBuffer;
		racBuffer = nullptr;
		riSize = 0;
		return false;
	}

	return true;
}

bool Seer::File::Save(const char* acFilename, const char* acBuffer, int iSize)
{
	if (!acBuffer || iSize <= 0)
	{
		// The input buffer must exist.  It is not possible to verify that
		// the buffer has the specified number of bytes.
		return false;
	}

	FILE* pkFile = Fopen(acFilename, "wb");
	if (!pkFile)
	{
		return false;
	}

	int iWrite = (int)fwrite(acBuffer, sizeof(char), iSize, pkFile);
	if (Fclose(pkFile) != 0 || iWrite != iSize)
	{
		return false;
	}

	return true;
}

bool Seer::File::Append(const char* acFilename, char* acBuffer, int iSize)
{
	if (!acBuffer || iSize <= 0)
	{
		// The input buffer must exist.  It is not possible to verify that
		// the buffer has the specified number of bytes.
		return false;
	}

	FILE* pkFile = Fopen(acFilename, "ab");
	if (!pkFile)
	{
		return false;
	}

	int iWrite = (int)fwrite(acBuffer, sizeof(char), iSize, pkFile);
	if (Fclose(pkFile) != 0 || iWrite != iSize)
	{
		return false;
	}

	return true;
}


