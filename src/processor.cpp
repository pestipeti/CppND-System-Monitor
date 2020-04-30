#include <string>
#include <vector>

#include "processor.h"
#include "linux_parser.h"

using std::string;
using std::vector;

// TODO: Return the aggregate CPU utilization
double Processor::Utilization() {
    vector<double> values = ReadFile();

    double user = values[0];
    double nice = values[1];
    double sys = values[2];
    double idle = values[3];
    double iowait = values[4];
    double irq = values[5];
    double softirq = values[6];
    double steal = values[7];

    double old_idle = prev_idle + prev_iowait;
    double new_idle = idle + iowait;

    double old_non_idle = prev_user + prev_nice + prev_system + prev_irq + prev_softirq + prev_steal;
    double new_non_idle = user + nice + sys + irq + softirq + steal;

    double old_total = old_idle + old_non_idle;
    double new_total = new_idle + new_non_idle;

    double total_diff = new_total - old_total;
    double idle_diff = new_idle - old_idle;

    SetPreviousValues(values);

    return (total_diff - idle_diff) / total_diff;
}

void Processor::SetPreviousValues(vector<double> newValues) {
    prev_user = newValues[0];
    prev_nice = newValues[1];
    prev_system = newValues[2];
    prev_idle = newValues[3];
    prev_iowait = newValues[4];
    prev_irq = newValues[5];
    prev_softirq = newValues[6];
    prev_steal = newValues[7];
}

vector<double> Processor::ReadFile() {
    string line, key;
    double value;
    vector<double> cpuNumbers;

    std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);

    if (stream.is_open()) {

        while(std::getline(stream, line)) {
            std::istringstream linestream(line);
            while (linestream >> key) {
                if (key == "cpu") {
                    while (linestream >> value) {
                        cpuNumbers.emplace_back(value);
                    }
                }
            }
        }

    }

    return cpuNumbers;
}