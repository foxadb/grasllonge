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

using namespace std;

/**
 * @brief Get the tournament's infos
 *
 * @param user account's username
 * @param pass account's password
 * @param tname tournament's name (custom url)
 *
 * @return tournament's infos in JSON format
 */
string getTournament(string user, string pass, string tname);

/**
 * @brief Change the tournament's name (not url)
 *
 * @param user account's username
 * @param pass account's password
 * @param tname tournament's name (custom url)
 * @param newName new tournament's name
 */
void changeTournamentName(string user, string pass, string tname, string newName);

/**
 * @brief Add a player into the tournament
 *
 * @param user account's username
 * @param pass account's password
 * @param tname tournament's name (custom url)
 * @param pname player's name to add
 */
void addPlayer(string user, string pass, string tname, string pname);

/**
 * @brief Add a list of players
 *
 * @param user account's username
 * @param pass account's password
 * @param tname tournament's name (custom url)
 * @param file file containing the players' list
 */
void addPlayerList(string user, string pass, string tname, char *file);

#endif /* CONNECTION_H */
