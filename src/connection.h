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

/**
 * @brief Initialize the user and password
 * @param suser username
 * @param spass password (aka api key)
 */
void initialize_param_values(std::string suser, std::string spass);

/**
 * @brief Pull of the tournements created with the account
 * @return array of all tournaments
 */
JSON::Array pullTournaments();

/**
 * @brief Print the list of all tournaments
 * @param tournaments tournaments array
 */
void printTournaments(JSON::Array tournaments);

/**
 * @brief Create the JSON::Object of participants
 * @param tName
 * @return participants in a JSON::Object
 */
JSON::Object create_participants(const std::string tName);

/**
 * @brief Print all participants
 * @param participants
 */
void printParticipants(JSON::Object participants);

/**
 * @brief Get the tournament's infos
 *
 * @param tName tournament's name (custom url)
 *
 * @return tournament's infos in JSON format
 */
std::string getTournament(const std::string tName);

/**
 * @brief Display tournament infos
 * @param tInfos String to parse after getting from Challonge JSON request
 */
void displayTournament(const std::string tInfos);

/**
 * @brief Change the tournament's name (not url)
 *
 * @param tName tournament's name (custom url)
 * @param newName new tournament's name
 */
void changeTournamentName(const std::string tName, std::string newName);

/**
 * @brief Add a player into the tournament
 *
 * @param tName tournament's name (custom url)
 * @param pName player's name to add
 */
void addPlayer(const std::string tName, std::string pName);

/**
 * @brief Add a list of players
 *
 * @param tName tournament's name (custom url)
 * @param file file containing the players' list
 */
void addPlayerList(const std::string tName, std::vector<std::string> list);

/**
 * @brief Delete a player into the tournament
 *
 * @param tName tournament's name (custom url)
 * @param pName player's name to delete
 */
void deletePlayer(const std::string tName, std::string pName, JSON::Object participants);

/**
 * @brief Reset the tournament's players list
 *
 * @param tName tournament's name (custom url)
 */
void resetPlayers(const std::string tName, JSON::Object participants);

/**
 * @brief Start the tournament
 * @param tName tournament url
 */
void startTournament(const std::string tName);

/**
 * @brief Pull matches of the tournament
 * @param tName tournament url
 * @return JSON::Array containing all the matches
 */
JSON::Array pullMatches(const std::string tName);

void searchMatch(JSON::Array matches, int player_id, JSON::Object participants);

void displayMatch(JSON::Array matches, int matchNum, JSON::Object participants);

void updateMatch(JSON::Array* matches, int matchNum, std::string score);

void pushMatches(const std::string tName, JSON::Array* matches);

void endTournament(const std::string tName);

std::string player_id_to_name(int id, JSON::Object participants);

int match_id_to_num(int id, JSON::Array matches);

#endif /* CONNECTION_H */
