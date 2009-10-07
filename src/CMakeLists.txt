
add_library(
	json SHARED
	array.cpp
	generator.cpp
	generator_stub.cpp
	object.cpp
	parser.cpp
	primitives.cpp
	utf8.cpp
)

install(TARGETS json
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)

