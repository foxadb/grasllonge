/*
 * =====================================================================================
 *
 *       Filename:  connection.h
 *
 *    Description:  Header of connection.cxx
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
#include <vector>

using namespace std;

void initialize_param_values(string suser, string spass);

void create_liste_participants(string tname);

/**
 * @brief Get the tournament's infos
 *
 * @param user account's username
 * @param pass account's password
 * @param tname tournament's name (custom url)
 *
 * @return tournament's infos in JSON format
 */
string getTournament(string tname);

/**
 * @brief Change the tournament's name (not url)
 *
 * @param user account's username
 * @param pass account's password
 * @param tname tournament's name (custom url)
 * @param newName new tournament's name
 */
void changeTournamentName(string tname, string newName);

/**
 * @brief Add a player into the tournament
 *
 * @param user account's username
 * @param pass account's password
 * @param tname tournament's name (custom url)
 * @param pname player's name to add
 */
void addPlayer(string tname, string pname);

/**
 * @brief Add a list of players
 *
 * @param user account's username
 * @param pass account's password
 * @param tname tournament's name (custom url)
 * @param file file containing the players' list
 */
void addPlayerList(string tname, vector<string> list);

void deletePlayer(string tname, string pname);

void resetPlayers(string tname);

#endif /* CONNECTION_H */
