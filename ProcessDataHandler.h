//
// Created by aryesh on 02/02/20.
//
#include <bits/stdc++.h>
#include "json.hpp"

#ifndef STATLOGGER_PROCESSDATAHANDLER_H
#define STATLOGGER_PROCESSDATAHANDLER_H


#include <string>

class ProcessDataHandler {
    private:
        std::string dataFileName = "ProcData.txt";
        std::string dataCMD = R"(ps axco cmd,%mem --sort=-%mem | head -11 | tail -10 > ProcData.txt)";
        std::string cpuFileName = "/proc/stat";
        std::string identifier;

    public:
        ProcessDataHandler(std::string &identifier);

        void writeProcData();
        void readProcData(std::vector<std::pair <std::string, std::string>> &data);
        float getCPUUsage();
        void jsonifyData(nlohmann::json &dataPoint);
};

#endif //STATLOGGER_PROCESSDATAHANDLER_H
