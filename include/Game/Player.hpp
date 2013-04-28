#ifndef __GAME_PLAYER_HPP__
#define __GAME_PLAYER_HPP__

#include <SDL.h>
#include <SDL_opengl.h>
#include <Engine/RenderQuad.hpp>
#include <Engine/Texture.hpp>
#include <Engine/Vector2.hpp>
#include <Engine/Color.hpp>

class Player
{

public:

	// Constructors / destructors
	Player( );
	Player( LDE::Texture * m_pTexture );
	~Player( );
	
	// Public general functions
	bool Load( );
	void Update( double p_DeltaTime );
	void Render( );
	void BurstLeft( );
	void BurstRight( );
	void BurstForwards( );
	void BurstBackwards( );
	
	// Set functions
	void SetPosition( LDE::Vector2f p_Position );
	void SetViewDirection( LDE::Vector2f p_Direction );
	void SetDirection( LDE::Vector2f p_Direction );
	void SetRotationSpeed( float p_Speed );
	void SetRotation( float p_Rotation );
	void SetMaxSpeed( float p_Speed );
	void SetColor( LDE::Color p_Color );

	// Get functions
	LDE::Vector2f GetPosition( ) const;
	LDE::Vector2f GetSize( ) const;
	LDE::Vector2f GetDirection( ) const;
	LDE::Vector2f GetViewDirection( ) const;
	float GetRotation( ) const;
	float GetRotationSpeed( ) const;
	float GetSpeed( ) const;
	float GetMaxSpeed( ) const;
	LDE::Color GetColor( ) const;

private:

	// Private functions

	// Private variables
	LDE::RenderQuad m_RenderQuad;
	LDE::Texture * m_pTexture;
	LDE::Vector2f m_Position;
	LDE::Vector2f m_Size;
	LDE::Vector2f m_Direction;
	LDE::Vector2f m_ViewDirection;
	float m_Rotation;	// Same as direction but as an angle.
	float m_RotationSpeed;
	float m_Speed;
	float m_MaxRotationSpeed;
	float m_MaxSpeed;
	LDE::Color m_Color;
	int m_BurstingState;
	int m_RotatingState;

	bool m_Loaded;

};

#endif