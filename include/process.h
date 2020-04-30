#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>

/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int, long);
  [[nodiscard]] int Pid() const;                               // TODO: See src/process.cpp
  [[nodiscard]] std::string User() const;                      // TODO: See src/process.cpp
  [[nodiscard]] std::string Command() const;                   // TODO: See src/process.cpp
  [[nodiscard]] float CpuUtilization() const;                  // TODO: See src/process.cpp
  [[nodiscard]] float RawRam() const;
  [[nodiscard]] std::string Ram() const;                       // TODO: See src/process.cpp
  [[nodiscard]] long int UpTime() const;                       // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
    int pid_;
    long hertz_;
    float utime_ = 0.0;
    float stime_ = 0.0;
    float cutime_ = 0.0;
    float cstime_ = 0.0;
    float starttime_ = 0.0;

    static std::vector<std::string> ReadFile(int);

};

#endif