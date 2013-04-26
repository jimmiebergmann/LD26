#include <Game/Game.hpp>
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
		while( 1 )
		{
			double deltaTime = 1.0f / 60.0f;

			// Update everything
			if( Update( deltaTime ) != 0 )
			{
				std::cout << "ERROR!" << std::endl;
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

	if( !m_Window.Create( 800, 600, 32, "LD26 Entry.", false ) )
	{
		std::cout << "[Game::Load] Can not create the window. " << std::endl;
		return false;
	}

	return true;
}

void Game::Unload( )
{

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

	return 0;
}

void Game::Render( )
{
	// Clear the screen
	m_Window.ClearScreen( );


	// Present the screen
	m_Window.PresentScreen( );
}