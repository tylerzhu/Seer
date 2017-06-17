#pragma once

namespace Seer
{
	
	class IndexBuffer
	{

	public:
		IndexBuffer(int iIQuantity);
		IndexBuffer(const IndexBuffer* pkIBuffer);
		virtual ~IndexBuffer();

		void SetIndex(int* pIdx, int iSize);

		// Access to indices.
		int operator[] (int i) const;
		int& operator[] (int i);

		// Direct access to the index buffer data.  The quantity is the number of
		// int elements.  The number of bytes for the entire index buffer is
		// GetIndexQuantity()*sizeof(int).
		int GetIndexQuantity() const;
		int* GetData();
		const int* GetData() const;

		// An application might want to vary the "active quantity" of indices.
		// Use this function to do so.  It does not change the data storage,
		// only the m_iQuantity member.  The caller is responsible for saving the
		// full quantity of indices and resetting this when finished with the
		// index buffer.  The caller also should not pass in a quantity that is
		// larger than the original full quantity.
		void SetIndexQuantity(int iIQuantity);

	protected:
		// streaming support
		IndexBuffer();

		int m_iIQuantity;
		int* m_aiIndex;
	};

#include "IndexBuffer.inl"
}

