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
            cpr::Authentication{user, pass},
            cpr::Parameters{{"anon", "true"}, {"key", "value"}}
            );
    res.status_code;
    //res.header["content-type"];

    /*  JSON text string */
    res.text;

    cout << res.text << endl;
}
