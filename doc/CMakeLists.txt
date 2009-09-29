find_package(Doxygen)

if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    add_custom_target(doxygen ALL ${DOXYGEN_EXECUTABLE}
    ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
else(DOXYGEN_FOUND)
    message("Doxygen was not found on your system. The doxygen documentation
    will not be generated.")
endif(DOXYGEN_FOUND)
