cmake_minimum_required(VERSION 3.14)
project(
 AD9834
 VERSION 1.0 
 LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 11)
add_library(AD9834 INTERFACE)
target_include_directories(AD9834 INTERFACE src)
