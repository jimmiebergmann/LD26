#include <Game/Pump.hpp>

// Constructors
Pump::Pump( ) :
	m_Resources( 0 ),
	m_Attached( false )
{
}

// General public functions
void Pump::Update( double p_DeltaTime )
{
}
void Pump::Render( )
{

}

void Pump::SetPosition( LDE::Vector2f p_Position )
{
	m_Position = p_Position;
}