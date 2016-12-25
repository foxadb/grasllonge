cmake_minimum_required(VERSION 2.6)
project(grasllonge)
add_executable(grasllonge src/grasllonge.cxx src/connection.cxx)
target_link_libraries(grasllonge readline history curl)

add_subdirectory(cpr)
include_directories(${CPR_INCLUDE_DIRS})
target_link_libraries(grasllonge ${CPR_LIBRARIES})

add_library(libjson STATIC IMPORTED)
set_target_properties(libjson PROPERTIES IMPORTED_LOCATION ../libjson/libjson.a)
target_link_libraries(grasllonge libjson)
