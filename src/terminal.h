/*
 * terminal.h
 *
 *  Created on: 26 mars 2017
 *      Author: samy
 */

#ifndef SRC_TERMINAL_H_
#define SRC_TERMINAL_H_

#include "connection.h"

char** function_name_completion(const char*, int, int);

char* function_name_generator(const char*, int);

void execute_function(const char*, const std::string);

#endif /* SRC_TERMINAL_H_ */
