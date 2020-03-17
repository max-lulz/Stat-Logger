//
// Created by aryesh on 02/02/20.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <utility>
#include "ProcessDataHandler.h"

ProcessDataHandler::ProcessDataHandler(std::string &identifier) {
    this->identifier = identifier;
}

ProcessDataHandler::ProcessDataHandler(std::string &identifier, std::string &outputFile){
    this->identifier = identifier;
    this->outputFile = outputFile;
}

float ProcessDataHandler::getCPUUsage() {
    std::ifstream in_cpu;
    in_cpu.open(cpuFileName);

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

    catch(const std::runtime_error &er){
        std::cerr << er.what() << "\n";
        return -1;
    }
}

void ProcessDataHandler::writeProcessData() {
    system(dataCMD.c_str());
}

void ProcessDataHandler::readProcessData(std::vector<std::pair <std::string, std::string>> &data) {
    std::ifstream in_ram;
    in_ram.open(outputFile);

    try{
        if(in_ram.is_open()){
            std::string procName, procMemUsage;
            while(in_ram >> procName && in_ram >> procMemUsage){
                if(procMemUsage == "Content"){                                  // for processes with whitespace in name
                    procName+=procMemUsage;
                    in_ram >> procMemUsage;
                }
                data.emplace_back(procName, procMemUsage);
            }

            in_ram.close();
        }

        else{
            throw std::runtime_error("Memory Usage Data could not be accessed");
        }
    }

    catch(const std::runtime_error &er) {
        std::cerr << er.what() << "\n";
    }
}

void ProcessDataHandler::jsonifyData(nlohmann::json &jsonData) {

    time_t init_time = time(nullptr);
    int id = -1;

    while((id++) < 10 && time(nullptr) - init_time <= 10){
        std::vector<std::pair <std::string, std::string>> dataPoints;

        writeProcessData();
        readProcessData(dataPoints);

        jsonData["Data Points"][id]["Team Identifier"] = identifier;
        jsonData["Data Points"][id]["CPU Usage"] = getCPUUsage();

        for(int procNum=0;procNum<dataPoints.size();procNum++){
            jsonData["Data Points"][id]["Memory Info"][procNum]["Process Name"] = dataPoints[procNum].first;
            jsonData["Data Points"][id]["Memory Info"][procNum]["Memory Usage"] = dataPoints[procNum].second;
        }
    }

    std::ofstream jsonOut("test.json");
    jsonOut << std::setw(4) << jsonData << "\n";
    jsonOut.close();
}
