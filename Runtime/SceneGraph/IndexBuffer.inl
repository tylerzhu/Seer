#pragma once

//----------------------------------------------------------------------------
inline int IndexBuffer::GetIndexQuantity() const
{
	return m_iIQuantity;
}
//----------------------------------------------------------------------------
inline int* IndexBuffer::GetData()
{
	return m_aiIndex;
}
//----------------------------------------------------------------------------
inline const int* IndexBuffer::GetData() const
{
	return m_aiIndex;
}
//----------------------------------------------------------------------------
inline int IndexBuffer::operator[] (int i) const
{
	return m_aiIndex[i];
}
//----------------------------------------------------------------------------
inline int& IndexBuffer::operator[] (int i)
{
	return m_aiIndex[i];
}
//----------------------------------------------------------------------------
inline void IndexBuffer::SetIndexQuantity(int iIQuantity)
{
	m_iIQuantity = iIQuantity;
}
//----------------------------------------------------------------------------


