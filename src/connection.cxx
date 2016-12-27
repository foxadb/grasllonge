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

static Object liste_participants;

static string user;
static string pass;
static string tname;

void initialize_param_values(string suser, string spass)
{
	user = suser;
	pass = spass;
}

void create_liste_participants(string tname)
{
	string url = challongeUrl + "/" + tname + "/participants.json";
	
	auto res = Get(
            Url{url}, 
            Authentication{user, pass}
            );

	Array temp = Array(parse_string(res.text));
	std::cout << "PENIS:\n" << temp << std::endl;

	for(auto it = temp.begin(); it != temp.end(); ++it)
	{
		liste_participants[std::string((*it)["participant"]["display_name"])] = (*it)["participant"]["id"];
	}
}

string getTournament(string tname)
{
    string url = challongeUrl + "/" + tname + ".json"; 
    
    auto res = Get(
            Url{url},
            Authentication{user, pass}
            );

    /*  JSON text string */
    return res.text;
}

void changeTournamentName(string tname, string newName)
{
    string url = challongeUrl + "/" + tname + ".json"; 

    auto res = Put(
            Url{url},
            Authentication{user, pass},
            Payload{{"tournament[name]", newName}}
            );
}

void addPlayer(string tname, string pname)
{
    string url = challongeUrl + "/" + tname + "/participants.json"; 

    auto res = Post(
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
    string url = challongeUrl + "/" + tname + "/participants/"
        + string(liste_participants[pname]) + ".json";

    cout << liste_participants[pname] << endl;
    cout << string(liste_participants[pname]) << endl;   
    cout << url << endl;

    auto res = Delete(Url{url});
}

void resetPlayers(string tname)
{
    auto it = liste_participants.begin();
    while (it != liste_participants.end())
    {
        deletePlayer(tname, (*it).first);
        it++;
    }
}
