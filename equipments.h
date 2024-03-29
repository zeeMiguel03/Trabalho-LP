#include "user.h"
#ifndef TRABALHO_LP_EQUIPMENTS_H
#define TRABALHO_LP_EQUIPMENTS_H

#define MAX_CATEGORY 20
#define MAX_NOTES_LENGTH 100
#define MAX_DESIGNATION 20
#define MAX_TYPE_MAIN 30
#define MAX_EQUIP 5
#define MAX_CATE 10
#define MAX_MANU 5

#define MSG_GET_DESIGNATION "Insert equipment designation: "
#define MSG_GET_DATE_ACQUISITION "Insert acquisition date"
#define MSG_GET_STATE_EQUIPMENT "Insert equipment state '1 - Operation, 2 - Maintenance, 3 - Non-Operational, 4 - Recycling': "
#define MSG_CHOOSE_CATEGORY "Choose a category by number:"
#define MSG_CREATE_CATEGORY "Insert a new category name: "
#define MSG_CHOOSE_EQUIPMENT "\nChoose a equipment to maintenance:"
#define MSG_CHOOSE_DELETE "Choose a equipment to delete:"
#define MSG_CHOOSE_USER "Choose user: "
#define MSG_GET_EQUIPMENT "Choose a equipment by the number:"

#define MSG_GET_DATE_MAINTENANCE "Maintenance date"
#define MSG_GET_TYPE_MAINTENANCE "Maintenance type:"
#define MSG_GET_NOTE_MAINTENANCE "Insert a note:"

#define ERROR_ALREADY_USER "This equipment is already associated!"
#define ERROR_DEL_EQUIP "You cannot delete this equipment!"
#define ERROR_USER_INACTIVE "User is not in active status. Cannot assign equipment!"
#define ERROR_RECYCLE_EQUIP "You cannot add a recycle equipment to a user!"
#define SUCCESS_DEL_EQUIP "Equipment delete with success!"

#define FILE_EQUIPMENTS "fileEquipment.bin"

#define OPTION_CATEGORY "\n1 - Use existent category\n2 - Create a new category\n  Choose:"

#define MSG_EQUIPMENT_NOT_FOUND "Equipment not founded"

typedef enum {OPERATIONAL = 1, MAINTENANCE, NON_OPERATION, RECYCLING} stateEquipment;

typedef struct {
    int day, month, year;
} Date;

typedef struct {
    int movementNumber;
    Date date;
    char maintenanceType[MAX_TYPE_MAIN];
    char notes[MAX_NOTES_LENGTH];
} MaintenanceHistory;

typedef struct {
    char category[MAX_CATEGORY];
}Category;

typedef struct {
    Category *categories;
    int counterCategory, maxCategories;
}Categories;

typedef struct {
    int identify, counterMaintenance, maxMaintenance;
    int userIdentify;
    char designation[MAX_DESIGNATION];
    Date acquisitionDate;
    stateEquipment state;
    char category[MAX_CATEGORY];
    MaintenanceHistory *maintenanceHistory;
} Equipment;

typedef struct {
    int counterEquipment, maxEquipments;
    Equipment *equipments;
} Equipments;

void bootEquipments(Equipments *equipments, Categories *categories);
void saveEquipments(Equipments *equipments, Categories *categories);
void insertEquipment(Equipments *equipments, Categories *categories);
void bootEquipmentMaintenance(Equipments *equipments, int equipmentIndex);
void getCategory(Equipments *equipments, Categories *categories);
void addMaintenance(Equipments *equipments, Categories *categories);
void removeEquipment(Equipments *equipments, Categories *categories);
void addEquipmentUser(Users *users, Equipments *equipments, Categories *categories);
void relocateEquip(Equipments *equipments);
void relocateCategories(Categories *categories);
void relocateMaintenance(Equipments *equipments);
const char *getStateString(stateEquipment state);
int verifyExistentNumber(Equipments *equipments, int number);
int isNumberInUse(Equipments *equipments, int number);

#endif
