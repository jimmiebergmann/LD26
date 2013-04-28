#ifndef __LDE_TIMER_HPP__
#define __LDE_TIMER_HPP__

namespace LDE
{

	class Timer
	{
	public:

		Timer( );
		void Start( );
		void Stop( );
		double GetTime( );
		void DeltaLock(double delta);
		static double GetSystemTime( );

	private:

		double m_StartTime;
		double m_Time;

	};
}


#endif