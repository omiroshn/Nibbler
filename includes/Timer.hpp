#ifndef _TIMER_HPP
#define _TIMER_HPP

#include <SDL.h>

//**************************************************************************************************
//	Timer
//--------------------------------------------------------------------------------------------------
class Timer
{
public:
	static Timer*	Instance();
	static void		Release();
	void			Reset();
	float			getDeltaTime();
	void			setTimeScale(float t);
	float			getTimeScale();

	void			Update();

private:
	Timer();
	~Timer();

	static Timer*	sInstance;
	unsigned int	mStartTicks;
	unsigned int	mElapseTicks;
	float			mDeltaTime;
	float			mTimeScale;


};

#endif