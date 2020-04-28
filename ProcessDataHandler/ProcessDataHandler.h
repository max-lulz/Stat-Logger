//
// Created by aryesh on 02/02/20.
//

#include "nlohmann/json.hpp"

#ifndef STATLOGGER_PROCESSDATAHANDLER_H
#define STATLOGGER_PROCESSDATAHANDLER_H

class ProcessDataHandler {
    private:
        std::string dataFile = "ProcData.txt";
        std::string dataCMD = R"(ps axco cmd,%mem --sort=-%mem | head -11 | tail -10 > ProcData.txt)";
        std::string cpuFileName = "/proc/stat";
        std::string identifier;
        std::string outputFile = "ProcOutput.json";

    public:
        explicit ProcessDataHandler(std::string &identifier);
        ProcessDataHandler(std::string &identifier, std::string &outputFile);

        void writeProcessData();
        void readProcessData(std::vector<std::pair <std::string, std::string>> &data);
        float getCPUUsage();
        void jsonifyData(nlohmann::json &jsonData);
};

#endif //STATLOGGER_PROCESSDATAHANDLER_H
