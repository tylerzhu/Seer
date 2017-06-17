#pragma once

#include "Vector3.h"

namespace Seer
{

	class Triangle3
	{
	public:
		// The triangle is represented as an array of three vertices, V0, V1,
		// and V2.

		// construction
		Triangle3();  // uninitialized
		Triangle3(const Vector3& rkV0, const Vector3& rkV1,
			const Vector3& rkV2);
		Triangle3(const Vector3 akV[3]);

		// distance from the point Q to the triangle
		float DistanceTo(const Vector3& rkQ) const;

		Vector3 V[3];
	};
}
