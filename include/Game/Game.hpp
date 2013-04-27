#ifndef __GAME_GAME_HPP__
#define __GAME_GAME_HPP__

#include <SDL.h>
#include <SDL_opengl.h>
#include <Engine/RenderQuad.hpp>
#include <Engine/Texture.hpp>
#include <Engine/Vector2.hpp>

//#include <SFML/Graphics.hpp>

/*
#include <Engine/Window.hpp>
#include <Engine/Sprite.hpp>*/
//#include <Engine/Sound.hpp>

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

	// Private variables
	SDL_Surface * pSurface;
	SDL_Surface * pScreen;
	LDE::RenderQuad m_RenderQuad;
	LDE::Texture m_Texture;
	bool m_Running;

};

#endif
