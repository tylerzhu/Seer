#include "IndexBuffer.h"
#include <set>


Seer::IndexBuffer::IndexBuffer(int iIQuantity)
{
	m_iIQuantity = iIQuantity;
	m_aiIndex = new int[m_iIQuantity];
	memset(m_aiIndex, 0, m_iIQuantity*sizeof(int));
}

Seer::IndexBuffer::IndexBuffer(const IndexBuffer* pkIBuffer)
{
	m_iIQuantity = pkIBuffer->m_iIQuantity;
	m_aiIndex = new int[m_iIQuantity];
	size_t uiSize = m_iIQuantity*sizeof(int);
	memcpy_s(m_aiIndex, uiSize, pkIBuffer->m_aiIndex, uiSize);
}

Seer::IndexBuffer::IndexBuffer()
{
	m_iIQuantity = 0;
	m_aiIndex = nullptr;
}

Seer::IndexBuffer::~IndexBuffer()
{
	delete[] m_aiIndex;
}

void Seer::IndexBuffer::SetIndex(int* pIdx, int iSize)
{
	size_t uiSize = iSize*sizeof(int);
	memcpy_s(m_aiIndex, uiSize, pIdx, uiSize);
}
