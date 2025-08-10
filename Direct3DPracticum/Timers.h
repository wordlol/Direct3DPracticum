#pragma once
#include <chrono> ///управляют длительностью и моментами времени
/// для приостоновки потока можно использовать многопоточночну функцию из thread this_thread::sleep_for(std::chrono::milliseconds(милисекунд));

class Timer
{	/// обычный монопоточный таймер
public:
	Timer()
	{
		last = std::chrono::steady_clock::now(); /// возвращает текущее время
	};
	float Mark()
	{
		const std::chrono::steady_clock::time_point old = last; /// переопределние часов
		last = std::chrono::steady_clock::now(); /// врзвращает новое текущее время
		const std::chrono::duration<float> FrameTime = last - old; /// получаем их разницу
		return FrameTime.count(); /// выводим результат
	};
	float Reack()
	{
		return std::chrono::duration <float>(std::chrono::steady_clock::now() - last).count(); /// разница от текущего времени и переопределенного времени
	};
private:
	std::chrono::steady_clock::time_point last;/// переопределние часов указатель на время
};