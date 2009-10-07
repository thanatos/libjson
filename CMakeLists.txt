cmake_minimum_required(VERSION 2.6)

project(json)
set(VERSION 0.01)


include_directories(
	${CMAKE_SOURCE_DIR}/include/libjson
)


add_subdirectory(doc)
add_subdirectory(example)
add_subdirectory(src)
add_subdirectory(test)

