//
// Created by aryesh on 02/02/20.
//
#include <bits/stdc++.h>
#include "ProcessDataHandler.h"

float ProcessDataHandler::getCPUUsage() {
    std::ifstream in_cpu(cpuFileName);
    char cpu[3];
    double ticks[8], total_time=0.0, idle_time;
    in_cpu >> cpu;
    float cpu_usage;

    try{
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
            throw std::runtime_error("CPU Usage data could not be accessed");
        }
    }

    catch(const std::exception &er){
        std::cerr << er.what() << "\n";
    }

    return -1;
}

void ProcessDataHandler::writeProcData() {
    system(dataCMD.c_str());
}

void ProcessDataHandler::readProcData(std::vector<std::pair <std::string, std::string>> &data) {
    std::ifstream in_ram(dataFileName);
    std::string line;

    try{
        if(in_ram.is_open()){
            std::string a,b;
            while(in_ram >> a && in_ram >> b){
                if(b == "Content"){
                    a+=b;
                    in_ram >> b;
                }

                data.emplace_back(a, b);
            }
        }

        else{
            throw std::runtime_error("Memory Usage Data could not be accessed");
        }
    }

    catch(const std::exception &er) {
        std::cerr << er.what() << "\n";
    }

    in_ram.close();
}

