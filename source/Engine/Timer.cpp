#include <Engine/Timer.hpp>

#include <windows.h>

/*
#ifdef PLATFORM_WINDOWS
#include <windows.h>
#elif PLATFORM_LINUX
#include <sys/time.h>
#endif
*/

#include <ctime>

namespace LDE
{

	Timer::Timer( ) :
		m_StartTime( 0 ),
		m_Time( 0 )
	{
	}

	void Timer::Start( )
	{
		m_StartTime = GetSystemTime( );
	}

	void Timer::Stop( )
	{
		double CurrentTime = GetSystemTime( );
		m_Time = ( CurrentTime - m_StartTime );
	}

	double Timer::GetTime( )
	{
		return m_Time;
	}

	double Timer::GetSystemTime( )
	{
//#ifdef PLATFORM_WINDOWS
		static __int64 Counter = 0;
		static __int64 Frequency = 0;

		QueryPerformanceCounter( (LARGE_INTEGER*)&Counter );
		QueryPerformanceFrequency( (LARGE_INTEGER*)&Frequency );

		return double( Counter ) / double( Frequency );
/*
#elif PLATFORM_LINUX

		timeval Time;
		gettimeofday( &Time, 0 );
		return Time.tv_sec + ( Time.tv_usec * 0.000001 );

#endif*/
	}
}

