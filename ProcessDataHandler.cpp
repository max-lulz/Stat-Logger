//
// Created by aryesh on 02/02/20.
//
#include <bits/stdc++.h>
#include "ProcessDataHandler.h"

float ProcessDataHandler::getCPUUsage() {
    std::ifstream in_cpu("/proc/stat");
    char cpu[3];
    double ticks[8], total_time=0.0, idle_time=0.0;
    in_cpu >> cpu;
    float cpu_usage;

    if(in_cpu.is_open()){
        for(double &tick : ticks){
            in_cpu >> tick;
            total_time += tick;
        }

        idle_time = ticks[3] + ticks[4];
        cpu_usage = (float)(((total_time - idle_time)*100)/(total_time));

        return cpu_usage;
    }

    else{
        std::cout << "CPU Usage data could not be accessed" << "\n";
        return -1;
    }
}

void ProcessDataHandler::writeProcData() {
    std::string cmd = R"(ps xco pid,cmd,%mem,%cpu --sort=-%mem | head -11 | tail -10 > ProcData.txt)";
    system(cmd.c_str());
}

void ProcessDataHandler::readProcData(std::string &data) {
    std::ifstream in_ram("ram_data.txt");
    std::string line;

    if(in_ram.is_open()){
        int i=0;
        while(in_ram >> line){
            data[i/2][i%2] = line;
            i++;
        }
    }

    else
        std::cout << "Memory Usage Data could not be accessed";

    in_ram.close();
}
