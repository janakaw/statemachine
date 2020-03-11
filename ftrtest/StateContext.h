#pragma once
#include <future>
#include <memory>
#include <map>
#include <string>

#include "State.h"

namespace FTRTestProgram {

	class StateContext
	{
	public:
		explicit StateContext();
		StateEnum getState(void);
		void transitState(StateEnum);
		void handleInput(std::condition_variable& condition_var, std::mutex& condition_var_mutex, std::map<int, long>& inputQueue, std::string& inStr);

	private:
		std::map<StateEnum, std::unique_ptr<State>> _states;
		StateEnum _activeState;
	};

}

