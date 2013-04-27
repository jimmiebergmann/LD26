#ifndef __LDE_UTILITY_HPP__
#define __LDE_UTILITY_HPP__

#include <Engine/Vector2.hpp>
#include <cmath>

namespace LDE
{

	const double PI = 3.141592653589793238f;

	double DegreesToRadians( double p_Degrees)
	{
		return  p_Degrees * PI / 180.0f;
	}
	double RadiansToDegrees( double p_Radians )
	{
		return p_Radians * 180.0f / PI;
	}


	LDE::Vector2f RotateVector2f( LDE::Vector2f p_Vector, double p_Angle )
	{
		float cs = cos( DegreesToRadians( p_Angle ) );
		float sn = sin( DegreesToRadians( p_Angle ) );
	
		return LDE::Vector2f(
			p_Vector.x * cs - p_Vector.y * sn,
			p_Vector.x * sn + p_Vector.y * cs
			);
	}

	/*
	px = x * cs - y * sn; 
	py = x * sn + y * cs;
*/

}

#endif