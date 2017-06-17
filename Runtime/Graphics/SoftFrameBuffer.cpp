#include "SoftFrameBuffer.h"




Seer::SoftFrameBuffer::SoftFrameBuffer(Renderer* pkRenderer, int iWidth, int iHeight)
	:FrameBuffer(pkRenderer)
{	
	{
		m_iWidth = iWidth;
		m_iHeight = iHeight;
	}

	m_iQuantity = m_iWidth*m_iHeight;

	{
		m_auiColorBuffer = new unsigned int[m_iQuantity];
		m_afDepthBuffer = new float[m_iQuantity];
	}
}

Seer::SoftFrameBuffer::~SoftFrameBuffer()
{
	//if (m_bColorBufferOwner)
	{
		delete[] m_auiColorBuffer;
	}
}

Seer::FrameBuffer* Seer::SoftFrameBuffer::Create(Renderer* pkRenderer)
{
	// Offscreen framebuffers are created by the factory.  The SoftRenderer
	// uses the SoftFrameBuffer constructor directly.
	if (pkRenderer)
	{
		return new SoftFrameBuffer(pkRenderer, 0, 0);
	}
	return nullptr;
}

void Seer::SoftFrameBuffer::Destroy(FrameBuffer* pkBuffer)
{

}
