#ifndef __LDE_UTILITY_HPP__
#define __LDE_UTILITY_HPP__

#include <Engine/Vector2.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>

namespace LDE
{

	const double PI = 3.141592653589793238f;

	inline double DegreesToRadians( double p_Degrees)
	{
		return  p_Degrees * PI / 180.0f;
	}
	inline double RadiansToDegrees( double p_Radians )
	{
		return p_Radians * 180.0f / PI;
	}

	inline LDE::Vector2f RotateVector2f( LDE::Vector2f p_Vector, double p_Angle )
	{
		float cs = cos( DegreesToRadians( p_Angle ) );
		float sn = sin( DegreesToRadians( p_Angle ) );
	
		return LDE::Vector2f(
			p_Vector.x * cs - p_Vector.y * sn,
			p_Vector.x * sn + p_Vector.y * cs
			);
	}

	inline float AngleBetweenVectors2( LDE::Vector2f p_Vec1, LDE::Vector2f p_Vec2 )
	{
		float dotProduct = p_Vec1.Dot( p_Vec2 );			
		float vectorsMagnitude = p_Vec1.Magnitude( ) * p_Vec2.Magnitude( );

		float angle = RadiansToDegrees( acos(dotProduct / vectorsMagnitude)  );

		if(_isnan(angle))
			return 0;
		
		return angle ;
	}


	inline bool PointCircleIntersection( LDE::Vector2f p_Point,
		LDE::Vector2f p_CirclePoint, float p_CircleRadius )
	{
		float distance = LDE::Vector2f( p_CirclePoint - p_Point ).Magnitude( );

		if( distance <= p_CircleRadius )
		{
			return true;
		}

		return false;
	}


	inline LDE::Vector2f InterpolatePoints( float ax, float ay, float bx, float by, float f )
	{
		return LDE::Vector2f(
			f * ax + (1.0f - f) * bx,
			f * ay + (1.0f - f) * by );
	}

	inline int lineCircleIntersection( LDE::Vector2f p_LStart, LDE::Vector2f p_LEnd,
		LDE::Vector2f p_Circle, float p_R,
		LDE::Vector2f & p_Enter, LDE::Vector2f & p_Exit)
	{

		/*
		
		result = 1 // intersection
		result = -1 // none
		result = 0 // tangent
	
		*/

		float ax = p_LStart.x;
		float ay = p_LStart.y;
		float bx = p_LEnd.x;
		float by = p_LEnd.y;
		float cx = p_Circle.x;
		float cy = p_Circle.y;
		float r = p_R;

		int result = -1;
		bool setEnter = false;
		bool setExit = false;

		float a = (bx - ax) * (bx - ax) + (by - ay) * (by - ay);
		float b = 2.0f * ((bx - ax) * (ax - cx) + (by - ay) * (ay - cy));
		float cc = cx * cx + cy * cy + ax * ax + ay * ay - 2.0f * (cx * ax + cy * ay) - r * r;
		float deter = b * b - 4.0f * a * cc;
		if( deter <= 0.0f)
		{
			result = -1;
		}
		else
		{
			float e = sqrt(deter);
			float u1 = (-b + e) / (2.0f * a);
			float u2 = (-b - e) / (2.0f * a);
			if((u1 < 0.0f || u1 > 1.0f) && (u2 < 0.0f || u2 > 1.0f))
			{
				if((u1 < 0.0f && u2 < 0.0f) || (u1 > 1.0f && u2 > 1.0f))
				{
					result = -1;
				}
				else
				{
					result = 1;
				}
			}
			else
			{
				if(0.0f <= u2 && u2 <= 1.0f)
				{
					p_Enter = InterpolatePoints(ax, ay, bx, by, 1.0f - u2);
					setEnter = true;
				}
				if(0.0f <= u1 && u1 <= 1)
				{
					p_Exit = InterpolatePoints(ax, ay, bx, by, 1.0f - u1);
					setExit = true;
				}
				result = 1;
				if( setExit && setEnter && p_Exit.x == p_Enter.x && p_Exit.y == p_Enter.y)
				{
					result = 0;
				}
			}
		}

		return result;
	}


	/*
	function interpolatePoints(ax, ay, bx, by, f) {
  return [f * ax + (1 - f) * bx, f * ay + (1 - f) * by];
}

function lineCircleIntersection(ax, ay, bx, by, cx, cy, r) {
  var result = {
    inside: false,
    tangent: false,
    intersects: false,
    enter: null,
    exit: null
  };
  var a = (bx - ax) * (bx - ax) + (by - ay) * (by - ay);
  var b = 2 * ((bx - ax) * (ax - cx) + (by - ay) * (ay - cy));
  var cc = cx * cx + cy * cy + ax * ax + ay * ay - 2 * (cx * ax + cy * ay) - r * r;
  var deter = b * b - 4 * a * cc;
  if(deter <= 0) {
    result.inside = false;
  } else {
    var e = Math.sqrt(deter);
    var u1 = (-b + e) / (2 * a);
    var u2 = (-b - e) / (2 * a);
    if((u1 < 0 || u1 > 1) && (u2 < 0 || u2 > 1)) {
      if((u1 < 0 && u2 < 0) || (u1 > 1 && u2 > 1)) {
        result.inside = false;
      } else {
        result.inside = true;
      }
    } else {
      if(0 <= u2 && u2 <= 1) {
        result.enter = interpolatePoints(ax, ay, bx, by, 1 - u2);
      }
      if(0 <= u1 && u1 <= 1) {
        result.exit = interpolatePoints(ax, ay, bx, by, 1 - u1);
      }
      result.intersects = true;
      if(result.exit != null && result.enter != null && result.exit[0] == result.enter[0] && result.exit[1] == result.enter[1]) {
        result.tangent = true;
      }
    }
  }
  return result.intersects ? result : false;
}
*/

}

#endif