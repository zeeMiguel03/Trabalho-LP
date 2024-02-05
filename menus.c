#include "menus.h"
#include "stdio.h"
#include "geral.h"
#include "user.h"
#include "listings.h"
#include "search.h"

/**
 * @brief Main menu function to start the program.
 *
 * This function displays the main menu and handles user input to navigate
 * to different sections of the program.
 *
 * @param users Pointer to the Users structure.
 * @param categories Pointer to the Categories structure.
 * @param equipments Pointer to the Equipments structure.
 */
void menuStart(Users *users, Categories *categories, Equipments *equipments) {
    int option;
    do {
        header("Menu Main");
        option = getInt(0, 5, MENU_MAIN);
        switch (option) {
            case 0:
                puts("Goodbye");
                break;
            case 1:
                menuEquipments(users,equipments,categories);
                break;
            case 2:
                menuUser(users);
                break;
            case 3:
                listMaintenance(*equipments);
                break;
            case 4:
                menuList(users,equipments,categories);
                break;
            case 5:
                if (verifyCounter(equipments->counterEquipment, NO_EQUIPMENTS) == 1) {
                    menuSearch(equipments);
                }
                break;
        }
    } while (option != 0);
}

/**
 * @brief User menu function for managing user-related operations.
 *
 * This function displays the user menu and handles user input to perform
 * operations such as inserting, modifying, deleting, or listing users.
 *
 * @param users Pointer to the Users structure.
 */
void menuUser(Users *users) {
    int option;
    do {
        header("Menu user");
        option = getInt(0, 4, MENU_MANAGE_USERS);
        switch (option) {
            case 1:
                insertUser(users);
                break;
            case 2:
                modifyUser(users);
                break;
            case 3:
                deleteUser(users);
                break;
            case 4:
                listUsers(*users);
                break;
        }
    } while (option != 0);
}

/**
 * @brief Equipment menu function for managing equipment-related operations.
 *
 * This function displays the equipment menu and handles user input to perform
 * operations such as inserting, adding maintenance, removing, adding equipment to users,
 * or listing equipment.
 *
 * @param users Pointer to the Users structure.
 * @param equipments Pointer to the Equipments structure.
 * @param categories Pointer to the Categories structure.
 */
void menuEquipments(Users *users,Equipments *equipments, Categories *categories) {
    int option;
    do {
        header("Menu Equipments");
        option = getInt(0, 5, MENU_MANAGE_EQUIPMENT);
        switch (option) {
            case 1:
                insertEquipment(equipments, categories);
                break;
            case 2:
                addMaintenance(equipments, categories);
                break;
            case 3:
                removeEquipment(equipments, categories);
                break;
            case 4:
                addEquipmentUser(users, equipments, categories);
                break;
            case 5:
                listEquipments(*equipments);
                break;
        }
    } while (option != 0);
}

/**
 * @brief List menu function for managing various lists.
 *
 * This function displays the list menu and handles user input to perform
 * operations such as listing maintenance, listing equipment, listing recycling equipment,
 * or listing free equipment.
 *
 * @param users Pointer to the Users structure.
 * @param equipments Pointer to the Equipments structure.
 * @param categories Pointer to the Categories structure.
 */
void menuList(Users *users, Equipments  *equipments, Categories *categories) {
    int option;
    do {
        header("Menu list's");
        option = getInt(0, 4, MENU_LIST);
        switch (option) {
            case 1:
                listMaintenance(*equipments);
                break;
            case 2:
                listEquipments(*equipments);
                break;
            case 3:
                listRecyclingEquip(equipments);
                break;
            case 4:
                listFreeEquipments(equipments, users, categories);
                break;
        }
    } while (option != 0);
}

/**
 * @brief Search menu function for searching equipment.
 *
 * This function displays the search menu and handles user input to perform
 * operations such as searching equipment by name, category, state, or date.
 *
 * @param equipments Pointer to the Equipments structure.
 */
void menuSearch(Equipments *equipments) {
    int option;
    do {
        header("Menu search");
        option = getInt(0, 4, MENU_SEARCH);
        switch (option) {
            case 1:
                searchEquipmentName(equipments);
                break;
            case 2:
                searchEquipmentCategory(equipments);
                break;
            case 3:
                searchEquipmentState(equipments);
                break;
            case 4:
                searchEquipmentDate(equipments);
        }
    } while (option != 0);
}


