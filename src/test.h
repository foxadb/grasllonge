/*
 * test.h
 *
 *  Created on: 24 févr. 2017
 *      Author: samy
 */

#ifndef SRC_TEST_H_
#define SRC_TEST_H_

#include "connection.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include "../libjson/json.hh"

using namespace std;

void grasllongeTest(int num, std::string tournament, JSON::Object participants);

#endif /* SRC_TEST_H_ */
