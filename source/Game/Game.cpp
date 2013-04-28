#include <Game/Game.hpp>
#include <Engine/Utility.hpp>
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
	SDL_WM_SetCaption( "LD26", NULL );

	// Load the opengl SDL surface
	if( (pSurface = SDL_SetVideoMode( m_WindowSize.x, m_WindowSize.y, 16, SDL_OPENGL /*| SDL_FULLSCREEN */ ) ) == NULL )
	{
		std::cout << "[Game::Load( )] Unable to set SDL surface: " << SDL_GetError( ) << std::endl;
		return false;
	}

	SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 8 );

	// Set up opengl
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_LINE_SMOOTH );
	//glClearColor( 39.0f / 255.0f, 43.0f / 255.0f, 47.0f / 255.0f, 0.0f );
	glClearColor( 5.0f / 255.0f, 5.0f / 255.0f, 5.0f / 255.0f, 0.0f );
	glViewport( 0, 0, m_WindowSize.x, m_WindowSize.y );
	glClear( GL_COLOR_BUFFER_BIT /*|GL_DEPTH_BUFFER_BIT */ );

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

	// Load all the textures
	if( !m_PlanetTexture.Load( "Data/Textures/Planet2.BMP" ) )
	{
		std::cout << "[Game::Load( )] Unable to load the texture: " << SDL_GetError( ) << std::endl;
		return false;
	}

	if( !m_SpacecraftTexture.Load( "Data/Textures/Spacecraft.BMP" ) )
	{
		std::cout << "[Game::Load( )] Unable to load the texture: " << SDL_GetError( ) << std::endl;
		return false;
	}

	// Load the player
	m_Player = Player( &m_SpacecraftTexture );
	if( !m_Player.Load( ) )
	{
		std::cout << "[Game::Load( )] Unable to load the player" << std::endl;
		return false;
	}
	m_Player.SetPosition( LDE::Vector2f( -400.0f, -400.0f ) );
	m_Player.SetDirection( LDE::Vector2f( 0.0f, 1.0f ) );
	m_Player.SetColor( LDE::Color( 203, 203, 203 ) );
	m_Player.SetMaxSpeed( 300.0f );
	m_Player.SetRotationSpeed( 200.0f );

	// Load the hook
	m_Hook.SetLength( 300.0f );
	m_Hook.SetColor( m_Player.GetColor( ) );

	// Load the planet
	m_pPlanet = new Planet( LDE::Vector2f( 0.0f, 0.0f ), m_PlanetTexture.GetSize( ).x / 2, 50.0f, &m_PlanetTexture );
	if( !m_pPlanet->Load( ) )
	{
		std::cout << "[Game::Load( )] Unable to load the planet: " << SDL_GetError( ) << std::endl;
		return false;
	}
	m_pPlanet->SetPosition( LDE::Vector2f( 100.0f, 100.0f ) /*m_WindowSize / 2.0f*/ );
	m_pPlanet->SetColor( LDE::Color( 100, 171, 100 ) );
	//m_pPlanet->SetThickness( 50 );
	m_pPlanet->SetResourcesMax( 500 );
	m_pPlanet->SetResources( m_pPlanet->GetResourcesMax( ) );
	m_pPlanet->SetRotationSpeed( 30.0f );

	// Clear all pumps
	ClearAllPumpBullets( );

	// Clear all key inputs
	ClearKeyStates( );

	return true;
}

