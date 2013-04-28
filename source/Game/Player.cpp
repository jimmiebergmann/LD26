#include <Game/Player.hpp>
#include <Engine/Utility.hpp>
#include <iostream>

// Constructors / destructors
Player::Player( ) :
	m_pTexture( NULL ),
	m_ViewDirection( 0.0f, 1.0f ),
	m_Rotation( 0.0f ),
	m_RotationSpeed( 0.0f ),
	m_Speed( 0.0f ),
	m_MaxRotationSpeed( 0.0f ),
	m_MaxSpeed( 0.0f ),
	m_BurstingState( 0 ),
	m_RotatingState( 0 ),
	m_Loaded( false )
{
}

Player::Player( LDE::Texture * m_pTexture ) :
	m_pTexture( m_pTexture ),
	m_ViewDirection( 0.0f, 1.0f ),
	m_Rotation( 0.0f ),
	m_RotationSpeed( 0.0f ),
	m_Speed( 0.0f ),
	m_MaxRotationSpeed( 0.0f ),
	m_MaxSpeed( 0.0f ),
	m_BurstingState( 0 ),
	m_RotatingState( 0 ),
	m_Loaded( false )
{
}

Player::~Player( )
{
}


// Public general functions
bool Player::Load( )
{
	if( m_Loaded )
	{
		std::cout << "[Player::Load( )] Already loaded." << std::endl;
		return false;
	}

	m_Size = LDE::Vector2f( 27.0f, 40.0f );

	m_RenderQuad.SetVertLowCoo( LDE::Vector2f( -m_Size.x / 2.0f, -m_Size.x / 2.0f) );
	m_RenderQuad.SetVertHighCoo( LDE::Vector2f( m_Size.x / 2.0f, m_Size.y / 2.0f ) );
	m_RenderQuad.SetTexLowCoo( LDE::Vector2f( 0.0f, 0.0f ) );
	m_RenderQuad.SetTexHighCoo( LDE::Vector2f( 1.0f, 1.0f ) );


	m_Loaded = true;
	return true;
}

void Player::Update( double p_DeltaTime )
{
	if( !m_Loaded )
	{
		std::cout << "[Player::Update( )] Not loaded" << std::endl;
		return;
	}

	static const float acceleration = 400.0f;

	// Update rotating / moving
	if( m_RotatingState != 0 )
	{
		m_Rotation -= m_RotationSpeed * ( p_DeltaTime * (double)(m_RotatingState));

		if( m_Rotation > 360.0f )
		{
			m_Rotation -= 360.0f;
		}

		if( m_Rotation < 0.0f )
		{
			m_Rotation += 360.0f;
		}

		// Calculate the view direction
		m_ViewDirection = LDE::RotateVector2f( LDE::Vector2f( 0.0f, 1.0f ), m_Rotation );

	}
	if( m_BurstingState != 0 )
	{
		m_Direction += m_ViewDirection * acceleration * (float)( m_BurstingState ) * p_DeltaTime;
		m_Speed = m_Direction.Magnitude( );

		if( m_Speed > m_MaxSpeed )
		{
			m_Direction = m_Direction.Normal( ) * m_MaxSpeed;
		}

	}

	// Now move the player
	m_Position += m_Direction * p_DeltaTime;
	m_RenderQuad.SetPosition( m_Position );

	// Reset the busting/rotating states
	m_BurstingState = 0;
	m_RotatingState = 0;

}

void Player::Render( )
{
	if( !m_Loaded || m_pTexture == NULL )
	{
		std::cout << "[Player::Render( )] " << m_Loaded << "   " << m_pTexture << std::endl;
		return;
	}
	
	glPushMatrix( );
	// Rotate the player around it's own center
	glTranslatef( m_Position.x, m_Position.y, 0.0f );
	glRotatef( m_Rotation, 0.0f, 0.0f, 1.0f );
	glTranslatef( -m_Position.x, -m_Position.y, 0.0f );



	// Render the player
	glEnable( GL_TEXTURE_2D );
	m_pTexture->Bind( );

	glColor3f( (float)m_Color.r / 255.0f, (float)m_Color.g / 255.0f,
		(float)m_Color.b / 255.0f );
	m_RenderQuad.Render( );

	glPopMatrix( );

}

void Player::BurstLeft( )
{
	m_RotatingState = -1;
}

void Player::BurstRight( )
{
	m_RotatingState = 1;
}

void Player::BurstForwards( )
{
	m_BurstingState = 1;
}

void Player::BurstBackwards( )
{
	m_BurstingState = -1;
}


// Set functions
void Player::SetPosition( LDE::Vector2f p_Position )
{
	m_Position = p_Position;
	m_RenderQuad.SetPosition( p_Position );
}

void Player::SetViewDirection( LDE::Vector2f p_Direction )
{
	m_ViewDirection = p_Direction;
}

void Player::SetDirection( LDE::Vector2f p_Direction )
{
	m_Direction = p_Direction;
}

void Player::SetRotationSpeed( float p_Speed )
{
	m_RotationSpeed = p_Speed;
}

void Player::SetRotation( float p_Rotation )
{
	m_Rotation = p_Rotation;
}

void Player::SetMaxSpeed( float p_Speed )
{
	m_MaxSpeed = p_Speed;
}

void Player::SetColor( LDE::Color p_Color )
{
	m_Color = p_Color;
}

// Get functions
LDE::Vector2f Player::GetPosition( ) const
{
	return m_Position;
}

LDE::Vector2f Player::GetSize( ) const
{
	return m_Size;
}

LDE::Vector2f Player::GetDirection( ) const
{
	return m_Direction;
}

LDE::Vector2f Player::GetViewDirection( ) const
{
	return m_ViewDirection;
}

float Player::GetRotation( ) const
{
	return m_Rotation;
}

float Player::GetRotationSpeed( ) const
{
	return m_RotationSpeed;
}

float Player::GetSpeed( ) const
{
	return m_Speed;
}

float Player::GetMaxSpeed( ) const
{
	return m_MaxSpeed;
}

LDE::Color Player::GetColor( ) const
{
	return m_Color;
}