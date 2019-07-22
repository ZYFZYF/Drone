#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <thread>
#include "updater/PlanningPathUpdater.h"
#include <vector>
#include "../Common/utils/ShallowLearning.h"
#include "../Common/utils/utils.h"
#include "updater/PlanningVisionUpdater.h"

int client_id;
std::vector<std::string> float_signals = Config::Instance()->getStringVectorParam("Main", "CLEAN_FLOAT_SIGNALS");

void clearSignals()
{
    for (const auto &float_signal: float_signals)
    {
        std::cout << float_signal << std::endl;
        simxClearFloatSignal(client_id, float_signal.c_str(), simx_opmode_oneshot);
    }
}

void doSomethingBeforeSimulation()
{
    //simxFinish(-1);
    client_id = simxStart("127.0.0.1", 19997, 1, 1, 2000, 5);
    if (client_id == -1)
    {
        std::cout << "Failed to connect to remote API server" << std::endl;
        std::cout << "So think the first script has been running, so use 0 as client_id" << std::endl;
        client_id = 0;
        return;
    }
    std::cout << "Connect to remote API server and cid is " << client_id << std::endl;
    simxStartSimulation(client_id, simx_opmode_oneshot);
    clearSignals();
}

void doSomethingAfterSimulation()
{
    clearSignals();
    // stop simulation
    while(simxStopSimulation(client_id, simx_opmode_blocking) != simx_return_ok);
    // close connection
    simxFinish(-1);
    std::cout << "Close connection to V-REP" << std::endl;
}

void doSomethingAfterSimulationForLinux(int sig)
{
    doSomethingAfterSimulation();
}

#ifdef __WIN32
bool ctrlHandler(DWORD fdwctrltype)
{
    switch (fdwctrltype)
    {
        case CTRL_C_EVENT:
        {
            doSomethingAfterSimulation();
            return false;
        }
        default:
        {
            return false;
        }
    }
}
#endif

int main(int argc, char const *argv[])
{
    if(argc < 2)
    {
        std::cout << "need a parameter to decide exec path or vision" << std::endl;
        return 0;
    }
#ifdef __WIN32
    if (!SetConsoleCtrlHandler((PHANDLER_ROUTINE) ctrlHandler, true))
    {
        std::cout << "Capture ctrl-c event failed" << std::endl;
        exit(0);
    };
#else
    signal(SIGINT, doSomethingAfterSimulationForLinux);
#endif
    doSomethingBeforeSimulation();

    if(strcmp(argv[1], "path") == 0)
    {
        PlanningPathUpdater path_updater(client_id);
        path_updater.run();
    } else
    {
        PlanningVisionUpdater vision_updater(client_id);
        vision_updater.run();
    }
    doSomethingAfterSimulation();
    return 0;
}

