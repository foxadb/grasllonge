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
#include "terminal.h"
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
    //Flush the history
    rl_clear_history();

    //Initialize libcurl
    curl_global_init(CURL_GLOBAL_ALL);

    const char *prompt = "grasllonge > ";

	//Configuration
	std::string login;
	std::string api_key;
	
	// Read login
	std::cout << "Reading login" << std::endl;
	std::ifstream infile("../login.txt");
	infile >> login >> api_key;
	initialize_param_values(login, api_key);

	// Tournament selection
	tournamentSelect:

	std::cout << "Print all tournaments infos ? (y/n): ";
	char answer = 'n';
	std::cin >> answer;
	if (answer == 'y')
	{
		std::cout << "Reaching tournaments database" << std::endl << std::endl;
		const JSON::Array tournamentsArr = pullTournaments();
		printTournaments(tournamentsArr);
	}

	std::string tournament;
	std::cout << "Enter the tournament's url: ";
	std::cin >> tournament;

	// Display tournament infos
	displayTournament(getTournament(tournament));

	JSON::Object participants;
	JSON::Array matches;

    while(1)
    {
    	participants = create_participants(tournament);

    	rl_attempted_completion_function = function_name_completion;

        char* line;
        line = readline(prompt);

        if (line==0 || !strncmp(line, "exit", 4))
        {
            std::cout << "\nBye :)" << std::endl;
            break;
        }

        else if (!strncmp(line, "quit", 4))
        {
            std::cout << "Disconnecting from " + tournament << std::endl;
            goto tournamentSelect;
            break;
        }

        ////////////////// TEST LINES
        else if (!strncmp(line, "test", 4))
        {
        	int testNum;
        	std::cout << "Enter the test number: ";
        	std::cin >> testNum;
        	grasllongeTest(testNum, tournament, participants);
        }
        //////////////// ENDING OF TEST LINES

        else matches = execute_function(line, tournament, participants, matches);

        add_history(line);

        std::istringstream iss(line);
        std::vector<std::string> tokens;

        do
        {
            std::string sub;
            iss >> sub;
            tokens.push_back(sub);
        } while (iss);

        std::cout << std::endl;
    }

    //Cleaning libcurl
    curl_global_cleanup();

    return EXIT_SUCCESS;
}
