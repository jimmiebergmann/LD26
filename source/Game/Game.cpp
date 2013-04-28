#include <Game/Game.hpp>
#include <windows.h>
#include <Engine/Utility.hpp>
#include <Engine/Timer.hpp>
#include <iostream>

// Constructors / destructors
Game::Game( ) :
	m_pSurface( NULL ),
	m_CurrPlanet( ) ,
	m_ActiveLazer( false ),
	m_OverlayAlpha( 0.0f ),
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
			timer.DeltaLock( 256.0f );
			double deltaTime = timer.GetTime( );

			
			//std::cout << 1.0f / deltaTime << " FPS." << std::endl;
			// Sleep some time if the delta time is day too much

			/*const float fpslock = 1000.0;
			if( (1.0f / deltaTime ) > fpslock )
			{

				float time = 1.0f / deltaTime;
				

				
				Sleep( 0 );
			}*/

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
	if( (m_pSurface = SDL_SetVideoMode( m_WindowSize.x, m_WindowSize.y, 16, SDL_OPENGL /*| SDL_FULLSCREEN */ ) ) == NULL )
	{
		std::cout << "[Game::Load( )] Unable to set SDL surface: " << SDL_GetError( ) << std::endl;
		return false;
	}

	//Initialize SDL_ttf
   /* if( TTF_Init() == -1 )
    {
		std::cout << "[Game::Load( )] Unable to init TTF: " << SDL_GetError( ) << std::endl;
        return false;    
    }*/

	// Load the font
	/*if( !m_Font.Load( "Data/Fonts/pixelart.ttf", 28 ) )
	{
		std::cout << "[Game::Load( )] Unable to load the font: " << SDL_GetError( ) << std::endl;
		return false;
	}*/

	//SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 8 );

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

	// Load the game start values
	LoadStartValues( );


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

	if( !m_OverlayTexture.Load( "Data/Textures/Overlay.BMP" ) )
	{
		std::cout << "[Game::Load( )] Unable to load the texture: " << SDL_GetError( ) << std::endl;
		return false;
	}

	// Load the overlay quad
	m_OverlayQuad.SetPosition( LDE::Vector2f( 0.0f, 0.0f ) );
	m_OverlayQuad.SetVertLowCoo( LDE::Vector2f( 0.0f, 0.0f ) );
	m_OverlayQuad.SetVertHighCoo( m_WindowSize );
	m_OverlayQuad.SetTexLowCoo( LDE::Vector2f( 0.0f, 0.0f ) );
	m_OverlayQuad.SetTexHighCoo( LDE::Vector2f( 1.0f, 1.0f ) );

	// Load the player
	m_Player = Player( &m_SpacecraftTexture );
	if( !m_Player.Load( ) )
	{
		std::cout << "[Game::Load( )] Unable to load the player" << std::endl;
		return false;
	}
	m_Player.SetPosition( m_StartPlayerPosition );
	m_Player.SetDirection( m_StartPlayerDirection );
	m_Player.SetColor( m_StartPlayerColor );
	m_Player.SetMaxSpeed( 300.0f );
	m_Player.SetRotationSpeed( 200.0f );

	// Load the hook
	m_Hook.SetLength( 300.0f );
	m_Hook.SetColor( m_Player.GetColor( ) );

	// Load the planets
	for( unsigned int i = 0; i < PLANET_COUNT; i++ )
	{
		m_Planets[ i ].SetTexture( &m_PlanetTexture );
		m_Planets[ i ].Load( );
	}
	// Set all the other planet values
	SetPlanetValues( );

	// Clear all pumps
	ClearAllPumpBullets( );

	// Clear all key inputs
	ClearKeyStates( );

	return true;
}

