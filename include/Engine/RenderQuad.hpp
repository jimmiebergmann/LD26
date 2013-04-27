#ifndef __LDE_RENDERQUAD_HPP__
#define __LDE_RENDERQUAD_HPP__

#include <SDL_opengl.h>
#include <Engine/Vector2.hpp>

namespace LDE
{

	class RenderQuad
	{

	public:

		// Constructors
		RenderQuad(  );
		RenderQuad( LDE::Vector2f p_Position,
			LDE::Vector2f p_VertLowCoo, LDE::Vector2f p_VertHighCoo );
		RenderQuad( LDE::Vector2f p_Position,
			LDE::Vector2f p_VertLowCoo, LDE::Vector2f p_VertHighCoo,
			LDE::Vector2f p_TexLowCoo, LDE::Vector2f p_TexHighCoo);
		
		// General functions
		void Render( );
		void EnableTexture( );
		void DisableTexture( );

		// Get functions
		LDE::Vector2f GetPosition( ) const;
		LDE::Vector2f GetSize( ) const;
		LDE::Vector2f GetVertLowCoo( ) const;
		LDE::Vector2f GetVertHighCoo( ) const;
		LDE::Vector2f GetTexLowCoo( ) const;
		LDE::Vector2f GetTexHighCoo( ) const;
		LDE::Vector2f GetScale( ) const;
		float GetRotation( ) const;

		// Set functions
		void SetPosition( LDE::Vector2f p_Position );
		void SetVertLowCoo( LDE::Vector2f p_VertLowCoo );
		void SetVertHighCoo( LDE::Vector2f p_VertHighCoo );
		void SetTexLowCoo( LDE::Vector2f p_TexLowCoo );
		void SetTexHighCoo( LDE::Vector2f p_TexHighCoo );
		void SetScale( LDE::Vector2f p_Scale );
		void SetRotation( float p_Rotation );

	private:

		LDE::Vector2f m_Position;
		LDE::Vector2f m_VertLowCoo;
		LDE::Vector2f m_VertHighCoo;
		LDE::Vector2f m_TexLowCoo;
		LDE::Vector2f m_TexHighCoo;
		LDE::Vector2f p_HighCoo;
		LDE::Vector2f m_Scale;
		float m_Rotation;

	};

}

#endif