#pragma once
#include <chrono> ///��������� ������������� � ��������� �������
/// ��� ������������ ������ ����� ������������ ��������������� ������� �� thread this_thread::sleep_for(std::chrono::milliseconds(����������));

class Timer
{	/// ������� ������������ ������
public:
	Timer()
	{
		last = std::chrono::steady_clock::now(); /// ���������� ������� �����
	};
	float Mark()
	{
		const std::chrono::steady_clock::time_point old = last; /// �������������� �����
		last = std::chrono::steady_clock::now(); /// ���������� ����� ������� �����
		const std::chrono::duration<float> FrameTime = last - old; /// �������� �� �������
		return FrameTime.count(); /// ������� ���������
	};
	float Reack()
	{
		return std::chrono::duration <float>(std::chrono::steady_clock::now() - last).count(); /// ������� �� �������� ������� � ����������������� �������
	};
private:
	std::chrono::steady_clock::time_point last;/// �������������� ����� ��������� �� �����
};