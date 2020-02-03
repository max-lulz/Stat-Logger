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
    std::string iden = "Aryesh";
    ProcessDataHandler ProcData(iden);

	time_t init_time = time(nullptr);

	int num=0;
  	while(time(nullptr) - init_time <= 60){
  		nlohmann::json dataPoint;
  		ProcData.jsonifyData(dataPoint);
        num+=10;

  		/*std::ifstream in("test.json");
		
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
  		{}*/
  	}
  	std::cout << num;
  	return 0;  
}


