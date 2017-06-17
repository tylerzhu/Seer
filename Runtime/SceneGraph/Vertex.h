#pragma once

#include "Math/Vector4.h"
#include "Math/ColorRGBA.h"

namespace Seer
{

	class Vertex
	{
	public:
		Vertex();
		~Vertex();

		Vertex Lerp(const Vertex* v1, const Vertex* v2, float t);
		Vertex GetStep(const Vertex* x1, const Vertex* x2, float width);

		// The number of 'float' channels used by all the attributes.
		static int GetVertexSize() { return sizeof(Vector4) + sizeof(ColorRGBA) + sizeof(float); };
	public:

		Vector4 Pos;
		ColorRGBA Color;
		float Rhw; // Reciprocal of Homogeneous W - RHW
	};
	
#include "Vertex.inl"
}

