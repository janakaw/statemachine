#pragma once
#include "State.h"
#include "StateContext.h"

namespace FTRTestProgram
{

	class AwaitInputState :
		public State
	{
	public:
		AwaitInputState(StateContext& context);
		void handleInput(std::condition_variable& condition_var, std::mutex& condition_var_mutex, std::map<int, long>& inputQueue, std::string& inStr);

	private:
		StateContext& _context;
	};
}

