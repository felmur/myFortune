cmake_minimum_required(VERSION 3.5)

project(myFortune LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_link_options(-lpthread)
add_executable(myFortune main.cpp application.cpp timer.cpp)
