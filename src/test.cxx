/*
 * test.cxx
 *
 *  Created on: 24 févr. 2017
 *      Author: samy
 */

#include "test.h"

void grasllongeTest(int num, std::string tournament, JSON::Object participants)
{
	std::string newName;
	std::string player;

	std::vector<std::string> list;
	std::string line;
	std::ifstream infile("../test/players_list.txt");

	JSON::Array matches = pullMatches(tournament);
	std::string url;
	std::string score;
	int winner_id;
	cpr::Response res;

	switch (num)
	{
	case 1:
		newName = "BITEEEEE";
		changeTournamentName(tournament, newName);

		player = "Matthieu";
		std::cout << "Adding " + player << std::endl;
		addPlayer(tournament, player);
		std::cout << getTournament(tournament) << std::endl;
		break;

	case 2:
		std::cout << "Changing tournament's name" << std::endl;
		newName = "Nouveau Nom";
		changeTournamentName(tournament, newName);

		std::cout << "Reading players' list" << std::endl;
		if (infile)
		{
			while (getline(infile, line))
			{
				list.push_back(line);
			}
		}
		std::cout << "Adding players..." << std::endl;
		addPlayerList(tournament, list);
		std::cout << "...completed";
		break;

	case 3:
		std::cout << "Delete Camus" << std::endl;
		deletePlayer(tournament, "Camus", participants);
		std::cout << "Reset the players' list" << std::endl;
		resetPlayers(tournament, participants);
		break;

	case 4:
		std::cout << "Submiting match result" << std::endl;
		score = "1-2";
		winner_id = 46015449;

		url = challongeUrl + "/gras7_test1/matches/71652578.json";
		res = cpr::Put(
				cpr::Url{url},
				cpr::Authentication{"dothraki", "uMhQBV4EbwHMuIpbHO0sZ0POyXop7VUbbd7FiDig"},
				cpr::Payload{{"match[scores_csv]", score}}
		);
		std::cout << parse_string(res.text) << std::endl;

		break;

	default:
		std::cout << "Test number does not exist" << std::endl;
	}
}
