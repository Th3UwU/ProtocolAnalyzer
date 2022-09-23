cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME ProtocolAnalyzer)
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

list(APPEND CMAKE_CXX_FLAGS "-Wall -pedantic")

file(
	GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
	"include/*.hpp"
	"src/*.cpp"
)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(
	${PROJECT_NAME} PRIVATE
	"include"
)
