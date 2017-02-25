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

using namespace std;
using namespace cpr;
using namespace JSON;

static const std::string challongeUrl = "https://api.challonge.com/v1/tournaments";

static JSON::Object liste_participants;

static std::string user;
static std::string pass;
static std::string tname;

void initialize_param_values(string suser, string spass)
{
	user = suser;
	pass = spass;
}

void create_liste_participants(string tname)
{
	std::string url = challongeUrl + "/" + tname + "/participants.json";
	
	auto res = cpr::Get(
            Url{url}, 
            Authentication{user, pass}
            );

	JSON::Array temp = JSON::Array(parse_string(res.text));
	std::cout << "PENIS:\n" << temp << std::endl;

	for(auto it = temp.begin(); it != temp.end(); ++it)
	{
		liste_participants[std::string((*it)["participant"]["display_name"])] = (*it)["participant"]["id"];
	}

	//Print liste_participants
	for(auto it = liste_participants.begin(); it != liste_participants.end(); ++it)
	{
		std::cout << "Le nom " << (*it).first << " a l'ID " << (*it).second << std::endl;
	}
}

string getTournament(string tname)
{
    std::string url = challongeUrl + "/" + tname + ".json";
    
    auto res = cpr::Get(
            Url{url},
            Authentication{user, pass}
            );

    /*  JSON text string */
    return res.text;
}

void changeTournamentName(string tname, string newName)
{
    std::string url = challongeUrl + "/" + tname + ".json";

    auto res = cpr::Put(
            Url{url},
            Authentication{user, pass},
            Payload{{"tournament[name]", newName}}
            );
}

void addPlayer(string tname, string pname)
{
    std::string url = challongeUrl + "/" + tname + "/participants.json";

    auto res = cpr::Post(
            Url{url},
            Authentication{user, pass},
            Payload{{"participant[name]", pname}}
            );
}

void addPlayerList(string tname, vector<string> list)
{
	for(size_t i=0; i<list.size(); ++i)
		addPlayer(tname, list[i]);
}

void deletePlayer(string tname, string pname)
{
	long id = (long long int) (liste_participants[pname]);
    std::string url = challongeUrl + "/" + tname + "/participants/" + to_string(id) + ".json";

    auto res = cpr::Delete(Url{url}, Authentication{user, pass});
}

void resetPlayers(string tname)
{
    for(auto it = liste_participants.begin(); it != liste_participants.end(); ++it)
    {
        deletePlayer(tname, (*it).first);
    }
}
