#include <iostream>
#include "AwaitInputState.h"

using namespace FTRTestProgram;

AwaitInputState::AwaitInputState(StateContext& context) : _context(context) {}

void AwaitInputState::handleInput(std::condition_variable& condition_var, std::mutex& condition_var_mutex, std::map<int, long>& inputQueue, std::string& inStr) {
	try {
		auto inVal = std::stoi(inStr);
		if (inputQueue.find(inVal) != inputQueue.end()) {
			inputQueue[inVal]++;
		}
		else {
			inputQueue[inVal] = 1;
		}
	}
	catch (const std::invalid_argument & except) {
		std::cerr << "Invalid input, integer was expected. " << except.what() << std::endl;
	} 
	_context.transitState(StateEnum::Running);
}
