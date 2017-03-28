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

static const std::string challongeUrl = "https://api.challonge.com/v1/tournaments";

static std::string user;
static std::string pass;

void initialize_param_values(std::string suser, std::string spass);

JSON::Object create_participants(std::string tName);

void printParticipants(JSON::Object participants);

/**
 * @brief Get the tournament's infos
 *
 * @param tName tournament's name (custom url)
 *
 * @return tournament's infos in JSON format
 */
std::string getTournament(std::string tName);

/**
 * @brief Change the tournament's name (not url)
 *
 * @param tName tournament's name (custom url)
 * @param newName new tournament's name
 */
void changeTournamentName(std::string tName, std::string newName);

/**
 * @brief Add a player into the tournament
 *
 * @param tName tournament's name (custom url)
 * @param pName player's name to add
 */
void addPlayer(std::string tName, std::string pName);

/**
 * @brief Add a list of players
 *
 * @param tName tournament's name (custom url)
 * @param file file containing the players' list
 */
void addPlayerList(std::string tName, std::vector<std::string> list);

/**
 * @brief Delete a player into the tournament
 *
 * @param tName tournament's name (custom url)
 * @param pName player's name to delete
 */
void deletePlayer(std::string tName, std::string pName, JSON::Object participants);

/**
 * @brief Reset the tournament's players list
 *
 * @param tName tournament's name (custom url)
 */
void resetPlayers(std::string tName, JSON::Object participants);

std::string player_id_to_name(int id, JSON::Object participants);

int match_id_to_num(int id, JSON::Array matches);

JSON::Array pullMatches(std::string tName);

void searchMatch(JSON::Array matches, int player_id, JSON::Object participants);

void displayMatch(JSON::Array matches, int matchNum, JSON::Object participants);

void updateMatch(JSON::Array* matches, int matchNum, std::string score);

void pushMatches(std::string tName, JSON::Array* matches);

#endif /* CONNECTION_H */
