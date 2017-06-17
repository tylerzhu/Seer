#pragma once
#include <cstdio>
#include <string>
#include <vector>

namespace Seer
{
	
	class File
	{
	public:

		// Maintain a list of directories that applications can search to find
		// data files.  The list is initially empty when an application starts,
		// so you must insert directories of interest, even the current working
		// directory.  The directory name should *not* end with a "/".  The
		// InsertDirectory and RemoveDirectory functions will manage that
		// character themselves.
		static void Initialize();
		static void Terminate();


		// The GetPath function searches the list of directories and returns the
		// fully decorated file name, if it exists, or return null, if it does
		// not exist.  The input iMode is selected from one of the three
		// enumerated values listed below.
		enum
		{
			SM_READ,
			SM_WRITE,
			SM_READ_WRITE
		};
		static const char* GetPath(const char* acFilename, int eMode);
		// This is needed on the Macintosh because of its complicated application
		// structure.  In particular, this function is used in Xcode projects and
		// ignores the directory entry, but assumes that the data files required
		// by an application are added to the Resources folder of the projects.
		// The other platforms concatenate the directory and filename, the result
		// stored in class-static memory (so be careful with threads).
		static const char* GetPath(const char* acDirectory,
			const char* acFilename);


		// Wrappers for standard I/O functions to support security enhancements
		// related to buffer overruns.  TO DO:  For now these support MSVC8.0
		// and fall back to the older standard I/O functions on other platforms.
		// Implementations may be provided for those other platforms to adhere
		// to the destination buffer size specification.
		static FILE* Fopen(const char* acFilename, const char* acMode);
		static int Fprintf(FILE* pkFile, const char* acFormat, ...);
		static int Fclose(FILE* pkFile);

		// File support for buffer load and save.
		static bool Load(const char* acFilename, char*& racBuffer, int& riSize);
		static bool Save(const char* acFilename, const char* acBuffer,
			int iSize);
		static bool Append(const char* acFilename, char* acBuffer, int iSize);

	private:
		enum { SYSTEM_MAX_PATH = 1024 };

		static char ms_acPath[SYSTEM_MAX_PATH];
		static std::vector<std::string>* ms_pkDirectories;
	};

}