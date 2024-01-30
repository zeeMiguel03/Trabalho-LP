#include "listings.h"
#include "user.h"
#include "equipments.h"
#include "stdio.h"
#include "geral.h"

void listUsers(Users users) {
    int i;
    if (verifyCounter(users.counterUsers, NO_USERS) == 1) {
        for (i = 1; i < users.counterUsers; i++) {
            printf("\nUser name: %s", users.users[i].name);
            printf("\nUser acronym: %s", users.users[i].acronym);
            printf("\nUser number: %d", users.users[i].codIdentify);
            printf("\nUser code: %d", users.users[i].codIdentify);
            printf("\nUser equipment number: %d", users.users[i].numberEquipments);
            printf("\nUser function: %s", users.users[i].functionUser);
            printf("\nUser state: %s", (users.users[i].state == ACTIVE) ? "Active" : "Inactive");
            printf("\n");
        }
    }
}

void listEquipments(Equipments equipments) {
    int i;
    if (verifyCounter(equipments.counterEquipment, NO_EQUIPMENTS) == 1) {
        for (i = 1; i < equipments.counterEquipment; i++) {
            printf("\nEquipment number: %d", equipments.equipments[i].identify);
            printf("\nEquipment designation: %s", equipments.equipments[i].designation);
            printf("\nEquipment category: %s", equipments.equipments[i].category);
            printf("\nEquipment acquisition date: %d/%d/%d", equipments.equipments[i].acquisitionDate.day, equipments.equipments[i].acquisitionDate.month,
                   equipments.equipments[i].acquisitionDate.year);
            printf("\n");
        }
    }
}

void listMaintenance(Equipments equipments) {
    int i, equipment, index;
    if (verifyCounter(equipments.counterEquipment, NO_EQUIPMENTS) == 1) {
        equipment = getInt(1, equipments.counterEquipment, MSG_CHOOSE_EQUIPMENT);
        index = searchEquipment(&equipments, equipment);
        if (index != -1) {
            if (verifyCounter(equipments.equipments[index].counterMaintenance, NO_MAINTENANCE) == 1) {
                for (i = 1; i < equipments.equipments[index].counterMaintenance; i++) {
                    printf("\nMaintenance number: %d", equipments.equipments[index].maintenanceHistory[i].movementNumber);
                    printf("\nMaintenance type: %s", equipments.equipments[index].maintenanceHistory[i].maintenanceType);
                    printf("\nMaintenance Note: %s", equipments.equipments[index].maintenanceHistory[i].notes);
                    printf("\nMaintenance date: %d/%d/%d", equipments.equipments[index].maintenanceHistory[i].date.day,
                           equipments.equipments[index].maintenanceHistory[i].date.month,
                           equipments.equipments[index].maintenanceHistory[i].date.year);
                    printf("\n");
                }
            }
        }
    }
}

int listCategory(Categories *categories) {
    int i;
    if (verifyCounter(categories->counterCategory, MSG_CREATE_CATEGORY) != 0) {
        printf("\n-------Category List -------");
        for (i = 1; i < categories->counterCategory; i++) {
            printf("\n%d - %s", i, categories->categories[i].category);
        }
        printf("\n----------------------------");
        return 0;
    }
    return -1;
}





