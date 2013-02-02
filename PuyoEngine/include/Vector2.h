#ifndef VECTOR2_H
#define VECTOR2_H

#include "PuyoEngine.h"
#include "PuyoMath.h"
namespace PuyoEngine
{

	struct Vector2
	{
		Real x,y;
		Vector2() {}
		explicit Vector2(Real i_x, Real i_y) : x(i_x), y(i_y) {}
		Vector2& operator = ( const Vector2& rhs )
		{
			x = rhs.x;
			y = rhs.y;
			return *this;
		}

		bool operator == ( const Vector2& rhs ) const
		{
			return ( x == rhs.x && y == rhs.y );
		}
		bool operator != ( const Vector2& rhs ) const
		{
			return ( x != rhs.x || y != rhs.y  );
		}
		Vector2 operator + ( const Vector2& rhs ) const
		{
			return Vector2(x + rhs.x,y + rhs.y);
		}

		Vector2 operator - ( const Vector2& rhs ) const
		{
			return Vector2(
				x - rhs.x,
				y - rhs.y);
		}

		Vector2 operator * ( const Real scalar ) const
		{
			return Vector2(
				x * scalar,
				y * scalar);
		}

		Vector2 operator * ( const Vector2& rhs) const
		{
			return Vector2(
				x * rhs.x,
				y * rhs.y);
		}

		Vector2 operator / ( const Real scalar ) const
		{
			PASSERT( scalar != 0.0f );

			Real fInv = 1.0f / scalar;

			return Vector2(
				x * fInv,
				y * fInv);
		}

		Vector2 operator / ( const Vector2& rhs) const
		{
			return Vector2(
				x / rhs.x,
				y / rhs.y);
		}

		const Vector2& operator + () const
		{
			return *this;
		}

		Vector2 operator - () const
		{
			return Vector2(-x, -y);
		}

		// overloaded operators to help Vector2
		friend Vector2 operator * ( const Real scalar, const Vector2& rhs )
		{
			return Vector2(
				scalar * rhs.x,
				scalar * rhs.y);
		}

		friend Vector2 operator / ( const Real scalar, const Vector2& rhs )
		{
			return Vector2(
				scalar / rhs.x,
				scalar / rhs.y);
		}

		friend Vector2 operator + (const Vector2& lhs, const Real rhs)
		{
			return Vector2(
				lhs.x + rhs,
				lhs.y + rhs);
		}

		friend Vector2 operator + (const Real lhs, const Vector2& rhs)
		{
			return Vector2(
				lhs + rhs.x,
				lhs + rhs.y);
		}

		friend Vector2 operator - (const Vector2& lhs, const Real rhs)
		{
			return Vector2(
				lhs.x - rhs,
				lhs.y - rhs);
		}

		friend Vector2 operator - (const Real lhs, const Vector2& rhs)
		{
			return Vector2(
				lhs - rhs.x,
				lhs - rhs.y);
		}
		// arithmetic updates
		Vector2& operator += ( const Vector2& rhs )
		{
			x += rhs.x;
			y += rhs.y;

			return *this;
		}

		Vector2& operator += ( const Real scalar )
		{
			x += scalar;
			y += scalar;

			return *this;
		}

		Vector2& operator -= ( const Vector2& rhs )
		{
			x -= rhs.x;
			y -= rhs.y;

			return *this;
		}

		Vector2& operator -= ( const Real scalar )
		{
			x -= scalar;
			y -= scalar;

			return *this;
		}

		Vector2& operator *= ( const Real scalar )
		{
			x *= scalar;
			y *= scalar;

			return *this;
		}

		Vector2& operator *= ( const Vector2& rhs )
		{
			x *= rhs.x;
			y *= rhs.y;

			return *this;
		}

		Vector2& operator /= ( const Real scalar )
		{
			PASSERT( scalar != 0.0f );

			Real inv = 1.0f / scalar;

			x *= inv;
			y *= inv;

			return *this;
		}

		Vector2& operator /= ( const Vector2& rhs )
		{
			x /= rhs.x;
			y /= rhs.y;

			return *this;
		}
		Real GetLength () const
		{
			return Math::Sqrt( x * x + y * y );
		}

		Real GetSquaredLength () const
		{
			return x * x + y * y;
		}

		Real DotProduct(const Vector2& vec) const
		{
			return x * vec.x + y * vec.y;
		}

		Real normalise()
		{
			Real length = Math::Sqrt( x * x + y * y);

			// Will also work for zero-sized vectors, but will change nothing
			if ( length > 1e-08 )
			{
				Real fInvLength = 1.0f / length;
				x *= fInvLength;
				y *= fInvLength;
			}

			return length;
		}
		Real CrossProduct( const Vector2& rhs ) const
		{
			return x * rhs.y - y * rhs.x;
		}
		static const Vector2 ZERO;
		static const Vector2 UNIT_X;
		static const Vector2 UNIT_Y;


	};


}

#endif