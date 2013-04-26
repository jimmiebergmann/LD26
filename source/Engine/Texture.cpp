#include <Engine/Texture.hpp>
#include <iostream>

namespace LDE
{

	// Constructors / destructors
	Texture::Texture( ) :
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

		// Load the image from a file
		if( !m_sfImage.loadFromFile( p_Path ) )
		{
			std::cout << "[Image::Load] Can not load the image: " << p_Path << std::endl;
			return false;
		}

		// Load the texture from the image
		if( !m_sfTexture.loadFromImage( m_sfImage ) )
		{
			std::cout << "[Image::Load] Can not load the image: " << p_Path << std::endl;
			return false;
		}




		m_Loaded = true;
		return true;
	}

	void Texture::Unload( )
	{

		m_Loaded = false;
	}

	// Get functions
	/*Vector2f GetPosition( ) const;

	Vector2f GetSize( ) const;*/

	bool Texture::IsLoaded( ) const
	{
		return m_Loaded;
	}

}