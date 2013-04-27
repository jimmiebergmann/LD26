#include <Game/Game.hpp>
#include <Engine/Timer.hpp>
#include <iostream>

// Constructors / destructors
Game::Game( ) :
	pSurface( NULL ),
	pScreen( NULL ),
	m_pPlanet( NULL ),
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
	m_WindowSize = LDE::Vector2i( 1024, 720 );

	// Initialize SDL IMPORTANT
	if( SDL_Init( SDL_INIT_VIDEO ) != 0 )
	{
		std::cout << "[Game::Load( )] Unable to initialize SDL: " << SDL_GetError( ) << std::endl;
		return false;
	}

	// use OGL double buffer
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	// Load the opengl SDL surface
	if( (pSurface = SDL_SetVideoMode( m_WindowSize.x, m_WindowSize.y, 32, SDL_OPENGL /*| SDL_FULLSCREEN */ ) ) == NULL )
	{
		std::cout << "[Game::Load( )] Unable to set SDL surface: " << SDL_GetError( ) << std::endl;
		return false;
	}

	SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 8 );

	// Set up opengl
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_LINE_SMOOTH );
	glClearColor( 39.0f / 255.0f, 43.0f / 255.0f, 47.0f / 255.0f, 0.0f );
	glViewport( 0, 0, m_WindowSize.x, m_WindowSize.y );
	glClear( GL_COLOR_BUFFER_BIT /* |GL_DEPTH_BUFFER_BIT */ );

	// Enable alpha blending
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glEnable( GL_BLEND );
	glAlphaFunc( GL_GREATER, 0 );
	glEnable( GL_ALPHA_TEST );

	// Set up opengl matrices
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	glOrtho( 0.0f, m_WindowSize.x, 0.0f, m_WindowSize.y, -1.0f, 1.0f );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );

	// Load a test texture
	if( !m_PlanetTexture.Load( "Data/Textures/Test.BMP" ) )
	{
		std::cout << "[Game::Load( )] Unable to load the texture: " << SDL_GetError( ) << std::endl;
		return false;
	}

	// Load the planet
	m_pPlanet = new Planet( LDE::Vector2f( 0.0f, 0.0f ), m_PlanetTexture.GetSize( ).x / 2, &m_PlanetTexture );
	if( !m_pPlanet->Load( ) )
	{
		std::cout << "[Game::Load( )] Unable to load the planet: " << SDL_GetError( ) << std::endl;
		return false;
	}
	m_pPlanet->SetPosition( m_WindowSize / 2.0f );
	m_pPlanet->SetColor( LDE::Color( 100, 171, 100 ) );
	m_pPlanet->SetResourcesMax( 100 );
	m_pPlanet->SetResources( 50 );
	m_pPlanet->SetRotationSpeed( 30.0f );

	// Clear all key inputs
	ClearKeyStates( );


	return true;
}

void Game::Unload( )
{
	// Unload the texture
	m_PlanetTexture.Unload( );

	// Unload the planet
	if( m_pPlanet )
	{
		delete m_pPlanet;
		m_pPlanet = NULL;
	}

	// Close SDL
	SDL_Quit();
}

void Game::PollEvents( )
{
	// Update prev key events
	UpdatePreKeyEvents( );

	// Poll SDL event
	SDL_Event e;
	while( SDL_PollEvent( &e ) )
	{
		switch( e.type )
		{

		case SDL_QUIT:
			m_Running = false;
			break;

		case SDL_KEYDOWN:
			m_CurrentKeyState[ (int)(e.key.keysym.sym) ] = true;
			break;

		case SDL_KEYUP:
			m_CurrentKeyState[ (int)(e.key.keysym.sym) ] = false;
			break;

		default:
			break;

		}
	}
}

int Game::Update( double p_DeltaTime )
{
	// /////////////////////////////////////////////
	// INPUT

	// Exit if we press Escape
	if( KeyIsJustPressed( SDLK_ESCAPE ) )
	{
		return 1;
	}

	if( KeyIsDown( SDLK_a ) )
	{
		if( m_pPlanet->GetResources( ) != m_pPlanet->GetResourcesMax( ) )
		{
			m_pPlanet->SetResources( m_pPlanet->GetResources( ) + 1 );
		}
	}
	else if( KeyIsDown( SDLK_s ) )
	{
		if( m_pPlanet->GetResources( ) != 0 )
		{
			m_pPlanet->SetResources( m_pPlanet->GetResources( ) - 1 );
		}
	}


	// //////////////////////////////////////////////////////////////
	// Game update
	
	// Update the planet
	m_pPlanet->Update( p_DeltaTime );

	return 0;
}

void Game::Render( )
{
	// Clear the buffers
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Render the planet
	m_pPlanet->Render( );

	// Swap all buffers
	SDL_GL_SwapBuffers( );
}

// Input functions
void Game::ClearKeyStates( )
{
	for( unsigned int i = 0; i < SDLK_LAST; i++ )
	{
		m_CurrentKeyState[ i ] = false;
		m_LastKeyState[ i ] = false;
	}
}

void Game::UpdatePreKeyEvents( )
{
	// SLOW!!!!
	for( unsigned int i = 0; i < SDLK_LAST; i++ )
	{
		m_LastKeyState[ i ] = m_CurrentKeyState[ i ];
	}
}

bool Game::KeyIsDown( SDLKey p_Key )
{
	return m_CurrentKeyState[ (unsigned int)(p_Key) ];
}

bool Game::KeyIsUp( SDLKey p_Key )
{
	return !m_CurrentKeyState[ (unsigned int)(p_Key) ];
}

bool Game::KeyIsJustPressed( SDLKey p_Key )
{
	return m_CurrentKeyState[ (unsigned int)(p_Key) ] &&
		!m_LastKeyState[ (unsigned int)(p_Key) ];
}

bool Game::KeyIsJustReleased( SDLKey p_Key )
{
	return !m_CurrentKeyState[ (unsigned int)(p_Key) ] &&
		m_LastKeyState[ (unsigned int)(p_Key) ];
}

