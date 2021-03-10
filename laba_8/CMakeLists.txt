project(laba_9)

add_executable(LABA_8_iteration_method main.cpp)

set_target_properties(
	LABA_8_iteration_method PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

target_link_libraries(
	LABA_8_iteration_method
	HTMLTable
)