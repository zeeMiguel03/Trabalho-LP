#ifndef TRABALHO_LP_LISTINGS_H
#define TRABALHO_LP_LISTINGS_H
#include "user.h"
#include "equipments.h"

#define NO_EQUIPMENTS "No equipments yet!"
#define NO_USERS "No users yet!"
#define NO_MAINTENANCE "This equipment don't have any maintenance!"

void listUsers(Users users);
void listEquipments(Equipments equipments);
void listMaintenance(Equipments equipments);

#endif
