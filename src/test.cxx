/*
 * test.cxx
 *
 *  Created on: 24 févr. 2017
 *      Author: samy
 */

#include "test.h"

void grasllongeTest(int num, string login, string apikey, string tournament)
{
	string newName;
	string player;

	vector<string> liste;
	string line;
	ifstream infile("liste_joueurs.txt");


	switch (num)
	{
	case 1:
		newName = "BITEEEEE";
		changeTournamentName(tournament, newName);

		player = "Matthieu";
		cout << "Ajout de " + player << endl;
		addPlayer(tournament, player);
		cout << getTournament(tournament) << endl;
		break;

	case 2:
		cout << "Changement de nom" << endl;
		newName = "Nouveau Nom";
		changeTournamentName(tournament, newName);

		cout << "Lecture de la liste des joueurs" << endl;
		if (infile)
		{
			while (getline(infile, line))
			{
				liste.push_back(line);
			}
		}
		cout << "Ajout des joueurs" << endl;
		addPlayerList(tournament, liste);
		break;

	case 3:
		create_liste_participants(tournament);
		break;

	case 4:
		deletePlayer(tournament, "Camus");
		resetPlayers(tournament);
		break;
	}
}
