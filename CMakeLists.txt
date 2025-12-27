
cmake_minimum_required(VERSION 3.14)
project(tafel LANGUAGES CXX)

# === Compiler Settings ===
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# === Project Structure ===
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE SRC_FILES
    ${SRC_DIR}/*.cpp
    ${CMAKE_SOURCE_DIR}/main.cpp
)

include_directories(
    ${INC_DIR}
    ${INC_DIR}/tools
    ${INC_DIR}/drawables
)

# === Qt6 ===
find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(
		main
    ${SRC_FILES}
)

qt_add_resources(
		APP_RESOURCES
    resources.qrc
)

target_sources(
	main 
	PRIVATE 
	${APP_RESOURCES}
)

target_link_libraries(
	main
  PRIVATE
  Qt6::Widgets
)

