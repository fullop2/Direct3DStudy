#include "Timer.h"

bool Timer::Init()
{
	// 시스템이 고해상도 타이머를 지원하는지 체크
	QueryPerformanceFrequency((LARGE_INTEGER*)&mFrequency);

	if (0 == mFrequency)
	{
		return false;
	}

	// 밀리초동안 몇 주파수로 카운트 되는지 확인
	mTickPerMs = (float)(mFrequency / 1000);

	QueryPerformanceCounter((LARGE_INTEGER*)&mStartTime);

	return true;
}

void Timer::Frame()
{
	INT64 currentTime;
	float timeDifference;

	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	timeDifference = (float)(currentTime - mStartTime);

	mFrameTime = timeDifference / mTickPerMs;

	mStartTime = currentTime;
}

const float Timer::GetTime()
{
	return mFrameTime;
}

Timer::Timer()
{
}


Timer::~Timer()
{
}
