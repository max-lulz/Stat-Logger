#include <bits/stdc++.h>
#include "json.hpp"
#include <curl/curl.h>
#include "ProcessDataHandler.h"

void postRequest(char *data_to_send, int &length){
	CURL *curl;
	CURLcode res;

	//curl_global_init(CURL_GLOBAL_ALL);

 	curl = curl_easy_init();
	if(curl){
		struct curl_slist *headers=nullptr;      // always init to NULL

		headers = curl_slist_append(headers, "Accept: application/json");
		headers = curl_slist_append(headers, "Content-Type: application/json");

		curl_easy_setopt(curl, CURLOPT_URL, "https://fathomless-thicket-66026.herokuapp.com/argo");
   		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data_to_send);
   		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, length);
   		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
 
		res = curl_easy_perform(curl);
		if(res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		
    		curl_easy_cleanup(curl);
  	}
	//curl_global_cleanup();
}

int main(){
    ProcessDataHandler ProcData();
	std::string Mem_data[10][2];
	time_t init_time = time(nullptr);

  	while(time(nullptr) - init_time <= 60)
  	{
  		time_t req_time = time(nullptr);
  		int id = 0;
  		nlohmann::json dataPoint;
  		while(time(nullptr) - req_time <= 10 && id < 10)
  		{
  			write_MemData();
  			read_MemData(Mem_data);

  			dataPoint["Data Points"][id]["Team Identifier"] = "Argo";
  			dataPoint["Data Points"][id]["CPU Usage"] = get_cpu_usage();

  			for(int proc=0;proc<10;proc++)
  			{
  				dataPoint["Data Points"][id]["Memory Info"][proc]["Process Name"] = Mem_data[proc][1];
  				dataPoint["Data Points"][id]["Memory Info"][proc]["Memory Usage"] = Mem_data[proc][0];
  			}

  			
  			id++;
  		}

  		std::ofstream o("test.json");
  		o << std::setw(4) << dataPoint << "\n";
  		std::ifstream in("test.json");
		
  		if(in.is_open())
		{
  			in.seekg(0, std::ifstream::end);
  		    	long length = in.tellg();
         		in.seekg(0, std::ifstream::beg);
			
            		char json_data[length];
            		in.read(json_data, length);
            		in.close();
			
            		postRequest(json_data, length);
		}

  		// add a sleep func or empty while loop 
  		while(time(nullptr) - req_time <= 10)
  		{}
  	}
  	return 0;  
}


