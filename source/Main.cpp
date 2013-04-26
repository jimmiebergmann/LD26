#include <iostream>
#include <SFML/Window.hpp>


int main( int argc, char ** argv )
{
	sf::Window window(sf::VideoMode( 800, 600, 32 ), "LD26" );

	std::cout << "Ludum Dare 26 entry by Jimmie Bergmann." << std::endl;
	return 0;
}