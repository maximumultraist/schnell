cmake_minimum_required(VERSION 3.9)
project(schnell)

set(CMAKE_CXX_STANDARD 11)

add_executable(schnell
        cat.c
        cat.h
        cp.c
        cp.h
        grep.c
        grep.h
        ls.c
        ls.h
        mycommands.h
        myshell.c sleep.c sleep.h)
