cmake_minimum_required(VERSION 3.9)
project(cpp_arcade)

include_directories(include lib/nCurses/include lib/allegro/include lib/sdl/include)

set_source_files_properties(xmppgw.c PROPERTIES LANGUAGE CXX)

set(CMAKE_CXX_STANDARD 14)

add_executable(cpp_arcade
    src/core/Core.cpp
        games
        include
        lib
        src
        Makefile
)