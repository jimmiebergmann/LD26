#ifndef __LDE_TIMER_HPP__
#define __LDE_TIMER_HPP__

#include <SFML/System.hpp>
namespace LDE
{

	class Timer
	{

	public:

		// Constructor
		Timer( );

		// Public general functions
		float GetTime( );
		void Start( );
		void Stop( );

	private:

		// Private variables
		sf::Clock m_sfClock;
		float m_Time;
		bool m_Started;

	};

}

#endif