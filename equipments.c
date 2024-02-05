#include "geral.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "listings.h"
#include "search.h"

/**
 * @brief Boots the equipment data from a file or initializes a new file if not found.
 *
 * This function reads equipment and category data from a file or initializes a new file
 * if not found. It populates the Equipments and Categories structures with the data.
 *
 * @param equipments Pointer to the Equipments structure.
 * @param categories Pointer to the Categories structure.
 */
void bootEquipments(Equipments *equipments, Categories *categories) {
    FILE *file = fopen(FILE_EQUIPMENTS, "rb");
    if (file == NULL) {
        file = fopen(FILE_EQUIPMENTS, "wb");
        equipments->counterEquipment = BEGIN_COUNTER;
        equipments->maxEquipments = MAX_EQUIP;
        categories->counterCategory = BEGIN_COUNTER;
        categories->maxCategories = MAX_CATE;
        fclose(file);
    }

    fread(&equipments->counterEquipment, sizeof(int), 1, file);
    fread(&equipments->maxEquipments, sizeof(int), 1, file);
    equipments->equipments = (Equipment*) malloc(sizeof(Equipment) * equipments->maxEquipments);
    fread(equipments->equipments, sizeof(Equipment), equipments->counterEquipment, file);

    fread(&categories->counterCategory, sizeof(int), 1, file);
    fread(&categories->maxCategories, sizeof(int), 1, file);
    categories->categories = (Category*)malloc(sizeof(Category) * categories->maxCategories);
    fread(categories->categories, sizeof(Category), categories->counterCategory, file);

    for (int i = BEGIN_COUNTER; i < equipments->counterEquipment; i++) {
        fread(&equipments->equipments[i].counterMaintenance, sizeof(int), 1, file);
        fread(&equipments->equipments[i].maxMaintenance, sizeof(int), 1, file);
        equipments->equipments[i].maintenanceHistory = (MaintenanceHistory *)malloc(sizeof(MaintenanceHistory) * equipments->equipments[i].maxMaintenance);
        fread(equipments->equipments[i].maintenanceHistory, sizeof(MaintenanceHistory), equipments->equipments[i].counterMaintenance, file);
    }

    fclose(file);
}

/**
 * @brief Saves the equipment and category data to a file.
 *
 * This function saves the current state of the Equipments and Categories structures to a file.
 *
 * @param equipments Pointer to the Equipments structure.
 * @param categories Pointer to the Categories structure.
 */
void saveEquipments(Equipments *equipments, Categories *categories) {
    FILE *file = fopen(FILE_EQUIPMENTS, "wb");
    if (file == NULL) {
        exit(EXIT_FAILURE);
    }

    fwrite(&equipments->counterEquipment, sizeof(int), 1, file);
    fwrite(&equipments->maxEquipments, sizeof(int), 1, file);
    fwrite(equipments->equipments, sizeof(Equipment), equipments->counterEquipment, file);

    fwrite(&categories->counterCategory, sizeof(int), 1, file);
    fwrite(&categories->maxCategories, sizeof(int), 1, file);
    fwrite(categories->categories, sizeof(Category), categories->counterCategory, file);

    for (int i = BEGIN_COUNTER; i < equipments->counterEquipment; i++) {
        fwrite(&equipments->equipments[i].counterMaintenance, sizeof(int), 1, file);
        fwrite(&equipments->equipments[i].maxMaintenance, sizeof(int), 1, file);
        fwrite(equipments->equipments[i].maintenanceHistory, sizeof(MaintenanceHistory), equipments->equipments[i].counterMaintenance, file);
    }

    fclose(file);
}

/**
 * @brief Relocates memory for the Equipments structure if necessary.
 *
 * This function checks if the current number of equipments has reached the maximum limit,
 * and if so, it reallocates memory to accommodate more equipment entries.
 *
 * @param equipments Pointer to the Equipments structure.
 */
