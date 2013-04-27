#ifndef __GAME_HOOK_HPP__
#define __GAME_HOOK_HPP__

#include <SDL.h>
#include <SDL_opengl.h>
#include <Engine/RenderQuad.hpp>
#include <Engine/Texture.hpp>
#include <Engine/Vector2.hpp>
#include <Engine/Color.hpp>
#include <Engine/Timer.hpp>

class Hook
{

public:

	// Constructors
	Hook( );

	// General public functions
	void Update( double p_DeltaTime );
	void Render( );
	void Fire( LDE::Vector2f p_Direction);

	// Set functions
	void SetPosition( LDE::Vector2f p_Position );
	void SetColor( LDE::Color p_Color );
	void SetHooked( bool p_Status );
	void SetLength( float p_Length );

	// Get functions
	LDE::Vector2f GetPosition( ) const;
	LDE::Color GetColor( ) const;
	bool GetHooked( ) const;

private:

	LDE::Vector2f m_Position;
	LDE::Vector2f m_HookPosition;
	LDE::Vector2f m_Direction;
	float m_Length;
	LDE::Timer m_Timer;

	LDE::Color m_Color;
	bool m_Fired;
	bool m_Hooked;


};

#endif