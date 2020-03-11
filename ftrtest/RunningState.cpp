#include "RunningState.h"

using namespace FTRTestProgram;

RunningState::RunningState(StateContext& context) : _context(context) {}

void RunningState::handleInput(std::condition_variable& condition_var, std::mutex& condition_var_mutex, std::map<int, long>& inputQueue, std::string& inStr) {
	
	switch (inStr.c_str()[0])
	{
	case 'P':
		_context.transitState(StateEnum::Paused);
		break;
	case 'N':
		_context.transitState(StateEnum::AwaitInput);
		break;
	case 'Q':
		_context.transitState(StateEnum::Quitting);
		break;
	default:
		break;
	}
}
