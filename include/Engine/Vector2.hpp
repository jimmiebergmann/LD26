#ifndef __LDE_VECTOR2_HPP__
#define __LDE_VECTOR2_HPP__

#include <cmath>

namespace LDE
{

	template <typename T>
	class Vector2
	{

	public:

		Vector2( ) { }
		Vector2( T p_X, T p_Y ) { x = p_X; y = p_Y; } 
		Vector2( const Vector2<int> & V ) { x = static_cast<T>(V.x); y = static_cast<T>(V.y); } 
		Vector2( const Vector2<float> & V ) { x = static_cast<T>(V.x); y = static_cast<T>(V.y); } 

		const Vector2< T > operator = ( const Vector2< T > p_Vector )
		{
			x = p_Vector.x;
			y = p_Vector.y;
			return *this;
		}

		const Vector2< T > operator += ( const Vector2< T > p_Vector )
		{
			this->x += p_Vector.x;
			this->y += p_Vector.y;
			return *this;
		}

		const Vector2< T > operator -= ( const Vector2< T > p_Vector )
		{
			this->x -= p_Vector.x;
			this->y -= p_Vector.y;
			return *this;
		}

		const Vector2< T > operator *= ( const Vector2< T > p_Vector )
		{
			this->x *= p_Vector.x;
			this->y *= p_Vector.y;
			return *this;
		}

		const Vector2< T > operator /= ( const Vector2< T > p_Vector )
		{
			this->x /= p_Vector.x;
			this->y /= p_Vector.y;
			return *this;
		}

		const Vector2< T > operator + ( const Vector2< T > p_Vector ) const
		{
			return Vector2< T >( this->x + p_Vector.x, this->y + p_Vector.y );
		}

		const Vector2 <T > operator - ( const Vector2< T > p_Vector ) const
		{
			return Vector2< T >( this->x - p_Vector.x, this->y - p_Vector.y );
		}

		const Vector2< T > operator * ( const Vector2< T > p_Vector ) const
		{
			return Vector2< T >( this->x * p_Vector.x, this->y * p_Vector.y );
		}

		const Vector2< T > operator * ( const T p_Value ) const
		{
			return Vector2< T >( this->x * p_Value, this->y * p_Value );
		}

		const Vector2< T > operator / ( const Vector2< T > p_Vector ) const
		{
			return Vector2< T >( this->x / p_Vector.x, this->y / p_Vector.y );
		}

		const Vector2< T > operator / ( const T p_Value ) const
		{
			return Vector2< T >( this->x / p_Value, this->y / p_Value );
		}

		const float Magnitude( ) const
		{
			return sqrt( ( x*x ) + ( y*y ) );
		};

		const Vector2< T > Normal( ) const
		{
			float length = Magnitude( );
			
			if( length == 0.0f )
			{
				return *this;
			}

			return Vector2< T >( ( x / length ),( y / length ) );
		}

		void Normalize( )
		{
			float length = Magnitude( );

			// Error check.
			if( length == 0.0f )
			{
				return;
			}

			x /= length;
			y /= length;
		}


		// Variables
		T x, y;

	};

	// Typedefs
	typedef Vector2<float> Vector2f;
	typedef Vector2<int> Vector2i;

}

#endif