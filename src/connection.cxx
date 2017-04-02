/*
 * =====================================================================================
 *
 *       Filename:  connection.cxx
 *
 *    Description:  Interaction functions with Challonge servers
 *
 *        Version:  1.0
 *       Revision:  none
 *       Compiler:  gcc
 *
 * =====================================================================================
 */

#include "connection.h"

void initialize_param_values(std::string suser, std::string spass)
{
	user = suser;
	pass = spass;
}

JSON::Array pullTournaments()
{
	std::string url = challongeUrl + ".json";

	auto res = cpr::Get(
            cpr::Url{url},
            cpr::Authentication{user, pass},
			cpr::Parameters{{"state", "underway"}}
            );

	JSON::Array temp = JSON::Array(parse_string(res.text));

	JSON::Array tournamentsArr;

	for(auto it = temp.begin(); it != temp.end(); ++it)
	{
		JSON::Object t;
		t["id"] = (*it)["tournament"]["id"];
		t["name"] = (*it)["tournament"]["name"];
		t["url"] = (*it)["tournament"]["url"];
		t["participants_count"] = (*it)["tournament"]["participants_count"];
		t["state"] = (*it)["tournament"]["state"];

		tournamentsArr.push_back(t);
	}

	return tournamentsArr;
}

void printTournaments(JSON::Array tournaments)
{
	for(auto it = tournaments.begin(); it != tournaments.end(); ++it)
	{
		std::cout << "ID: " << (*it)["id"] << std::endl;
		std::cout << "Name: " << (*it)["name"] << std::endl;
		std::cout << "Url: " << (*it)["url"] << std::endl;
		std::cout << "Participants' number: " << (*it)["participants_count"] << std::endl;
		std::cout << "State: " << (*it)["state"] << std::endl;
		std::cout << std::endl;
	}
}

JSON::Object create_participants(const std::string tName)
{
	JSON::Object participants;
	std::string url = challongeUrl + "/" + tName + "/participants.json";

	auto res = cpr::Get(
            cpr::Url{url},
            cpr::Authentication{user, pass}
            );

    JSON::Array temp = JSON::Array(parse_string(res.text));

	for(auto it = temp.begin(); it != temp.end(); ++it)
	{
		participants[std::string((*it)["participant"]["display_name"].as_string())] =
				(*it)["participant"]["id"].as_int();
	}

	return participants;

}

void printParticipants(JSON::Object participants)
{
	for(auto it = participants.begin(); it != participants.end(); ++it)
	{
		std::cout << "Name: " << (*it).first << " ID: " << (*it).second << std::endl;
    }
}

std::string getTournament(const std::string tName)
{
    std::string url = challongeUrl + "/" + tName + ".json";
    
    auto res = cpr::Get(
            cpr::Url{url},
            cpr::Authentication{user, pass}
            );

    /*  JSON text string */
    return res.text;
}

void displayTournament(const std::string tInfos)
{
	JSON::Value infos = parse_string(tInfos);

	std::cout << std::endl;
	std::cout << "=== Tournament ID: " << infos["tournament"]["id"] << " ===" << std::endl;
	std::cout << "Name: " << infos["tournament"]["name"] << std::endl;
	std::cout << "Url: " << infos["tournament"]["url"] << std::endl;
	std::cout << "Game: " << infos["tournament"]["game_name"] << std::endl;
	std::cout << "Type: " << infos["tournament"]["tournament_type"] << std::endl;
	std::cout << "Participants count: " << infos["tournament"]["participants_count"] << std::endl;
	std::cout << std::endl;
}

void changeTournamentName(const std::string tName, std::string newName)
{
    std::string url = challongeUrl + "/" + tName + ".json";

    auto res = cpr::Put(
            cpr::Url{url},
            cpr::Authentication{user, pass},
            cpr::Payload{{"tournament[name]", newName}}
            );
}

void addPlayer(const std::string tName, std::string pName)
{
    std::string url = challongeUrl + "/" + tName + "/participants.json";

    auto res = cpr::Post(
            cpr::Url{url},
            cpr::Authentication{user, pass},
            cpr::Payload{{"participant[name]", pName}}
            );
}

void addPlayerList(const std::string tName, std::vector<std::string> list)
{
	for(size_t i=0; i<list.size(); ++i)
		addPlayer(tName, list[i]);
}

void deletePlayer(const std::string tName, std::string pName, JSON::Object participants)
{
	long id = (long long int) (participants[pName]);
    std::string url = challongeUrl + "/" + tName + "/participants/"
    		+ std::to_string(id) + ".json";

    auto res = cpr::Delete(cpr::Url{url}, cpr::Authentication{user, pass});
}

