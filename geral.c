#include "geral.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "user.h"
#include "equipments.h"

void cleanInputBuffer() {
    char ch;
    while ((ch = getchar() != '\n' && ch != EOF));
}


int getInt(int minValor, int maxValor, char *message) {
    int valor;
    printf(" %s", message);
    scanf(" %d", &valor);

    while (valor < minValor || valor > maxValor) {
        printf(INVALID_VALOR);
        cleanInputBuffer();
        printf(" %s", message);
        scanf(" %d", &valor);
    }
    cleanInputBuffer();
    return valor;
}


void readString(char *string, unsigned int max, char *message) {
    printf(" %s", message);
    if (fgets(string, max, stdin) != NULL) {
        unsigned int len = strlen(string) - 1;
        if (string[len] == '\n') {
            string[len] = '\0';
        } else {
            cleanInputBuffer();
        }
    }
}


int verifyCounter(int counter, char *message) {
    if (counter > BEGIN_COUNTER) {
        return 1;
    } else {
        puts(message);
        return 0;
    }
}

void header(char *title) {
    printf("\n");
    printf("##########################################################\n");
    printf("|                                                        |\n");
    printf("|               tracking the technology Park             |\n");
    printf("|                                                        |\n");
    printf("##########################################################\n");
    printf("\n");
    printf("                        %s\n", title);
}

void getDate(int *day, int *month, int *year, char *msg) {
    puts(msg);
    *day = getInt(1,31,MSG_INSERT_DAY);
    *month = getInt(1,12,MSG_INSERT_MONTH);
    *year = getInt(1900,2024,MSG_INSERT_YEAR);
}


void freeMemory(Users users, Equipments equipments, Categories categories) {
    free(users.users);
    free(categories.categories);
    for (int i = BEGIN_COUNTER; i < equipments.counterEquipment; i++) {
        free(equipments.equipments[i].maintenanceHistory);
    }
    free(equipments.equipments);
}

