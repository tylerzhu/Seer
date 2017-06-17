#include "SoftRenderer.h"




Seer::SoftRenderer::~SoftRenderer()
{

}

Seer::SoftRenderer::SoftRenderer(int iWidth, int iHeight) : 
	Renderer(iWidth, iHeight),
	m_kMain(nullptr, iWidth, iHeight)
{
	m_uiBackgroundColor = ColorRGBA::WHITE.GetHex();


	// Functions for drawing of primitives.
	m_aoDrawFunction[0] = &SoftRenderer::DrawPolypoint;
	m_aoDrawFunction[1] = &SoftRenderer::DrawPolylineDisjoint;
	m_aoDrawFunction[2] = &SoftRenderer::DrawPolylineContiguous;
	m_aoDrawFunction[3] = &SoftRenderer::DrawPolylineContiguous;
	m_aoDrawFunction[4] = &SoftRenderer::DrawTriMesh;
}

void Seer::SoftRenderer::SetRenderTarget(SoftFrameBuffer* pkFrameBuffer)
{
	if (pkFrameBuffer)
	{
		m_iWidth = pkFrameBuffer->GetWidth();
		m_iHeight = pkFrameBuffer->GetHeight();
		m_iQuantity = pkFrameBuffer->GetQuantity();
		m_auiColorBuffer = pkFrameBuffer->GetColorBufferUI();	
		m_afDepthBuffer = pkFrameBuffer->GetDepthBufferF();
	}
	else
	{
		m_iWidth = m_kMain.GetWidth();
		m_iHeight = m_kMain.GetHeight();
		m_iQuantity = m_kMain.GetQuantity();
		m_auiColorBuffer = m_kMain.GetColorBufferUI();	
		m_afDepthBuffer = m_kMain.GetDepthBufferF();
	}
}

void Seer::SoftRenderer::ClearBackBuffer(int iXPos, int iYPos, int iWidth, int iHeight)
{
	int iXMin, iYMin, iXMax, iYMax;
	//if (Scissor(iXPos, iYPos, iWidth, iHeight, iXMin, iYMin, iXMax, iYMax))
	{
		//ClearSubBackBuffer(iXMin, iYMin, iXMax, iYMax);
	}
}

//----------------------------------------------------------------------------
void Seer::SoftRenderer::ClearZBuffer()
{
	if (m_afDepthBuffer)
	{		
		for (int i = 0; i < m_iQuantity; i++)
		{
		m_afDepthBuffer[i] = 0.0f;
		}
	}
}
//----------------------------------------------------------------------------

void Seer::SoftRenderer::ClearBuffers()
{
	ClearBackBuffer();
	ClearZBuffer();
}

void Seer::SoftRenderer::OnViewportChange()
{

}

