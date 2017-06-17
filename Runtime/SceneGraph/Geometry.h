#pragma once

#include "SceneGraph/VertexBuffer.h"
#include "SceneGraph/IndexBuffer.h"
#include <Math/Matrix4.h>

namespace Seer
{
	
	class Geometry
	{
	public:
		// abstract base class
		virtual ~Geometry();

		// member access
		VertexBuffer* VBuffer;
		IndexBuffer* IBuffer;

		Matrix4 Local;
		Matrix4 View;


	protected:
		Geometry();
		Geometry(VertexBuffer* pkVBuffer, IndexBuffer* pkIBuffer);

		// internal use
	public:
		// Render state and lights in path to this object.  An attached effect
		// provides additional render state, lights, and any other information
		// needed to draw the object.

		enum GeometryType
		{
			GT_POLYPOINT,
			GT_POLYLINE_SEGMENTS,
			GT_POLYLINE_OPEN,
			GT_POLYLINE_CLOSED,
			GT_TRIMESH,
			GT_MAX_QUANTITY
		};

		GeometryType Type;
	};

}