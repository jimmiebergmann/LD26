#ifndef __GAME_PUMPBULLET_HPP__
#define __GAME_PUMPBULLET_HPP__

#include <SDL.h>
#include <SDL_opengl.h>
#include <Engine/RenderQuad.hpp>
#include <Engine/Vector2.hpp>
#include <Engine/Color.hpp>
#include <Engine/Timer.hpp>

class PumpBullet
{

public:
	
	// Constructors
	PumpBullet( );

	// General public functions
	void Update( double p_DeltaTime );
	void Render( );

	// Set functions
	void SetPosition( LDE::Vector2f p_Position );
	void SetDirection( LDE::Vector2f p_Direction );
	void SetColor( LDE::Color p_Color );
	void SetSpeed( float p_Speed );

	// Get functions
	float GetLifeTime( );
	LDE::Vector2f GetPosition( ) const;
	LDE::Vector2f GetDirection( ) const;
	float GetSpeed( ) const;
	unsigned int GetResources( ) const;
	bool GetAttached( ) const;

private:

	LDE::Timer m_LifeTimer;
	LDE::Vector2f m_Position;
	LDE::Vector2f m_Direction;
	LDE::Color m_Color;
	float m_Speed;

};

#endif