void relocateEquip(Equipments *equipments) {
    if (equipments->maxEquipments == equipments->counterEquipment) {
        Equipment *pEquipment = realloc(equipments->equipments, sizeof(Equipment) * (equipments->maxEquipments * 2));
        if (pEquipment == NULL) {
            exit(EXIT_FAILURE);
        }

        equipments->equipments = pEquipment;
        equipments->maxEquipments *= 2;
    }
}

/**
 * @brief Relocates memory for the Categories structure if necessary.
 *
 * This function checks if the current number of categories has reached the maximum limit,
 * and if so, it reallocates memory to accommodate more category entries.
 *
 * @param categories Pointer to the Categories structure.
 */
void relocateCategories(Categories *categories) {
    if (categories->maxCategories == categories->counterCategory) {
        Category *pCategory = realloc(categories->categories, sizeof(Category) * (categories->maxCategories * 2));
        if (pCategory == NULL) {
            exit(EXIT_FAILURE);
        }

        categories->categories = pCategory;
        categories->maxCategories *= 2;
    }
}

/**
 * @brief Relocates memory for maintenance history if necessary.
 *
 * This function checks if the maintenance history for each equipment has reached its limit,
 * and if so, it reallocates memory to accommodate more maintenance history entries.
 *
 * @param equipments Pointer to the Equipments structure.
 */
void relocateMaintenance(Equipments *equipments) {
    int i;
    for (i = BEGIN_COUNTER; i < equipments->counterEquipment; i++) {
        if (equipments->equipments[i].maxMaintenance == equipments->equipments[i].counterMaintenance) {
            MaintenanceHistory *pMaintenance = realloc(equipments->equipments[i].maintenanceHistory, sizeof(MaintenanceHistory)
            * (equipments->equipments[i].maxMaintenance * 2));

            if (pMaintenance == NULL) {
                exit(EXIT_FAILURE);
            }

            equipments->equipments[i].maintenanceHistory = pMaintenance;
            equipments->equipments[i].maxMaintenance *= 2;
        }
    }
}

/**
 * @brief Inserts a new equipment into the system.
 *
 * This function adds a new equipment to the Equipments structure, prompting the user for
 * relevant information such as designation, acquisition date, state, and category.
 *
 * @param equipments Pointer to the Equipments structure.
 * @param categories Pointer to the Categories structure.
 */
void insertEquipment(Equipments *equipments, Categories *categories) {
    relocateEquip(equipments);

    equipments->equipments[equipments->counterEquipment].identify = verifyExistentNumber(equipments,equipments->counterEquipment);

    readString(equipments->equipments[equipments->counterEquipment].designation, MAX_DESIGNATION, MSG_GET_DESIGNATION);
    getDate(&equipments->equipments[equipments->counterEquipment].acquisitionDate.day, &equipments->equipments[equipments->counterEquipment].acquisitionDate.month,
            &equipments->equipments[equipments->counterEquipment].acquisitionDate.year, MSG_GET_DATE_ACQUISITION);
    equipments->equipments[equipments->counterEquipment].state = getInt(1, 4, MSG_GET_STATE_EQUIPMENT);
    equipments->equipments[equipments->counterEquipment].userIdentify = 0;

    getCategory(equipments, categories);

    bootEquipmentMaintenance(equipments,equipments->counterEquipment);
    equipments->counterEquipment++;
    saveEquipments(equipments, categories);
}

/**
 * @brief Initializes maintenance history for a given equipment.
 *
 * This function initializes the maintenance history for a specific equipment,
 * setting the counters and allocating memory for maintenance history entries.
 *
 * @param equipments Pointer to the Equipments structure.
 * @param equipmentIndex Index of the equipment for which maintenance history is being initialized.
 */
