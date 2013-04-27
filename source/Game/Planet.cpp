#include <Game/Planet.hpp>
#include <iostream>


// Constructors / destructors
Planet::Planet( ) :
	m_pTexture( NULL ),
	m_Loaded( false )
{
}

Planet::Planet( LDE::Vector2f p_Position, float p_Size, LDE::Texture * p_pTexture ) :
	m_Position( p_Position ),
	m_Size( p_Size ),
	m_pTexture( p_pTexture ),
	m_Rotation( 0.0f ),
	m_RotationSpeed( 0.0f ),
	m_ResourcesMax( 1 ),
	m_Resources( 1 ),
	m_Loaded( false )
{

}
Planet::~Planet( )
{
}

// Public general functions
bool Planet::Load( )
{
	if( m_Loaded )
	{
		std::cout << "[Planet::Load] Already loaded. " << std::endl;
		return false;
	}

	if( m_pTexture == NULL )
	{
		std::cout << "[Planet::Load] Texture NULL ptr. " << std::endl;
		return false;
	}



	// Load the render object
	m_RenderQuad.SetPosition( m_Position );
	m_RenderQuad.SetVertLowCoo( LDE::Vector2f( -m_Size, -m_Size ) );
	m_RenderQuad.SetVertHighCoo( LDE::Vector2f( m_Size, m_Size ) );
	m_RenderQuad.SetTexLowCoo( LDE::Vector2f( 0.0f, 0.0f ) );
	m_RenderQuad.SetTexHighCoo( LDE::Vector2f( 1.0f, 1.0f ) );


	m_Loaded = true;
	return true;
}

void Planet::Update( double p_DeltaTime )
{
	if( !m_Loaded )
	{
		return;
	}

	// Rotate the planet
	m_Rotation += m_RotationSpeed * p_DeltaTime;
	if( m_Rotation > 360.0f )
	{
		m_Rotation -= 360.0f;
	}
	
}

void Planet::Render( )
{
	if( !m_Loaded || m_pTexture == NULL )
	{
		return;
	}

	// Set up OGL for this
	glLineWidth( 2 );

	// Pull the matrix
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix( );

	// Rotate the planet around it's own center
	glTranslatef( m_Position.x, m_Position.y, 0.0f );
	glRotatef( m_Rotation, 0.0f, 0.0f, 1.0f );
	glTranslatef( -m_Position.x, -m_Position.y, 0.0f );

	// Render the planet
	glEnable( GL_TEXTURE_2D );
	m_pTexture->Bind( );

	glColor3f( (float)m_Color.r / 255.0f, (float)m_Color.g / 255.0f,
		(float)m_Color.b / 255.0f );
	m_RenderQuad.Render( );

	// fill it!
	glDisable( GL_TEXTURE_2D );
	RenderFill( );


	// Pull the matrix
	glPopMatrix( );
}

// Set functions
void Planet::SetPosition( LDE::Vector2f p_Position )
{
	m_Position = p_Position;
	m_RenderQuad.SetPosition( m_Position );
}

void Planet::SetSize( float p_Size )
{
	m_Size = p_Size;
	m_RenderQuad.SetVertLowCoo( LDE::Vector2f( -m_Size, -m_Size ) );
	m_RenderQuad.SetVertHighCoo( LDE::Vector2f( m_Size, m_Size ) );
}

void Planet::SetRotation( float p_Rotation )
{
	m_Rotation = p_Rotation;
	//m_RenderQuad.SetRotation( m_Position );
}

void Planet::SetRotationSpeed( float p_Speed )
{
	m_RotationSpeed = p_Speed;
}

void Planet::SetColor( LDE::Color p_Color )
{
	m_Color = p_Color;
}

void Planet::SetResources( int p_Resources )
{
	m_Resources = p_Resources;
}

void Planet::SetResourcesMax( int p_Resources )
{
	m_ResourcesMax = p_Resources;
}

// Get functions
LDE::Vector2f Planet::GetPosition( ) const
{
	return m_Position;
}

