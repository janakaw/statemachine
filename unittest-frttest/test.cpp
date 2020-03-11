#include "pch.h"
#include "../ftrtest/StateContext.h"

using namespace FTRTestProgram;

TEST(StateContextTests, Test1) {
    StateContext stateConext;
    EXPECT_EQ(stateConext.getState(), StateEnum::Running);
}