void bootEquipmentMaintenance(Equipments *equipments, int equipmentIndex) {
    equipments->equipments[equipmentIndex].counterMaintenance = BEGIN_COUNTER;
    equipments->equipments[equipmentIndex].maxMaintenance = MAX_MANU;
    equipments->equipments[equipmentIndex].maintenanceHistory = (MaintenanceHistory *)malloc(sizeof(MaintenanceHistory) *
            equipments->equipments[equipmentIndex].maxMaintenance);
}

/**
 * @brief Gets the category for a new equipment.
 *
 * This function prompts the user to choose an existing category or create a new one
 * for a new equipment. It then assigns the selected or created category to the equipment.
 *
 * @param equipments Pointer to the Equipments structure.
 * @param categories Pointer to the Categories structure.
 */
void getCategory(Equipments *equipments, Categories *categories) {
    int index = listCategory(categories), option;
    relocateCategories(categories);

    if (index != -1) {
        option = getInt(1, 2, OPTION_CATEGORY);
        switch (option) {
            case 1:
                option = getInt(1, categories->counterCategory, MSG_CHOOSE_CATEGORY);
                strcpy(equipments->equipments[equipments->counterEquipment].category, categories->categories[option].category);
                break;
            case 2:
                readString(categories->categories[categories->counterCategory].category, MAX_CATEGORY, MSG_CREATE_CATEGORY);
                strcpy(equipments->equipments[equipments->counterEquipment].category, categories->categories[categories->counterCategory].category);
                categories->counterCategory++;
                saveEquipments(equipments, categories);
                break;
        }
    } else {
        readString(categories->categories[categories->counterCategory].category, MAX_CATEGORY, "");
        strcpy(equipments->equipments[equipments->counterEquipment].category, categories->categories[categories->counterCategory].category);
        categories->counterCategory++;
        saveEquipments(equipments, categories);
    }
}

/**
 * @brief Adds maintenance history for a specific equipment.
 *
 * This function adds maintenance history entries for a specific equipment, prompting
 * the user for relevant information such as date, notes, and maintenance type.
 *
 * @param equipments Pointer to the Equipments structure.
 * @param categories Pointer to the Categories structure.
 */
void addMaintenance(Equipments *equipments, Categories *categories) {
    int equipment;
    int index;

    listEquipments(*equipments);
    equipment = getInt(1, equipments->counterEquipment, MSG_CHOOSE_EQUIPMENT);
    index = searchEquipmentNumber(equipments, equipment);

    relocateMaintenance(equipments);
    
    if (index != -1) {
        equipments->equipments[index].maintenanceHistory[equipments->equipments[index].counterMaintenance].movementNumber = equipments->equipments[index].counterMaintenance;
        getDate(&equipments->equipments[index].maintenanceHistory[equipments->equipments[index].counterMaintenance].date.day,
                &equipments->equipments[index].maintenanceHistory[equipments->equipments[index].counterMaintenance].date.month,
                &equipments->equipments[index].maintenanceHistory[equipments->equipments[index].counterMaintenance].date.year, MSG_GET_DATE_MAINTENANCE);
        readString(equipments->equipments[index].maintenanceHistory[equipments->equipments[index].counterMaintenance].notes, MAX_NOTES_LENGTH, MSG_GET_NOTE_MAINTENANCE);
        readString(equipments->equipments[index].maintenanceHistory[equipments->equipments[index].counterMaintenance].maintenanceType, MAX_TYPE_MAIN, MSG_GET_TYPE_MAINTENANCE);
        equipments->equipments[index].counterMaintenance++;
        saveEquipments(equipments, categories);
    }
}

/**
 * @brief Removes an equipment from the system.
 *
 * This function removes an equipment from the Equipments structure, provided that
 * the equipment is in the recycling state. It updates counters and saves the changes.
 *
 * @param equipments Pointer to the Equipments structure.
 * @param categories Pointer to the Categories structure.
 */
