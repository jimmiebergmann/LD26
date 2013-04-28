#include <Game/Pump.hpp>

// Constructors
Pump::Pump( ) :
	m_pTexture( NULL ),
	m_Size( 1.0f ),
	m_MaxSize( 1.0f ),
	m_DrainSpeed( 1.0f ),
	m_Resources( 0.0f ),
	//m_MaxResources( 1 ),
	m_Active( false )
{
	m_RenderQuad.SetTexLowCoo( LDE::Vector2f( 0.0f, 0.0f ) );
	m_RenderQuad.SetTexHighCoo( LDE::Vector2f( 1.0f, 1.0f ) );
	m_RenderQuad.SetVertLowCoo( LDE::Vector2f( -m_Size, -m_Size ) );
	m_RenderQuad.SetVertHighCoo( LDE::Vector2f( m_Size, m_Size ) );
	
}

// General public functions

void Pump::Render( )
{
	if( m_pTexture == NULL || !m_Active )
	{
		return;
	}

	glEnable( GL_TEXTURE_2D );
	m_pTexture->Bind( );

	glColor3f( (float)m_Color.r / 255.0f, (float)m_Color.g / 255.0f,
		(float)m_Color.b / 255.0f );

	m_RenderQuad.Render( );

}

void Pump::CalculateSize( )
{
	m_Size = m_MaxSize * m_Resources; //( (float)m_Resources / (float)m_MaxResources );

	m_RenderQuad.SetVertLowCoo( LDE::Vector2f( -m_Size, -m_Size ) );
	m_RenderQuad.SetVertHighCoo( LDE::Vector2f( m_Size, m_Size ) );
}

void Pump::SetTexture( LDE::Texture * p_pTexture )
{
	m_pTexture = p_pTexture;
}

void Pump::SetPosition( LDE::Vector2f p_Position )
{
	m_Position = p_Position;
	m_RenderQuad.SetPosition( p_Position );
}

void Pump::SetColor( LDE::Color p_Color )
{
	m_Color = p_Color;
}

void Pump::SetResources( float p_Count )
{
	if( p_Count > 1.0f )
	{
		p_Count = 1.0f;
	}

	m_Resources = p_Count;
	CalculateSize( );
}
/*
void Pump::SetMaxResources( int m_Count )
{
	m_MaxResources = m_Count;
}*/

void Pump::SetMaxSize( float p_Size )
{
	m_MaxSize = p_Size;
}

void Pump::SetDrainSpeed( float p_Speed )
{
	m_DrainSpeed = p_Speed;
}

void Pump::SetActive( bool p_Status )
{
	m_Active = p_Status;
}

// Get functions
/*float Pump::GetTickTimer( )
{
	m_Timer.Stop( );
	return m_Timer.GetTime( ) * m_TimeSpeed;
}*/

LDE::Vector2f Pump::GetPosition( ) const
{
	return m_Position;
}

float Pump::GetSize( ) const
{
	return m_Size;
}

float Pump::GetResources( ) const
{
	return m_Resources;
}

float Pump::GetMaxSize( ) const
{
	return m_MaxSize;
}

float Pump::GetDrainSpeed( ) const
{
	return m_DrainSpeed;
}

bool Pump::IsActive( ) const
{
	return m_Active;
}