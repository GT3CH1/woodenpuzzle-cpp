#ifndef TIMEHELPER_H
#define TIMEHELPER_H
#include <chrono>
namespace puzzle {
	/**
	 * The TimeHelper class is a simple utility class that allows for
	 * calculating the time between two points in the program.
	 * @author GT3CH1
	 */
	class TimeHelper {
	public:
		/**
		 * Calculates the time between the start and end time in seconds.
		 * @return The time between the start and end time in seconds.
		 */
		double calculate_time();

		/**
		 * Sets the start time to the current time.
		 */
		void set_start_time();

		/**
		 * Sets the end time to the current time.
		 */
		void set_end_time();

		TimeHelper& operator=(const TimeHelper& other) = default;
		TimeHelper() = default;
		TimeHelper(const TimeHelper& other) = default;

	private:
		/**
		 * The start time.
		 */
		std::chrono::system_clock::time_point start_time;

		/**
		 * The end time.
		 */
		std::chrono::system_clock::time_point end_time;
	};
}
#endif
