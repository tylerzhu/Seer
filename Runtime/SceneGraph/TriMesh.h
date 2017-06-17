#pragma once
#include "Geometry.h"

#include "Math/Triangle3.h"

namespace Seer
{

	class TriMesh: public Geometry
	{
	public:
		// Construction and destruction.
		TriMesh(VertexBuffer* pkVBuffer, IndexBuffer* pkIBuffer);
		virtual ~TriMesh();

		// member access
		int GetTriangleQuantity() const;
		void GetModelTriangle(int i, Triangle3& rkMTri) const;
		void GetWorldTriangle(int i, Triangle3& rkWTri) const;

	protected:
		TriMesh();
	};
	
#include "TriMesh.inl"

}

