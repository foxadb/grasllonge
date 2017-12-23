# Grasllonge

## Description

C++ coded application to improve user experience of tournament organisers using Challonge bracket
system.
This application provide a fast-paced terminal way to import a player list on Challonge, submit a match result and research the next matches to be played.

## Libraries
[CPR](https://github.com/whoshuu/cpr) - C++ Requests: Curl for People, a spiritual port of Python Requests

## Instructions

Create a login.txt file with 2 lines:

```
login
api key
```

Then compile with CMake :
```
mkdir build
cd build
cmake ..
make
./grasllonge
```

## Authors

* Samy Amraoui
* Matthieu Charly-Desroches
