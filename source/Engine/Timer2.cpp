#include <Engine/Timer.hpp>

namespace LDE
{

	// Constructor
	Timer::Timer( ) :
		m_Time( 0.0f ),
		m_Started( false )
	{
	}

	// Public general functions
	float Timer::GetTime( )
	{
		return m_Time;
	}

	void Timer::Start( )
	{
		m_Started = true;
		m_sfClock.Reset( );
	}

	void Timer::Stop( )
	{
		m_Time = m_sfClock.GetElapsedTime( );
		m_Started = false;
	}

}