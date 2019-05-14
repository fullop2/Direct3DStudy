#include "Timer.h"

bool Timer::Init()
{
	// �ý����� ���ػ� Ÿ�̸Ӹ� �����ϴ��� üũ
	QueryPerformanceFrequency((LARGE_INTEGER*)&mFrequency);

	if (0 == mFrequency)
	{
		return false;
	}

	// �и��ʵ��� �� ���ļ��� ī��Ʈ �Ǵ��� Ȯ��
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
