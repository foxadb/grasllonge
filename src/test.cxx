/*
 * test.cxx
 *
 *  Created on: 24 févr. 2017
 *      Author: samy
 */

#include "test.h"

void grasllongeTest(int num, string tournament)
{
	string newName;
	string player;

	vector<string> list;
	string line;
	ifstream infile("../test/players_list.txt");

	switch (num)
	{
	case 1:
		newName = "BITEEEEE";
		changeTournamentName(tournament, newName);

		player = "Matthieu";
		cout << "Adding " + player << endl;
		addPlayer(tournament, player);
		cout << getTournament(tournament) << endl;
		break;

	case 2:
		cout << "Changing tournament's name" << endl;
		newName = "Nouveau Nom";
		changeTournamentName(tournament, newName);

		cout << "Reading players' list" << endl;
		if (infile)
		{
			while (getline(infile, line))
			{
				list.push_back(line);
			}
		}
		cout << "Adding players..." << endl;
		addPlayerList(tournament, list);
		cout << "...completed";
		break;

	case 3:
		create_participants_list(tournament);
		break;

	case 4:
		cout << "Delete Camus" << endl;
		deletePlayer(tournament, "Camus");
		cout << "Reset the players' list" << endl;
		resetPlayers(tournament);
		break;

	default:
		cout << "Test number does not exist" << endl;
	}
}
