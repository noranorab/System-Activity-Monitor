#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>
#include <vector>

namespace LinuxParser {
// Paths


// System

// Returns overall memory utilization
float MemoryUtilization();

 // Returns the uptime of the system in seconds
long UpTime();

// Returns a vector of PIDs (Process IDs) of running processes
std::vector<int> Pids();

// Returns the total number of processes running on the system
int TotalProcesses();

// Returns the number of running processes on the system
int RunningProcesses();

// Returns the operating system name of the system
std::string OperatingSystem();

// Returns the kernel version of the system
std::string Kernel();

// Returns a vector of available disk devices in the system
std::vectorstd::string GetAvailableDevices();

// Returns a vector of available disk partitions in the system
std::vectorstd::string GetAvailablePartitions();


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


std::vector<std::string> CpuUtilization();

// Processes
std::string Command(int pid);
std::string Ram(int pid);
std::string Uid(int pid);
std::string User(int pid);
long int UpTime(int pid);
std::vector<std::string> ProcessCpuUtilization(int pid);
double GetDiskReadRateForPID(int pid);
double GetDiskWriteRateForPID(int pid);
}; 


#endif // SYSTEM_PARSER_H
