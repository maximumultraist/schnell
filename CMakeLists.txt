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
        rmdir.c
        rmdir.h
        mkdir.c
        mkdir.h
        stat.c
        stat.h
        env.h
        env.c
        mycommands.h
        myshell.c sleep.c sleep.h cd.c cd.h mykill.c mykill.h)
