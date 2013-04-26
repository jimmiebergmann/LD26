#include <Engine/Sprite.hpp>
#include <iostream>

namespace LDE
{

	// Constructors / destructors
	Sprite::Sprite( ) :
		m_Loaded( false )
	{
	}

	Sprite::~Sprite( )
	{
	}
	
	// Public general functions
	bool Sprite::Load( Image & p_Image )
	{
		if( m_Loaded )
		{
			return false;
		}

		// Load the sprite by using an image
		if( !p_Image.IsLoaded( ) )
		{
			std::cout << "[Sprite::Load] The image is not loaded." << std::endl;
			return false;
		}

		m_sfSprite.SetImage( p_Image.m_sfImage );

		m_Loaded = true;
		return true;
	}

	void Sprite::Unload( )
	{


		m_Loaded = false;
	}

	// Get functions
	Vector2f Sprite::GetPosition( ) const
	{
		return m_Position;
	}

	Vector2f Sprite::GetSize( ) const
	{
		return m_Size;
	}

	bool Sprite::IsLoaded( ) const
	{
		return m_Loaded;
	}

	// Set functions
	void Sprite::SetPosition( const Vector2f p_Position )
	{
		m_sfSprite.SetPosition( p_Position.x, p_Position.y );
		m_Position = p_Position;
	}

	void Sprite::SetSize(  const Vector2f p_Size )
	{
		m_sfSprite.SetPosition( p_Size.x, p_Size.y );
		m_Size = p_Size;
	}


}