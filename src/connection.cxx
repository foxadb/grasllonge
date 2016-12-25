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
using namespace JSON;

static const string challongeUrl = "https://api.challonge.com/v1/tournaments";

void getTournament(string user, string pass, string name)
{
    string url = challongeUrl + "/" + name + ".json"; 
    
    auto res = cpr::Get(
            cpr::Url{url},
            cpr::Authentication{user, pass}
            );

    /*  JSON text string */
    res.text;

    cout << res.text << endl;
}

void changeTournamentName(string user, string pass, string tname, string newName)
{
    string url = challongeUrl + "/" + tname + ".json"; 

    auto res = cpr::Put(
            cpr::Url{url},
            cpr::Authentication{user, pass},
            cpr::Payload{{"tournament[name]", newName}}
            );

    /*  JSON text string */
    res.text;
}

void addPlayer(string user, string pass, string tname, string pname)
{
    string url = challongeUrl + "/" + tname + "/participants.json"; 

    auto res = cpr::Post(
            cpr::Url{url},
            cpr::Authentication{user, pass},
            cpr::Payload{{"participant[name]", pname}}
            );

    /*  JSON text string */
    res.text;
}
