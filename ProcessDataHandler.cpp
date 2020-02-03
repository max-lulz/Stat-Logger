//
// Created by aryesh on 02/02/20.
//
#include <bits/stdc++.h>
#include "ProcessDataHandler.h"

ProcessDataHandler::ProcessDataHandler(std::string &identifier) {
    this->identifier = identifier;
}

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

    try{
        if(in_ram.is_open()){
            std::string procName, procMemUsage;
            while(in_ram >> procName && in_ram >> procMemUsage){
                if(procMemUsage == "Content"){
                    procName+=procMemUsage;
                    in_ram >> procMemUsage;
                }
                data.emplace_back(procName, procMemUsage);
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

void ProcessDataHandler::jsonifyData(nlohmann::json &dataPoint) {
    std::vector<std::pair <std::string, std::string>> dataPoints;
    //dataPoint["Data Points"]["Team Identifier"] = identifier;

    writeProcData();
    readProcData(dataPoints);

    time_t req_time = time(nullptr);

    int id = 0;
    while((++id) <= 10 && time(nullptr) - req_time <= 10){
        dataPoint["Data Points"][id]["CPU Usage"] = getCPUUsage();

        for(int procNum=0;procNum<dataPoints.size();procNum++){
            dataPoint["Data Points"][id]["Memory Info"][procNum]["Process Name"] = dataPoints[procNum].first;
            dataPoint["Data Points"][id]["Memory Info"][procNum]["Memory Usage"] = dataPoints[procNum].second;
        }
    }

    std::ofstream jsonOut("test.json");
    jsonOut << std::setw(4) << dataPoint << "\n";
    jsonOut.close();
}

