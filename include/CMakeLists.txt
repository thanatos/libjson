file(GLOB libjson_headers json/*.h)

install(FILES ${libjson_headers} DESTINATION include/json)
