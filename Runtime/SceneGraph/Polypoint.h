#pragma once
#include "Geometry.h"

namespace Seer
{

	class Polypoint: public Geometry
	{
	public:
		// construction and destruction
		Polypoint(VertexBuffer* pkVBuffer);
		virtual ~Polypoint();

	protected:
		Polypoint();
	};

	
}

