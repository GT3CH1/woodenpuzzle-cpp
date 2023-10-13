#include "TimeHelper.h"
using namespace puzzle;
double TimeHelper::calculate_time()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() / 1000.0;
}

void TimeHelper::set_start_time()
{
	start_time = std::chrono::system_clock::now();
}

void TimeHelper::set_end_time()
{
	end_time = std::chrono::system_clock::now();
}
