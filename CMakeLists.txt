cmake_minimum_required(VERSION 2.8)
project(Programming_Project C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Programming_Project
        book_management.h
        book_management.c
        loans.c
        loans.h
        main.c
        regOrLogin.c
        regOrLogin.h)

set(CMAKE_C_FLAGS "-std=c99 -fdump-rtl-expand")