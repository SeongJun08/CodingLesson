#include <Windows.h>
#include "Timer.h"

namespace GameUtil
{
	Timer::Timer() :
		mdDeltaTime(-1.0),
		mfScale(1.0f),
		mbStopped(false),
		mdSecondsPerCount(),
		mllBaseTime(),
		mllPausedTime(),
		mllStopTime(),
		mllPrevTime(),
		mllCurTime()
	{
		long long countsPerSecond;

		// 일반 시간 ms(1/1000)
		// 1 s = 1000ms = 1000000 us(마이크로세컨드)
		QueryPerformanceFrequency((LARGE_INTEGER*) & countsPerSecond);
		mdSecondsPerCount = 1.0 / static_cast<double>(countsPerSecond);
	}

	void Timer::Start()
	{
		long long curTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&curTime);

		mllBaseTime = curTime;
		mllPrevTime = curTime;
		mllStopTime = 0;
		mbStopped = false;
	}

	void Timer::Stop()
	{
		if (!mbStopped)
		{
			long long curTime;
			QueryPerformanceCounter((LARGE_INTEGER *)&curTime);
			mllStopTime = curTime;

			mbStopped = true;
		}
	}

	void Timer::Resume()
	{
		if (mbStopped)
		{
			long long curTime;
			QueryPerformanceCounter((LARGE_INTEGER *)&curTime);

			mllPausedTime += (curTime - mllStopTime);
			mllPrevTime = curTime;
			mllStopTime = 0;
			mbStopped = false;

		}
	}

	void Timer::Update()
	{
		if (mbStopped)
		{
			mdDeltaTime = 0.0;
			return;
		}

		long long curTime;
		QueryPerformanceCounter((LARGE_INTEGER *)&curTime);
		mllCurTime = curTime;
		mdDeltaTime = (mllCurTime - mllPrevTime) * mdSecondsPerCount;
		mllPrevTime = mllCurTime;

		if (mdDeltaTime < 0.0)
		{
			mdDeltaTime = 0.0;
		}
	}

	float Timer::TotalTime() const
	{
		if (mbStopped)
		{
			return static_cast<float>((mllStopTime - mllPausedTime - mllBaseTime) * mdSecondsPerCount);
		}
		else
		{
			return static_cast<float>((mllCurTime - mllPausedTime - mllBaseTime) * mdSecondsPerCount);
		}
	}

	float Timer::DeltaTime() const
	{
		return static_cast<float>(mdDeltaTime * mfScale);
	}

	void Timer::SetScale(float scale)
	{
		mfScale = scale;
	}
}
