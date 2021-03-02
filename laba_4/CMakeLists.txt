project(laba_4)

add_executable(LABA_4_iteration_method main.cpp)

set_target_properties(
	LABA_4_iteration_method PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

target_link_libraries(
	LABA_4_iteration_method
	HTMLTable
)