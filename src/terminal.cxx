/*
 * terminal.cxx
 *
 *  Created on: 26 mars 2017
 *      Author: samy
 */

#include "terminal.h"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <readline/readline.h>

char *function_names[] = {
		"exit",
		"test",
		"changeTournamentName",
		"addPlayer",
		"addPlayerList",
		"deletePlayer",
		"resetPlayers",
		nullptr
};

char** function_name_completion(const char* text, int start, int end)
{
	rl_attempted_completion_over = 1;
	return rl_completion_matches(text, function_name_generator);
}

char* function_name_generator(const char* text, int state)
{
	static int list_index, len;
	char *name;

	if (!state) {
		list_index = 0;
		len = strlen(text);
	}

	while ((name = function_names[list_index++])) {
		if (strncmp(name, text, len) == 0) {
			return strdup(name);
		}
	}

	return nullptr;
}

void execute_function(const char* function_name, const std::string tournament)
{
	if (!strncmp(function_name, "changeTournamentName", 20))
	{
		std::string newName;
		std::cout << "Enter the new tournament name: ";
		std::cin >> newName;
		changeTournamentName(tournament, newName);
	}

	else if (!strncmp(function_name, "addPlayerList", 13))
	{

		char* pList;
		std::cout << "Enter players list name: ";
		std::cin >> pList;
		std::ifstream infile(pList);

		std::vector<std::string> pVect;
		std::string line;

		std::cout << "Reading players' list" << std::endl;
		if (infile)
		{
			while (getline(infile, line))
			{
				pVect.push_back(line);
			}
		}
		addPlayerList(tournament, pVect);
	}

	else if (!strncmp(function_name, "addPlayer", 9))
	{
		std::string pName;
		std::cout << "Enter a player name to add: ";
		std::cin >> pName;
		addPlayer(tournament, pName);
	}

	else if (!strncmp(function_name, "deletePlayer", 12))
	{
		std::string pName;
		std::cout << "Enter player name to delete: ";
		std::cin >> pName;
		deletePlayer(tournament, pName);
	}

	else if (!strncmp(function_name, "resetPlayers", 12))
	{
		char answer;
		std::cout << "Are you sure to reset the entire player list ? (y/n): ";
		std::cin >> answer;
		if (answer == 'y') {
			std::cout << "Reseting the player list..." << std::endl;
			resetPlayers(tournament);
			std::cout << "...completed";
		}
	}

	else
	{
		std::cout << "Function name does not exit" << std::endl;
	}
}