void Game::LoadStartValues( )
{
	m_CurrPlanet = 0;
	m_StartPlayerPosition = LDE::Vector2f( -400.0f, -400.0f );
	m_StartPlayerDirection = LDE::Vector2f( 0.0f, 1.0f );
	m_StartPlayerColor = LDE::Color( 203, 203, 203 );
	m_StartPlayerRadius = 15.0f;
	m_StartPumpSpeed = 0.2f;
	m_StartBulletSpeed = 300.0f;
	m_StartMaxPlanetRange = 1000.0f;

	m_StartPlanetPosition = LDE::Vector2f( 0.0f, 0.0f );

	m_StartPlanetColors[ 0 ] = LDE::Color( 100, 171, 100 );	// Green
	m_StartPlanetColors[ 1 ] = LDE::Color( 192, 82, 78 );	// Red
	m_StartPlanetColors[ 2 ] = LDE::Color( 80, 156, 190 );	// Blue
	m_StartPlanetColors[ 3 ] = LDE::Color( 175, 181, 89 );	// Yellow
	m_StartPlanetColors[ 4 ] = LDE::Color( 95, 89, 181 );	// Purple

	m_StartPlanetSizes[ 0 ] = 250;
	m_StartPlanetThicknesses[ 0 ] = 50;

	m_StartPlanetSizes[ 1 ] = 200;
	m_StartPlanetThicknesses[ 1 ] = 40;

	m_StartPlanetSizes[ 2 ] = 160;
	m_StartPlanetThicknesses[ 2 ] = 25;

	m_StartPlanetSizes[ 3 ] = 135;
	m_StartPlanetThicknesses[ 3 ] = 20;

	m_StartPlanetSizes[ 4 ] = 115;
	m_StartPlanetThicknesses[ 4 ] = 18;

	m_StartPlanetMaxResources[ 0 ] = 1.0f;
	m_StartPlanetMaxResources[ 1 ] = 1.0f;
	m_StartPlanetMaxResources[ 2 ] = 1.0f;
	m_StartPlanetMaxResources[ 3 ] = 1.0f;
	m_StartPlanetMaxResources[ 4 ] = 1.0f;

	m_StartPlanetRotationSpeed[ 0 ] = 30.0f;
	m_StartPlanetRotationSpeed[ 1 ] = 40.0f;
	m_StartPlanetRotationSpeed[ 2 ] = 50.0f;
	m_StartPlanetRotationSpeed[ 3 ] = 55.0f;
	m_StartPlanetRotationSpeed[ 4 ] = 60.0f;
	
/*
	m_StartPlanetRotationSpeed[ 0 ] = 0.0f;
	m_StartPlanetRotationSpeed[ 1 ] = 0.0f;
	m_StartPlanetRotationSpeed[ 2 ] = 0.0f;
*/

}

void Game::SetPlanetValues( )
{
	m_CurrPlanet = 0;

	for( unsigned int i = 0; i < PLANET_COUNT; i++ )
	{
		m_Planets[ i ].SetPosition( m_StartPlanetPosition );
		m_Planets[ i ].SetColor( m_StartPlanetColors[ i ] );
		m_Planets[ i ].SetSize( m_StartPlanetSizes[ i ] );
		m_Planets[ i ].SetResources( m_StartPlanetMaxResources[ i ] );
		//m_Planets[ i ].SetResourcesMax( m_StartPlanetMaxResources[ i ] );
		//m_Planets[ i ].SetPumpMaxResources( m_StartPlanetMaxResources[ i ] );
		m_Planets[ i ].SetRotationSpeed( m_StartPlanetRotationSpeed[ i ] );
		m_Planets[ i ].SetThickness( m_StartPlanetThicknesses[ i ] );
		m_Planets[ i ].SetPumpSpeed( m_StartPumpSpeed );
		m_Planets[ i ].ResetPump( );
	}

}

