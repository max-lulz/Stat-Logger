//
// Created by aryesh on 02/02/20.
//

#ifndef STATLOGGER_PROCESSDATAHANDLER_H
#define STATLOGGER_PROCESSDATAHANDLER_H


#include <string>

class ProcessDataHandler {
    private:
        static std::string fileName;

    public:
        static void writeProcData();
        static void readProcData(std::string &data);
        static float getCPUUsage();
};


#endif //STATLOGGER_PROCESSDATAHANDLER_H
