#include "WinSoftRenderer.h"

using namespace Seer;

WinSoftRenderer::WinSoftRenderer(HWND hWnd, int iWidth, int iHeight) :SoftRenderer(iWidth, iHeight)
{
	m_hWnd = hWnd;
	m_hWindowDC = GetDC(m_hWnd);
	m_hMemoryDC = CreateCompatibleDC(m_hWindowDC);

	// Create the back buffer (32-bit format ARGB8888).  Despite its name,
	// the structure RGBQUAD is 32-bit and has blue, red, green, and reserved
	// channels.
	const size_t uiLength = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD*);
	char* acBitMapInfo = new char[uiLength];
	memset(acBitMapInfo, 0, uiLength);
	BITMAPINFOHEADER& bmih = *(BITMAPINFOHEADER*)acBitMapInfo;
	bmih.biSize = sizeof(BITMAPINFOHEADER);
	bmih.biWidth = m_iWidth;
	bmih.biHeight = -m_iHeight;
	bmih.biPlanes = 1;
	bmih.biBitCount = 32;
	bmih.biCompression = BI_RGB;
	bmih.biSizeImage = m_iWidth*m_iHeight;
	bmih.biXPelsPerMeter = 0;
	bmih.biYPelsPerMeter = 0;
	bmih.biClrUsed = 0;
	bmih.biClrImportant = 0;

	unsigned int* auiColorBuffer = 0;
	m_hBBitmap = CreateDIBSection(m_hMemoryDC, (CONST BITMAPINFO*)acBitMapInfo,
		DIB_RGB_COLORS, (void**)&auiColorBuffer, 0, 0);

	delete[] acBitMapInfo;

	SelectObject(m_hMemoryDC, m_hBBitmap);

	// Set the main colorbuffer to be the hardware-allocated one.
	m_kMain.SetColorBufferUI(auiColorBuffer);

	// Set the active framebuffer to be the main framebuffer.
	SetRenderTarget(nullptr);
}

Seer::WinSoftRenderer::~WinSoftRenderer()
{

}

void Seer::WinSoftRenderer::SetBackgroundColor(const ColorRGBA& rkColor)
{
	SoftRenderer::SetBackgroundColor(rkColor);
	//
	m_uiBackgroundColor = rkColor.GetHex();
}

void Seer::WinSoftRenderer::ClearBackBuffer()
{
	if (m_auiColorBuffer)
	{
		unsigned int* puiColorBuffer = m_auiColorBuffer;
		//ColorRGBA* pkColorBuffer = m_akColorBuffer;
		for (int i = 0; i < m_iQuantity; i++)
		{
			*puiColorBuffer++ = m_uiBackgroundColor;
			//*pkColorBuffer++ = m_kBackgroundColor;
		}
	}
}

void Seer::WinSoftRenderer::DisplayBackBuffer()
{
	BitBlt(m_hWindowDC, 0, 0, m_iWidth, m_iHeight, m_hMemoryDC, 0, 0, SRCCOPY);
}

void Seer::WinSoftRenderer::Draw(int iX, int iY, const ColorRGBA& rkColor, const char* acText)
{

}

void Seer::WinSoftRenderer::Draw(const unsigned char* aucBuffer)
{

}

void Seer::WinSoftRenderer::SetColorBuffer(int iX, int iY, int iIndex, const ColorRGBA& rkColor)
{
	if (iIndex > 0 && iIndex < m_iQuantity)
	{
	/*	unsigned char ucR = (unsigned char)(255.0f*rkColor.R());
		unsigned char ucG = (unsigned char)(255.0f*rkColor.G());
		unsigned char ucB = (unsigned char)(255.0f*rkColor.B());
		unsigned char ucA = (unsigned char)(255.0f*rkColor.A());
		unsigned int uiColor = (ucB | (ucG << 8) | (ucR << 16) | (ucA << 24));*/

		m_auiColorBuffer[iIndex] = rkColor.GetHexIngoreA();
	}

}

void Seer::WinSoftRenderer::ClearSubBackBuffer(int iXMin, int iYMin, int iXMax, int iYMax)
{
	if (m_auiColorBuffer)
	{
		int iMin = iXMin + m_iWidth*iYMin;
		int iMax = iXMax + m_iWidth*iYMin;
		for (int iY = iYMin; iY < iYMax; iY++)
		{
			for (int i = iMin; i < iMax; i++)
			{
				m_auiColorBuffer[i] = m_uiBackgroundColor;
				//m_akColorBuffer[i] = m_kBackgroundColor;
			}

			iMin += m_iWidth;
			iMax += m_iWidth;
		}
	}
}


