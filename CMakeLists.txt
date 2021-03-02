cmake_minimum_required(VERSION 3.0)


project(NMP)

SET(RESOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_BINARY_DIR}/include
)

add_subdirectory(include)

add_subdirectory(laba_3)
add_subdirectory(laba_4)
