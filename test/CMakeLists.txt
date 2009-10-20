
add_executable(
	build_object
	build_object.cpp
)

target_link_libraries(
	build_object
	json
)

add_test(
	build_object
	build_object
)
