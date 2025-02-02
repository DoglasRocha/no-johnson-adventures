cmake_minimum_required(VERSION 3.18)

project(no-johnson-adventures VERSION 0.0.1 DESCRIPTION "NO Johnson Adventures")

#find_package(libnop QUIET)
if(NOT libnop_FOUND)
	include(FetchContent)
	FetchContent_Declare(libnop
		GIT_REPOSITORY https://nop.dainf.ct.utfpr.edu.br/nop-implementations/frameworks/nop-framework-cpp-4-dot-5/nop-framework-cpp-4-dot-5-kernel.git
		GIT_TAG main
	)
	FetchContent_GetProperties(libnop)
	if(NOT libnop_POPULATED)
		FetchContent_MakeAvailable(libnop)
	endif()
endif()

set(SFML_DIR "./SFML/lib/cmake/SFML")
find_package(SFML 2.6.1 COMPONENTS network audio graphics window system REQUIRED)

include_directories(include/ SFML/include)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

add_executable(no-johnson-adventures ${SOURCES})

set_target_properties(no-johnson-adventures PROPERTIES
	CXX_STANDARD 20
)
target_link_libraries(no-johnson-adventures libnop sfml-graphics sfml-window sfml-network sfml-audio sfml-system)

add_custom_target(
	run ALL
	COMMAND ./no-johnson-adventures
)