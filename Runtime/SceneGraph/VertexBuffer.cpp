#include "VertexBuffer.h"

using namespace Seer;


//----------------------------------------------------------------------------
VertexBuffer::VertexBuffer(Vertex akVertexs[], int iVertexQuantity)
	:m_kVertex(iVertexQuantity)
{	
	for (size_t i = 0; i < iVertexQuantity; i++)
	{
		m_kVertex[i] = akVertexs[i];
	}
}
//----------------------------------------------------------------------------
VertexBuffer::VertexBuffer(const VertexBuffer* pkVBuffer)
{
	
}
//----------------------------------------------------------------------------
VertexBuffer::VertexBuffer()
{

}
//----------------------------------------------------------------------------
VertexBuffer::~VertexBuffer()
{
	
}

Vector4& Seer::VertexBuffer::Position4(int i)
{
	return m_kVertex[i].Pos;
}

//Seer::Vector4 Seer::VertexBuffer::Position4(int i) const
//{
//	return m_kVertex[i].GetPosition();
//}

ColorRGBA& Seer::VertexBuffer::Color4(int iUnit, int i)
{
	return m_kVertex[i].Color;
}

//Seer::ColorRGBA Seer::VertexBuffer::Color4(int iUnit, int i) const
//{
//	return m_kVertex[i].GetColorRGBA();
//}
