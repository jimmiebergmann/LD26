#ifndef __GAME_PLANET_HPP__
#define __GAME_PLANET_HPP__

#include <SDL.h>
#include <SDL_opengl.h>
#include <Engine/RenderQuad.hpp>
#include <Engine/Texture.hpp>
#include <Engine/Vector2.hpp>
#include <Engine/Color.hpp>
#include <Game/Pump.hpp>
#include <vector>

class Planet
{

public:

	// Constructors / destructors
	Planet( );
	Planet( LDE::Vector2f p_Position, float p_Size,
		float p_Thickness, LDE::Texture * p_pTexture );
	~Planet( );
	
	// Public general functions
	bool Load( );
	void Update( double p_DeltaTime );
	void Render( );
	bool AddNewPump( float p_Angle );
	
	// Set functions
	void SetPosition( LDE::Vector2f p_Position );
	void SetSize( float p_Size );
	void SetThickness( float p_Thickness );
	void SetRotation( float p_Rotation );
	void SetRotationSpeed( float p_Speed );
	void SetColor( LDE::Color p_Color );
	void SetResources( int p_Resources );
	void SetResourcesMax( int p_Resources );

	// Get functions
	LDE::Vector2f GetPosition( ) const;
	float GetSize( ) const;
	float GetRotation( ) const;
	float GetRotationSpeed( ) const;
	LDE::Color GetColor( ) const;
	int GetResources( ) const;
	int GetResourcesMax( ) const;

private:

	// Private functions
	void RenderFill( );
	void RenderFillPart( float startHeight, float stopHeight,
		float width, float rise );
	void UpdateAllPumps( );
	void RenderPumps( );
	void ClearAllPumps( );

	// Private variables
	LDE::RenderQuad m_RenderQuad1;
	LDE::RenderQuad m_RenderQuad2;
	LDE::Texture * m_pTexture;
	LDE::Vector2f m_Position;
	float m_Thickness;
	LDE::Color m_Color;
	float m_Size;
	float m_Rotation;
	float m_RotationSpeed;
	int m_Resources;
	int m_ResourcesMax;
	bool m_Loaded;

	// Pump varaibles
	std::vector< Pump* > m_Pumps;

};

#endif