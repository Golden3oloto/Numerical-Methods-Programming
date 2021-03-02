project(inc)

configure_file(
	config.h.in 
	${CMAKE_CURRENT_BINARY_DIR}/config.h
)

add_library(
	HTMLTable STATIC
	HTMLTable.h 
	HTMLTable.cpp
)

set_target_properties(
	HTMLTable PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)