/*
 * terminal.h
 *
 *  Created on: 26 mars 2017
 *      Author: samy
 */

#ifndef SRC_TERMINAL_H_
#define SRC_TERMINAL_H_

#include "connection.h"

char** function_name_completion(const char* text, int start, int end);

char* function_name_generator(const char* text, int state);

JSON::Array execute_function(const char* function_name, const std::string tournament,
		JSON::Object participants, JSON::Array matches);

#endif /* SRC_TERMINAL_H_ */
