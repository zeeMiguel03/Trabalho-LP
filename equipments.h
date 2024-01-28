#ifndef TRABALHO_LP_EQUIPMENTS_H
#define TRABALHO_LP_EQUIPMENTS_H

#define MAX_CATEGORY 20
#define MAX_NAME_LENGTH 50
#define MAX_NOTES_LENGTH 100
#define MAX_DESIGNATION 20

#define MSG_GET_DESIGNATION "Insert equipment designation: "
#define MSG_GET_CATEGORY "Choose equipment category:"
#define MSG_GET_DATE_ACQUISITION "Insert acquisition date"

#define FILE_EQUIPMENTS "file_equipment.bin"

typedef enum {OPERATIONAL = 1, MAINTENANCE, NON_OPERATION, RECYCLING} stateEquipment;

typedef struct {
    int day, month, year;
} Date;

typedef struct {
    int movementNumber;
    Date date;
    char maintenanceType[MAX_NAME_LENGTH];
    char notes[MAX_NOTES_LENGTH];
} MaintenanceHistory;

typedef struct {
    char category[MAX_CATEGORY];
}Category;

typedef struct {
    int identify;
    char designation[MAX_DESIGNATION];
    Date acquisitionDate;
    stateEquipment state;
    int userCode, counterCategory;
    Category category;
    MaintenanceHistory maintenanceHistory;
} Equipment;

typedef struct {
    int counterEquipment, maxEquipments;
    Equipment *equipments;
} Equipments;

void bootEquipments(Equipments *equipments);
void saveEquipments(Equipments *equipments);
void insertEquipment(Equipments *equipments);

#endif
