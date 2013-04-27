#include <Game/Game.hpp>
#include <Engine/Timer.hpp>
#include <iostream>

// Constructors / destructors
Game::Game( )
{
}

Game::~Game( )
{
}

// General functions
int Game::Run( int p_Argc, char ** p_Argv )
{
	// Load the game
	// No errors? Let's run the game loop
	if( Load( ) )
	{
		// Create a game timer
		LDE::Timer timer;
		timer.Start( );

		// Loop until we break it
		while( 1 )
		{
			// Get the delta time
			timer.Stop( );
			double deltaTime = timer.GetTime( );
			//std::cout << 1.0f / deltaTime << " FPS." << std::endl;
			timer.Start( );

			// Update everything
			if( Update( deltaTime ) != 0 )
			{
				// Break the game loop
				break;
			}

			//Render everything in the window
			Render( );

		}
	}
	// We couldn't load the game
	else
	{
		// Wait for any input to close the program.
		std::cin.get( );
	}

	// Unload everything
	Unload( );
	
	return 0;
}

// Private functions
bool Game::Load( )
{
	// Create the window
	if( !m_Window.Create( 800, 600, 32, "LD26 Entry.", false ) )
	{
		std::cout << "[Game::Load] Can not create the window. " << std::endl;
		return false;
	}

	// Load the image
	if( !m_Texture.Load( "Data/Textures/Test.png" ) )
	{
		std::cout << "[Game::Load] Can not load the image. " << std::endl;
		return false;
	}

	// Load the sprite
	if( !m_Sprite.Load( m_Texture ) )
	{
		std::cout << "[Game::Load] Can not load the sprite. " << std::endl;
		return false;
	}

	m_Sprite.SetPosition( LDE::Vector2f( 200, 200 ) );


	return true;
}

void Game::Unload( )
{
	m_Window.Destroy( );
}

int Game::Update( double p_DeltaTime )
{

	// Poll all the events
	bool exit = false;
	LDE::Window::Event e;
	while( m_Window.PollEvent( e ) )
	{
		switch( e )
		{
		case LDE::Window::Closed:
			exit = true;
			break;
		default:
			break;
		}
	}

	// Should we exit?
	if( exit )
	{
		return 1;
	}


	// Update the sprtie
	LDE::Vector2f spritePos = m_Sprite.GetPosition( );
	m_Sprite.SetPosition( LDE::Vector2f( spritePos.x + ( 300.0f * p_DeltaTime ), spritePos.y ) );

	if( m_Window.KeyIsDown( sf::Keyboard::A ) )
	{
		std::cout << "A" << std::endl;
	}



	// Test input

	//m_Window.KeyIsDown( sf::Key::Escape );


	return 0;
}

void Game::Render( )
{
	// Clear the screen
	m_Window.ClearScreen( );

	// Render everything
	m_Window.Render( m_Sprite );


	// Present the screen
	m_Window.PresentScreen( );
}