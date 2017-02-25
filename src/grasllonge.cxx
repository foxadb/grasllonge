/*
 * =====================================================================================
 *
 *       Filename:  grasllonge.cxx
 *
 *    Description:	Main file containing the main while loop
 *
 *        Version:  1.0
 *       Revision:  none
 *       Compiler:  gcc
 *
 * =====================================================================================
 */

#include "connection.h"
#include "test.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <readline/readline.h>
#include <readline/history.h>

#include "../libjson/json.hh"

int main(int argc, char* argv[])
{
    const char *prompt = "grasllonge > ";

	//Configuration
	const std::string login = "dothraki";
	const std::string apikey = "uMhQBV4EbwHMuIpbHO0sZ0POyXop7VUbbd7FiDig";
	const std::string tournament = "gras8_test1";
	
	initialize_param_values(login, apikey);

    //Flush the history
    rl_clear_history();	

    //Initialize libcurl
    curl_global_init(CURL_GLOBAL_ALL);

    while(1)
    {
        char* line;
        line = readline(prompt);

        if (line==0 || !strncmp(line, "exit", 4))
        {
            std::cout << "\nBye :)" << std::endl;
            break;
        }

        ////////////////// LIGNES DE TEST
        if (!strncmp(line, "test", 4))
        {
        	int testNum;
        	std::cout << "Enter the test number :" << std::endl;
        	cin >> testNum;
        	grasllongeTest(testNum, login, apikey, tournament);
        }
        //////////////// FIN DES LIGNES DE TEST

        add_history(line);

        std::istringstream iss(line);
        std::vector<std::string> tokens;

        do
        {
            std::string sub;
            iss >> sub;
            tokens.push_back(sub);
        } while (iss);

        std::cout << "You idiot wrote: " << std::endl;
        for(size_t i=0; i<tokens.size(); ++i)
        {
            std::cout << tokens[i] << ' ';
        }
        std::cout << std::endl;
    }

    //Cleaning libcurl
    curl_global_cleanup();

    return EXIT_SUCCESS;
}
