/*
 * =====================================================================================
 *
 *       Filename:  connection.cxx
 *
 *    Description:  Fichier contenant les fichiers d'interaction avec Challonge
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

string getTournament(string user, string pass, string name)
{
    string url = challongeUrl + "/" + name + ".json"; 
    
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

    auto res = cpr::Post(
            cpr::Url{url},
            cpr::Authentication{user, pass},
            cpr::Payload{{"participant[name]", pname}}
            );
}
