project(laba_5)

add_executable(LABA_5_Gaussian_method main.cpp)

set_target_properties(
	LABA_5_Gaussian_method PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

target_link_libraries(
	LABA_5_Gaussian_method
	HTMLTable
)