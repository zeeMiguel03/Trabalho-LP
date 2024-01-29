#include "equipments.h"
#include "geral.h"
#include "user.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

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
    fclose(file);
}

void insertEquipment(Equipments *equipments, Categories *categories) {
    equipments->equipments[equipments->counterEquipment].identify = equipments->counterEquipment;
    readString(equipments->equipments[equipments->counterEquipment].designation, MAX_DESIGNATION, MSG_GET_DESIGNATION);
    getDate(equipments->equipments[equipments->counterEquipment].acquisitionDate.day, equipments->equipments[equipments->counterEquipment].acquisitionDate.month,
            equipments->equipments[equipments->counterEquipment].acquisitionDate.year, MSG_GET_DATE_ACQUISITION);
    equipments->equipments[equipments->counterEquipment].state = getInt(1, 4, MSG_GET_STATE_EQUIPMENT);
    getCategory(equipments, categories);
    equipments->counterEquipment++;
    saveEquipments(equipments, categories);
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

