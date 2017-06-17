#pragma once
#include <string>
#include "Math/ColorRGBA.h"


namespace Seer
{
	
	class Image
	{
	public:
		// NOTE:  Image dimensions must be a power of two.  Assert statements are
		// placed in the constructors to trap when the dimensions are not power
		// of two.

		enum FormatMode
		{
			IT_RGB888,
			IT_RGBA8888,
			IT_DEPTH16,
			IT_DEPTH24,
			IT_DEPTH32,
			IT_CUBE_RGB888,
			IT_CUBE_RGBA8888,
			IT_RGB32,
			IT_RGBA32,
			IT_QUANTITY
		};

		// 1D image
		Image(FormatMode eFormat, int iBound0, unsigned char* aucData,
			const char* acImageName);

		// 2D image
		Image(FormatMode eFormat, int iBound0, int iBound1,
			unsigned char* aucData, const char* acImageName);

		// 3D image
		Image(FormatMode eFormat, int iBound0, int iBound1, int iBound2,
			unsigned char* aucData, const char* acImageName);

		virtual ~Image();

		// member access
		FormatMode GetFormat() const;
		const std::string& GetFormatName() const;
		static std::string GetFormatName(int eFormat);
		bool IsDepthImage() const;
		bool IsCubeImage() const;
		int GetBytesPerPixel() const;
		static int GetBytesPerPixel(int eFormat);
		int GetDimension() const;
		int GetBound(int i) const;
		int GetQuantity() const;
		unsigned char* GetData() const;
		unsigned char* operator() (int i);

		// Create an image of ColorRGBA values.  The function returns an image
		// of the same width and height for these formats.  The returned image
		// is dynamically allocated; the caller is responsible for deleting it.
		ColorRGBA* CreateRGBA() const;

		// Copy to an already existing image of ColorRGBA values.  The input
		// array must have the correct dimensions as the Image itself.
		void CopyRGBA(ColorRGBA* akCImage) const;

		// Streaming support.  The sharing system is automatically invoked by
		// these calls.  In Load, if an image corresponding to the filename is
		// already in memory, then that image is returned (i.e. shared).
		// Otherwise, a new image is created and returned.  The filename is used
		// as the image name.
		static Image* Load(const char* acImageName);

		// This is intended to support saving procedurally generated images or
		// for utilities that convert to WMIF from another format.  The filename
		// in this call does not replace the image name that might already exist.
		bool Save(const char* acFilename);

	protected:
		// support for streaming
		Image();

		FormatMode m_eFormat;
		int m_iDimension;
		int m_aiBound[3];
		int m_iQuantity;
		unsigned char* m_aucData;

		static int ms_aiBytesPerPixel[IT_QUANTITY];
		static std::string ms_akFormatName[IT_QUANTITY];
	};

}

