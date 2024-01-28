#include "menus.h"
#include "stdio.h"
#include "geral.h"
#include "user.h"
#include "listings.h"

void menuUser(Users *users) {
    int option;
    header("MENU USER");
    do {
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
            case 0:
                menuStart(users);
        }
    } while (option != 0);
}

void menuStart(Users *users) {
    int option = getInt(0, 5, MENU_MAIN);
    header("MENU START");
    switch (option) {
        case 0:
            puts("Goodbye");
            break;
        case 1:
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
}
