#ifndef TRABALHO_LP_EQUIPMENTS_H
#define TRABALHO_LP_EQUIPMENTS_H

#define MAX_CATEGORY 20
#define MAX_NAME_LENGTH 50
#define MAX_NOTES_LENGTH 100

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
    int identify;
    Date acquisitionDate;
    stateEquipment state;
    int userCode;
    char category[MAX_CATEGORY];
    MaintenanceHistory maintenanceHistory;
} Equipment;

typedef struct {
    int counterEquipment, maxEquipments;
    Equipment *equipments;
} Equipments;

#endif
