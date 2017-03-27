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

static const std::string challongeUrl = "https://api.challonge.com/v1/tournaments";

static std::string user;
static std::string pass;

void initialize_param_values(std::string suser, std::string spass)
{
	user = suser;
	pass = spass;
}

JSON::Object create_participants(std::string tName)
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

std::string getTournament(std::string tName)
{
    std::string url = challongeUrl + "/" + tName + ".json";
    
    auto res = cpr::Get(
            cpr::Url{url},
            cpr::Authentication{user, pass}
            );

    /*  JSON text string */
    return res.text;
}

void changeTournamentName(std::string tName, std::string newName)
{
    std::string url = challongeUrl + "/" + tName + ".json";

    auto res = cpr::Put(
            cpr::Url{url},
            cpr::Authentication{user, pass},
            cpr::Payload{{"tournament[name]", newName}}
            );
}

void addPlayer(std::string tName, std::string pName)
{
    std::string url = challongeUrl + "/" + tName + "/participants.json";

    auto res = cpr::Post(
            cpr::Url{url},
            cpr::Authentication{user, pass},
            cpr::Payload{{"participant[name]", pName}}
            );
}

void addPlayerList(std::string tName, std::vector<std::string> list)
{
	for(size_t i=0; i<list.size(); ++i)
		addPlayer(tName, list[i]);
}

void deletePlayer(std::string tName, std::string pName, JSON::Object participants)
{
	long id = (long long int) (participants[pName]);
    std::string url = challongeUrl + "/" + tName + "/participants/"
    		+ std::to_string(id) + ".json";

    auto res = cpr::Delete(cpr::Url{url}, cpr::Authentication{user, pass});
}

void resetPlayers(std::string tName, JSON::Object participants)
{
    for(auto it = participants.begin(); it != participants.end(); ++it)
    {
        deletePlayer(tName, (*it).first, participants);
    }
}

JSON::Array pullMatches(std::string tName)
{
    std::string url = challongeUrl + "/" + tName + "/matches.json";

    auto res = cpr::Get(
            cpr::Url{url},
            cpr::Authentication{user, pass}
            );

	JSON::Array temp = JSON::Array(parse_string(res.text));
	JSON::Array matches;

	int index = 0;

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

			//displayMatch(matches, index);
			++index;
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
	std::cout << "Match " << matchNum << "\tID: " << match["id"];
	std::cout << "\tRound: " << match["round"] << std::endl;

	std::string name1 = player_id_to_name(match["player1_id"].as_int(), participants);
	std::string name2 = player_id_to_name(match["player2_id"].as_int(), participants);
	std::cout << name1 + " vs " + name2 << std::endl;

	std::cout << "Score: " + std::string(match["score"]) << std::endl;
	std::cout << "Updated: " << match["updated"].as_bool() << std::endl;

	std::cout << std::endl;

}

void updateMatch(JSON::Array* matches, int matchNum, std::string score)
{
	(*matches)[matchNum]["score"] = score;

	if (score[0] > score[2])
	{
		(*matches)[matchNum]["winner_id"] =
				(*matches)[matchNum]["player1_id"];
	}
	else
	{
		(*matches)[matchNum]["winner_id"] =
				(*matches)[matchNum]["player2_id"];
	}

	(*matches)[matchNum]["updated"] = true;
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

void pushMatches(std::string tName, JSON::Array* matches)
{
	for(auto it = (*matches).begin(); it != (*matches).end(); ++it)
	{
		if ((*it)["updated"])
		{
			std::string url = challongeUrl + "/" + tName + "/matches/"
					+ std::string((*it)["id"]) + ".json";
		    auto res = cpr::Put(
		            cpr::Url{url},
		            cpr::Authentication{user, pass},
		            cpr::Payload{{"match[scores_csv]", (*it)["score"].as_string()},
		            	{"match[winner_id]", (*it)["winner_id"].as_int()}}
		            );
		    (*it)["updated"] = false;
		}
	}
}
