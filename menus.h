/**
 * @file Menus.h
 * @brief Header file containing functions for various menus in the company management system.
 *
 * This file defines functions related to different menus.
 * These menus include the main start menu, user-specific menus, admin menus, and activity-related menus.
 *
 * @author José Rocha
 * @date 28-01-2024
 */
#ifndef TRABALHO_LP_MENUS_H
#define TRABALHO_LP_MENUS_H
#include "user.h"

#define MENU_MAIN "\n1 - Manage Equipment\n2 - Manage Users\n3 - View equipment historic\n4 - Listings\n5 - Search Equipment\n0 - Leave\nChoose: "
#define MENU_MANAGE_USERS "\n1 - Create User\n2 - Modify User\n3 - Delete Users\n4 - List Users\n0 - Leave\nChoose: "

void menuUser(Users *users);
void menuStart(Users *users);

#endif
