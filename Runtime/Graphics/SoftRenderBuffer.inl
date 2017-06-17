#pragma once

//----------------------------------------------------------------------------
inline int SoftFrameBuffer::GetWidth() const
{
	return m_iWidth;
}
//----------------------------------------------------------------------------
inline int SoftFrameBuffer::GetHeight() const
{
	return m_iHeight;
}
//----------------------------------------------------------------------------
inline int SoftFrameBuffer::GetQuantity() const
{
	return m_iQuantity;
}
//----------------------------------------------------------------------------
inline void SoftFrameBuffer::SetColorBufferUI(unsigned int* auiColorBuffer)
{
	m_auiColorBuffer = auiColorBuffer;
}
//----------------------------------------------------------------------------
inline unsigned int* SoftFrameBuffer::GetColorBufferUI() const
{
	return m_auiColorBuffer;
}
//----------------------------------------------------------------------------
inline float* SoftFrameBuffer::GetDepthBufferF() const
{
	return m_afDepthBuffer;
}
//----------------------------------------------------------------------------