cmake_minimum_required(VERSION 2.6)
project(grasllonge)
add_executable(grasllonge src/grasllonge.cxx)
target_link_libraries(grasllonge readline history)
