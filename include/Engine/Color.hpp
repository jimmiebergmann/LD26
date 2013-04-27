#ifndef __LDE_COLOR_HPP__
#define __LDE_COLOR_HPP__

#include <cmath>

namespace LDE
{

	struct Color
	{
		// Constructors
		Color( ) :
			r( 0 ),
			g( 0 ),
			b( 0 ),
			a( 0 )
		{
		}

		Color( const unsigned char p_R, const unsigned char p_G,
			const unsigned char p_B, const unsigned char p_A )
		{
			r = p_R;
			g = p_G;
			b = p_B;
			a = p_A;
		}

		Color( const unsigned char p_R, const unsigned char p_G,
			const unsigned char p_B )
		{
			r = p_R;
			g = p_G;
			b = p_B;
			a = 0;
		}

		// Variables
		unsigned char r, g, b, a;
	};

}

#endif