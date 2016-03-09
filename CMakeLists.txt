cmake_minimum_required(VERSION 2.6)

project(FastMarching)

add_executable(test_priorite
               pointDist.h
               priorite.h priorite.cpp
               test_priorite.cpp)
