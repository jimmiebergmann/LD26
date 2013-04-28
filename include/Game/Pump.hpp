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
	void Render( );
	void CalculateSize( );

	// Set functions
	void SetTexture( LDE::Texture * p_pTexture );
	void SetPosition( LDE::Vector2f p_Position );
	void SetColor( LDE::Color p_Color );
	void SetResources( float p_Count );
	void SetMaxSize( float p_Size );
	void SetDrainSpeed( float p_Speed );
	void SetActive( bool p_Status );

	// Get functions
	float GetTickTimer( );
	LDE::Vector2f GetPosition( ) const;
	float GetSize( ) const;
	float GetResources( ) const;
	float GetMaxSize( ) const;
	float GetDrainSpeed( ) const;
	bool IsActive( ) const;

private:

	LDE::RenderQuad m_RenderQuad;
	LDE::Texture * m_pTexture;
	LDE::Timer m_Timer;
	LDE::Vector2f m_Position;
	float m_Size;
	float m_MaxSize;
	float m_DrainSpeed;
	LDE::Color m_Color;
	float m_Resources;
	bool m_Active;

};

#endif