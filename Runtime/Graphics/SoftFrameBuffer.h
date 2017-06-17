#pragma once
#include "FrameBuffer.h"

namespace Seer
{
	
	class SoftFrameBuffer: public FrameBuffer
	{
	public:
		SoftFrameBuffer(Renderer* pkRenderer, int iWidth, int iHeight);

		virtual ~SoftFrameBuffer();

		// Accessors for the software renderer to switch between framebuffer
		// objects.  The SetColorBufferUI call allows for a hardware-based buffer
		// to be used as the main colorbuffer.
		int GetWidth() const;
		int GetHeight() const;
		int GetQuantity() const;
		void SetColorBufferUI(unsigned int* auiColorBuffer);
		unsigned int* GetColorBufferUI() const;
		float* GetDepthBufferF() const;

	protected:
		// TO DO.  Only single-buffering is supported.  Multisampling is not yet
		// supported.  Only 2D buffers are supported.

		// The 32-bit color buffer.  The format depends on the platform (little
		// endian or big endian) and how the graphics system on the platform
		// stores the color channels.
		int m_iWidth, m_iHeight;
		int m_iQuantity;
		unsigned int* m_auiColorBuffer;
		float* m_afDepthBuffer;

	protected: // static
		// factory functions
		static FrameBuffer* Create(Renderer* pkRenderer);

		static void Destroy(FrameBuffer* pkBuffer);
	};

#include "SoftRenderBuffer.inl"
}

