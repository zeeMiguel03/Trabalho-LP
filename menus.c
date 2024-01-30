#include "menus.h"
#include "stdio.h"
#include "geral.h"
#include "user.h"
#include "listings.h"

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
                menuList(users,equipments);
                break;
            case 5:
                break;
        }
    } while (option != 0);
}

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

void menuList(Users *users, Equipments  *equipments) {
    int option;
    do {
        header("Menu list's");
        option = getInt(0, 3, MENU_LIST);
        switch (option) {
            case 1:
                listMaintenance(*equipments);
                break;
            case 2:
                listEquipments(*equipments);
                break;
            case 3:
                listUsers(*users);
                break;
        }
    } while (option != 0);
}


