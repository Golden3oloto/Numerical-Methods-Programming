project(laba_6)

add_executable(LABA_6_determinant main.cpp)

set_target_properties(
	LABA_6_determinant PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

target_link_libraries(
	LABA_6_determinant
	HTMLTable
)