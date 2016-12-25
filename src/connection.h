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
#include <curl/curl.h>
#include <sys/stat.h>
#include "../libjson/json.hh"

using namespace std;

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);

void getRequest(string url);

void postRequest(string url, string post);

size_t read_data(void *ptr, size_t size, size_t nmemb, FILE *stream);

void putRequest(const char *file, string url);

#endif /* CONNECTION_H */