void Game::Unload( )
{
	// Unload the textures
	m_SpacecraftTexture.Unload( );
	m_PlanetTexture.Unload( );

	// Clear all the pumps
	ClearAllPumpBullets( );

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

	if( KeyIsDown( SDLK_w ) )
	{
		m_Player.BurstForwards( );
	}
	else if( KeyIsDown( SDLK_s ) )
	{
		m_Player.BurstBackwards( );
	}
	if( KeyIsDown( SDLK_a ) )
	{
		m_Player.BurstLeft( );
	}
	else if( KeyIsDown( SDLK_d ) )
	{
		m_Player.BurstRight( );
	}

	// Shooting the hook
	if( KeyIsDown( SDLK_LCTRL ) )
	{
		LDE::Vector2f HookPosition = m_Player.GetPosition( );
		HookPosition += m_Player.GetViewDirection( ) * m_Player.GetSize( ).y / 2.1f;

		m_Hook.SetPosition( HookPosition  );
		m_Hook.Fire( m_Player.GetViewDirection( ) );
	}

	// Shoot pumps
	if( KeyIsJustPressed( SDLK_SPACE ) )
	{
		if( m_PumpBullets.size( ) == 0 )
		{
			PumpBullet * pPumpBullet = new PumpBullet( );
			pPumpBullet->SetPosition( m_Player.GetPosition( ) );
			pPumpBullet->SetDirection( m_Player.GetViewDirection( ) );
			pPumpBullet->SetSpeed( 300.0f );
			pPumpBullet->SetColor( m_Player.GetColor( ) );
			m_PumpBullets.push_back( pPumpBullet );
		}
	}

	
	// Fill test
	if( KeyIsDown( SDLK_z ) )
	{
		if( m_pPlanet->GetResources( ) != m_pPlanet->GetResourcesMax( ) )
		{
			m_pPlanet->SetResources( m_pPlanet->GetResources( ) + 1 );
		}
	}
	else if( KeyIsDown( SDLK_x ) )
	{
		if( m_pPlanet->GetResources( ) != 0 )
		{
			m_pPlanet->SetResources( m_pPlanet->GetResources( ) - 1 );
		}
	}
	


	// //////////////////////////////////////////////////////////////
	// Game update

	// Update the player
	m_Player.Update( p_DeltaTime );

	// Update the hook
	LDE::Vector2f HookPosition = m_Player.GetPosition( );
	HookPosition += m_Player.GetViewDirection( ) * m_Player.GetSize( ).y / 2.1f;

	m_Hook.SetPosition( HookPosition  );
	m_Hook.Update( p_DeltaTime );

	// Update the planet
	m_pPlanet->Update( p_DeltaTime );

	// Update all pump bullets
	UpdatePumpBullets( p_DeltaTime );

	// Add planet gravity if we are close enought
	LDE::Vector2f planetDirection = m_pPlanet->GetPosition( ) - m_Player.GetPosition( );
	float planetDistance = planetDirection.Magnitude( );
	const float planetGravityStart = m_pPlanet->GetSize( ) * 4.5f;

	if( planetDistance <= planetGravityStart )
	{
		float gravityPower = 1.0f - ( planetDistance / planetGravityStart );
		
		LDE::Vector2f gravityVector = planetDirection.Normal( ) *
			gravityPower * (m_pPlanet->GetSize( ) / 50.0f );

		m_Player.SetDirection( m_Player.GetDirection( ) + gravityVector );
		
		//std::cout << gravityPower << std::endl;
	}

	//std::cout << planetDistance << std::endl;

	return 0;
}

void Game::Render( )
{
	// Clear the buffers
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );

	// Set up the camera
	LDE::Vector2f cameraDiff = m_Player.GetPosition( ) - ( LDE::Vector2f( m_WindowSize ) / 2.0f );
	glTranslatef( -cameraDiff.x, -cameraDiff.y, 0.0f );
	
	// Render the player
	m_Player.Render( );

	// Render the hook
	m_Hook.Render( );

	// Render the planet
	m_pPlanet->Render( );

	// Render pumps
	for( unsigned int i = 0; i < m_PumpBullets.size( ); i++ )
	{
		m_PumpBullets[ i ]->Render( );
	}

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

void Game::UpdatePumpBullets( double p_DeltaTime )
{
	std::vector<PumpBullet*>::iterator it = m_PumpBullets.begin();
	while (it != m_PumpBullets.end())
	{
		// Remove the bullet if it's too far away from the player
		float distance = LDE::Vector2f( m_Player.GetPosition( ) -
			(*it)->GetPosition( ) ).Magnitude( );
		if ( distance >= 1500.0f )
		{
			// erase returns the new iterator
			it = m_PumpBullets.erase(it);
		}
		else
		{
			// Store the last position
			LDE::Vector2f lastPos = (*it)->GetPosition( );

			// Update the bullet
			(*it)->Update( p_DeltaTime );

			// Check if any bullet hit the planet
			// Get the In and Out point of the intersection
			LDE::Vector2f In;
			LDE::Vector2f Out;
			int status = LDE::lineCircleIntersection(
				lastPos,
				(*it)->GetPosition( ),
				m_pPlanet->GetPosition( ),
				m_pPlanet->GetSize( ),
				In, Out);

			if( status == 1 )
			{
				// Add a pump to the planet
				// Calculate the angle of the position for the pump
				LDE::Vector2f pumpDirection = LDE::Vector2f( In - m_pPlanet->GetPosition( ) ).Normal( );
			
				// Calculate the angle
				float angle = LDE::AngleBetweenVectors2( LDE::Vector2f( 0.0f, 1.0f ), pumpDirection );
				if( pumpDirection.x < 0.0f )
				{
					angle = 360.f - angle;
				}

				// Add the pump the the planet
				// Fails if there's not enought space on the surface.
				m_pPlanet->AddNewPump( angle );

				// ////////////////////////////////////////////////////////////
				// Erase the bullet and add a pump to the planet instead.
				it = m_PumpBullets.erase(it);
			}
			else
			{
				// ////////////////////////
				// Increase the iterator
				++it;
			}
		}
	}


}

void Game::ClearAllPumpBullets( )
{
	for( unsigned int i = 0; i < m_PumpBullets.size( ); i++ )
	{
		delete m_PumpBullets[ i ];
	}
	m_PumpBullets.clear( );
}
