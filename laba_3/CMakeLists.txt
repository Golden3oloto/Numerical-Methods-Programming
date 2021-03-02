project(laba_3)

add_executable(LABA_3_chord_method main.cpp)

set_target_properties(
	LABA_3_chord_method PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

target_link_libraries(
	LABA_3_chord_method
	HTMLTable
)