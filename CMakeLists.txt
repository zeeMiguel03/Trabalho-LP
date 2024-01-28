cmake_minimum_required(VERSION 3.26)
project(Trabalho_LP C)

set(CMAKE_C_STANDARD 11)

add_executable(Trabalho_LP
        main.c
        user.h
        user.c
        geral.h
        geral.c
        menus.h
        menus.c
        equipments.h
        equipments.c
        listings.c
        listings.h
)