float Planet::GetSize( ) const
{
	return m_Size;
}

float Planet::GetRotation( ) const
{
	return m_Rotation;
}

float Planet::GetRotationSpeed( ) const
{
	return m_RotationSpeed;
}

LDE::Color Planet::GetColor( ) const
{
	return m_Color;
}


int Planet::GetResources( ) const
{
	return m_Resources;
}

int Planet::GetResourcesMax( ) const
{
	return m_ResourcesMax;
}

// Private functions
void Planet::RenderFill( )
{
	const LDE::Vector2f planetLowerCorner = LDE::Vector2f( -m_Size, -m_Size );
	const LDE::Vector2f planetUpperCorner = LDE::Vector2f( m_Size, m_Size );

	// Calculate how much we should fill
	float percent = (float)( m_Resources ) / (float)( m_ResourcesMax );

	
	const unsigned int pieces = 7;
	float fl[ pieces + 1 ] =
	{
		0.0f, 0.07f, 0.16f, 0.24f, 0.64f, 0.72f, 0.81f, 0.88f
	};
	float widths[ pieces ] =
	{
		0.29f, 0.18f, 0.11f, 0.06f, 0.11f, 0.18f, 0.29f
	};

	// We need to use this as the percentage since we are not covering the entire planet.
	float sumFill = fl[ pieces ];
	float fillPercent = sumFill * percent;

	for( unsigned int i = 0; i < pieces; i++ )
	{
		if( fillPercent > fl[ i + 1 ] )
		{
			RenderFillPart( fl[ i ], fl[ i+1 ], widths[ i ], 0.06f );
		}
		else
		{
			// We are not filling the entire quad, but partly
			// Calculate the percentage of this part.
			float height = fillPercent - fl[ i ];
			float heightPart = fl[ i + 1 ] - fl[ i ];
			float diff = height / heightPart;

			// Render the last part
			RenderFillPart(
				fl[ i ],
				fl[ i ] + (heightPart * diff),
				widths[ i ],
				0.06f );

			// Render a smooth line at the corner to make it smooth
			float Size = m_Size * 2.0f;
			LDE::Vector2f Pos = m_Position - LDE::Vector2f( m_Size, m_Size );
			float y =  ( Size * (fl[ i ] + (heightPart * diff) ) ) + ( Size * 0.06f );
			float x1 = Pos.x + ( Size * widths[ i ] );
			float x2 = Pos.x + ( Size * ( 1.0f - widths[ i ] ) );
			
			// Render the line
			glColor3f( GetColor( ).r / 255.0f, GetColor( ).g / 255.0f, GetColor( ).b / 255.0f );
			glBegin( GL_LINES );
				glVertex2f( x1, Pos.y + y );
				glVertex2f( x2, Pos.y + y );
			glEnd( );

			// Break since we are done.
			break;
		}
	}
}

/*

	loat Size = m_Size * 2.0f;
	Pos.y + ( Size * stopHeight ) + ( Size * rise )

*/

void Planet::RenderFillPart( float startHeight, float stopHeight,
							float width, float rise )
{

	glBegin( GL_QUADS );

	LDE::Vector2f Pos = m_Position - LDE::Vector2f( m_Size, m_Size );
	float Size = m_Size * 2.0f;

	// Quad 1
	const float w1 = width;
	const float w2 = 1.0f - w1;
	const float h1 = startHeight;
	const float h2 = stopHeight;
	glVertex2f( Pos.x + ( Size * w1) ,			Pos.y + ( Size * h1 ) + ( Size * rise ) );
	glVertex2f( Pos.x + ( Size * w2) ,			Pos.y + ( Size * h1 ) + ( Size * rise ) );
	glVertex2f( Pos.x + ( Size * w2),			Pos.y + ( Size * h2 ) + ( Size * rise ) );
	glVertex2f( Pos.x + ( Size * w1),			Pos.y + ( Size * h2 ) + ( Size * rise ) );

	glEnd( );


}
