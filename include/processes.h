#ifndef MONITOR_PROCESSES_H
#define MONITOR_PROCESSES_H

#include "process.h"

#include <string>
#include <vector>

class Processes {
public:
    Processes();

    std::vector<Process> &GetProcesses();

private:
    long hertz;
    std::vector<int> current_pids_;
    std::vector<Process> processes_;

    void UpdateProcesses();

    void AddNewProcesses(bool &);

    void RemoveFinishedProcesses(bool &);

    static std::vector<int> ReadFolders();

};

#endif //MONITOR_PROCESSES_H
