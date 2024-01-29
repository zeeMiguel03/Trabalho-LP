#ifndef TRABALHO_LP_EQUIPMENTS_H
#define TRABALHO_LP_EQUIPMENTS_H
//ss//
#define MAX_CATEGORY 20
#define MAX_NAME_LENGTH 50
#define MAX_NOTES_LENGTH 100
#define MAX_DESIGNATION 20

#define MSG_GET_DESIGNATION "Insert equipment designation: "
#define MSG_GET_DATE_ACQUISITION "Insert acquisition date"
#define MSG_GET_STATE_EQUIPMENT "Insert equipment state '1 - Operation, 2 - Maintenance, 3 - Non-Operational, 4 - Recycling': "
#define MSG_CHOOSE_CATEGORY "Choose a category:"
#define MSG_CREATE_CATEGORY "Insert a new category name: "

#define FILE_EQUIPMENTS "fileEquipment.bin"

#define OPTION_CATEGORY "\n1 - Use existent category\n2 - Create a new category\n  Choose:"

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
    Category *categories;
    int counterCategory, maxCategories;
}Categories;

typedef struct {
    int identify;
    char designation[MAX_DESIGNATION];
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

void bootEquipments(Equipments *equipments, Categories *categories);
void saveEquipments(Equipments *equipments, Categories *categories);
void insertEquipment(Equipments *equipments, Categories *categories);
int listCategory(Categories *categories);
void getCategory(Equipments *equipments, Categories *categories);

#endif
