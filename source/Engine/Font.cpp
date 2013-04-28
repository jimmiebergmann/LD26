#include <Engine/Font.hpp>
#include <iostream>

namespace LDE
{

	Font::Font( ) :
		m_pFont( NULL ),
		m_pSurface( NULL ),
		m_Loaded( false )
	{

	}

	bool Font::Load( std::string p_Path, unsigned int p_Size )
	{
		if( m_Loaded )
		{
			return false;
		}

		if( (m_pFont = TTF_OpenFont( p_Path.c_str( ), p_Size )) == NULL )
		{
			std::cout << "[Font::Load] Can not load the font." << std::endl;
			return false;
		}

		SDL_Color textColor = { 255, 255, 255 };

		if( (m_pSurface = TTF_RenderText_Solid( m_pFont, "Hej!", textColor )) == NULL )
		{
			std::cout << "[Font::Load] Can not load the surface." << std::endl;
			return false;
		}

		m_Loaded = true;
		return true;
	}

	void Font::Unload( )
	{
		if( m_pFont )
		{
			TTF_CloseFont( m_pFont );
		}

		if( m_pSurface )
		{
			SDL_FreeSurface( m_pSurface );
		}

		m_Loaded = false;
	}

	void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
	{
		//Holds offsets
		SDL_Rect offset;
	    
		//Get offsets
		offset.x = x;
		offset.y = y;
	    
		//Blit
		SDL_BlitSurface( source, clip, destination, &offset );
	}

	void Font::Render( std::string p_String, SDL_Surface * p_Screen )
	{
		if( m_Loaded == false )
		{
			return;
		}

		apply_surface( 0, 150, m_pSurface, p_Screen );

	}


}