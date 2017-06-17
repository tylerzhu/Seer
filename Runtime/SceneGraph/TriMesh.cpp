#include "TriMesh.h"




void Seer::TriMesh::GetModelTriangle(int i, Triangle3& rkMTri) const
{
	
	int* aiIndex = IBuffer->GetData();
	int* piIndex = &aiIndex[3 * i];
	//rkMTri.V[0] = VBuffer->Position4(*piIndex++);
	//rkMTri.V[1] = VBuffer->Position4(*piIndex++);
	//rkMTri.V[2] = VBuffer->Position4(*piIndex);
}

void Seer::TriMesh::GetWorldTriangle(int i, Triangle3& rkWTri) const
{
	int* aiIndex = IBuffer->GetData();
	int* piIndex = &aiIndex[3 * i];
	/*rkWTri.V[0] = World.ApplyForward(VBuffer->Position3(*piIndex++));
	rkWTri.V[1] = World.ApplyForward(VBuffer->Position3(*piIndex++));
	rkWTri.V[2] = World.ApplyForward(VBuffer->Position3(*piIndex));*/
}

Seer::TriMesh::TriMesh()
{
	Type = GT_TRIMESH;
}

Seer::TriMesh::TriMesh(VertexBuffer* pkVBuffer, IndexBuffer* pkIBuffer)
	:Geometry(pkVBuffer, pkIBuffer)
{
	Type = GT_TRIMESH;
}

Seer::TriMesh::~TriMesh()
{

}
