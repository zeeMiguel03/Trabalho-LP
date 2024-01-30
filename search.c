#include "search.h"
#include "equipments.h"
#include "user.h"
#include "listings.h"
#include "geral.h"
#include "stdio.h"

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

