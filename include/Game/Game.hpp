#ifndef __GAME_GAME_HPP__
#define __GAME_GAME_HPP__

#include <Engine/Window.hpp>
#include <Engine/Sprite.hpp>

class Game
{

public:

	// Constructors / destructors
	Game( );
	~Game( );

	// Public general functions
	int Run( int p_Argc, char ** p_Argv );

private:

	// Private functions
	bool Load( );
	void Unload( );
	int Update( double p_DeltaTime );
	void Render( );

	// Private variables
	LDE::Window m_Window;
	LDE::Image m_Image;
	LDE::Sprite m_Sprite;

};

#endif
