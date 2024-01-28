#include "listings.h"
#include "user.h"
#include "equipments.h"
#include "stdio.h"

void listUsers(Users users) {
    int i;
    for (i = 1; i < users.counterUsers; i++) {
        printf("\nUser name: %s", users.users[i].name);
        printf("\nUser acronym: %s", users.users[i].acronym);
        printf("\nUser number: %d", users.users[i].codIdentify);
        printf("\nUser code: %d", users.users[i].codIdentify);
        printf("\nUser equipment number: %d", users.users[i].numberEquipments);
        printf("\nUser function: %s", users.users[i].functionUser);
        printf("\n");
    }
}

void listRecycling(Equipments equipments) {
    int i;
    for (i = 1; i < equipments.counterEquipment; i++) {
        if (equipments.equipments[i].state == RECYCLING) {
            printf("\n");
        }
    }
}

