#include <Game/PumpBullet.hpp>

// Constructors
PumpBullet::PumpBullet( )
{
	m_LifeTimer.Start( );
}

// General public functions
void PumpBullet::Update( double p_DeltaTime )
{
	m_Position += m_Direction * m_Speed * p_DeltaTime;

}

void PumpBullet::Render( )
{
	glDisable( GL_TEXTURE_2D );

	glColor3f( (float)m_Color.r / 255.0f, (float)m_Color.g / 255.0f,
		(float)m_Color.b / 255.0f );

	glPointSize( 6.0f );
	glBegin( GL_POINTS );

	glVertex2f( m_Position.x, m_Position.y );

	glEnd( );

}

void PumpBullet::SetPosition( LDE::Vector2f p_Position )
{
	m_Position = p_Position;
}

void PumpBullet::SetDirection( LDE::Vector2f p_Direction )
{
	m_Direction = p_Direction;
}

void PumpBullet::SetColor( LDE::Color p_Color )
{
	m_Color = p_Color;
}

void PumpBullet::SetSpeed( float p_Speed )
{
	m_Speed = p_Speed;
}

// Get functions
float PumpBullet::GetLifeTime( )
{
	m_LifeTimer.Stop( );
	return m_LifeTimer.GetTime( );
}

LDE::Vector2f PumpBullet::GetPosition( ) const
{
	return m_Position;
}

LDE::Vector2f PumpBullet::GetDirection( ) const
{
	return m_Direction;
}

float PumpBullet::GetSpeed( ) const
{
	return m_Speed;
}