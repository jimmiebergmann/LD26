#ifndef __LDE_WINDOW_HPP__
#define __LDE_WINDOW_HPP__

#include <Engine/Sprite.hpp>
#include <Engine/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Event.hpp>
#include <string>

namespace LDE
{

	class Window
	{

	public:

		// Enums
		enum Event
		{
			Closed = sf::Event::Closed/*,
			Resized = sf::Event::Resized, 
			LostFocus = sf::Event::LostFocus, 
			GainedFocus = sf::Event::GainedFocus, 
			TextEntered = sf::Event::TextEntered, 
			KeyPressed = sf::Event::KeyPressed, 
			KeyReleased = sf::Event::KeyReleased,
			MouseWheelMoved = sf::Event::MouseWheelMoved, 
			MouseButtonPressed = sf::Event::MouseButtonPressed, 
			MouseButtonReleased = sf::Event::MouseButtonReleased, 
			MouseMoved = sf::Event::MouseMoved, 
			MouseEntered = sf::Event::MouseEntered, 
			MouseLeft = sf::Event::MouseLeft, 
			JoyButtonPressed = sf::Event::JoyButtonPressed, 
			JoyButtonReleased = sf::Event::JoyButtonReleased,
			JoyMoved = sf::Event::JoyMoved,
			Count = sf::Event::Count*/
		};

		// Constructors / destructors
		Window( );
		~Window( );

		// Public general functions
		bool Create( const unsigned int p_Width, const unsigned int p_Height,
			const unsigned int p_Bits, std::string p_Title, const bool p_Fullscreen );
		void Destroy( );
		void PresentScreen( );
		void ClearScreen( );
		bool PollEvent( Event & p_Event );
		void Show( );
		void Hide( );

		// Input functions
		LDE::Vector2i GetMousePositionLocal( );
		LDE::Vector2i GetMousePositionGlobal( );
		bool KeyIsDown( sf::Keyboard::Key p_Key );
		bool KeyIsUp( sf::Keyboard::Key p_Key );

		// Render functions
		void Render( Sprite  p_Sprite );

		// Get functions
		unsigned int GetWidth( ) const;
		unsigned int GetHeight( ) const;
		unsigned int GetBits( ) const;
		std::string GetTitle( ) const;

	private:

		// Private variables
		sf::RenderWindow m_sfWindow;
		unsigned int m_Width;
		unsigned int m_Height;
		unsigned int m_Bits;
		std::string m_Title;
		bool m_Fullscreen;
		bool m_Created;

	};

}

#endif