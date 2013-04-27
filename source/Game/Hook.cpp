#include <Game/Hook.hpp>

// Constructors
Hook::Hook( ) :
	m_Length( 1.0f ),
	m_Fired( false ),
	m_Hooked( false )

{
}

// General public functions
void Hook::Update( double p_DeltaTime )
{
	if( !m_Fired )
	{
		return;
	}

	// Check if we should disable the hook
	m_Timer.Stop( );
	double hookTime = m_Timer.GetTime( );
	if( hookTime >= 1.0f )
	{
		m_Fired = false;
		return;
	}


	m_Direction -= ( LDE::Vector2f(m_HookPosition - m_Position).Normal( ) ) * p_DeltaTime * ( m_Length * 2.0f );
	m_HookPosition += m_Direction * p_DeltaTime;
	
}
void Hook::Render( )
{
	if( m_Fired )
	{
		glDisable( GL_TEXTURE_2D );

		glBegin( GL_LINES );

		glColor3f( (float)m_Color.r / 255.0f, (float)m_Color.g / 255.0f,
			(float)m_Color.b / 255.0f );

		glVertex2f( m_Position.x, m_Position.y );
		glVertex2f( m_HookPosition.x, m_HookPosition.y );
		
		glEnd( );
	}
}

void Hook::Fire( LDE::Vector2f p_Direction )
{
	if( m_Fired )
	{
		return;
	}

	m_Direction = p_Direction.Normal( ) * ( m_Length * 2.0f );
	m_HookPosition = m_Position;
	m_Fired = true;
	m_Timer.Start( );
}

// Set functions
void Hook::SetPosition( LDE::Vector2f p_Position )
{
	m_Position = p_Position;
}
void Hook::SetColor( LDE::Color p_Color )
{
	m_Color = p_Color;
}
void Hook::SetHooked( bool p_Status )
{
	m_Hooked = p_Status;
}

void Hook::SetLength( float p_Length )
{
	m_Length = p_Length;
}
// Get functions
LDE::Vector2f Hook::GetPosition( ) const
{
	return m_Position;
}

LDE::Color Hook::GetColor( ) const
{
	return m_Color;
}

bool Hook::GetHooked( ) const
{
	return m_Hooked;
}