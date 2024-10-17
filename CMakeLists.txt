cmake_minimum_required(VERSION 3.5.0)
project(PasswordGen VERSION 0.1.0 LANGUAGES C CXX)

# Option to build CLI and/or GUI versions
option(BUILD_CLI "Build the CLI version" ON)
option(BUILD_GUI "Build the GUI version" OFF)

# Common settings
set(SOURCES_COMMON Main.cpp LibSodium.h)

# CLI target
if(BUILD_CLI)
    set(CLI_SOURCES ${SOURCES_COMMON})
    add_executable(PasswordGenCli ${CLI_SOURCES})
    target_compile_definitions(PasswordGenCli PRIVATE CLI_BUILD)
    message(STATUS "CLI version will be built")
endif()

# GUI target
if(BUILD_GUI)
    set(GUI_SOURCES ${SOURCES_COMMON})
    add_executable(PasswordGenGui ${GUI_SOURCES})
    target_compile_definitions(PasswordGenGui PRIVATE GUI_BUILD)
    message(STATUS "GUI version will be built")
endif()