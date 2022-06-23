cmake_minimum_required(VERSION 3.15)
project(DoltLib C)
set(CMAKE_C_STANDARD 11)

# Variables
set(DOLT_STATIC_LIBRARY_NAME doltlib.a)

# Dependencies
include(FetchContent)
FetchContent_Declare(dolt
    GIT_REPOSITORY https://github.com/dolthub/dolt.git
    GIT_TAG cca9e426f291ca5b1991a1b64428b8ba38e80013
)
FetchContent_MakeAvailable(dolt)
find_program(GOLANG_BINARY "go")
IF(NOT GOLANG_BINARY)
    # TODO: download and install go depending on the OS rather than error
    message(FATAL_ERROR "Cannot find the \"go\" binary, please install it and add it to PATH")
ENDIF()
execute_process(COMMAND ${GOLANG_BINARY} build -o ${dolt_BINARY_DIR}/${DOLT_STATIC_LIBRARY_NAME} -buildmode=c-archive .
    WORKING_DIRECTORY ${dolt_SOURCE_DIR}/go/cmd/dolt/export)
add_library(DOLT_STATIC_LIBRARY STATIC IMPORTED)
set_target_properties(DOLT_STATIC_LIBRARY PROPERTIES IMPORTED_LOCATION ${dolt_BINARY_DIR}/${DOLT_STATIC_LIBRARY_NAME})

# Project
include_directories(include src ${dolt_BINARY_DIR})
file(GLOB all_SRCS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.c"
    "${PROJECT_SOURCE_DIR}/src/*/*.c"
)
add_executable(${PROJECT_NAME} ${all_SRCS})
target_link_libraries(${PROJECT_NAME} DOLT_STATIC_LIBRARY)