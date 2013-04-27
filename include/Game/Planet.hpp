#ifndef __GAME_PLANET_HPP__
#define __GAME_PLANET_HPP__

#include <SDL.h>
#include <SDL_opengl.h>
#include <Engine/RenderQuad.hpp>
#include <Engine/Texture.hpp>
#include <Engine/Vector2.hpp>
#include <Engine/Color.hpp>

class Planet
{

public:

	// Constructors / destructors
	Planet( );
	Planet( LDE::Vector2f p_Position, float p_Size, LDE::Texture * p_pTexture );
	~Planet( );
	
	// Public general functions
	bool Load( );
	void Update( double p_DeltaTime );
	void Render( );
	
	// Set functions
	void SetPosition( LDE::Vector2f p_Position );
	void SetSize( float p_Size );
	void SetRotation( float p_Rotation );
	void SetColor( LDE::Color p_Color );
	void SetResources( int p_Resources );
	void SetResourcesMax( int p_Resources );

	// Get functions
	LDE::Vector2f GetPosition( ) const;
	float GetSize( ) const;
	float GetRotation( ) const;
	int GetResources( ) const;
	int GetResourcesMax( ) const;

private:

	// Private functions
	void RenderFill( );
	void RenderFillPart( float startHeight, float stopHeight,
		float width, float rise );

	// Private variables
	LDE::RenderQuad m_RenderQuad;
	LDE::Texture * m_pTexture;
	LDE::Vector2f m_Position;
	LDE::Color m_Color;
	float m_Size;
	float m_Rotation;
	int m_Resources;
	int m_ResourcesMax;
	bool m_Loaded;

};

#endif