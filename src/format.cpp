#include <string>
#include <sstream>
#include <iomanip>

#include "format.h"

using std::string;
using std::to_string;

string Format::Format(int time) {
    string timeString = to_string(time);
    return string(2 - timeString.length(), '0') + timeString;
}

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
    int hour = 0;
    int min = 0;
    int sec = 0;

    hour = seconds / 3600;
    seconds = seconds % 3600;

    min = seconds / 60;
    seconds = seconds % 60;

    sec = seconds;

    return Format(hour) + ":" + Format(min) + ":" + Format(sec);
}

string Format::ConvertToMb(float kb) {
    float mb = kb / 1024;
    std::stringstream mb_stream;
    mb_stream << std::fixed << std::setprecision(1) << mb;
    return mb_stream.str();
}
