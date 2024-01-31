#include "geral.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "listings.h"
#include "search.h"

void bootEquipments(Equipments *equipments, Categories *categories) {
    FILE *file = fopen(FILE_EQUIPMENTS, "rb");
    if (file == NULL) {
        file = fopen(FILE_EQUIPMENTS, "wb");
        equipments->counterEquipment = BEGIN_COUNTER;
        equipments->maxEquipments = 5;
        categories->counterCategory = BEGIN_COUNTER;
        categories->maxCategories = 10;
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

void insertEquipment(Equipments *equipments, Categories *categories) {
    relocateEquip(equipments);
    equipments->equipments[equipments->counterEquipment].identify = equipments->counterEquipment;
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

void bootEquipmentMaintenance(Equipments *equipments, int equipmentIndex) {
    equipments->equipments[equipmentIndex].counterMaintenance = 1;
    equipments->equipments[equipmentIndex].maxMaintenance = 5;
    equipments->equipments[equipmentIndex].maintenanceHistory = (MaintenanceHistory *)malloc(sizeof(MaintenanceHistory) * equipments->equipments[equipmentIndex].maxMaintenance);
}

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

void addMaintenance(Equipments *equipments, Categories *categories) {
    int equipment = getInt(1, equipments->counterEquipment, MSG_CHOOSE_EQUIPMENT);
    int index = searchEquipmentNumber(equipments, equipment);
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

void removeEquipment(Equipments *equipments, Categories *categories) {
    int index, optionEquip;
    if (verifyCounter(equipments->counterEquipment, NO_EQUIPMENTS) == 1) {
        optionEquip = getInt(1, equipments->counterEquipment, MSG_CHOOSE_EQUIPMENT);
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

void addEquipmentUser(Users *users, Equipments *equipments, Categories *categories) {
    int i, getEquipment, getUser;
    if (verifyCounter(equipments->counterEquipment, NO_EQUIPMENTS) == 1) {
        if (verifyCounter(users->counterUsers, NO_USERS) == 1) {
            for (i = BEGIN_COUNTER; i < equipments->counterEquipment; i++) {
                if (equipments->equipments[i].userIdentify == 0) {
                    printf("\nEquipment number: %d", equipments->equipments[i].identify);
                    printf("\nEquipment designation: %s", equipments->equipments[i].designation);
                    printf("\nEquipment category: %s", equipments->equipments[i].category);
                    printf("\nEquipment acquisition date: %d/%d/%d", equipments->equipments[i].acquisitionDate.day, equipments->equipments[i].acquisitionDate.month,
                           equipments->equipments[i].acquisitionDate.year);
                    printf("\n");
                }
            }

            getEquipment = getInt(BEGIN_COUNTER, equipments->counterEquipment, MSG_GET_EQUIPMENT);
            getUser = getInt(BEGIN_COUNTER, users->counterUsers, MSG_CHOOSE_USER);

            if (users->users[getUser].state == ACTIVE) {
                equipments->equipments[getEquipment].userIdentify = users->users[getUser].codIdentify;
                users->users[getUser].numberEquipments++;
                saveEquipments(equipments, categories);
                saveUsers(users);
            } else {
                puts(ERROR_USER_INACTIVE);
            }
        }
    }
}
