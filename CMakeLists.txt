cmake_minimum_required(VERSION 3.22)

project(renderer_package)

if(ENGINE_BUILD)
add_subdirectory(renderer)
else()
add_subdirectory(renderer_test)
endif()