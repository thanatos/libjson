cmake_minimum_required(VERSION 2.6)

project(json)
set(VERSION 0.1.1)
set(AUTHOR "Roy Wellington <cactus_hugged@yahoo.com>") 
set(PACKAGE_DESCRIPTION "C++ JSON Library")


set(CPACK_PACKAGE_CONTACT ${AUTHOR})
set(CPACK_PACKAGE_VERSION ${VERSION})
set(CPACK_PACKAGE_DESCRIPTION ${PACKAGE_DESCRIPTION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PACKAGE_DESCRIPTION})
include(CPack)


include_directories(
	${CMAKE_SOURCE_DIR}/include/json
	${CMAKE_SOURCE_DIR}/include
)


configure_file(${CMAKE_SOURCE_DIR}/libjson.pc.cmake
	${CMAKE_BINARY_DIR}/libjson.pc
	@ONLY)
install(FILES ${CMAKE_BINARY_DIR}/libjson.pc
	DESTINATION lib/pkgconfig)

configure_file(${CMAKE_SOURCE_DIR}/libjson-9999.ebuild
	${CMAKE_BINARY_DIR}/libjson-9999.ebuild
	@ONLY)

add_subdirectory(doc)
add_subdirectory(example)
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)