void Game::Unload( )
{
	// Unload the textures
	m_SpacecraftTexture.Unload( );
	m_PlanetTexture.Unload( );
	m_OverlayTexture.Unload( );

	// Clear all the pumps
	ClearAllPumpBullets( );

	// Unload the font
	//m_Font.Unload( );

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

	// Shoot pumps / lazer
	m_ActiveLazer = false;

	if( KeyIsDown( SDLK_SPACE ) )
	{
		if( m_PumpBullets.size( ) == 0 )
		{
			// Shoot bullets
			if( !m_Planets[ m_CurrPlanet ].IsPumpActive( ) &&
				KeyIsJustPressed( SDLK_SPACE ) )
			{
				PumpBullet * pPumpBullet = new PumpBullet( );
				pPumpBullet->SetPosition( m_Player.GetPosition( ) );
				pPumpBullet->SetDirection( m_Player.GetViewDirection( ) );
				pPumpBullet->SetSpeed( m_StartBulletSpeed );
				pPumpBullet->SetColor( m_Player.GetColor( ) );
				m_PumpBullets.push_back( pPumpBullet );
			}
			// Shoot lazer
			else if( m_Planets[ m_CurrPlanet ].IsPumpActive( ) )
			{
				m_ActiveLazer = true;
			}
		}
	}

	
	// Fill test
	if( KeyIsDown( SDLK_z ) )
	{
		if( m_Planets[ m_CurrPlanet ].GetResources( ) != 1.0f )
		{
			m_Planets[ m_CurrPlanet ].SetResources( m_Planets[ m_CurrPlanet ].GetResources( ) + ( 0.25f * p_DeltaTime) );
		}
	}
	else if( KeyIsDown( SDLK_x ) )
	{
		if( m_Planets[ m_CurrPlanet ].GetResources( ) != 0.0f )
		{
			m_Planets[ m_CurrPlanet ].SetResources( m_Planets[ m_CurrPlanet ].GetResources( ) - ( 0.25f * p_DeltaTime) );
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
	m_Planets[ m_CurrPlanet ].Update( p_DeltaTime );

	// Update all pump bullets
	UpdatePumpBullets( p_DeltaTime );

	const LDE::Vector2f pumpPosition = m_Planets[ m_CurrPlanet ].GetGlobalPumpPosition( );;

	// Update the lazer
	m_LazerHittingPump = false;
	if( m_ActiveLazer )
	{
		m_LazerPoints[ 0 ] = m_Player.GetPosition( );
		m_LazerPoints[ 1 ] = m_Player.GetPosition( ) + ( m_Player.GetViewDirection( ) * 1000.0f );

		// Check if any bullet hit the planet
		// Get the In and Out point of the intersection
		LDE::Vector2f inPump;
		LDE::Vector2f out;
		int pumpCol = LDE::LineCircleIntersection( m_LazerPoints[ 0 ], m_LazerPoints[ 1 ],
			pumpPosition, m_Planets[ m_CurrPlanet ].GetPumpSize( ), inPump, out);

		LDE::Vector2f inPlanet;
		int planetCol = LDE::LineCircleIntersection( m_LazerPoints[ 0 ], m_LazerPoints[ 1 ],
			m_Planets[ m_CurrPlanet ].GetPosition( ), m_Planets[ m_CurrPlanet ].GetSize( ), inPlanet, out);


		// Calculate the lazer
		if( pumpCol == 1 || planetCol == 1)
		{
			float planetDist = LDE::Vector2f( m_LazerPoints[ 0 ] - inPlanet ).Magnitude( );
			float pumpDist = LDE::Vector2f( m_LazerPoints[ 0 ] - inPump ).Magnitude( );
			
			if( planetDist <= pumpDist )
			{
				m_LazerPoints[ 1 ] = inPlanet;
			}
			else
			{
				m_LazerPoints[ 1 ] = inPump;
				m_Planets[ m_CurrPlanet ].DrainPlanet( );
			}
		}
		else if( pumpCol == 1)
		{
          	m_LazerPoints[ 1 ] = inPump;
		}
		else if( planetCol == 1)
		{
			m_LazerPoints[ 1 ] = inPlanet;
		}

	}

	// Add planet gravity if we are close enought
	LDE::Vector2f planetDirection = m_Planets[ m_CurrPlanet ].GetPosition( ) - m_Player.GetPosition( );
	float planetDistance = planetDirection.Magnitude( );
	const float planetGravityStart = m_Planets[ m_CurrPlanet ].GetSize( ) * 7.5f;

	if( planetDistance <= planetGravityStart )
	{
		float gravityPower = 1.0f - ( planetDistance / planetGravityStart );
		gravityPower *= 35.0f;
		//gravityPower /= 2.0f;
		
		LDE::Vector2f gravityVector = planetDirection.Normal( ) *
			gravityPower * p_DeltaTime * (m_Planets[ m_CurrPlanet ].GetSize( ) / 50.0f );

		m_Player.SetDirection( m_Player.GetDirection( ) + gravityVector );
	}

	// Collision detect the player and the player/pump
	if( CircleCircleIntersection( m_Player.GetPosition( ), m_StartPlayerRadius,
		m_Planets[ m_CurrPlanet ].GetPosition( ), m_Planets[ m_CurrPlanet ].GetSize( ) ) )
	{
		// We died!
		ResetGame( );
	}

	// Are we coliding with the pump?
	if( CircleCircleIntersection( m_Player.GetPosition( ), m_StartPlayerRadius,
		pumpPosition, m_Planets[ m_CurrPlanet ].GetPumpSize( ) ) )
	{
		// We died!
		ResetGame( );
		return 0;
	}
	//std::cout << pumpPosition.x << "   " << pumpPosition.y << std::endl;

	// Are we outside the navigation system? Then reset
	if( planetDistance >= m_StartMaxPlanetRange + m_Planets[ m_CurrPlanet ].GetSize( ) )
	{
		// We are lost!
		ResetGame( );
		return 0;
	}

	// Update the overlay alpha which is depending on the planet distance
	const float distMaxSurface = m_StartMaxPlanetRange + m_Planets[ m_CurrPlanet ].GetSize( );
	const float distToSurface = planetDistance - m_Planets[ m_CurrPlanet ].GetSize( );
	const float minOffset = distToSurface / 2.0f;
	const float maxOffset = distToSurface;
	const float offsetDiff1 = minOffset / distToSurface;
	const float offsetDiff2 = 1.0f / offsetDiff1;
	m_OverlayAlpha = ((distToSurface / distMaxSurface ) * offsetDiff2 ) - offsetDiff1;
	m_OverlayAlpha = std::max( 0.0f, m_OverlayAlpha );

	// Is the current planet out of resources?
	if( m_Planets[ m_CurrPlanet ].GetResources( ) == 0 )
	{
		if( m_CurrPlanet < PLANET_COUNT - 1 )
		{
			m_CurrPlanet++;

			// Set the planet's start position to the pump's position
			m_Planets[ m_CurrPlanet ].SetPosition( pumpPosition );

		}
	}



	return 0;
}

void Game::Render( )
{
	// Clear the buffers
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );

	glPushMatrix( );

	// Set up the camera
	LDE::Vector2f cameraDiff = m_Player.GetPosition( ) - ( LDE::Vector2f( m_WindowSize ) / 2.0f );
	glTranslatef( -cameraDiff.x, -cameraDiff.y, 0.0f );
	
	// Render the player
	m_Player.Render( );

	// Render the hook
	m_Hook.Render( );

	// Render the planet
	m_Planets[ m_CurrPlanet ].Render( );

	// Render pumps
	for( unsigned int i = 0; i < m_PumpBullets.size( ); i++ )
	{
		m_PumpBullets[ i ]->Render( );
	}

	// Render lazer
	if( m_ActiveLazer )
	{
		// Render the lines
		glColor3f( m_Player.GetColor( ).r / 255.0f,
			m_Player.GetColor( ).g / 255.0f, m_Player.GetColor( ).b / 255.0f );

		glLineWidth( 4.0f );
		glBegin( GL_LINES );
			glVertex2f( m_LazerPoints[ 0 ].x, m_LazerPoints[ 0 ].y );
			glVertex2f( m_LazerPoints[ 1 ].x, m_LazerPoints[ 1 ].y );
		glEnd( );
	}

	glPopMatrix( );


	// Render overlay
	glEnable( GL_TEXTURE_2D );
	glColor4f( 1.0f, 1.0f, 1.0f, m_OverlayAlpha );
	m_OverlayTexture.Bind( );
	m_OverlayQuad.Render( );
	glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );

	// ///////////////////////////////////////////////////////////////////////////
	// Render stat boxes
	const float boxSize = 80.0f;
	
	glPushMatrix( );

	glDisable( GL_TEXTURE_2D );

	LDE::Vector2f statPos;
	statPos.x = ((boxSize * PLANET_COUNT ) - boxSize ) / 2.0f;
	statPos.y =  30.0f;
	glTranslatef( statPos.x, statPos.y, 0.0f );

	// Draw the background
	glPushMatrix( );
		for( unsigned int i = 0; i < PLANET_COUNT; i++ )
		{
			glColor3f( m_StartPlanetColors[ i ].r / 255.0f,
				m_StartPlanetColors[ i ].g / 255.0f, m_StartPlanetColors[ i ].b / 255.0f );

			glBegin( GL_QUADS );
				glVertex2f( 0.0f, 0.0f );
				glVertex2f( boxSize, 0.0f );
				glVertex2f( boxSize, boxSize );
				glVertex2f( 0.0f, boxSize );
			glEnd( );

			glTranslatef( boxSize * 2.0f, 0.0f, 0.0f );
		}
	glPopMatrix( );

	// Draw the fill
	const float edgeSize = 6.0f;

	glColor3f( 5.0f / 255.0f, 5.0f / 255.0f, 5.0f / 255.0f );

	for( unsigned int i = m_CurrPlanet; i < PLANET_COUNT; i++ )
	{
	
		glPushMatrix( );
		glTranslatef( i *boxSize * 2.0f, 0.0f, 0.0f );
		glBegin( GL_QUADS );
			glVertex2f( edgeSize, edgeSize );
			glVertex2f( boxSize - edgeSize, edgeSize );
			glVertex2f( boxSize - edgeSize, boxSize - edgeSize );
			glVertex2f( edgeSize, boxSize - edgeSize );
		glEnd( );

		glPopMatrix( );
	}

	// Draw percentage
	glPushMatrix( );
		glColor3f( m_StartPlanetColors[ m_CurrPlanet ].r / 255.0f,
				m_StartPlanetColors[ m_CurrPlanet ].g / 255.0f,
				m_StartPlanetColors[ m_CurrPlanet ].b / 255.0f );
		
		float percent = 1.0f - m_Planets[ m_CurrPlanet ].GetResources( );
		glTranslatef( (m_CurrPlanet ) *boxSize * 2.0f, 0.0f, 0.0f );
		glBegin( GL_QUADS );
			glVertex2f( edgeSize, edgeSize );
			glVertex2f( boxSize - edgeSize, edgeSize );
			glVertex2f( boxSize - edgeSize, edgeSize + ( boxSize - ( edgeSize* 2 ) ) * percent );
			glVertex2f( edgeSize, edgeSize + ( boxSize - ( edgeSize* 2 ) ) * percent );
		glEnd( );

		glPopMatrix( );

	glPopMatrix( );


	//m_Font.Render( "Hello World!", m_pSurface );

	// ///////////////////////////////////////////////////////
	// Render a navigation system
	/*static const LDE::Vector2f navSize( 160.0f, 60.0f );
	glLineWidth( 2.0f );
	glPointSize( 6.0f );
	glPushMatrix( );
	glTranslatef(  (navSize.x / 2.0f ) + 10.0f, (navSize.y / 2.0f ) + 10.0f, 0.0f );
	
	// Render the lines
	glColor3f( m_StartPlayerColor.r / 255.0f,
		m_StartPlayerColor.g / 255.0f, m_StartPlayerColor.b / 255.0f );
	
	glBegin( GL_LINES );
		glVertex2f( -navSize.x / 2.0f, 0.0f );
		glVertex2f( navSize.x / 2.0f, 0.0f );
		glVertex2f( 0.0f, -navSize.y / 2.0f );
		glVertex2f( 0.0f, navSize.y / 2.0f );
	glEnd( );

	// Render the indicator
	LDE::Vector2f diff = m_Player.GetPosition( ) - m_Planets[ m_CurrPlanet ].GetPosition( );
	diff /= LDE::Vector2f( m_StartMaxPlanetRange, m_StartMaxPlanetRange );
	diff *= navSize / 2.0f;
	
	// Render the navigation points
	glBegin( GL_POINTS );
		glVertex2f( diff.x, 0.0f );
		glVertex2f( 0.0f, diff.y );
	glEnd( );

	glPopMatrix( );*/


	// Swap all buffers
	SDL_GL_SwapBuffers( );
}

