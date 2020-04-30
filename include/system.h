#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "processes.h"

class System {
public:
    Processor &Cpu();                   // TODO: See src/system.cpp
    Processes &GetProcesses();  // TODO: See src/system.cpp
    static float MemoryUtilization();          // TODO: See src/system.cpp
    static long UpTime();                      // TODO: See src/system.cpp
    static int TotalProcesses();               // TODO: See src/system.cpp
    static int RunningProcesses();             // TODO: See src/system.cpp
    static std::string Kernel();               // TODO: See src/system.cpp
    static std::string OperatingSystem();      // TODO: See src/system.cpp

    // TODO: Define any necessary private members
private:
    Processor cpu_{};
    Processes processes_;
};

#endif