#include <bits/stdc++.h>
#include <string>
#include <fstream>
#include "json.hpp"
#include <curl/curl.h>
#include <time.h>

using namespace std;
using json = nlohmann::json;

void postRequest(json data_to_send)     // make a POST request
{
	CURL *curl;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_ALL);

 	curl = curl_easy_init();
	if(curl) 
	{
		struct curl_slist *headers=NULL;      // always init to NULL

		headers = curl_slist_append(headers, "Accept: application/json");
		headers = curl_slist_append(headers, "Content-Type: application/json");

    		curl_easy_setopt(curl, CURLOPT_URL, "https://fathomless-thicket-66026.herokuapp.com/argo");
   		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data_to_send.dump().c_str());
   		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
 
		res = curl_easy_perform(curl);
		if(res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		
    		curl_easy_cleanup(curl);
  	}
	
	curl_global_cleanup();
}

string read_ram_data()		          // read from file and store ram_usage in a string			
{
	ifstream in_ram("ram_data.txt");
	string data, line;

	if(in_ram.is_open())
	{
		while(getline(in_ram,line))  // add ram usage by process linewise
		{ 
			data += line;      
			data += '\n';
		}

	}
	in_ram.close();

	return data;
}

void get_ram_data()                  // get name and %usage of top 10 memory using processes and store in a file
{
	string cmd = R"(ps axo rss,comm,pid \
				| awk '{ proc_list[$2] += $1; } END \
				{ for (proc in proc_list) { printf("%d\t%s\n", proc_list[proc],proc); }}' \
				| sort -n | tail -n 10 | sort -rn \
				| awk '{$1/=80204.16;printf "%.2f%%\t",$1}{print $2}' > ram_data.txt)";

	system(cmd.c_str());
}

int main()
{                   
  
  	time_t init_time = time(NULL);

  	while(time(NULL) - init_time <= 60)
  	{
  		time_t req_time = time(NULL);
  		while(time(NULL) - req_time <= 10)
  		{
  			get_ram_data();
  			json data_to_send;
  			data_to_send["Team name"] = "Argo";
  			data_to_send["ram_usage"] = read_ram_data();
  			postRequest(data_to_send);
  			//cout <<  << endl;
  		}
  	}
	
  	return 0;  
}


