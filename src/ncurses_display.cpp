#include <chrono>
#include <curses.h>
#include <string>
#include <thread>
#include <vector>
#include <iostream>

#include "format.h"
#include "ncurses_display.h"
#include "system.h"

using std::string;
using std::to_string;

// 50 bars uniformly displayed from 0 - 100 %
// 2% is one bar(|)
std::string NCursesDisplay::ProgressBar(float percent) {
/**
   * @brief Creates a progress bar string based on the given percentage.
   * 
   * @param percent The percentage value (between 0 and 1).
   * @return The progress bar string.
   */
  std::string result{"0%"};
  int size{50};
  float bars{percent * size};

  for (int i{0}; i < size; ++i) {
    result += i <= bars ? '|' : ' ';
  }

  string display{to_string(percent * 100).substr(0, 4)};
  if (percent < 0.1 || percent == 1.0)
    display = " " + to_string(percent * 100).substr(0, 3);
  return result + " " + display + "/100%";
}

/**
   * @brief Displays the system information in the specified ncurses window.
   * 
   * @param system The System object containing system information.
   * @param window The ncurses window to display the information in.
   */
void NCursesDisplay::DisplaySystem(System &system, WINDOW *window) {

  int row{0};
  mvwprintw(window, ++row, 2, ("OS: " + system.OperatingSystem()).c_str());
  mvwprintw(window, ++row, 2, ("Kernel: " + system.Kernel()).c_str());
  mvwprintw(window, ++row, 2, "CPU: ");
  wattron(window, COLOR_PAIR(1));
  mvwprintw(window, row, 10, "");
  wprintw(window, ProgressBar(system.Cpu().Utilization()).c_str());
  wattron(window, COLOR_PAIR(1));
  mvwprintw(window, ++row, 2, "Memory: ");
  wattron(window, COLOR_PAIR(1));
  mvwprintw(window, row, 10, "");
  wprintw(window, ProgressBar(system.MemoryUtilization()).c_str());
  wattroff(window, COLOR_PAIR(1));
  mvwprintw(window, row, 10, "");
  mvwprintw(window,++row,2, "Available disk devices: ");
	  // Get available devices
  std::vector<std::string> devices = system.GetAvailableDevices();
	  // Display the available devices in the devices window
  std::string devicesString; 
  int maxWidth = getmaxx(window) - 2;
  for (const auto& device : devices) {
        if (devicesString.length() + device.length() + 1 <= maxWidth) {
        	if (device == "name") continue;
                devicesString += device + " ";
        } else {
            break;  // Break if adding the next device exceeds the maximum width
        }
    }
    mvwprintw(window, row, 28, devicesString.c_str());
    wattroff(window, COLOR_PAIR(1));
    mvwprintw(window, ++row, 10, "");
    mvwprintw(window, ++row, 10, "");
    wattroff(window, COLOR_PAIR(1));
    mvwprintw(window, row, 2, "Available Disk Partitions: ");
    std::vector<std::string> partitions = system.GetAvailablePartitions();
    std::string partitionsString;
    for (const auto& partition : partitions) {
        if (partitionsString.length() + partition.length() + 1 <= maxWidth) {
            partitionsString += partition + " ";
        } else {
            break;  // Break if adding the next partition exceeds the maximum width
        }
    }
    mvwprintw(window, row, 28, partitionsString.c_str());

    wattroff(window, COLOR_PAIR(1));
    mvwprintw(window, ++row, 10, "");
  mvwprintw(window, ++row, 2,
            ("Total Processes: " + to_string(system.TotalProcesses())).c_str());
  mvwprintw(
      window, ++row, 2,
      ("Running Processes: " + to_string(system.RunningProcesses())).c_str());
  mvwprintw(window, ++row, 2,
            ("Up Time: " + Format::ElapsedTime(system.UpTime())).c_str());

     wrefresh(window);
}


 /**
   * @brief Displays the process information in the specified ncurses window.
   * 
   * @param processes The vector of Process objects containing process information.
   * @param window The ncurses window to display the information in.
   * @param n The number of processes to display.
   */

void NCursesDisplay::DisplayProcesses(std::vector<Process> &processes,
                                      WINDOW *window, int n) {
  int row{0};
  int const pid_column{2};
  int const user_column{8};
  int const cpu_column{16};
  int const ram_column{23};
  int const time_column{30};
  int const rr_column{39};
  int const wr_column{49};
  int const command_column{58};
  wattron(window, COLOR_PAIR(2));
  mvwprintw(window, ++row, pid_column, "PID");
  mvwprintw(window, row, user_column, "USER");
  mvwprintw(window, row, cpu_column, "CPU[%%]");
  mvwprintw(window, row, ram_column, "RAM[MB]");
  mvwprintw(window, row, time_column, "TIME+");
  mvwprintw(window, row, rr_column, "rr[kB/s]");
  mvwprintw(window, row, wr_column, "wr[kB/s]");
  mvwprintw(window, row, command_column, "COMMAND");
  wattroff(window, COLOR_PAIR(2));
  for (int i = 0; i < n; ++i) {
    mvwprintw(window, ++row, pid_column, to_string(processes[i].Pid()).c_str());
    mvwprintw(window, row, user_column, processes[i].User().c_str());
    float cpu = processes[i].getCpuUtilization() * 100;
    mvwprintw(window, row, cpu_column, to_string(cpu).substr(0, 4).c_str());
    mvwprintw(window, row, ram_column, processes[i].Ram().c_str());
    mvwprintw(window, row, time_column,
              Format::ElapsedTime(processes[i].UpTime()).c_str());
    mvwprintw(window, row, rr_column, to_string(processes[i].GetDiskReadRateForPID()).substr(0, 8).c_str());
    mvwprintw(window, row, wr_column, to_string(processes[i].GetDiskWriteRateForPID()).substr(0, 8).c_str());
    mvwprintw(window, row, command_column,
              processes[i].Command().substr(0, window->_maxx - 57).c_str());
  }
}

/**
   * @brief Displays the system information and process information in the terminal using ncurses.
   * 
   * @param system The System object containing system information.
   * @param n The number of processes to display.
   */

void NCursesDisplay::Display(System &system, int n) {
  initscr();     // start ncurses
  noecho();      // do not print input values
  cbreak();      // terminate ncurses on ctrl + c
  start_color(); // enable color

 int x_max{getmaxx(stdscr)};
    int y_max{getmaxy(stdscr)};

    int system_height = 13;  // Minimum height for system information
    int process_height = 4 + n;

    int available_height = y_max - system_height - process_height - 3;

    int devices_y = system_height + 1;
    int process_y = y_max - process_height - 2;

    WINDOW* system_window = newwin(system_height, x_max - 2, 0, 1);
    WINDOW* process_window = newwin(process_height, x_max - 2, process_y, 1);



  while (1) {
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    
    box(system_window, 0, 0);
    box(process_window, 0, 0);
    
    wattron(system_window, COLOR_PAIR(1));
    DisplaySystem(system, system_window);
    wattroff(system_window, COLOR_PAIR(1));
    

    DisplayProcesses(system.Processes(), process_window, n);
    wrefresh(system_window);
    wrefresh(process_window);
    refresh();
    std::this_thread::sleep_for(std::chrono::seconds(1));

  }
  endwin();
}
