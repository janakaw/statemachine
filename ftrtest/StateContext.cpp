#include <set>

#include "StateContext.h"
#include "RunningState.h"
#include "PauseState.h"
#include "AwaitInputState.h"
#include "QuittingState.h"

using namespace FTRTestProgram;

StateContext::StateContext() : _activeState(StateEnum::Running) {
	std::unique_ptr<State> runningState = std::make_unique<RunningState>(*this);
	_states[StateEnum::Running] = std::move(runningState);
	std::unique_ptr<State> pauseState = std::make_unique<PauseState>(*this);
	_states[StateEnum::Paused] = std::move(pauseState);
	std::unique_ptr<State> awaitInputState = std::make_unique<AwaitInputState>(*this);
	_states[StateEnum::AwaitInput] = std::move(awaitInputState);
	std::unique_ptr<State> quittingState = std::make_unique<QuittingState>(*this);
	_states[StateEnum::Quitting] = std::move(quittingState);
}

StateEnum StateContext::getState() {
	return _activeState;
}

void StateContext::transitState(StateEnum state) {
	_activeState = state;
}
void StateContext::handleInput(std::condition_variable& condition_var, std::mutex& condition_var_mutex, std::map<int, long>& inputQueue, std::string& inStr) {
	_states[_activeState]->handleInput(condition_var, condition_var_mutex, inputQueue, inStr);
}
