#pragma once

#include "Precision.h"

namespace Seer
{
	class Rect
	{
	public:
		real x; ///< Rectangle x coordinate.
		real y; ///< Rectangle y coordinate.
		real width; ///< Rectangle width.
		real height; ///< Rectangle height.

		Rect() { Reset(); };

		inline void Reset() { x = y = width = height = 0; }
		inline void Set(real inX, real inY, real iWidth, real iHeight)
		{
			x = inX; width = iWidth;
			y = inY; height = iHeight;
		}

		inline void Scale(real dx, real dy)		{ x *= dx; width *= dx; y *= dy; height *= dy; }
	};

}

