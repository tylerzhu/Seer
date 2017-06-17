#pragma once

#include "Math/Vector4.h"
#include "Math/ColorRGBA.h"
#include "Vertex.h"
#include <vector>

namespace Seer
{
	
	class VertexBuffer
	{
	public:
		VertexBuffer(Vertex akVertexs[], int iVertexQuantity);
		VertexBuffer(const VertexBuffer* pkVBuffer);
		virtual ~VertexBuffer();

		// The number of vertices in the buffer.
		int GetVertexQuantity() const;

		// Access to indices.
		Vertex operator[] (int i) const;
		Vertex& operator[] (int i);

		// 位置数据
		Vector4& Position4(int i);
		//Vector4 Position4(int i) const;
		// 颜色数据
		ColorRGBA& Color4(int iUnit, int i);
		//ColorRGBA Color4(int iUnit, int i) const;
	private:
		// streaming support
		VertexBuffer();

		// The vertex buffer data.
		std::vector<Vertex> m_kVertex;
	};

#include "VertexBuffer.inl"

}

