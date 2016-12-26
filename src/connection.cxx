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

static const string challongeUrl = "https://api.challonge.com/v1/tournaments";

string getTournament(string user, string pass, string tname)
{
    string url = challongeUrl + "/" + tname + ".json"; 

    auto res = Get(
            Url{url},
            Authentication{user, pass}
            );

    /*  JSON text string */
    return res.text;
}

void changeTournamentName(string user, string pass, string tname, string newName)
{
    string url = challongeUrl + "/" + tname + ".json"; 

    auto res = Put(
            Url{url},
            Authentication{user, pass},
            Payload{{"tournament[name]", newName}}
            );
}

void addPlayer(string user, string pass, string tname, string pname)
{
    string url = challongeUrl + "/" + tname + "/participants.json"; 

    auto res = Post(
            Url{url},
            Authentication{user, pass},
            Payload{{"participant[name]", pname}}
            );
}

void addPlayerList(string user, string pass, string tname, std::vector<string> list)
{
	for(size_t i=0; i<list.size(); ++i)
		addPlayer(user, pass, tname, list[i]);
}
