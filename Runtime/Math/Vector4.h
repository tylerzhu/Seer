#pragma once
#include "Precision.h"
#include "Vector3.h"

/*!
 * \file Vector4.h
 * \date 2017/04/26 9:47
 *
 * \author tylerzhu
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/
namespace Seer 
{
	
	class Vector4
	{
	public:		
		real x;
		real y;
		real z;
		real w;

	public:
		/** The default constructor creates a zero vector. */
		Vector4() : x(0), y(0), z(0), w(0) {}

		Vector4(const real x, const real y, const real z, const real w)
			: x(x), y(y), z(z), w(w) {}

		const static Vector4 GRAVITY;
		const static Vector4 HIGH_GRAVITY;
		const static Vector4 UP;
		const static Vector4 RIGHT;
		const static Vector4 OUT_OF_SCREEN;
		const static Vector4 X;
		const static Vector4 Y;
		const static Vector4 Z;
		const static Vector4 W;

		// ... Other Vector4 code as before ...
		Vector3 ToVector3() const { return Vector3(x, y, z); }

		real operator[](unsigned i) const
		{
			if (i == 0) return x;
			if (i == 1) return y;
			return z;
		}

		real& operator[](unsigned i)
		{
			if (i == 0) return x;
			if (i == 1) return y;
			return z;
		}

		/** Adds the given vector to this. */
		void operator+=(const Vector4& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;
		}

		/**
		* Returns the value of the given vector added to this.
		*/
		Vector4 operator+(const Vector4& v) const
		{
			return Vector4(x + v.x, y + v.y, z + v.z, 1);
		}

		/** Subtracts the given vector from this. */
		void operator-=(const Vector4& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}

		/**
		* Returns the value of the given vector subtracted from this.
		*/
		Vector4 operator-(const Vector4& v) const
		{
			return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
		}

		/** Multiplies this vector by the given scalar. */
		void operator*=(const real value)
		{
			x *= value;
			y *= value;
			z *= value;
		}

		/** Returns a copy of this vector scaled the given value. */
		Vector4 operator*(const real value) const
		{
			return Vector4(x*value, y*value, z*value, w*value);
		}

		/**
		* Calculates and returns a component-wise product of this
		* vector with the given vector.
		*/
		Vector4 componentProduct(const Vector4 &vector) const
		{
			return Vector4(x * vector.x, y * vector.y, z * vector.z, z * vector.w);
		}

		/**
		* Performs a component-wise product with the given vector and
		* sets this vector to its result.
		*/
		void componentProductUpdate(const Vector4 &vector)
		{
			x *= vector.x;
			y *= vector.y;
			z *= vector.z;
		}
		//
		//		/**
		//		* Calculates and returns the vector product of this vector
		//		* with the given vector.
		//		*/
		//		Vector4 vectorProduct(const Vector4 &vector) const
		//		{
		//			return Vector4(y*vector.z - z*vector.y,
		//				z*vector.x - x*vector.z,
		//				x*vector.y - y*vector.x);
		//		}

		//		/**
		//		* Updates this vector to be the vector product of its current
		//		* value and the given vector.
		//		*/
		//		void operator %=(const Vector4 &vector)
		//		{
		//			*this = vectorProduct(vector);
		//		}
		//
		//		/**
		//		* Calculates and returns the vector product of this vector
		//		* with the given vector.
		//		*/
		//		Vector4 operator%(const Vector4 &vector) const
		//		{
		//			return Vector4(y*vector.z - z*vector.y,
		//				z*vector.x - x*vector.z,
		//				x*vector.y - y*vector.x);
		//		}

		/**
		* Calculates and returns the scalar product of this vector
		* with the given vector.
		*/
		real scalarProduct(const Vector4 &vector) const
		{
			return x*vector.x + y*vector.y + z*vector.z;
		}

		
		Vector4 operator *(const Vector4 &vector) const
		{
			return Vector4(x*vector.x, y*vector.y, z*vector.z, 1);
		}

		/**
		* Adds the given vector to this, scaled by the given amount.
		*/
		void addScaledVector(const Vector4& vector, real scale)
		{
			x += vector.x * scale;
			y += vector.y * scale;
			z += vector.z * scale;
		}

		/** Gets the magnitude of this vector. */
		real Magnitude() const
		{
			return real_sqrt(x*x + y*y + z*z);
		}

		/** Gets the squared magnitude of this vector. */
		real squareMagnitude() const
		{
			return x*x + y*y + z*z;
		}

		/** Limits the size of the vector to the given maximum. */
		void trim(real size)
		{
			if (squareMagnitude() > size*size)
			{
				normalise();
				x *= size;
				y *= size;
				z *= size;
			}
		}

		/** Turns a non-zero vector into a vector of unit length. */
		void normalise()
		{
			real l = Magnitude();
			if (l > 0)
			{
				(*this) *= ((real)1) / l;
			}
		}

		/** Returns the normalised version of a vector. */
		Vector4 unit() const
		{
			Vector4 result = *this;
			result.normalise();
			return result;
		}

		/** Checks if the two vectors have identical components. */
		bool operator==(const Vector4& other) const
		{
			return x == other.x &&
				y == other.y &&
				z == other.z;
		}

		/** Checks if the two vectors have non-identical components. */
		bool operator!=(const Vector4& other) const
		{
			return !(*this == other);
		}

		/**
		* Checks if this vector is component-by-component less than
		* the other.
		*
		* @note This does not behave like a single-value comparison:
		* !(a < b) does not imply (b >= a).
		*/
		bool operator<(const Vector4& other) const
		{
			return x < other.x && y < other.y && z < other.z;
		}

		/**
		* Checks if this vector is component-by-component less than
		* the other.
		*
		* @note This does not behave like a single-value comparison:
		* !(a < b) does not imply (b >= a).
		*/
		bool operator>(const Vector4& other) const
		{
			return x > other.x && y > other.y && z > other.z;
		}

		/**
		* Checks if this vector is component-by-component less than
		* the other.
		*
		* @note This does not behave like a single-value comparison:
		* !(a <= b) does not imply (b > a).
		*/
		bool operator<=(const Vector4& other) const
		{
			return x <= other.x && y <= other.y && z <= other.z;
		}

		/**
		* Checks if this vector is component-by-component less than
		* the other.
		*
		* @note This does not behave like a single-value comparison:
		* !(a <= b) does not imply (b > a).
		*/
		bool operator>=(const Vector4& other) const
		{
			return x >= other.x && y >= other.y && z >= other.z;
		}

		/** Zero all the components of the vector. */
		void clear()
		{
			x = y = z = 0;
		}

		/** Flips all the components of the vector. */
		void invert()
		{
			x = -x;
			y = -y;
			x = -z;
		}

		Vector4 Lerp(const Vector4& from, const Vector4& to, float t)
		{
			//*this = to * t + from * (1.0F - t);
			*this = from + (to - from)*t;
			return *this;
		}
	};

}