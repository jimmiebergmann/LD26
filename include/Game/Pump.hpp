#ifndef __GAME_PUMP_HPP__
#define __GAME_PUMP_HPP__

#include <SDL.h>
#include <SDL_opengl.h>
#include <Engine/RenderQuad.hpp>
#include <Engine/Vector2.hpp>
#include <Engine/Color.hpp>
#include <Engine/Timer.hpp>

class Pump
{

public:
	
	// Constructors
	Pump( );

	// General public functions
	void Update( double p_DeltaTime );
	void Render( );
	void IncreaseResources( unsigned int p_Amount );
	void DecreaseResources( unsigned int p_Amount );

	// Set functions
	void SetPosition( LDE::Vector2f p_Position );
	void SetColor( LDE::Color p_Color );
	void SetResources( unsigned int m_Count );;

	// Get functions
	float GetLifeTime( );
	LDE::Vector2f GetPosition( ) const;
	unsigned int GetResources( ) const;

private:

	LDE::Timer m_LifeTimer;
	LDE::Vector2f m_Position;
	LDE::Color m_Color;
	unsigned int m_Resources;
};

#endif