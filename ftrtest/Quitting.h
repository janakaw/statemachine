#pragma once
#include "State.h"
#include "StateContext.h"

namespace FTRTestProgram
{

	class QuittingState :
		public State
	{
	public:
		QuittingState(StateContext& context);
		void handleInput(std::atomic<bool>& programRunning, std::atomic<StateEnum>& state, std::vector<int>& inputQueue, const std::string& inStr);

	private:
		StateContext& _context;
	};
}

