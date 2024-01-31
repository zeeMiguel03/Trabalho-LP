#ifndef TRABALHO_LP_LISTINGS_H
#define TRABALHO_LP_LISTINGS_H
#include "user.h"
#include "equipments.h"

#define NO_EQUIPMENTS "No equipments yet!"
#define NO_USERS "No users yet!"
#define NO_MAINTENANCE "This equipment don't have any maintenance!"
#define NO_EQUIPMENTS_FREE "No free equipments!"
#define NO_EQUIPMENTS_RECYCLE "No equipments to recycle!"

void listUsers(Users users);
void printEquipment(Equipment *equipment);
void listRecyclingEquip(Equipments *equipments);
void listEquipments(Equipments equipments);
void listMaintenance(Equipments equipments);
int listCategory(Categories *categories);
void listFreeEquipments(Equipments *equipments, Users *users, Categories *categories);

#endif
