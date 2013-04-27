#include <Engine/RenderQuad.hpp>

namespace LDE
{


	// Constructors
	RenderQuad::RenderQuad(  ) :
		m_VertLowCoo( 0.0f, 0.0f ),
		m_VertHighCoo( 0.0f, 0.0f )
	{
	}

	RenderQuad::RenderQuad( LDE::Vector2f p_Position,
		LDE::Vector2f p_VertLowCoo, LDE::Vector2f p_VertHighCoo ) :
		
	m_Position( p_Position ),
		m_VertLowCoo( p_VertLowCoo ),
		m_VertHighCoo( p_VertHighCoo )
	{
	}

	RenderQuad::RenderQuad( LDE::Vector2f p_Position,
		LDE::Vector2f p_VertLowCoo, LDE::Vector2f p_VertHighCoo,
		LDE::Vector2f p_TexLowCoo, LDE::Vector2f p_TexHighCoo) :
		
		m_Position( p_Position ),
		m_VertLowCoo( p_VertLowCoo ),
		m_VertHighCoo( p_VertHighCoo ),
		m_TexLowCoo( p_TexLowCoo ),
		m_TexHighCoo( p_TexHighCoo )
	{
	}

	
	// General functions
	void RenderQuad::Render( )
	{
		glBegin( GL_QUADS );

		glTexCoord2f( m_TexLowCoo.x, m_TexLowCoo.y );
		glVertex2f( m_VertLowCoo.x, m_VertLowCoo.y );

		glTexCoord2f( m_TexHighCoo.x, m_TexLowCoo.y );
		glVertex2f( m_VertHighCoo.x, m_VertLowCoo.y );

		glTexCoord2f( m_TexHighCoo.x, m_TexHighCoo.y );
		glVertex2f( m_VertHighCoo.x, m_VertHighCoo.y );

		glTexCoord2f( m_TexLowCoo.x, m_TexHighCoo.y );
		glVertex2f( m_VertLowCoo.x, m_VertHighCoo.y );

		glEnd( );
	}

	void RenderQuad::EnableTexture( )
	{
		glEnable( GL_TEXTURE_2D );
	}

	void RenderQuad::DisableTexture( )
	{
		glDisable( GL_TEXTURE_2D );
	}


	// Get functions
	LDE::Vector2f RenderQuad::GetPosition( ) const
	{
		return m_Position;
	}

	LDE::Vector2f RenderQuad::GetSize( ) const
	{
		return m_VertHighCoo - m_VertLowCoo;
	}

	LDE::Vector2f RenderQuad::GetVertLowCoo( ) const
	{
		return m_VertLowCoo;
	}

	LDE::Vector2f RenderQuad::GetVertHighCoo( ) const
	{
		return m_VertHighCoo;
	}

	LDE::Vector2f RenderQuad::GetTexLowCoo( ) const
	{
		return m_TexLowCoo;
	}

	LDE::Vector2f RenderQuad::GetTexHighCoo( ) const
	{
		return m_TexHighCoo;
	}

	LDE::Vector2f RenderQuad::GetScale( ) const
	{
		return m_Scale;
	}

	float RenderQuad::GetRotation( ) const
	{
		return m_Rotation;
	}

	// Set functions
	void RenderQuad::SetPosition( LDE::Vector2f p_Position )
	{
		m_Position = p_Position;
	}

	void RenderQuad::SetVertLowCoo( LDE::Vector2f p_VertLowCoo )
	{
		m_VertLowCoo = p_VertLowCoo;
	}

	void RenderQuad::SetVertHighCoo( LDE::Vector2f p_VertHighCoo )
	{
		m_VertHighCoo = p_VertHighCoo;
	}

	void RenderQuad::SetTexLowCoo( LDE::Vector2f p_TexLowCoo )
	{
		m_TexLowCoo = p_TexLowCoo;
	}

	void RenderQuad::SetTexHighCoo( LDE::Vector2f p_TexHighCoo )
	{
		m_TexHighCoo = p_TexHighCoo;
	}

	void RenderQuad::SetScale( LDE::Vector2f p_Scale )
	{
		m_Scale = p_Scale;
	}

	void RenderQuad::SetRotation( float p_Rotation )
	{
		m_Rotation = p_Rotation;
	}


}