#include <dirent.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
    float totalMem = GetValueByKey<int>("MemTotal:", LinuxParser::kMeminfoFilename);
    float freeMem = GetValueByKey<int>("MemFree:", LinuxParser::kMeminfoFilename);

    return (totalMem - freeMem) / totalMem;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
    return LinuxParser::GetValue<long>(LinuxParser::kUptimeFilename);
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
    return LinuxParser::GetValueByKey<int>("processes", LinuxParser::kStatFilename);
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
    return LinuxParser::GetValueByKey<int>("procs_running", LinuxParser::kStatFilename);
}

string LinuxParser::UserByUID(int UID) {
    string line, user, x;
    int fileUid;

    std::ifstream filestream(LinuxParser::kPasswordPath);

    if (filestream.is_open()) {
        while(std::getline(filestream, line)) {
            std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);
            while(linestream >> user >> x >> fileUid) {
                if (fileUid == UID) {
                    return user;
                }
            }
        }
    }

    return user;
}