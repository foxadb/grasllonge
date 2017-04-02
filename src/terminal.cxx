/*
 * terminal.cxx
 *
 *  Created on: 26 mars 2017
 *      Author: samy
 */

#include "terminal.h"
#include "connection.h"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <readline/readline.h>

char* function_names[] = {
		"exit",
		"quit",
		"test",
		"displayTournament",
		"changeTournamentName",
		"printParticipants",
		"addPlayer",
		"addPlayerList",
		"deletePlayer",
		"resetPlayers",
		"startTournament",
		"pullMatches",
		"displayMatch",
		"searchMatch",
		"updateMatch",
		"pushMatches",
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

JSON::Array execute_function(const char* function_name, const std::string tournament,
		JSON::Object participants, JSON::Array matches)
{
	if (!strncmp(function_name, "displayTournament", 17))
	{
		displayTournament(getTournament(tournament));
	}

	else if (!strncmp(function_name, "changeTournamentName", 20))
	{
		char answer = 'n';
		std::cout << "Do you want to change the tournament's name ? (y/n): ";
		std::cin >> answer;
		if (answer == 'y')
		{
			std::cout << "Enter the new tournament name: ";

			std::string newName;
			std::cin >> newName;

			std::cout << "The new name will be: " << newName << std::endl;
			changeTournamentName(tournament, newName);
		}
	}

	else if (!strncmp(function_name, "printParticipants", 17))
	{
		printParticipants(participants);
	}

	else if (!strncmp(function_name, "addPlayerList", 13))
	{

		std::string pList;
		std::cout << "Enter players list name: ";
		std::cin >> pList;

		std::ifstream infile(pList.c_str());
		std::vector<std::string> pVect;
		std::string line;

		std::cout << "Reading players' list" << std::endl;
		while (infile >> line)
				pVect.push_back(line);

		std::cout << "Adding players to Challonge" << std::endl;
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
		deletePlayer(tournament, pName, participants);
	}

	else if (!strncmp(function_name, "resetPlayers", 12))
	{
		char answer = 'n';
		std::cout << "Are you sure to reset the entire player list ? (y/n): ";
		std::cin >> answer;
		if (answer == 'y') {
			std::cout << "Reseting the player list..." << std::endl;
			resetPlayers(tournament, participants);
			std::cout << "...completed";
		}
	}

	else if (!strncmp(function_name, "startTournament", 14))
	{
		char answer = 'n';
		std::cout << "Do you want to start " + tournament + " ? (y/n): ";
		std::cin >> answer;
		if (answer == 'y')
		{
			std::cout << "Starting " + tournament << std::endl;
			startTournament(tournament);
		}
	}

	else if (!strncmp(function_name, "pullMatches", 11))
	{
		std::cout << "Pulling matches infos from Challonge" << std::endl;
		matches = pullMatches(tournament);
	}

	else if (!strncmp(function_name, "searchMatch", 11))
	{
		std::string player_name;
		std::cout << "Enter the player name: ";
		std::cin >> player_name;

		int player_id = participants[player_name].as_int();
		searchMatch(matches, player_id, participants);
	}

	else if (!strncmp(function_name, "displayMatch", 12))
	{
		int matchNum;
		std::cout << "Enter the match number: ";
		std::cin >> matchNum;
		displayMatch(matches, matchNum, participants);
	}

	else if (!strncmp(function_name, "updateMatch", 10))
	{
		int matchNum;
		std::cout << "Enter the match number: ";
		std::cin >> matchNum;
		displayMatch(matches, matchNum, participants);

		std::string score;
		std::cout << "Enter the score: ";
		std::cin >> score;
		updateMatch(&matches, matchNum, score);
	}

	else if (!strncmp(function_name, "pushMatches", 11))
	{
		std::cout << "Pushing matches update to Challonge" << std::endl;
		pushMatches(tournament, &matches);
	}

	else
	{
		std::cout << "Function name does not exit" << std::endl;
	}

	return matches;

}
