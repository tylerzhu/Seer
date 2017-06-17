#include "Polypoint.h"


Seer::Polypoint::Polypoint(VertexBuffer* pkVBuffer)
{
	Type = GT_POLYPOINT;

	int iVQuantity = VBuffer->GetVertexQuantity();

	IBuffer = new IndexBuffer(iVQuantity);
	int* aiIndex = IBuffer->GetData();
	for (int i = 0; i < iVQuantity; i++)
	{
		aiIndex[i] = i;
	}
}

Seer::Polypoint::Polypoint()
{
	Type = GT_POLYPOINT;
}

Seer::Polypoint::~Polypoint()
{

}
