#include "user.h"
#include "menus.h"
#include "stdlib.h"

int main() {
    Users users;
    Equipments equipments;
    Categories categories;
    bootUsers(&users);
    bootEquipments(&equipments,&categories);
    menuStart(&users, &categories, &equipments);
    free(users.users);
    free(categories.categories);
    free(equipments.equipments);
    return 0;
}
