#include <Game/Game.hpp>
#include <Engine/Timer.hpp>
#include <iostream>

// Constructors / destructors
Game::Game( ) :
	pSurface( NULL ),
	pScreen( NULL ),
	m_Running( false )
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
		m_Running = true;
		while( m_Running )
		{
			// Get the delta time
			timer.Stop( );
			double deltaTime = timer.GetTime( );
			//std::cout << 1.0f / deltaTime << " FPS." << std::endl;
			timer.Start( );

			// Poll events
			PollEvents( );

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
	LDE::Vector2i windowSize( 1024, 720 );

	// Initialize SDL IMPORTANT
	if( SDL_Init( SDL_INIT_VIDEO ) != 0 )
	{
		std::cout << "[Game::Load( )] Unable to initialize SDL: " << SDL_GetError( ) << std::endl;
		return false;
	}

	// use OGL double buffer
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	// Load the opengl SDL surface
	if( (pSurface = SDL_SetVideoMode( windowSize.x, windowSize.y, 16, SDL_OPENGL /*| SDL_FULLSCREEN */ ) ) == NULL )
	{
		std::cout << "[Game::Load( )] Unable to set SDL surface: " << SDL_GetError( ) << std::endl;
		return false;
	}

	// Set up opengl
	glEnable( GL_TEXTURE_2D );
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glViewport( 0, 0, windowSize.x, windowSize.y );
	glClear( GL_COLOR_BUFFER_BIT /* |GL_DEPTH_BUFFER_BIT */ );

	// Enable alpha blending
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glEnable( GL_BLEND );
	glAlphaFunc( GL_GREATER, 0 );
	glEnable( GL_ALPHA_TEST );

	// Set up opengl matrices
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	glOrtho( 0.0f, windowSize.x, 0.0f, windowSize.y, -1.0f, 1.0f );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );

	// Load a test texture
	if( !m_Texture.Load( "Data/Textures/Test.BMP" ) )
	{
		std::cout << "[Game::Load( )] Unable to load the texture: " << SDL_GetError( ) << std::endl;
		return false;
	}

	// Load the render quad
	m_RenderQuad.SetVertLowCoo( LDE::Vector2f( 0.0f, 0.0f ) );
	m_RenderQuad.SetVertHighCoo( m_Texture.GetSize( ) );
	m_RenderQuad.SetTexLowCoo( LDE::Vector2f( 0.0f, 0.0f ) );
	m_RenderQuad.SetTexHighCoo( LDE::Vector2f( 1.0f, 1.0f ) );

	return true;
}

void Game::Unload( )
{
	// Unload the texture
	m_Texture.Unload( );

	// Close SDL
	SDL_Quit();
}

void Game::PollEvents( )
{
	// Poll SDL event
	SDL_Event e;
	while( SDL_PollEvent( &e ) )
	{
		switch( e.type )
		{
		case SDL_QUIT:
			m_Running = false;
			break;
		default: break;
		}
	}
}

int Game::Update( double p_DeltaTime )
{
	/*m_Window.Update( );

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
*/
/*
	// Should we exit?
	if( exit )
	{
		rturn 1;
	}
*/

	// Update the sprtie
	//LDE::Vector2f spritePos = m_Sprite.GetPosition( );
	//m_Sprite.SetPosition( LDE::Vector2f( spritePos.x + ( 300.0f * p_DeltaTime ), spritePos.y ) );


/*
	if( m_Window.KeyIsJustPressed( sf::Keyboard::A ) )
	{
		m_pSound->Play( );
	}
*/


/*
	LDE::Vector2i mousePos = m_Window.GetMousePositionGlobal( );
	std::cout << mousePos.x << "  " << mousePos.y << std::endl;
*/

	// Test input

	//m_Window.KeyIsDown( sf::Key::Escape );


	return 0;
}

void Game::Render( )
{
	// Clear the buffers
	glClear( GL_COLOR_BUFFER_BIT );


	m_Texture.Bind( );
	m_RenderQuad.Render( );
/*
	//glBindTexture( GL_TEXTURE_2D, m_Texture );
	glBegin( GL_QUADS );

	glTexCoord2f( 0.0f, 0.0f );
	glVertex2f( 0.0f, 0.0f );

	glTexCoord2f( 1.0f, 0.0f );
	glVertex2f( 200.0f, 0.0f );

	glTexCoord2f( 1.0f, 1.0f );
	glVertex2f( 200.0f, 200.0f );

	glTexCoord2f( 0.0f, 1.0f );
	glVertex2f( 0.0f, 200.0f );
*/


	glEnd( );


	// Swap all buffers
	SDL_GL_SwapBuffers( );
}
