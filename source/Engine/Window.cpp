#include <Engine/Window.hpp>

namespace LDE
{

	// Constructors / destructors
	Window::Window( ) :
		m_Width( 0 ),
		m_Height( 0 ),
		m_Bits( 0 ),
		m_Title( "" ),
		m_Fullscreen( false ),
		m_Created( false )
	{
		
	}

	Window::~Window( )
	{
	}

	// Public general functions
	bool Window::Create( const unsigned int p_Width, const unsigned int p_Height,
		const unsigned int p_Bits, std::string p_Title, const bool p_Fullscreen )
	{
		// Make sure the window isn't created already,
		if( m_Created )
		{
			return false;
		}

		// Decide if we want fullscreen of window mode.
		unsigned long windowStyle = sf::Style::Titlebar | sf::Style::Close;
		if( p_Fullscreen )
		{
			windowStyle = sf::Style::Fullscreen;
		}

		// Create the window
		m_sfWindow.Create( sf::VideoMode( p_Width, p_Height, p_Bits ),
			p_Title, windowStyle );

		// Set the private variables
		m_Width = p_Width;
		m_Height = p_Height;
		m_Bits = p_Bits;
		m_Title = p_Title;
		m_Fullscreen = p_Fullscreen;
		m_Created = true;

		// Return true, everything went ok.
		return true;
	}

	void Window::Destroy( )
	{
		
		m_sfWindow.Close( );
		m_Created = false;
	}

	void Window::PresentScreen( )
	{
		m_sfWindow.Display( );
	}

	void Window::ClearScreen( )
	{
		m_sfWindow.Clear( );
	}

	bool Window::PollEvent( Event & p_Event )
	{
		sf::Event e;
		bool status = m_sfWindow.GetEvent( e );
		p_Event = (Window::Event)( e.Type );

		return status;
	}

	void Window::Show( )
	{
		m_sfWindow.Show( true );
	}

	void Window::Hide( )
	{
		m_sfWindow.Show( false );
	}

	// Get functions
	unsigned int Window::GetWidth( ) const
	{
		return m_Width;
	}

	unsigned int Window::GetHeight( ) const
	{
		return m_Height;
	}

	unsigned int Window::GetBits( ) const
	{
		return m_Bits;
	}

	std::string Window::GetTitle( ) const
	{
		return m_Title;
	}

}