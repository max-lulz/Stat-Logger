#include "ProcessDataHandler/ProcessDataHandler.h"
#include <cpr/cpr.h>
#include <iostream>
// Need to add a method for posting requests
// Need to replace time with chrono

int main(){
    std::string identifier = "AryeshKoya";
    ProcessDataHandler ProcData(identifier);

    time_t init_time = time(nullptr);

    int i=0;
	while(time(nullptr) - init_time <= 60){
  		nlohmann::json dataPoint;
  		ProcData.jsonifyData(dataPoint);
  		std::cout << "Writing Data Point: " << (i++) << "\n";
  	}

  	return 0;  
}


