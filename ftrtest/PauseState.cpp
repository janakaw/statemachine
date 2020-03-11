#include "PauseState.h"

using namespace FTRTestProgram;

PauseState::PauseState(StateContext& context) : _context(context) {}

void PauseState::handleInput(std::condition_variable& condition_var, std::mutex& condition_var_mutex, std::map<int, long>& inputQueue, std::string& inStr) {
	switch (inStr.c_str()[0])
	{
	case 'R':
		_context.transitState(StateEnum::Running);
		condition_var.notify_all();
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

