#include <Game/Pump.hpp>

// Constructors
Pump::Pump( ) :
	m_Resources( 0 ),
	m_Attached( false )
{
	m_LifeTimer.Start( );
}

// General public functions
void Pump::Update( double p_DeltaTime )
{
	if( m_Attached )
	{

	}
	else
	{

	}
}

void Pump::Render( )
{

}

void Pump::IncreaseResources( unsigned int p_Amount )
{
	m_Resources += p_Amount;
}

void Pump::DecreaseResources( unsigned int p_Amount )
{
	if( ((int)(m_Resources) - (int)(p_Amount) ) < 0 )
	{
		m_Resources = 0;
	}
	else
	{
		m_Resources -= p_Amount;
	}
}

void Pump::SetPosition( LDE::Vector2f p_Position )
{
	m_Position = p_Position;
}

void Pump::SetDirection( LDE::Vector2f p_Direction )
{
	m_Direction = p_Direction;
}

void Pump::SetColor( LDE::Color p_Color )
{
}

void Pump::SetSpeed( float p_Speed )
{
	m_Speed = p_Speed;
}

void Pump::SetResources( unsigned int m_Count )
{
	m_Resources = m_Count;
}

void Pump::SetAttached( bool p_Status )
{
	m_Attached = p_Status;
}

// Get functions
float Pump::GetLifeTime( )
{
	m_LifeTimer.Stop( );
	return m_LifeTimer.GetTime( );
}

LDE::Vector2f Pump::GetPosition( ) const
{
	return m_Position;
}

LDE::Vector2f Pump::GetDirection( ) const
{
	return m_Direction;
}

float Pump::GetSpeed( ) const
{
	return m_Speed;
}

unsigned int Pump::GetResources( ) const
{
	return m_Resources;
}

bool Pump::GetAttached( ) const
{
	return m_Attached;
}
