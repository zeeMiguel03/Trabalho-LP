#include "equipments.h"
#include "geral.h"
#include "user.h"
#include "stdlib.h"
#include "stdio.h"

void bootEquipments(Equipments *equipments) {
    FILE *file = fopen(FILE_EQUIPMENTS, "rb");
    if (file == NULL) {
        file = fopen(FILE_EQUIPMENTS, "wb");
        equipments->counterEquipment = 1;
        equipments->maxEquipments = 5;
        fclose(file);
    }
    fread(&equipments->counterEquipment, sizeof(int), 1, file);
    fread(&equipments->maxEquipments, sizeof(int), 1, file);
    equipments->equipments = (Equipment*) malloc(sizeof(Equipment) * equipments->maxEquipments);
    fread(equipments->equipments, sizeof(int), equipments->counterEquipment, file);
    fclose(file);
}

void saveEquipments(Equipments *equipments) {
    FILE *file = fopen(FILE_EQUIPMENTS, "wb");
    if (file == NULL) {
        exit(EXIT_FAILURE);
    }
    fwrite(&equipments->counterEquipment, sizeof(int), 1, file);
    fwrite(&equipments->maxEquipments, sizeof(int), 1, file);
    fwrite(equipments->equipments, sizeof(int), equipments->counterEquipment, file);
    fclose(file);
}

void insertEquipment(Equipments *equipments) {
    equipments->equipments[equipments->counterEquipment].identify = equipments->counterEquipment;
    readString(equipments->equipments[equipments->counterEquipment].designation, MAX_DESIGNATION, MSG_GET_DESIGNATION);

}

void listCategory(Equipments *equipments) {
    int i;
    for (i = 0; i < equipments->equipments->counterCategory; i++) {

    }
}
