#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>

class Processor {
// TODO: Declare any necessary private members
private:
    int prev_idle;
    int prev_iowait;
    int prev_user;
    int prev_nice;
    int prev_system;
    int prev_irq;
    int prev_softirq;
    int prev_steal;

    void SetPreviousValues(std::vector<double>);
    static std::vector<double> ReadFile();

public:
    double Utilization();  // TODO: See src/processor.cpp
};

#endif