#include "user.h"
#include "menus.h"
#include "geral.h"

int main() {
    Users users;
    Equipments equipments;
    Categories categories;
    bootUsers(&users);
    bootEquipments(&equipments,&categories);
    menuStart(&users, &categories, &equipments);
    saveEquipments(&equipments, &categories);
    saveUsers(&users);
    freeMemory(users,equipments, categories);
    return 0;
}
