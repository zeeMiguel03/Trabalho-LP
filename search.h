#ifndef TRABALHO_LP_SEARCH_H
#define TRABALHO_LP_SEARCH_H
#include "equipments.h"

#define SEARCH_BY_STATE "Insert equipment State (1 - Operation, 2 - Maintenance, 3 - Non operation, 4 - Recycling), Choose: "
#define SEARCH_BY_NAME "Insert equipment name:"
#define SEARCH_BY_CATEGORY "Insert equipment category:"
#define SEARCH_BY_DATE "Insert equipment acquisition date: "

#define ERROR_SEARCH_STATE "No equipment with that state!"
#define ERROR_SEARCH_NAME "No equipment with that name!"
#define ERROR_SEARCH_CATEGORY "No equipment with that category!"
#define ERROR_SEARCH_DATE "No equipment with that date!"

int searchEquipmentNumber(Equipments *equipments, int number);
void printEquipment(Equipment *equipment);
void searchEquipmentState(Equipments *equipments);
void searchEquipmentName(Equipments *equipments);
void searchEquipmentCategory(Equipments *equipments);
void searchEquipmentDate(Equipments *equipments);

#endif
