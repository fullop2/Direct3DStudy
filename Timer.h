#pragma once
#include <Windows.h>

class Timer
{
public:
	bool Init();
	void Frame();

	const float GetTime();
public:

	static Timer& Get()
	{
		static Timer timer;
		return timer;
	}

	Timer();
	~Timer();

private:
	INT64 mFrequency;
	float mTickPerMs;
	INT64 mStartTime;
	float mFrameTime;
};

