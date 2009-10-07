cmake_minimum_required(VERSION 2.6)

project(json)
set(VERSION 0.01)


include_directories(
	${CMAKE_SOURCE_DIR}/include/libjson
)

configure_file(${CMAKE_SOURCE_DIR}/libjson.pc.cmake
	${CMAKE_BINARY_DIR}/libjson.pc
	@ONLY)
install(FILES ${CMAKE_BINARY_DIR}/libjson.pc
	DESTINATION lib/pkgconfig)

add_subdirectory(doc)
add_subdirectory(example)
add_subdirectory(src)
add_subdirectory(test)

