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
	Pump(  );

	// General public functions
	void Update( double p_DeltaTime );
	void Render( );
	void IncreaseResources( unsigned int p_Amount );
	void DecreaseResources( unsigned int p_Amount );
	void RestartTickTimer( );
	void CalculateSize( );

	// Set functions
	void SetTexture( LDE::Texture * p_pTexture );
	void SetPosition( LDE::Vector2f p_Position );
	void SetColor( LDE::Color p_Color );
	void SetResources( int m_Count );
	void SetMaxResources( int m_Count );
	void SetMaxSize( float p_Size );
	void SetTimeSpeed( float p_Speed );
	void SetActive( bool p_Status );

	// Get functions
	float GetTickTimer( );
	LDE::Vector2f GetPosition( ) const;
	float GetSize( ) const;
	int GetResources( ) const;
	float GetMaxSize( ) const;
	bool IsActive( ) const;

private:

	LDE::RenderQuad m_RenderQuad;
	LDE::Texture * m_pTexture;
	LDE::Timer m_Timer;
	LDE::Vector2f m_Position;
	float m_Size;
	float m_MaxSize;
	float m_TimeSpeed;
	LDE::Color m_Color;
	int m_Resources;
	int m_MaxResources;
	bool m_Active;

};

#endif