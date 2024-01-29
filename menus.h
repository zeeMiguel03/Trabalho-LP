#ifndef TRABALHO_LP_MENUS_H
#define TRABALHO_LP_MENUS_H

#include "user.h"
#include "equipments.h"

#define MENU_MAIN "\n1 - Manage Equipment\n2 - Manage Users\n3 - View equipment historic\n4 - Listings\n5 - Search Equipment\n0 - Leave\n  Choose: "
#define MENU_MANAGE_EQUIPMENT "\n1 - Insert Equipment\n2 - Make Maintenance\n3 - Remove Equipment\n4 - Associate Equipment\n5 - List Equipments\n0 - Go Back!\n  Choose:"
#define MENU_MANAGE_USERS "\n1 - Create User\n2 - Modify User\n3 - Delete Users\n4 - List Users\n0 - Go Back!\n  Choose: "
#define MENU_LIST "\n1 - List maintenance\n2 - List Equipments\n3 - List users\n0 - Go Back!\n  Choose:"

void menuEquipments(Equipments *equipments, Categories *categories);
void menuUser(Users *users);
void menuStart(Users *users, Categories *categories, Equipments *equipments);
void menuList(Users *users, Equipments  *equipments);

#endif
