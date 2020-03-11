#pragma once
#include <condition_variable>
#include <future>
#include <map>
#include <string>


namespace FTRTestProgram
{
	enum class StateEnum
	{
		Running,
		Paused,
		AwaitInput,
		Quitting
	};

	class State
	{
	public:
		virtual void handleInput(std::condition_variable& condition_var, std::mutex& condition_var_mutex, std::map<int, long>& inputQueue, std::string& inStr) = 0;
	};
}
