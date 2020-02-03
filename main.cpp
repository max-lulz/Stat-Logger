#include <bits/stdc++.h>
#include "json.hpp"
#include <curl/curl.h>
#include "ProcessDataHandler.h"
#include <cpr/cpr.h>

// Need to add a method for posting requests

int main(){
    std::string identifier = "AryeshKoya";
    ProcessDataHandler ProcData(identifier);

	time_t init_time = time(nullptr);

  	while(time(nullptr) - init_time <= 60){
  		nlohmann::json dataPoint;
  		ProcData.jsonifyData(dataPoint);
  	}

  	return 0;  
}


