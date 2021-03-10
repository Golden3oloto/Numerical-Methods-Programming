project(laba_7)

add_executable(LABA_7_inverse_matrix main.cpp)

set_target_properties(
	LABA_7_inverse_matrix PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

target_link_libraries(
	LABA_7_inverse_matrix
	HTMLTable
)