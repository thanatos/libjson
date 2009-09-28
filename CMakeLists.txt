cmake_minimum_required(VERSION 2.6)

include_directories(
	${CMAKE_SOURCE_DIR}/h
)

project(json)

add_subdirectory(src)
add_subdirectory(test)

