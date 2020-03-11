// FTR Test Program main()
// 

#include <algorithm>
#include <array>
#include <condition_variable>
#include <future>
#include <iomanip>
#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "PauseState.h"
#include "RunningState.h"
#include "StateContext.h"

namespace FTRTestProgram {

    void readInput(StateContext& context, std::condition_variable& condition_var, std::mutex& condition_var_mutex, std::map<int, long>& inputs, std::mutex& lock_queue) {
        const auto sleepTime = std::chrono::microseconds(5); 

        while (context.getState() != StateEnum::Quitting) {
            std::this_thread::sleep_for(sleepTime);
            std::string inStr("");
            std::getline(std::cin, inStr);
            std::lock_guard<std::mutex> guard(lock_queue);
            context.handleInput(condition_var, condition_var_mutex, inputs, inStr);
        }
    }

    void printOutput(StateContext& context, std::condition_variable& condition_var, std::mutex& condition_var_mutex, std::map<int, long>& inputs, std::mutex& lock_queue, std::atomic<int>& outputPeriod) {
        StateEnum state = context.getState();
        while (state != StateEnum::Quitting) {
            state = context.getState();
            if (state == StateEnum::Paused) {
                std::unique_lock<std::mutex> pause_lock(condition_var_mutex);
                condition_var.wait_for(pause_lock, std::chrono::seconds(outputPeriod));
            }

            if (state != StateEnum::Paused && state != StateEnum::Quitting) {
                std::unique_lock<std::mutex> pause_lock(condition_var_mutex);
                condition_var.wait_for(pause_lock, std::chrono::seconds(outputPeriod));

                std::lock_guard<std::mutex> guard(lock_queue);
                std::cout << std::endl;
                std::vector<std::pair<int, long>> output;
                for (auto it = inputs.begin(); it != inputs.end(); ++it) {
                    auto p = std::make_pair(it->first, it->second);
                    output.push_back(p);
                }

                std::sort(output.begin(), output.end(), [](std::pair<int, long> a, std::pair<int, long> b) {
                    auto a0 = std::get<0>(a);
                    auto a1 = std::get<1>(a);
                    auto b0 = std::get<0>(b);
                    auto b1 = std::get<1>(b);
                    if (a1 != b1) return (a1 > b1);
                    else return (a0 < b0);
                });

                std::cout << "===== output =====" << std::endl;

                for (auto it = output.begin(); it != output.end(); ++it) {
                    int width = std::to_string(it->first).size();
                    std::cout << std::setw(width) << it->second << " ";
                }
                std::cout << std::endl;
                for (auto it = output.begin(); it != output.end(); ++it) {
                    std::cout << it->first << " ";
                }
                std::cout << std::endl;
            }
        }
    }
}

using namespace FTRTestProgram;

int main()
{
    std::cout << "Welcome to FTR test program" << std::endl;
    std::cout << "Starting up:" << std::endl;

    std::cout << "Please enter output period:" << std::endl;
    int outputPeriod = 0;
    std::cin >> outputPeriod;

    int inVal;
    std::cout << "Please enter first entry:" << std::endl;
    std::cin >> inVal;

    std::map<int, long> inputs;
    inputs[inVal] = 1;

    std::atomic<int> outputDuraton{ outputPeriod };
    std::mutex lock_inputs;
    std::condition_variable condition_var;
    std::mutex condition_var_mutex;
    StateContext context;

    auto readThred = std::thread(readInput, std::ref(context), std::ref(condition_var), std::ref(condition_var_mutex), std::ref(inputs), std::ref(lock_inputs));
    auto writeThread = std::thread(printOutput, std::ref(context), std::ref(condition_var), std::ref(condition_var_mutex), std::ref(inputs), std::ref(lock_inputs), std::ref(outputDuraton));

    readThred.join();
    writeThread.join();
}
