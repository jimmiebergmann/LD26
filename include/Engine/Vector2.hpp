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

		const Vector2< T > operator = ( const Vector2< T > p_Vector )
		{
			x = p_Vector.x;
			y = p_Vector.y;
			return *this;
		}

		const float Magnitude( ) const
		{
			return sqrt( ( x*x ) + ( y*y ) );
		};


		// Variables
		T x, y;

	};

	// Typedefs
	typedef Vector2<float> Vector2f;
	typedef Vector2<int> Vector2i;

}

#endif