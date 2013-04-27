#ifndef __GAME_PUMP_HPP__
#define __GAME_PUMP_HPP__

#include <SDL.h>
#include <SDL_opengl.h>
#include <Engine/RenderQuad.hpp>
#include <Engine/Texture.hpp>
#include <Engine/Vector2.hpp>
#include <Engine/Color.hpp>

class Pump
{

public:
	
	// Constructors
	Pump( );

	// General public functions
	void Update( double p_DeltaTime );
	void Render( );
	void SetPosition( LDE::Vector2f p_Position );

private:

	LDE::Vector2f m_Position;
	unsigned int m_Resources;
	bool m_Attached;

};

#endif