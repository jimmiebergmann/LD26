#ifndef __LDE_TEXTURE_HPP__
#define __LDE_TEXTURE_HPP__

#include <SDL_opengl.h>
#include <Engine/Vector2.hpp>
#include <string>


namespace LDE
{

	class Texture
	{

	public:

		// Constructors / destructors
		friend class Sprite;
		Texture( );
		~Texture( );
		
		// Public general functions
		bool Load( const std::string p_Path );
		void Unload( );
		void Bind( );
		void Unbind( );

		// Get functions
		Vector2i GetSize( ) const;
		bool IsLoaded( ) const;

	private:

		// Private functions

		// Private variables
		GLuint m_Id;
		LDE::Vector2i m_Size;
		bool m_Loaded;

	};

}

#endif