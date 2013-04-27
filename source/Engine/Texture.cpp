#include <Engine/Texture.hpp>
#include <SDL.h>
#include <iostream>

namespace LDE
{

	// Constructors / destructors
	Texture::Texture( ) :
		m_Id( 0 ),
		m_Loaded( false )
	{
	}

	Texture::~Texture( )
	{
	}

	// Public general functions
	bool Texture::Load( const std::string p_Path )
	{
		if( m_Loaded )
		{
			return false;
		}

		SDL_Surface *surface;	// This surface will tell us the details of the image
		GLenum texture_format;
		GLint  nOfColors;
		 
		if ( (surface = SDL_LoadBMP( p_Path.c_str( ) )) ) { 
		 
			/*// Check that the image's width is a power of 2
			if ( (surface->w & (surface->w - 1)) != 0 ) {
				printf("warning: image.bmp's width is not a power of 2\n");
			}
		 
			// Also check if the height is a power of 2
			if ( (surface->h & (surface->h - 1)) != 0 ) {
				printf("warning: image.bmp's height is not a power of 2\n");
			}*/
		 
			// get the number of channels in the SDL surface
			nOfColors = surface->format->BytesPerPixel;
			if (nOfColors == 4)     // contains an alpha channel
			{
					if (surface->format->Rmask == 0x000000ff)
							texture_format = GL_RGBA;
					else
							texture_format = GL_BGRA;
			} else if (nOfColors == 3)     // no alpha channel
			{
					if (surface->format->Rmask == 0x000000ff)
							texture_format = GL_RGB;
					else
							texture_format = GL_BGR;
			} else {
					printf("[Texture::Load] warning: the image is not truecolor..  this will probably break\n");
					// this error should not go unhandled
			}
		 
			// Have OpenGL generate a texture object handle for us
			glGenTextures( 1, &m_Id );
		 
			// Bind the texture object
			glBindTexture( GL_TEXTURE_2D, m_Id );
		 
			// Set the texture's stretching properties
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		 
			glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
			glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

			// Edit the texture object's image data using the information SDL_Surface gives us
			glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, surface->w, surface->h, 0,
							  texture_format, GL_UNSIGNED_BYTE, surface->pixels );

			m_Size.x = surface->w;
			m_Size.y = surface->h;
		} 
		else {
			std::cout << "[Texture::Load] SDL could not load image.bmp: " << SDL_GetError() << std::endl;
			return false;
		}    
		 
		// Free the SDL_Surface only if it was successfully created
		if ( surface ) { 
			SDL_FreeSurface( surface );
		}

		m_Loaded = true;
		return true;
	}

	void Texture::Unload( )
	{
		if( m_Id )
		{
			glDeleteTextures( 1, &m_Id );
		}
		
		m_Loaded = false;
	}

	void Texture::Bind( )
	{
		glBindTexture( GL_TEXTURE_2D, m_Id );
	}

	void Texture::Unbind( )
	{
		glBindTexture( GL_TEXTURE_2D, 0 );
	}

	Vector2i Texture::GetSize( ) const
	{
		return m_Size;
	}


	bool Texture::IsLoaded( ) const
	{
		return m_Loaded;
	}

}