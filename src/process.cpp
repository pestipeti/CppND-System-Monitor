#include <unistd.h>
#include <string>
#include <vector>

#include "format.h"
#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid, long hertz): pid_(pid), hertz_(hertz) {

    vector<string> cpuNumbers = ReadFile(pid);

    if (!cpuNumbers.empty()) {
        utime_ = stof(cpuNumbers[13]);
        stime_ = stof(cpuNumbers[14]);
        cutime_ = stof(cpuNumbers[15]);
        cstime_ = stof(cpuNumbers[16]);
        starttime_ = stof(cpuNumbers[21]);
    }
}

// TODO: Return this process's ID
int Process::Pid() const {
    return pid_;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const {
    long update = LinuxParser::UpTime();
    float total = utime_ + stime_ + cutime_ + cstime_;

    float sec = update - (starttime_ / hertz_);

    return(total / hertz_) / sec;
}

// TODO: Return the command that generated this process
string Process::Command() const {
    auto cmd = LinuxParser::GetValue<string>(to_string(pid_) + LinuxParser::kCmdlineFilename);

    size_t maxSize = 75;

    if (cmd.size() > maxSize) {
        cmd.resize(maxSize - 3);
        cmd = cmd + "...";
    }

    return cmd;
}

float Process::RawRam() const {
    auto mem = LinuxParser::GetValueByKey<float>("VmData:", to_string(pid_)
        + LinuxParser::kStatusFilename);

    return mem;
}

// TODO: Return this process's memory utilization
string Process::Ram() const {
    float memKb = RawRam();
    return Format::ConvertToMb(memKb);
}

// TODO: Return the user (name) that generated this process
string Process::User() const {
    int UID = LinuxParser::GetValueByKey<int>("Uid:", to_string(pid_) + LinuxParser::kStatusFilename);
    return LinuxParser::UserByUID(UID);
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() const {
    long uptime = LinuxParser::UpTime();
    return uptime - (starttime_ / hertz_);
}

vector<string> Process::ReadFile(int pid) {
    string line, skip;

    std::ifstream stream(LinuxParser::kProcDirectory + to_string(pid) + LinuxParser::kStatFilename);

    if (stream.is_open()) {
        getline(stream, line);
        std::istringstream linestream(line);
        std::istream_iterator<string> beg(linestream), end;
        vector<string> cpuNumbers(beg, end);

        return cpuNumbers;
    }

    vector<string> none = {};
    return none;
}