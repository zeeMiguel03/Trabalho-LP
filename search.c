#include "search.h"
#include "equipments.h"
#include "string.h"
#include "listings.h"
#include "geral.h"
#include "stdio.h"

/**
 * @brief Search for equipment by identification number.
 *
 * This function searches for an equipment in the Equipments structure by its identification number.
 *
 * @param equipments Pointer to the Equipments structure.
 * @param number Identification number of the equipment to be searched.
 * @return The index of the equipment if found, -1 if not found.
 */
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

/**
 * @brief Search for equipment by state.
 *
 * This function searches and prints equipment based on the specified state.
 *
 * @param equipments Pointer to the Equipments structure.
 */
void searchEquipmentState(Equipments *equipments) {
    int i, counter = 0;
    stateEquipment state;
    state = getInt(1, 4, SEARCH_BY_STATE);

    for (i = BEGIN_COUNTER; i < equipments->counterEquipment; i++) {
        if (equipments->equipments[i].state == state) {
            printEquipment(&equipments->equipments[i]);
            printEquipmentRecycle(&equipments->equipments[i]);
            counter++;
        }
    }

    if (counter == 0) {
            printf(ERROR_SEARCH_STATE);
    }
}

/**
 * @brief Search for equipment by name.
 *
 * This function searches and prints equipment based on the specified name.
 *
 * @param equipments Pointer to the Equipments structure.
 */
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

/**
 * @brief Search for equipment by category.
 *
 * This function searches and prints equipment based on the specified category.
 *
 * @param equipments Pointer to the Equipments structure.
 */
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

/**
 * @brief Search for equipment by date.
 *
 * This function searches and prints equipment based on the specified acquisition date.
 *
 * @param equipments Pointer to the Equipments structure.
 */
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

