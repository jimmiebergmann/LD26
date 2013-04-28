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
	void SetDirection( LDE::Vector2f p_Direction );
	void SetColor( LDE::Color p_Color );
	void SetSpeed( float m_Speed );
	void SetResources( unsigned int m_Count );
	void SetAttached( bool p_Status );

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
	unsigned int m_Resources;
	bool m_Attached;

};

#endif