#ifndef __LDE_IMAGE_HPP__
#define __LDE_IMAGE_HPP__

#include <SFML/Graphics.hpp>
#include <string>


namespace LDE
{

	class Image
	{

	public:

		// Constructors / destructors
		friend class Sprite;
		Image( );
		~Image( );
		
		// Public general functions
		bool Load( const std::string p_Path );
		void Unload( );

		// Get functions
		/*Vector2f GetPosition( ) const;
		Vector2f GetSize( ) const;*/
		bool IsLoaded( ) const;


	private:

		// Private functions

		// Private variables
		sf::Image m_sfImage;

		bool m_Loaded;




	};

}

#endif