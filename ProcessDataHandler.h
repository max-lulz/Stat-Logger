//
// Created by aryesh on 02/02/20.
//
#include <bits/stdc++.h>

#ifndef STATLOGGER_PROCESSDATAHANDLER_H
#define STATLOGGER_PROCESSDATAHANDLER_H


#include <string>

class ProcessDataHandler {
    public:
       //ProcessDataHandler();

        std::string dataFileName = "ProcData.txt";
        std::string dataCMD = R"(ps xco cmd,%mem --sort=-%mem | head -11 | tail -10 > ProcData.txt)";
        std::string cpuFileName = "/proc/stat";

        void writeProcData();
        void readProcData(std::vector<std::pair <std::string, std::string>> &data);
        float getCPUUsage();
};

#endif //STATLOGGER_PROCESSDATAHANDLER_H
