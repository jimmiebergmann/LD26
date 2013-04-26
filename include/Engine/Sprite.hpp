#ifndef __LDE_SPRITE_HPP__
#define __LDE_SPRITE_HPP__

#include <SFML/Graphics.hpp>
#include <Engine/Image.hpp>
#include <Engine/Vector2.hpp>


namespace LDE
{

	class Sprite
	{

	public:

		// Constructors / destructors
		friend class Window;
		Sprite( );
		~Sprite( );
		
		// Public general functions
		bool Load( Image & p_Image );
		void Unload( );

		// Get functions
		Vector2f GetPosition( ) const;
		Vector2f GetSize( ) const;
		bool IsLoaded( ) const;

		// Set functions
		void SetPosition( const Vector2f p_Position );
		void SetSize(  const Vector2f p_Size );

	private:

		// Private functions

		// Private variables
		sf::Sprite m_sfSprite;
		Vector2f m_Position;
		Vector2f m_Size;
		bool m_Loaded;


	};

}

#endif