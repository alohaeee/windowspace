cmake_minimum_required(VERSION 3.20)

project(windowspace)

add_library(tomlc17 STATIC deps/tomlc17/tomlc17.cpp)
target_include_directories(tomlc17 PUBLIC deps/tomlc17)

file(READ "${CMAKE_CURRENT_SOURCE_DIR}/DefaultConfig.toml" DEFAULT_CONFIG_TOML_HEX HEX)
string(LENGTH "${DEFAULT_CONFIG_TOML_HEX}" DEFAULT_CONFIG_TOML_HEX_LEN)
math(EXPR DEFAULT_CONFIG_TOML_SIZE "${DEFAULT_CONFIG_TOML_HEX_LEN} / 2")
string(REGEX MATCHALL ".." DEFAULT_CONFIG_TOML_HEX_LIST "${DEFAULT_CONFIG_TOML_HEX}")

set(DEFAULT_CONFIG_TOML_BYTES "")
set(_default_config_line_len 0)
foreach(_byte IN LISTS DEFAULT_CONFIG_TOML_HEX_LIST)
    string(APPEND DEFAULT_CONFIG_TOML_BYTES "0x${_byte}, ")
    math(EXPR _default_config_line_len "${_default_config_line_len} + 1")
    if(_default_config_line_len EQUAL 16)
        string(APPEND DEFAULT_CONFIG_TOML_BYTES "\n    ")
        set(_default_config_line_len 0)
    endif()
endforeach()
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/src/DefaultConfig.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/generated/DefaultConfig.h"
    @ONLY
)

add_executable(windowspace src/main.c)
target_link_libraries(windowspace tomlc17)
target_include_directories(windowspace PRIVATE deps/raddcore/)
target_include_directories(
    windowspace
    PRIVATE
        src
        "${CMAKE_CURRENT_BINARY_DIR}/generated"
)