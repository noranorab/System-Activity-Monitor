#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

class System {
public:
  // Returns the CPU object representing the system's processor
  Processor &Cpu();
  
  // Returns the vector of Process objects representing the running processes in the system
  std::vector<Process> &Processes();
  
  // Returns overall memory utilization
  float MemoryUtilization();
  
  // Returns the uptime of the system in seconds
  long UpTime();
  
  // Returns the total number of processes running on the system
  int TotalProcesses();
  
  // Returns the number of running processes on the system
  int RunningProcesses();
  
  // Returns a vector of available disk devices in the system
  std::vector<std::string> GetAvailableDevices();
  
  // Returns a vector of available disk partitions in the system
  std::vector<std::string> GetAvailablePartitions();
  
  // Returns the kernel version of the system
  std::string Kernel();
  
  // Returns the operating system name of the system
  std::string OperatingSystem();

private:
  // Processor object representing the system's CPU
  Processor cpu_ = {};
  std::vector<Process> processes_ = {};
};

#endif
