#include <Engine/Image.hpp>
#include <iostream>

namespace LDE
{

	// Constructors / destructors
	Image::Image( ) :
		m_Loaded( false )
	{
	}

	Image::~Image( )
	{
	}

	// Public general functions
	bool Image::Load( const std::string p_Path )
	{
		if( m_Loaded )
		{
			return false;
		}

		// Load the image from a file
		if( !m_sfImage.LoadFromFile( p_Path ) )
		{
			std::cout << "[Image::Load] Can not load the image: " << p_Path << std::endl;
			return false;
		}


		m_Loaded = true;
		return true;
	}

	void Image::Unload( )
	{

		m_Loaded = false;
	}

	// Get functions
	/*Vector2f GetPosition( ) const;

	Vector2f GetSize( ) const;*/

	bool Image::IsLoaded( ) const
	{
		return m_Loaded;
	}

}