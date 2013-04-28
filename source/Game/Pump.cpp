#include <Game/Pump.hpp>

// Constructors
Pump::Pump( ) :
	m_pTexture( NULL ),
	m_Size( 1.0f ),
	m_MaxSize( 1.0f ),
	m_TimeSpeed( 1.0f ),
	m_Resources( 0 ),
	m_MaxResources( 1 ),
	m_Active( false )
{
	m_RenderQuad.SetTexLowCoo( LDE::Vector2f( 0.0f, 0.0f ) );
	m_RenderQuad.SetTexHighCoo( LDE::Vector2f( 1.0f, 1.0f ) );
	m_RenderQuad.SetVertLowCoo( LDE::Vector2f( -m_Size, -m_Size ) );
	m_RenderQuad.SetVertHighCoo( LDE::Vector2f( m_Size, m_Size ) );
	
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
	if( m_Resources > m_MaxResources)
	{
		m_Resources = m_MaxResources;
	}

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
/*
void SetActive( bool p_Status );
m_Timer.Start( );*/

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

void Pump::SetResources( int m_Count )
{
	m_Resources = m_Count;
}

void Pump::SetMaxResources( int m_Count )
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

void Pump::SetActive( bool p_Status )
{
	m_Active = p_Status;
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

int Pump::GetResources( ) const
{
	return m_Resources;
}

float Pump::GetMaxSize( ) const
{
	return m_MaxSize;
}

bool Pump::IsActive( ) const
{
	return m_Active;
}

void Pump::CalculateRenderQuad( )
{
	m_Size = m_MaxSize * ( (float)m_Resources / (float)m_MaxResources );

	m_RenderQuad.SetVertLowCoo( LDE::Vector2f( -m_Size, -m_Size ) );
	m_RenderQuad.SetVertHighCoo( LDE::Vector2f( m_Size, m_Size ) );
}

