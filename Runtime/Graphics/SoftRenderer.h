#pragma once
#include "Renderer.h"
#include "SoftFrameBuffer.h"

namespace Seer
{
	class SoftRenderer : public Renderer
	{
	public:
		// Run-time type information.
		virtual int GetType() const;

		// Abstract class.  The derived classes must implement DisplayBackBuffer.
		virtual ~SoftRenderer();

		// full window buffer operations
		virtual void ClearBackBuffer() = 0;
		virtual void ClearZBuffer();
		virtual void ClearBuffers() override;

		// clear the buffer in the specified subwindow
		virtual void ClearBackBuffer(int iXPos, int iYPos, int iWidth,
			int iHeight);

	protected:
		// This class is abstract.  Derived classes are platform specific and
		// optionally may provide the chunks of memory to be used for
		// rasterization.  If the derived class wants to allocate the memory,
		// set bAllocateBackBuffer to 'false'; otherwise, SoftRenderer will
		// allocate the back buffer.
		SoftRenderer(int iWidth, int iHeight);

		// support for clearing the back buffer
		virtual void ClearSubBackBuffer(int iXMin, int iYMin, int iXMax,
			int iYMax) = 0;

		// Set both m_auiBBuffer and m_akBBuffer values, adhering to the current
		// color masks m_bAllowRed, m_bAllowGreen, m_bAllowBlue, and
		// m_bAllowAlpha.  Regarding m_auiBBuffer, the color channels in [0,1] are
		// mapped to an unsigned int that contains four channels, each in [0,255].
		// The order of red, green, blue, and alpha depends on the platform.
		virtual void SetColorBuffer(int iX, int iY, int iIndex,
			const ColorRGBA& rkColor) = 0;

		// Selection of the framebuffer to render to.  The input is null for
		// rendering to the main framebuffer, but nonnull for an offscreen
		// framebuffer.
		friend class SoftFrameBuffer;
		void SetRenderTarget(SoftFrameBuffer* pkFrameBuffer);

		// camera access and support
		virtual void OnViewportChange() override;
		//virtual void OnDepthRangeChange();

	private:

		void RasterizePoint(int iV0);
		void RasterizeEdge(Vertex* kV0, Vertex* kV1);
		void RasterizeTriangle(Vertex* kV0, Vertex* kV1, Vertex* kV2);
		void RasterizeScanLine(float y, Vertex* kVa, Vertex* kVb, Vertex* kVc, Vertex* kVd);

		// PRIMITIVE DRAWING SYSTEM.  This is the entry point into drawing the
		// geometric primitives.  The validation call checks if vertex or pixel
		// shaders.  If they do, the input of the pixel shader must match the
		// output of the vertex shader.  If these do not match, the default
		// shaders are used.
		virtual void DrawElements() override;

		void DrawPolypoint();
		void DrawPolylineDisjoint();
		void DrawPolylineContiguous();
		void DrawTriMesh();


	protected: // data member
		// The main framebuffer.
		SoftFrameBuffer m_kMain;
		// The active framebuffer.  The values m_iWidth and m_iHeight are part of
		// this context, but are members of the base class Renderer.
		int m_iQuantity;
		unsigned int* m_auiColorBuffer;
		float* m_afDepthBuffer;

		// The color to use when clearing the color buffer.
		unsigned int m_uiBackgroundColor;


		// For drawing various geometric primitives.
		typedef void (SoftRenderer::*DrawFunction)(void);
		DrawFunction m_aoDrawFunction[5];
		//DrawFunction m_aoDrawFunction[Geometry::GT_MAX_QUANTITY]; // todo:
	};


#include "SoftRenderer.inl"
}



