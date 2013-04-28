#ifndef __GAME_GAME_HPP__
#define __GAME_GAME_HPP__

#include <SDL.h>
#include <SDL_opengl.h>
#include <Engine/RenderQuad.hpp>
#include <Engine/Texture.hpp>
#include <Engine/Vector2.hpp>
#include <Game/Player.hpp>
#include <Game/Hook.hpp>
#include <Game/Pump.hpp>
#include <Game/PumpBullet.hpp>
#include <Game/Planet.hpp>
#include <vector>

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
	void LoadStartValues( );
	void SetPlanetValues( );
	void Unload( );
	void PollEvents( );
	int Update( double p_DeltaTime );
	void Render( );
	void ResetGame( );

	// Input functions
	void ClearKeyStates( );
	void UpdatePreKeyEvents( );
	bool KeyIsDown( SDLKey p_Key );
	bool KeyIsUp( SDLKey p_Key );
	bool KeyIsJustPressed( SDLKey p_Key );
	bool KeyIsJustReleased( SDLKey p_Key );
	
	// Pump functions
	void UpdatePumpBullets( double p_DeltaTime );
	void ClearAllPumpBullets( );

	
	// Private variables
	SDL_Surface * pSurface;
	SDL_Surface * pScreen;
	LDE::Vector2i m_WindowSize;
	LDE::Texture m_PlanetTexture;
	LDE::Texture m_SpacecraftTexture;
	LDE::Texture m_OverlayTexture;
	LDE::RenderQuad m_OverlayQuad;
	float m_OverlayAlpha;
	Player m_Player;
	Hook m_Hook;
	std::vector<PumpBullet*> m_PumpBullets;
	unsigned int m_CurrPlanet;
	bool m_ActiveLazer;
	LDE::Vector2f m_LazerPoints[ 2 ];
	bool m_LazerHittingPump;
	bool m_Running;

	// Input
	bool m_CurrentKeyState[ SDLK_LAST ];
	bool m_LastKeyState[ SDLK_LAST ];

	// Planets
	static const unsigned int PLANET_COUNT = 3;
	Planet m_Planets[ PLANET_COUNT ];

	// Start game values
	LDE::Vector2f m_StartPlayerPosition;
	LDE::Vector2f m_StartPlayerDirection;
	LDE::Color m_StartPlayerColor;
	float m_StartPlayerRadius;
	float m_StartBulletSpeed;
	float m_StartPumpSpeed;
	float m_StartMaxPlanetRange;
	LDE::Vector2f m_StartPlanetPosition;
	LDE::Color m_StartPlanetColors[ PLANET_COUNT ];
	float m_StartPlanetSizes[ PLANET_COUNT ];
	float m_StartPlanetThicknesses[ PLANET_COUNT ];
	float m_StartPlanetRotationSpeed[ PLANET_COUNT ];
	float m_StartPlanetMaxResources[ PLANET_COUNT ];

};

#endif
