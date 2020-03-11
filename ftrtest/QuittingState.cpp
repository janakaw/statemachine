#include "QuittingState.h"

using namespace FTRTestProgram;

QuittingState::QuittingState(StateContext& context) : _context(context) {}

void QuittingState::handleInput(std::condition_variable& condition_var, std::mutex& condition_var_mutex, std::map<int, long>& inputQueue, std::string& inStr) {
	_context.transitState(StateEnum::Quitting);
}

