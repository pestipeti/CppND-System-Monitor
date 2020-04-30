#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>

namespace LinuxParser {
// Paths
    const std::string kProcDirectory{"/proc/"};
    const std::string kCmdlineFilename{"/cmdline"};
    const std::string kCpuinfoFilename{"/cpuinfo"};
    const std::string kStatusFilename{"/status"};
    const std::string kStatFilename{"/stat"};
    const std::string kUptimeFilename{"/uptime"};
    const std::string kMeminfoFilename{"/meminfo"};
    const std::string kVersionFilename{"/version"};
    const std::string kOSPath{"/etc/os-release"};
    const std::string kPasswordPath{"/etc/passwd"};

// System
    float MemoryUtilization();

    long UpTime();

    std::vector<int> Pids();

    int TotalProcesses();

    int RunningProcesses();

    std::string OperatingSystem();

    std::string Kernel();

// CPU
    enum CPUStates {
        kUser_ = 0,
        kNice_,
        kSystem_,
        kIdle_,
        kIOwait_,
        kIRQ_,
        kSoftIRQ_,
        kSteal_,
        kGuest_,
        kGuestNice_
    };

// Processes
    std::string UserByUID(int UID);

// Helpers
    template <typename T>
    T GetValueByKey(std::string const &filter, std::string const &filename) {
        std::string line, key;
        T value;

        std::ifstream stream(kProcDirectory + filename);

        if (stream.is_open()) {
            while(std::getline(stream, line)) {
                std::istringstream linestream(line);
                while (linestream >> key >> value) {
                    if (key == filter) {
                        return value;
                    }
                }
            }
        }

        return value;
    }

    template <typename T>
    T GetValue(std::string const &filename) {
        std::string line;
        T value;

        std::ifstream stream(kProcDirectory + filename);
        if (stream.is_open()) {

            std::getline(stream, line);
            std::istringstream linestream(line);
            linestream >> value;

        }

        return value;
    }

};  // namespace LinuxParser

#endif