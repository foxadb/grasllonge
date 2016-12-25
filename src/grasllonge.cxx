/*
 * =====================================================================================
 *
 *       Filename:  grasllonge.cxx
 *
 *    Description:	Fichier principal contenant la boucle principale du programme
 *
 *        Version:  1.0
 *       Revision:  none
 *       Compiler:  gcc
 *
 * =====================================================================================
 */

#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <cstdlib>
#include <readline/readline.h>
#include <readline/history.h>
#include "connection.h"
#include "../libjson/json.hh"

int main(int argc, char* argv[])
{
    const char *prompt = "grasllonge > ";
    const std::string   add("add"),
          print("print"),
          json("json");

    //Flush the history
    rl_clear_history();	

    //Initialize libcurl
    curl_global_init(CURL_GLOBAL_ALL);

    while(1)
    {
        char* line;
        line = readline(prompt);

        if (line==0 || !strncmp(line, "exit", 4))
        {
            std::cout << "\nBye :)" << std::endl;
            break;
        }

        ////////////////// LIGNES DE TEST

        if (!strncmp(line, "tournoi", 7))
        {
            getTournament("dothraki", "uMhQBV4EbwHMuIpbHO0sZ0POyXop7VUbbd7FiDig", "gras8_test1");
        }


        //////////////// FIN DES LIGNES DE TEST

        add_history(line);

        std::istringstream iss(line);
        std::vector<std::string> tokens;

        do
        {
            std::string sub;
            iss >> sub;
            tokens.push_back(sub);
        } while (iss);

        std::cout << "You idiot wrote: " << std::endl;
        for(size_t i=0; i<tokens.size(); ++i)
        {
            std::cout << tokens[i] << ' ';
        }
        std::cout << std::endl;

        if (tokens[0] == add)
            std::cout << "You chose the add option" << std::endl;
        else if (tokens[0] == print)
            std::cout << "You chose the print option" << std::endl;
        else if (tokens[0] == json)
        {
            JSON::Object obj;
            obj["commande"] = tokens[0];
            JSON::Array a;
            for(size_t i=1; i<tokens.size(); ++i)
            {
                a.push_back(tokens[i]);
            }
            obj["parametres"] = a;
            std::cout << obj << std::endl;
        }
        else 
            std::cout << "This option is unknown to grasllonge" << std::endl;
    }

    //Cleaning libcurl
    curl_global_cleanup();

    return EXIT_SUCCESS;
}
