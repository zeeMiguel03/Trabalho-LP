#include "listings.h"
#include "user.h"
#include "equipments.h"
#include "stdio.h"
#include "geral.h"
#include "string.h"
#include "search.h"

void listUsers(Users users) {
    int i;
    if (verifyCounter(users.counterUsers, NO_USERS) == 1) {
        for (i = BEGIN_COUNTER; i < users.counterUsers; i++) {
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
        printf(LIST_EQUIP);
        for (i = BEGIN_COUNTER; i < equipments.counterEquipment; i++) {
            printEquipment(&equipments.equipments[i]);
        }
        printf(LIST_LINE);
    }
}

void listMaintenance(Equipments equipments) {
    int i, equipment, index;
    if (verifyCounter(equipments.counterEquipment, NO_EQUIPMENTS) == 1) {
        equipment = getInt(1, equipments.counterEquipment, MSG_CHOOSE_EQUIPMENT);
        index = searchEquipmentNumber(&equipments, equipment);
        if (index != -1) {
            if (verifyCounter(equipments.equipments[index].counterMaintenance, NO_MAINTENANCE) == 1) {
                printf(LIST_MAINTENANCE);
                for (i = BEGIN_COUNTER; i < equipments.equipments[index].counterMaintenance; i++) {
                    printf("\nMaintenance number: %d", equipments.equipments[index].maintenanceHistory[i].movementNumber);
                    printf("\nMaintenance type: %s", equipments.equipments[index].maintenanceHistory[i].maintenanceType);
                    printf("\nMaintenance Note: %s", equipments.equipments[index].maintenanceHistory[i].notes);
                    printf("\nMaintenance date: %d/%d/%d", equipments.equipments[index].maintenanceHistory[i].date.day,
                           equipments.equipments[index].maintenanceHistory[i].date.month,
                           equipments.equipments[index].maintenanceHistory[i].date.year);
                    printf("\n");
                }
                printf(LIST_LINE);
            }
        }
    }
}

int listCategory(Categories *categories) {
    int i;
    if (verifyCounter(categories->counterCategory, MSG_CREATE_CATEGORY) != 0) {
        printf(LIST_CATEGORY);
        for (i = BEGIN_COUNTER; i < categories->counterCategory; i++) {
            printf("\n%d - %s", i, categories->categories[i].category);
        }
        printf("\n"LIST_LINE);
        return 0;
    }
    return -1;
}

void listFreeEquipments(Equipments *equipments, Users *users, Categories *categories) {
    int i, counterFree = 0, j;

    if (verifyCounter(equipments->counterEquipment, NO_EQUIPMENTS) == 1) {
        if (verifyCounter(users->counterUsers, NO_USERS) == 1) {
            printf(LIST_FREE_EQUIP);

            for (j = BEGIN_COUNTER; j < categories->counterCategory; j++) {
                printf("\nCategory: %s", categories->categories[j].category);

                for (i = BEGIN_COUNTER; i < equipments->counterEquipment; i++) {
                    if (strcmp(equipments->equipments[i].category, categories->categories[j].category) == 0 &&
                        equipments->equipments[i].userIdentify == 0) {
                        printEquipment(&equipments->equipments[i]);
                        counterFree++;
                    }
                }

                printf("\n"LIST_LINE);
            }

            if (counterFree == 0) {
                puts(NO_EQUIPMENTS_FREE);
            }
        }
    }
}

void listRecyclingEquip(Equipments *equipments) {
    int i, counter = 0;
    if (verifyCounter(equipments->counterEquipment, NO_EQUIPMENTS) == 1) {
        for (i = BEGIN_COUNTER; i < equipments->counterEquipment; i++) {
            if (equipments->equipments[i].state == RECYCLING) {
                printEquipmentRecycle(&equipments->equipments[i]);
                counter++;
            }
        }

        if (counter == 0) {
            puts(NO_EQUIPMENTS_RECYCLE);
        }
    }
}


void printEquipment(Equipment *equipment) {
    if (equipment->state != RECYCLING) {
        printf("\nEquipment number: %d", equipment->identify);
        printf("\nEquipment designation: %s", equipment->designation);
        printf("\nEquipment category: %s", equipment->category);
        printf("\nEquipment acquisition date: %d/%d/%d", equipment->acquisitionDate.day, equipment->acquisitionDate.month,
               equipment->acquisitionDate.year);
        printf("\nEquipment state: %s", getStateString(equipment->state));
        printf("\nEquipment associate user: %d", equipment->userIdentify);
        printf("\n");
    }
}

void printEquipmentRecycle(Equipment *equipment) {
    if (equipment->state == RECYCLING) {
        printf("\nEquipment number: %d", equipment->identify);
        printf("\nEquipment designation: %s", equipment->designation);
        printf("\nEquipment category: %s", equipment->category);
        printf("\nEquipment acquisition date: %d/%d/%d", equipment->acquisitionDate.day, equipment->acquisitionDate.month,
               equipment->acquisitionDate.year);
        printf("\nEquipment state: %s", getStateString(equipment->state));
        printf("\n");
    }
}

const char *getStateString(stateEquipment state) {
    switch (state) {
        case OPERATIONAL:
            return "Operational";
        case MAINTENANCE:
            return "Maintenance";
        case NON_OPERATION:
            return "Non-Operational";
        case RECYCLING:
            return "Recycling";
    }
}

