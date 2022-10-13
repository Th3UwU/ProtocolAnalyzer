cmake_minimum_required(VERSION 3.24.2)
list(APPEND CMAKE_CXX_FLAGS "-Wall")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# ProtocolAnalyzer
set(PROJECT_NAME ProtocolAnalyzer)
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

file(
	GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
	"./src/*.cpp"
	"./src/msw/wx.rc"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(
	${PROJECT_NAME} PRIVATE
	"./include"
	"./include_lib"
)

target_link_directories(
	${PROJECT_NAME} PRIVATE
	"./lib"
)

target_link_libraries(${PROJECT_NAME}
	fmt
	Pcap++ Packet++ Common++ wpcap Packet pthread ws2_32 iphlpapi
)

#wxbase32u
#wxmsw32u_core
