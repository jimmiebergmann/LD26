//#include <SFML/Graphics.hpp>


#include <Game/Game.hpp>

int main( int argc, char *argv[] )
{
	Game game;
	return game.Run( argc, argv );
/*
	// Surfaces
	SDL_Surface * pSurface = NULL;
	SDL_Surface * pScreen = NULL;


	// Iniitilaize SDL
	SDL_Init( SDL_INIT_EVERYTHING );

	// Set up the sreen
	pScreen = SDL_SetVideoMode( 800, 600, 32, SDL_SWSURFACE );

	// Load the image
	pSurface = SDL_LoadBMP( "Data/Textures/Test.bmp" );

	// Blit the surface to the frame buffer
	SDL_BlitSurface( pSurface, NULL, pScreen, NULL );

	// Swap buffers
	SDL_Flip( pScreen );

	// Delay some time
	SDL_Delay( 3000 );


	// Unload everything
	SDL_FreeSurface( pSurface );

	// Quit SDL
	SDL_Quit( );


	return 0;*/
}





/*#include <Game/Game.hpp>
#include <iostream>


int main( int argc, char ** argv )
{
	Game game;
	return game.Run( argc, argv );

}
*/

/*
 #include <SFML/Audio.hpp>
 #include <SFML/Graphics.hpp>
 
 int main()
 {
     // Create the main window
     sf::RenderWindow App(sf::VideoMode(800, 600), "SFML window");
 
     // Load a sprite to display
     sf::Image Image;
     if (!Image.LoadFromFile("cute_image.jpg"))
         return EXIT_FAILURE;
     sf::Sprite Sprite(Image);
 
 
     // Start the game loop
     while (App.IsOpened())
     {
         // Process events
         sf::Event Event;
         while (App.GetEvent(Event))
         {
             // Close window : exit
             if (Event.Type == sf::Event::Closed)
                 App.Close();
         }
 
         // Clear screen
         App.Clear();
 
         // Draw the sprite
         App.Draw(Sprite);
         // Update the window
         App.Display();
     }
 
     return EXIT_SUCCESS;

 }*/