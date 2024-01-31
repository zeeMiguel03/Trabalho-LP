#include "search.h"
#include "equipments.h"
#include "string.h"
#include "listings.h"
#include "geral.h"
#include "stdio.h"

int searchEquipmentNumber(Equipments *equipments, int number) {
    int i;
    if (verifyCounter(equipments->counterEquipment, NO_EQUIPMENTS) == 1) {
        for (i = BEGIN_COUNTER; i < equipments->counterEquipment; i++) {
            if (equipments->equipments[i].identify == number) {
                return i;
            }
        }
        puts(MSG_EQUIPMENT_NOT_FOUND);
        return -1;
    } else {
        return -1;
    }
}

void printEquipment(Equipment *equipment) {
    printf("\nEquipment number: %d", equipment->identify);
    printf("\nEquipment designation: %s", equipment->designation);
    printf("\nEquipment category: %s", equipment->category);
    printf("\nEquipment acquisition date: %d/%d/%d", equipment->acquisitionDate.day, equipment->acquisitionDate.month,
           equipment->acquisitionDate.year);
    printf("\n");
}

void searchEquipmentState(Equipments *equipments) {
    int i, counter = 0;
    stateEquipment state;
    state = getInt(1, 3, SEARCH_BY_STATE);

    for (i = BEGIN_COUNTER; i < equipments->counterEquipment; i++) {
        if (equipments->equipments[i].state == state) {
                printEquipment(&equipments->equipments[i]);
                counter++;
        }
    }

    if (counter == 0) {
            printf(ERROR_SEARCH_STATE);
    }
}

void searchEquipmentName(Equipments *equipments) {
    int i, counter = 0;
    char name[MAX_DESIGNATION];
    readString(name, MAX_DESIGNATION, SEARCH_BY_NAME);

    for (i = BEGIN_COUNTER; i < equipments->counterEquipment; i++) {
        if (strcmp(equipments->equipments[i].designation, name) == 0) {
                printEquipment(&equipments->equipments[i]);
                counter++;
        }
    }

    if (counter == 0) {
        printf(ERROR_SEARCH_NAME);
    }
}

void searchEquipmentCategory(Equipments *equipments) {
    int i, counter = 0;
    char category[MAX_DESIGNATION];
    readString(category, MAX_CATEGORY, SEARCH_BY_CATEGORY);

    for (i = BEGIN_COUNTER; i < equipments->counterEquipment; i++) {
        if (strcmp(equipments->equipments[i].category, category) == 0) {
                printEquipment(&equipments->equipments[i]);
                counter++;
        }
    }

    if (counter == 0) {
        printf(ERROR_SEARCH_CATEGORY);
    }
}

void searchEquipmentDate(Equipments *equipments) {
    int i, day, month, year, counter = 0;
    getDate(&day, &month, &year, SEARCH_BY_DATE);

    for (i = BEGIN_COUNTER; i < equipments->counterEquipment; i++) {
        if (equipments->equipments[i].acquisitionDate.day == day && equipments->equipments[i].acquisitionDate.month == month &&
                equipments->equipments[i].acquisitionDate.day) {
                printEquipment(&equipments->equipments[i]);
                counter++;
        }
    }

    if (counter == 0) {
        printf(ERROR_SEARCH_DATE);
    }
}

