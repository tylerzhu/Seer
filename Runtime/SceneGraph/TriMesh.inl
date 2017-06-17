#pragma once

//----------------------------------------------------------------------------
inline int TriMesh::GetTriangleQuantity() const
{
	return IBuffer->GetIndexQuantity() / 3;
}
//----------------------------------------------------------------------------


