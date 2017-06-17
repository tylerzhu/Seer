#include "Geometry.h"




Seer::Geometry::~Geometry()
{

}

Seer::Geometry::Geometry()
{

}

Seer::Geometry::Geometry(VertexBuffer* pkVBuffer, IndexBuffer* pkIBuffer)
	:VBuffer(pkVBuffer), IBuffer(pkIBuffer)
{
	
}