void resetPlayers(const std::string tName, JSON::Object participants)
{
    for(auto it = participants.begin(); it != participants.end(); ++it)
    {
        deletePlayer(tName, (*it).first, participants);
    }
}

void startTournament(const std::string tName)
{
    std::string url = challongeUrl + "/" + tName + "/start.json";

    auto res = cpr::Post(
            cpr::Url{url},
            cpr::Authentication{user, pass},
			cpr::Payload{{"include_participants", 1},
            	{"include_matches", 1}}
            );
}

JSON::Array pullMatches(const std::string tName)
{
    std::string url = challongeUrl + "/" + tName + "/matches.json";

    auto res = cpr::Get(
            cpr::Url{url},
            cpr::Authentication{user, pass}
            );

	JSON::Array temp = JSON::Array(parse_string(res.text));
	JSON::Array matches;

	for(auto it = temp.begin(); it != temp.end(); ++it)
	{
		if ((*it)["match"]["state"].as_string() == "open")
		{
			JSON::Object match;
			match["id"] = (*it)["match"]["id"];
			match["round"] = (*it)["match"]["round"];
			match["player1_id"] = (*it)["match"]["player1_id"];
			match["player2_id"] = (*it)["match"]["player2_id"];
			match["score"] = (*it)["match"]["scores_csv"];
			match["winner_id"] = (*it)["match"]["winner_id"];
			match["updated"] = false;

			matches.push_back(match);
		}
	}

	return matches;
}

void searchMatch(JSON::Array matches, int player_id, JSON::Object participants)
{
	int matchNum = 0;
	for(auto it = matches.begin(); it != matches.end(); ++it)
	{
		if ((*it)["player1_id"].as_int() == player_id ||
				(*it)["player2_id"].as_int() == player_id)
			displayMatch(matches, matchNum, participants);

		++matchNum;
	}
}

void displayMatch(JSON::Array matches, int matchNum, JSON::Object participants)
{
	JSON::Value match = matches[matchNum];
	std::cout << "======\tMatch " << matchNum;
	std::cout << "\t\tID: " << match["id"];
	std::cout << "\tRound: " << match["round"] << "\t======"<< std::endl;

	std::string name1 = player_id_to_name(match["player1_id"].as_int(), participants);
	std::string name2 = player_id_to_name(match["player2_id"].as_int(), participants);
	std::cout << name1 << "\tvs\t" << name2 << std::endl;

	std::cout << "Score: " + std::string(match["score"]) << std::endl;

	std::string winner_name = player_id_to_name(match["winner_id"].as_int(), participants);
	std::cout << "Winner: " << winner_name << std::endl;

	std::cout << "Updated: " << match["updated"].as_bool() << std::endl;

	std::cout << std::endl;

}

void updateMatch(JSON::Array* matches, int matchNum, std::string score)
{
	(*matches)[matchNum]["score"] = score;

	if (score[0] > score[2])
	{
		(*matches)[matchNum]["winner_id"] =
				(*matches)[matchNum]["player1_id"].as_int();
	}
	else
	{
		(*matches)[matchNum]["winner_id"] =
				(*matches)[matchNum]["player2_id"].as_int();
	}

	(*matches)[matchNum]["updated"] = true;
}

void pushMatches(const std::string tName, JSON::Array* matches)
{
	for(auto it = (*matches).begin(); it != (*matches).end(); ++it)
	{
		if ((*it)["updated"])
		{
			std::string url = challongeUrl + "/" + tName + "/matches/"
					+ std::to_string((*it)["id"].as_int()) + ".json";

			std::string score = (*it)["score"].as_string();
			std::string winner_id = std::to_string((*it)["winner_id"].as_int());

			auto res = cpr::Put(
					cpr::Url{url},
					cpr::Authentication{user, pass},
					cpr::Payload{{"match[scores_csv]", score},
						{"match[winner_id]", winner_id}}
			);

			(*it)["updated"] = false;
		}
	}
}

std::string player_id_to_name(int id, JSON::Object participants)
{
	std::string name = "";
	auto it = participants.begin();
	while (it != participants.end() && (*it).second.as_int() != id)
	{
		++it;
	}

	if ((*it).second.as_int() == id)
		name = (*it).first;
	return name;
}

int match_id_to_num(int id, JSON::Array matches)
{
	int num = 0;
	while (num < matches.size() && matches[num]["id"].as_int() != id)
	{
		++num;
	}

	return num;
}
