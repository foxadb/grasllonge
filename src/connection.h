/*
 * =====================================================================================
 *
 *       Filename:  connection.h
 *
 *    Description:  Header pour le fichier qui va contenir les fonctions qui vont interragir
 *					avec Challonge
 *
 *        Version:  1.0
 *       Revision:  none
 *       Compiler:  gcc
 *
 * =====================================================================================
 */
#ifndef CONNECTION_H
#define CONNECTION_H
#include <sys/stat.h>
#include <curl/curl.h>
#include <cpr/cpr.h>
#include "../libjson/json.hh"

using namespace std;

string getTournament(string user, string pass, string name);

void changeTournamentName(string user, string pass, string tname, string newName);

void addPlayer(string user, string pass, string tname, string pname);

void addPlayerList(string user, string pass, string tname, char *file);

#endif /* CONNECTION_H */
