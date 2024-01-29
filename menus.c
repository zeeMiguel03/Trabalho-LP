#include "menus.h"
#include "stdio.h"
#include "geral.h"
#include "user.h"
#include "listings.h"
//ss//
void menuEquipments(Equipments *equipments, Categories *categories) {
    int option;
    do {
        header("Menu Equipments");
        option = getInt(0, 4, MENU_MANAGE_EQUIPMENT);
        switch (option) {
            case 1:
                insertEquipment(equipments, categories);
                break;
            case 2:
                listEquipments(*equipments);
                break;
            case 3:
                break;
            case 4:
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
                menuEquipments(equipments,categories);
                break;
            case 2:
                menuUser(users);
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
        }
    } while (option != 0);
}
