#pragma once

#include "Precision.h"
#include "MathUtil.h"

namespace Seer
{
	class ColorRGBA
	{
	public:
		real	r;
		real	g;
		real	b;
		real	a;
		
		ColorRGBA() {}

		ColorRGBA(const real r, const real g, const real b, const real a = 1)
			: r(r), g(g), b(b), a(1) {}

		void Set(real inR, real inG, real inB, real inA)
		{
			r = inR;
			g = inG; 
			b = inB; 
			a = inA;
		}
				
		unsigned int GetHex() const
		{
			unsigned int hex = (NormalizedToByte(r) << 24) | (NormalizedToByte(g) << 16) | (NormalizedToByte(b) << 8) | NormalizedToByte(a);
			return hex;
		}

		unsigned int GetHexIngoreA() const
		{
			unsigned int hex = (NormalizedToByte(r) << 16) | (NormalizedToByte(g) << 8) | NormalizedToByte(b);
			return hex;
		}

		real ColorRGBA::R() const
		{
			return r;
		}

		real ColorRGBA::G() const
		{
			return g;
		}

		real ColorRGBA::B() const
		{
			return b;
		}

		real ColorRGBA::A() const
		{
			return a;
		}

		ColorRGBA& operator += (const ColorRGBA &inRGBA)
		{
			r += inRGBA.r; 
			g += inRGBA.g; 
			b += inRGBA.b; 
			a += inRGBA.a;
			return *this;
		}

		ColorRGBA& operator -= (const ColorRGBA &inRGBA)
		{
			r -= inRGBA.r; g -= inRGBA.g; b -= inRGBA.b; a -= inRGBA.a;
			return *this;
		}

		ColorRGBA& operator *= (const ColorRGBA &inRGBA)
		{
			r *= inRGBA.r; g *= inRGBA.g; b *= inRGBA.b; a *= inRGBA.a;
			return *this;
		}

		inline ColorRGBA& operator *= (float inScale)
		{
			r *= inScale; g *= inScale; b *= inScale; a *= inScale;
			return *this;
		}

		inline void Clamp()
		{
			r = Clamp(r, 0, 255);
			g = Clamp(g, 0, 255);
			b = Clamp(b, 0, 255);
		}

		int Clamp(int outi, int min, int max)
		{
			return (outi < min) ? min : ((outi > max) ? max : outi);
		}

	public: // static
		static const ColorRGBA BLACK;   // = (0,0,0,1) 
		static const ColorRGBA WHITE;   // = (1,1,1,1)
	};

	inline ColorRGBA operator + (const ColorRGBA& inC0, const ColorRGBA& inC1)
	{
		return ColorRGBA(inC0.r + inC1.r, inC0.g + inC1.g, inC0.b + inC1.b, inC0.a + inC1.a);
	}

	inline ColorRGBA operator - (const ColorRGBA& inC0, const ColorRGBA& inC1)
	{
		return ColorRGBA(inC0.r - inC1.r, inC0.g - inC1.g, inC0.b - inC1.b, inC0.a - inC1.a);
	}

	inline ColorRGBA operator * (const ColorRGBA& inC0, const ColorRGBA& inC1)
	{
		return ColorRGBA(inC0.r * inC1.r, inC0.g * inC1.g, inC0.b * inC1.b, inC0.a * inC1.a);
	}

	inline ColorRGBA operator * (float inScale, const ColorRGBA& inC0)
	{
		return ColorRGBA(inC0.r * inScale, inC0.g * inScale, inC0.b * inScale, inC0.a * inScale);
	}

	inline ColorRGBA operator * (const ColorRGBA& inC0, float inScale)
	{
		return ColorRGBA(inC0.r * inScale, inC0.g * inScale, inC0.b * inScale, inC0.a * inScale);
	}

	inline ColorRGBA Lerp(const ColorRGBA& c0, const ColorRGBA& c1, float t)
	{
		// (1.0f - t) * c0 + t * c1 => c0 - c0*t + c1*t = > c0 + (c1 - c0)*t;		
		return c0 + (c1 - c0)*t;
	}
}

