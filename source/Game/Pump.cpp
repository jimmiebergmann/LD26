#include <Game/Pump.hpp>

// Constructors
Pump::Pump( LDE::Texture * p_pTexture ) :
	m_pTexture( p_pTexture ),
	m_Size( 1.0f ),
	m_MaxSize( 1.0f ),
	m_TimeSpeed( 1.0f ),
	m_Resources( 0 ),
	m_MaxResources( 1 )
{
	m_RenderQuad.SetTexLowCoo( LDE::Vector2f( 0.0f, 0.0f ) );
	m_RenderQuad.SetTexHighCoo( LDE::Vector2f( 1.0f, 1.0f ) );
	m_RenderQuad.SetVertLowCoo( LDE::Vector2f( 0.0f, 0.0f ) );
	m_RenderQuad.SetVertHighCoo( LDE::Vector2f( 100.0f, 100.0f ) );
	m_Timer.Start( );
}

// General public functions

void Pump::Update( double p_DeltaTime )
{

}

void Pump::Render( )
{
	if( m_pTexture == NULL )
	{
		return;
	}

	glEnable( GL_TEXTURE_2D );
	m_pTexture->Bind( );

	glColor3f( (float)m_Color.r / 255.0f, (float)m_Color.g / 255.0f,
		(float)m_Color.b / 255.0f );

	m_RenderQuad.Render( );

}

void Pump::IncreaseResources( unsigned int p_Amount )
{
	m_Resources += p_Amount;
	CalculateRenderQuad( );
}

void Pump::DecreaseResources( unsigned int p_Amount )
{
	// NEED THIS AT ALL?
	/*if( ((int)(m_Resources) - (int)(p_Amount) ) < 0 )
	{
		m_Resources = 0;
	}
	else
	{
		m_Resources -= p_Amount;
	}
	CalculateRenderQuad( );*/
}

void Pump::RestartTickTimer( )
{
	m_Timer.Start( );
}

void Pump::SetPosition( LDE::Vector2f p_Position )
{
	m_Position = p_Position;
	m_RenderQuad.SetPosition( p_Position );
}

void Pump::SetSize( float p_Size )
{
	m_Size = p_Size;
}

void Pump::SetColor( LDE::Color p_Color )
{
	m_Color = p_Color;
}

void Pump::SetResources( unsigned int m_Count )
{
	m_Resources = m_Count;
}

void Pump::SetMaxResources( unsigned int m_Count )
{
	m_MaxResources = m_Count;
}

void Pump::SetMaxSize( float p_Size )
{
	m_MaxSize = p_Size;
}

void Pump::SetTimeSpeed( float p_Speed )
{
	m_TimeSpeed = p_Speed;
}

// Get functions
float Pump::GetTickTimer( )
{
	m_Timer.Stop( );
	return m_Timer.GetTime( ) * m_TimeSpeed;
}

LDE::Vector2f Pump::GetPosition( ) const
{
	return m_Position;
}

unsigned int Pump::GetResources( ) const
{
	return m_Resources;
}

float Pump::GetMaxSize( ) const
{
	return m_MaxSize;
}

void Pump::CalculateRenderQuad( )
{
}

