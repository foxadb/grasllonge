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

static JSON::Object participants_list;

static std::string user;
static std::string pass;
static std::string tname;

void initialize_param_values(string suser, string spass)
{
	user = suser;
	pass = spass;
}

void create_participants_list(string tname)
{
	std::string url = challongeUrl + "/" + tname + "/participants.json";
	
	auto res = cpr::Get(
            cpr::Url{url},
            cpr::Authentication{user, pass}
            );

	JSON::Array temp = JSON::Array(parse_string(res.text));

	for(auto it = temp.begin(); it != temp.end(); ++it)
	{
		participants_list[std::string((*it)["participant"]["display_name"])] = (*it)["participant"]["id"];
	}

}

string getTournament(string tname)
{
    std::string url = challongeUrl + "/" + tname + ".json";
    
    auto res = cpr::Get(
            cpr::Url{url},
            cpr::Authentication{user, pass}
            );

    /*  JSON text string */
    return res.text;
}

void changeTournamentName(string tname, string newName)
{
    std::string url = challongeUrl + "/" + tname + ".json";

    auto res = cpr::Put(
            cpr::Url{url},
            cpr::Authentication{user, pass},
            cpr::Payload{{"tournament[name]", newName}}
            );
}

void addPlayer(string tname, string pname)
{
    std::string url = challongeUrl + "/" + tname + "/participants.json";

    auto res = cpr::Post(
            cpr::Url{url},
            cpr::Authentication{user, pass},
            cpr::Payload{{"participant[name]", pname}}
            );
}

void addPlayerList(string tname, vector<string> list)
{
	for(size_t i=0; i<list.size(); ++i)
		addPlayer(tname, list[i]);
}

void deletePlayer(string tname, string pname)
{
	long id = (long long int) (participants_list[pname]);
    std::string url = challongeUrl + "/" + tname + "/participants/" + to_string(id) + ".json";

    auto res = cpr::Delete(cpr::Url{url}, cpr::Authentication{user, pass});
}

void resetPlayers(string tname)
{
    for(auto it = participants_list.begin(); it != participants_list.end(); ++it)
    {
        deletePlayer(tname, (*it).first);
    }
}
