#pragma once


//----------------------------------------------------------------------------
inline int VertexBuffer::GetVertexQuantity() const
{
	return m_kVertex.size();
}
//----------------------------------------------------------------------------
inline Vertex VertexBuffer::operator[] (int i) const
{
	return m_kVertex[i];
}
//----------------------------------------------------------------------------
inline Vertex& VertexBuffer::operator[] (int i)
{
	return m_kVertex[i];
}
//----------------------------------------------------------------------------