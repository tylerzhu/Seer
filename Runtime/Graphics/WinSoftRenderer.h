#pragma once

#include <windows.h>
#include "Math/ColorRGBA.h"
#include "SoftRenderer.h"

namespace Seer
{

	class WinSoftRenderer : public SoftRenderer
	{
	public:
		WinSoftRenderer(HWND hWnd, int iWidth, int iHeight);
		virtual ~WinSoftRenderer();

		// background color access
		virtual void SetBackgroundColor(const ColorRGBA& rkColor) override;

		// back buffer handling
		virtual void ClearBackBuffer() override;
		virtual void DisplayBackBuffer() override;
		
		virtual void Draw(int iX, int iY, const ColorRGBA& rkColor,
			const char* acText);

		// 2D drawing
		virtual void Draw(const unsigned char* aucBuffer);

	private:
		virtual void ClearSubBackBuffer(int iXMin, int iYMin, int iXMax,
			int iYMax);

		virtual void SetColorBuffer(int iX, int iY, int iIndex,
			const ColorRGBA& rkColor);

		HWND m_hWnd;
		HDC m_hWindowDC, m_hMemoryDC;
		HBITMAP m_hBBitmap;

	};

}

