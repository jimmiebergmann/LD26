#ifndef __GAME_PUMP_HPP__
#define __GAME_PUMP_HPP__

#include <SDL.h>
#include <SDL_opengl.h>
#include <Engine/Texture.hpp>
#include <Engine/RenderQuad.hpp>
#include <Engine/Vector2.hpp>
#include <Engine/Color.hpp>
#include <Engine/Timer.hpp>

class Pump
{

public:
	
	// Constructors
	Pump( LDE::Texture * p_pTexture );

	// General public functions
	void Update( double p_DeltaTime );
	void Render( );
	void IncreaseResources( unsigned int p_Amount );
	void DecreaseResources( unsigned int p_Amount );
	void RestartTickTimer( );

	// Set functions
	void SetPosition( LDE::Vector2f p_Position );
	void SetSize( float p_Size );
	void SetColor( LDE::Color p_Color );
	void SetResources( unsigned int m_Count );
	void SetMaxResources( unsigned int m_Count );
	void SetMaxSize( float p_Size );
	void SetTimeSpeed( float p_Speed );

	// Get functions
	float GetTickTimer( );
	LDE::Vector2f GetPosition( ) const;
	unsigned int GetResources( ) const;
	float GetMaxSize( ) const;

private:

	void CalculateRenderQuad( );

	LDE::RenderQuad m_RenderQuad;
	LDE::Texture * m_pTexture;
	LDE::Timer m_Timer;
	LDE::Vector2f m_Position;
	float m_Size;
	float m_MaxSize;
	float m_TimeSpeed;
	LDE::Color m_Color;
	unsigned int m_Resources;
	unsigned int m_MaxResources;

};

#endif