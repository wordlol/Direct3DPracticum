#pragma once
#include <chrono>

//стандартный таймер на хроно
class Timer
{
public:
	Timer()
	{
		last = std::chrono::steady_clock::now();
	};
	float Mark()
	{
		const std::chrono::steady_clock::time_point old = last;
		last = std::chrono::steady_clock::now();
		const std::chrono::duration<float> FrameTime = last - old;
		return FrameTime.count();
	};
	float Reack()
	{
		return std::chrono::duration <float>(std::chrono::steady_clock::now() - last).count();
	};
private:
	std::chrono::steady_clock::time_point last;
}tTimer;