void removeEquipment(Equipments *equipments, Categories *categories) {
    int index, optionEquip;
    if (verifyCounter(equipments->counterEquipment, NO_EQUIPMENTS) == 1) {

        if (listRecyclingEquip(equipments) == 0) {
            return;
        }

        optionEquip = getInt(1, equipments->counterEquipment, MSG_CHOOSE_DELETE);
        index = searchEquipmentNumber(equipments, optionEquip);
        if (index != -1) {
            if (equipments->equipments[index].state != RECYCLING) {
                puts(ERROR_DEL_EQUIP);
                return;
            } else {
                free(equipments->equipments[index].maintenanceHistory);

                for (int i = index; i < equipments->counterEquipment - 1; i++) {
                    equipments->equipments[i] = equipments->equipments[i + 1];
                }

                equipments->counterEquipment--;
                puts(SUCCESS_DEL_EQUIP);
                saveEquipments(equipments, categories);
            }
        }
    }
}

/**
 * @brief Adds an equipment to a specific user.
 *
 * This function adds an equipment to a specific user, updating counters and saving changes
 * if conditions are met, such as the user being active and the equipment not being in recycling state.
 *
 * @param users Pointer to the Users structure.
 * @param equipments Pointer to the Equipments structure.
 * @param categories Pointer to the Categories structure.
 */
void addEquipmentUser(Users *users, Equipments *equipments, Categories *categories) {
    int i, getEquipment, getUser;
    if (verifyCounter(equipments->counterEquipment, NO_EQUIPMENTS) == 1) {
        if (verifyCounter(users->counterUsers, NO_USERS) == 1) {

            for (i = BEGIN_COUNTER; i < equipments->counterEquipment; i++) {
                if (equipments->equipments[i].userIdentify == 0) {
                    printEquipment(&equipments->equipments[i]);
                }
            }

            getEquipment = getInt(BEGIN_COUNTER, equipments->counterEquipment, MSG_GET_EQUIPMENT);

            listUsers(*users);
            getUser = getInt(BEGIN_COUNTER, users->counterUsers, MSG_CHOOSE_USER);

            if (searchEquipmentNumber(equipments, getEquipment) != -1) {
                if (users->users[getUser].state == ACTIVE) {
                    if (equipments->equipments[getEquipment].state != RECYCLING) {
                        if (equipments->equipments[getEquipment].userIdentify == 0) {
                            equipments->equipments[getEquipment].userIdentify = users->users[getUser].codIdentify;
                            users->users[getUser].numberEquipments++;
                            saveEquipments(equipments, categories);
                            saveUsers(users);
                        } else {
                            puts(ERROR_ALREADY_USER);
                        }
                    } else {
                        puts(ERROR_RECYCLE_EQUIP);
                    }
                } else {
                    puts(ERROR_USER_INACTIVE);
                }
            }
        }
    }
}

/**
 * @brief Checks if a given equipment number is already in use.
 *
 * This function checks if a given equipment number is already in use by comparing it
 * against existing equipment numbers in the Equipments structure.
 *
 * @param equipments Pointer to the Equipments structure.
 * @param number Equipment number to check for availability.
 * @return 1 if the number is in use, 0 otherwise.
 */
int isNumberInUse(Equipments *equipments, int number) {
    for (int i = BEGIN_COUNTER; i < equipments->counterEquipment; i++) {
        if (equipments->equipments[i].identify == number) {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Verifies and returns an available equipment number.
 *
 * This function verifies if a given equipment number is in use. If it is, it increments
 * the number until an available number is found and returns it.
 *
 * @param equipments Pointer to the Equipments structure.
 * @param number Proposed equipment number to check and modify if necessary.
 * @return An available equipment number.
 */
int verifyExistentNumber(Equipments *equipments, int number) {
   if (isNumberInUse(equipments, number) == 1) {
       do {
           number += 1;
       } while (isNumberInUse(equipments, number) == 1);
       return number;
   } else {
       return number;
   }
}


