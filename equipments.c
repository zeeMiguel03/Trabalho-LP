#include "equipments.h"
#include "geral.h"
#include "user.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "listings.h"

void bootEquipments(Equipments *equipments, Categories *categories) {
    FILE *file = fopen(FILE_EQUIPMENTS, "rb");
    if (file == NULL) {
        file = fopen(FILE_EQUIPMENTS, "wb");
        equipments->counterEquipment = 1;
        equipments->maxEquipments = 5;
        categories->counterCategory = 1;
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

    for (int i = 1; i < equipments->counterEquipment; i++) {
        fread(&equipments->equipments[i].counterMaintenance, sizeof(int), 1, file);
        fread(&equipments->equipments[i].maxMaintenance, sizeof(int), 1, file);
        equipments->equipments[i].maintenanceHistory = (MaintenanceHistory *)malloc(sizeof(MaintenanceHistory) * equipments->equipments[equipments->counterEquipment].maxMaintenance);
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

    for (int i = 1; i < equipments->counterEquipment; i++) {
        fwrite(&equipments->equipments[i].counterMaintenance, sizeof(int), 1, file);
        fwrite(&equipments->equipments[i].maxMaintenance, sizeof(int), 1, file);
        fwrite(equipments->equipments[i].maintenanceHistory, sizeof(MaintenanceHistory), equipments->equipments[i].counterMaintenance, file);
    }

    fclose(file);
}

void insertEquipment(Equipments *equipments, Categories *categories) {
    equipments->equipments[equipments->counterEquipment].identify = equipments->counterEquipment;
    readString(equipments->equipments[equipments->counterEquipment].designation, MAX_DESIGNATION, MSG_GET_DESIGNATION);
    getDate(equipments->equipments[equipments->counterEquipment].acquisitionDate.day, equipments->equipments[equipments->counterEquipment].acquisitionDate.month,
            equipments->equipments[equipments->counterEquipment].acquisitionDate.year, MSG_GET_DATE_ACQUISITION);
    equipments->equipments[equipments->counterEquipment].state = getInt(1, 4, MSG_GET_STATE_EQUIPMENT);
    getCategory(equipments, categories);
    bootEquipmentMaintenance(equipments, equipments->counterEquipment);
    equipments->counterEquipment++;
    saveEquipments(equipments, categories);
}

void bootEquipmentMaintenance(Equipments *equipments, int equipmentIndex) {
    equipments->equipments[equipmentIndex].counterMaintenance = 1;
    equipments->equipments[equipmentIndex].maxMaintenance = 5;
    equipments->equipments[equipmentIndex].maintenanceHistory = (MaintenanceHistory *)malloc(sizeof(MaintenanceHistory) * equipments->equipments[equipments->counterEquipment].maxMaintenance);
}

int listCategory(Categories *categories) {
    int index = verifyCounter(categories->counterCategory, MSG_CREATE_CATEGORY), i;
    if (index != 0) {
        puts("-------Category List -------");
        for (i = 1; i < categories->counterCategory; i++) {
            printf("\n%d - %s", i, categories->categories[i].category);
        }
        puts("\n----------------------------");
        return 0;
    }
    return -1;
}

void getCategory(Equipments *equipments, Categories *categories) {
    int index = listCategory(categories), option;
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

int searchEquipment(Equipments *equipments, int number) {
    int verify = verifyCounter(equipments->counterEquipment, NO_EQUIPMENTS), i;
    if (verify == 1) {
        for (i = 0; i < equipments->counterEquipment; i++) {
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

void addMaintenance(Equipments *equipments, Categories *categories) {
    int equipment = getInt(1, equipments->counterEquipment, MSG_CHOOSE_EQUIPMENT);
    int index = searchEquipment(equipments, equipment);
    if (index != -1) {
        equipments->equipments[index].maintenanceHistory[equipments->equipments[index].counterMaintenance].movementNumber = equipments->equipments[index].counterMaintenance;
        getDate(equipments->equipments[index].maintenanceHistory[equipments->equipments[index].counterMaintenance].date.day,
                equipments->equipments[index].maintenanceHistory[equipments->equipments[index].counterMaintenance].date.month,
                equipments->equipments[index].maintenanceHistory[equipments->equipments[index].counterMaintenance].date.year, MSG_GET_DATE_MAINTENANCE);
        readString(equipments->equipments[index].maintenanceHistory[equipments->equipments[index].counterMaintenance].notes, MAX_NOTES_LENGTH, MSG_GET_NOTE_MAINTENANCE);
        readString(equipments->equipments[index].maintenanceHistory[equipments->equipments[index].counterMaintenance].maintenanceType, MAX_TYPE_MAIN, MSG_GET_TYPE_MAINTENANCE);
        equipments->equipments[index].counterMaintenance++;
        saveEquipments(equipments, categories);
    }
}

