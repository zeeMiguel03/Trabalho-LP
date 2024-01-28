/**
 * @file main.c
 * @brief Main source file for the company management system.
 *
 * This file contains the main function for the company management system.
 * It initializes the necessary data structures, loads data from files, and starts the main menu loop.
 * After the user exits the program, it frees allocated memory.
 *
 * @author Antonio, Miguel, Luis
 * @date 20-12-2023
 */
#include "stdio.h"
#include "user.h"
#include "menus.h"
#include "stdlib.h"

int main() {
    Users users;
    bootUsers(&users);
    menuStart(&users);
    free(users.users);
    return 0;
}
