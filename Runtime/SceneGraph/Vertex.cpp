#include "Vertex.h"

using namespace Seer;


Seer::Vertex::Vertex()
{
	Rhw = 1.0;
}

Seer::Vertex::~Vertex()
{

}

Vertex Vertex::Lerp(const Vertex* v1, const Vertex* v2, float t)
{
	float temp = FloatMax(0, FloatMin(t, 1));

	Pos.Lerp(v1->Pos, v2->Pos, temp);
	Color = ::Lerp(v1->Color, v2->Color, temp);
	Rhw = (1.0f - temp) * v1->Rhw + temp * v2->Rhw;

	return *this;
}

Vertex Vertex::GetStep(const Vertex* x1, const Vertex* x2, float width)
{
	float inv = 1.0f / width;

	Pos = (x2->Pos - x1->Pos) * inv;
	Color = (x2->Color - x1->Color) * inv;
	Rhw = (x2->Rhw - x1->Rhw) * inv;

	return *this;
}
