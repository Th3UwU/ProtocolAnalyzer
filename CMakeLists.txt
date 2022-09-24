cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 17)
list(APPEND CMAKE_CXX_FLAGS "-Wall -pedantic")

# ProtocolAnalyzer
set(PROJECT_ANALYZER ProtocolAnalyzer)
project(${PROJECT_ANALYZER} VERSION 1.0.0 LANGUAGES CXX)

file(
	GLOB_RECURSE SOURCES_ANALYZER CONFIGURE_DEPENDS
	"./analyzer/include/*.hpp"
	"./analyzer/src/*.cpp"
)

add_executable(${PROJECT_ANALYZER} ${SOURCES_ANALYZER})

target_include_directories(
	${PROJECT_ANALYZER} PRIVATE
	"./analyzer/include"
)

# RNDPK
set(PROJECT_RNDPK RNDPK)
project(${PROJECT_RNDPK} VERSION 1.0.0 LANGUAGES CXX)

file(
	GLOB_RECURSE SOURCES_RNDPK CONFIGURE_DEPENDS
	"./rndpk/include/*.hpp"
	"./rndpk/src/*.cpp"
)

add_executable(${PROJECT_RNDPK} ${SOURCES_RNDPK})

target_include_directories(
	${PROJECT_RNDPK} PRIVATE
	"./rndpk/include"
)
