#include "pch.h"
#include "CppUnitTest.h"
#include "../ftrtest/AwaitInputState.h"
#include "../ftrtest/PauseState.h"
#include "../ftrtest/RunningState.h"
#include "../ftrtest/StateContext.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FTRTestProgram;

namespace UnitTestFRTTest
{
	TEST_CLASS(UnitTestStateContext)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			StateContext stateContext;
			Assert::IsTrue(stateContext.getState() == StateEnum::Running);
		}

		TEST_METHOD(TestMethod2)
		{
			StateContext stateContext;
			stateContext.transitState(StateEnum::AwaitInput);
			Assert::IsTrue(stateContext.getState() == StateEnum::AwaitInput);

			stateContext.transitState(StateEnum::Running);
			Assert::IsTrue(stateContext.getState() == StateEnum::Running);

			stateContext.transitState(StateEnum::Paused);
			Assert::IsTrue(stateContext.getState() == StateEnum::Paused);

			stateContext.transitState(StateEnum::Paused);
			Assert::IsTrue(stateContext.getState() == StateEnum::Paused);
		}

		TEST_METHOD(TestMethod3)
		{
			std::map<int, long> inputs;
			std::atomic<int> outputDuraton{ 10 };
			std::mutex lock_inputs;
			std::condition_variable condition_var;
			std::mutex condition_var_mutex;
			StateContext stateContext;

			Assert::IsTrue(stateContext.getState() == StateEnum::Running);

			std::string testInput = "10";
			stateContext.handleInput(condition_var, condition_var_mutex, inputs, testInput);
			Assert::IsTrue(stateContext.getState() == StateEnum::Running);

			testInput = "*+@!*_+-_*!@+*";
			stateContext.handleInput(condition_var, condition_var_mutex, inputs, testInput);
			Assert::IsTrue(stateContext.getState() == StateEnum::Running);

			testInput = "P";
			stateContext.handleInput(condition_var, condition_var_mutex, inputs, testInput);
			Assert::IsTrue(stateContext.getState() == StateEnum::Paused);

			testInput = "R";
			stateContext.handleInput(condition_var, condition_var_mutex, inputs, testInput);
			Assert::IsTrue(stateContext.getState() == StateEnum::Running);

			testInput = "P";
			stateContext.handleInput(condition_var, condition_var_mutex, inputs, testInput);
			Assert::IsTrue(stateContext.getState() == StateEnum::Paused);

			testInput = "N";
			stateContext.handleInput(condition_var, condition_var_mutex, inputs, testInput);
			Assert::IsTrue(stateContext.getState() == StateEnum::AwaitInput);

			testInput = "1";
			stateContext.handleInput(condition_var, condition_var_mutex, inputs, testInput);
			Assert::IsTrue(stateContext.getState() == StateEnum::Running);

			testInput = "P";
			stateContext.handleInput(condition_var, condition_var_mutex, inputs, testInput);
			Assert::IsTrue(stateContext.getState() == StateEnum::Paused);

			testInput = "Q";
			stateContext.handleInput(condition_var, condition_var_mutex, inputs, testInput);
			Assert::IsTrue(stateContext.getState() == StateEnum::Quitting);
		}

	};

	TEST_CLASS(UnitTestRunningState)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			std::map<int, long> inputs;
			std::atomic<int> outputDuraton{ 10 };
			std::mutex lock_inputs;
			std::condition_variable condition_var;
			std::mutex condition_var_mutex;
			StateContext stateContext;

			RunningState runningState(stateContext);
			Assert::IsTrue(stateContext.getState() == StateEnum::Running);

			std::string testInput = "10";
			runningState.handleInput(condition_var, condition_var_mutex, inputs, testInput);
			Assert::IsTrue(stateContext.getState() == StateEnum::Running);

			testInput = "P";
			runningState.handleInput(condition_var, condition_var_mutex, inputs, testInput);
			Assert::IsTrue(stateContext.getState() == StateEnum::Paused);

			testInput = "N";
			runningState.handleInput(condition_var, condition_var_mutex, inputs, testInput);
			Assert::IsTrue(stateContext.getState() == StateEnum::AwaitInput);

			testInput = "Q";
			runningState.handleInput(condition_var, condition_var_mutex, inputs, testInput);
			Assert::IsTrue(stateContext.getState() == StateEnum::Quitting);
		}
	};
}
