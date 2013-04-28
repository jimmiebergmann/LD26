#ifndef __LDE_FONT_HPP__
#define __LDE_FONT_HPP__

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <Engine/Vector2.hpp>

namespace LDE
{

	class Font
	{

	public:

		Font( );
		bool Load( std::string p_Path, unsigned int p_Size );
		void Unload( );
		void Render( std::string p_String, SDL_Surface * p_Screen );


	private:

		TTF_Font * m_pFont;
		SDL_Surface * m_pSurface;
		bool m_Loaded;


	};

}

#endif