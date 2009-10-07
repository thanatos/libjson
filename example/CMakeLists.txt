
add_executable(
	json_serialize
	json_serialize.cpp
)

target_link_libraries(
	json_serialize
	json
)


add_executable(
	json_parse
	json_parse.cpp
)

target_link_libraries(
	json_parse
	json
)

