#ifndef FILES_PARSER_H
#define FILES_PARSER_H

#include <fstream>
#include <regex>
#include <string>

namespace DataParser {
// Paths
const std::string kDataDirectory{"../data/"};
const std::string kPortfolioFilename{"portfolio.csv"};

// System
// float MemoryUtilization();
// long UpTime();
// std::vector<int> Pids();
// int TotalProcesses();
// int RunningProcesses();
// std::string OperatingSystem();
// std::string Kernel();

// // CPU
// enum CPUStates {
//   kUser_ = 0,
//   kNice_,
//   kSystem_,
//   kIdle_,
//   kIOwait_,
//   kIRQ_,
//   kSoftIRQ_,
//   kSteal_,
//   kGuest_,
//   kGuestNice_
// };
// std::vector<std::string> CpuUtilization();
// long Jiffies();
// long ActiveJiffies();
// long ActiveJiffies(int pid);
// long IdleJiffies();

// Processes
// std::string Command(int pid);
// std::string Ram(int pid);
// std::string Uid(int pid);
// std::string User(int pid);
// long int UpTime(int pid);

// Returns matrix
std::vector<std::vector<float>> ReturnPaths(std::string s_asset);
};  // namespace LinuxParser

#endif
