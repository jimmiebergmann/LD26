#ifndef __GAME_GAME_HPP__
#define __GAME_GAME_HPP__

#include <SDL.h>
#include <SDL_opengl.h>
#include <Engine/RenderQuad.hpp>
#include <Engine/Texture.hpp>
#include <Engine/Vector2.hpp>
#include <Game/Planet.hpp>

class Game
{

public:

	// Constructors / destructors
	Game( );
	~Game( );

	// Public general functions
	int Run( int p_Argc, char ** p_Argv );

private:

	// Private functions
	bool Load( );
	void Unload( );
	void PollEvents( );
	int Update( double p_DeltaTime );
	void Render( );

	// Input functions
	void ClearKeyStates( );
	void UpdatePreKeyEvents( );
	bool KeyIsDown( SDLKey p_Key );
	bool KeyIsUp( SDLKey p_Key );
	bool KeyIsJustPressed( SDLKey p_Key );
	bool KeyIsJustReleased( SDLKey p_Key );

	// Private variables
	SDL_Surface * pSurface;
	SDL_Surface * pScreen;
	LDE::Vector2i m_WindowSize;
	LDE::Texture m_PlanetTexture;
	Planet * m_pPlanet;
	bool m_Running;

	// Input
	bool m_CurrentKeyState[ SDLK_LAST ];
	bool m_LastKeyState[ SDLK_LAST ];

};

#endif