void Game::ResetGame( )
{
	SetPlanetValues( );
	ClearAllPumpBullets( );
	ClearKeyStates( );

	// Reset the player
	m_Player.SetPosition( m_StartPlayerPosition );
	m_Player.SetViewDirection( LDE::Vector2f( 0.0f, 1.0f ) );
	m_Player.SetDirection( LDE::Vector2f( 0.0f, 0.0f ) );
	m_Player.SetRotation( 0.0f );
	m_Player.SetColor( m_StartPlayerColor );
	m_ActiveLazer = false;
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
		if ( distance >= 1000.0f )
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
			int status = LDE::LineCircleIntersection(
				lastPos,
				(*it)->GetPosition( ),
				m_Planets[ m_CurrPlanet ].GetPosition( ),
				m_Planets[ m_CurrPlanet ].GetSize( ),
				In, Out);

			if( status == 1 )
			{
				// Add a pump to the planet
				// Calculate the angle of the position for the pump
				LDE::Vector2f pumpDirection = LDE::Vector2f( In - m_Planets[ m_CurrPlanet ].GetPosition( ) ).Normal( );
			
				// Calculate the angle
				float angle = LDE::AngleBetweenVectors2( LDE::Vector2f( 0.0f, 1.0f ), pumpDirection );
				if( pumpDirection.x < 0.0f )
				{
					angle = 360.f - angle;
				}

				// Add the pump to the planet
				// Fails if there's not enought space on the surface.
				m_Planets[ m_CurrPlanet ].SetPump( angle );

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
