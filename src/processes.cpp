#include <unistd.h>
#include <algorithm>
#include <vector>

#include "processes.h"
#include "process.h"
#include "linux_parser.h"

using std::sort;
using std::vector;

bool compareProcesses(Process &p1, Process &p2) {
    return (p1.RawRam() > p2.RawRam());
};

Processes::Processes() {
    hertz = sysconf(_SC_CLK_TCK);
    UpdateProcesses();
}

vector<Process> &Processes::GetProcesses() {
    UpdateProcesses();
    return processes_;
}

void Processes::UpdateProcesses() {
    current_pids_ = ReadFolders();
    bool processesChanged = false;

    AddNewProcesses(processesChanged);
    RemoveFinishedProcesses(processesChanged);

    if (processesChanged) {
        sort(processes_.begin(), processes_.end(), compareProcesses);
    }
}

void Processes::AddNewProcesses(bool & processesChanged) {
    for (int pid : current_pids_) {
        if (std::find_if(processes_.begin(), processes_.end(),
                [pid](Process& n){
                    return n.Pid() == pid;
                }) == processes_.end())
        {
            processesChanged = true;
            Process process(pid, hertz);
            processes_.emplace_back(process);
        }
    }
}

void Processes::RemoveFinishedProcesses(bool &processesChanged) {
    for (std::size_t i = 0; i < processes_.size(); i++) {
        int pid = processes_[i].Pid();

        if (std::find(current_pids_.begin(), current_pids_.end(), pid) == current_pids_.end()) {
            processesChanged = true;
            processes_.erase(processes_.begin() + i);
        }

    }
}

vector<int> Processes::ReadFolders() {
    return LinuxParser::Pids();
}