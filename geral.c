#include "geral.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "user.h"
#include "equipments.h"
#include <ctype.h>

/**
 * @brief Clears the input buffer.
 *
 * This function clears the standard input buffer by reading characters until a newline character or EOF is encountered.
 * It is useful to clear the input buffer after reading input to prevent unwanted characters from affecting subsequent input operations.
 */
void cleanInputBuffer() {
    char ch;
    while ((ch = getchar() != '\n' && ch != EOF));
}

int getInt(int minValor, int maxValor, char *message) {
    int valor = 0, i = 0;
    char input[maxValor];

    while (valor == 0) {
        printf(" %s", message);

        if (scanf(" %s", input) != 1) {
            printf(INVALID_VALOR);
            cleanInputBuffer();
            continue;
        }

        while (input[i] != '\0') {
            if (!isdigit(input[i])) {
                printf(INVALID_VALOR);
                cleanInputBuffer();
                break;
            }
            i++;
        }

        if (input[i] == '\0') {
            valor = atoi(input);
            if (valor >= minValor && valor <= maxValor) {
                break;
            } else {
                printf(INVALID_VALOR);
            }
        }
    }

    cleanInputBuffer();
    return valor;
}

/**
 * @brief Reads a string from the standard input.
 *
 * This function prompts the user with a message and reads a string from the standard input.
 * It stores the string in the provided character array and ensures that it does not exceed the specified maximum length.
 * The function handles newline characters, ensuring proper string termination.
 *
 * @param string Pointer to the character array to store the input string.
 * @param max Maximum length of the input string (including the null terminator).
 * @param message The message to be displayed as a prompt for the user.
 */
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

/**
 * @brief Verifies if the counter is greater than the specified beginning counter.
 *
 * This function checks if the provided counter is greater than the predefined beginning counter.
 * If the counter is greater, it returns 1; otherwise, it displays a specified message and returns 0.
 *
 * @param counter The counter value to be verified.
 * @param message The message to be displayed if the counter is not greater than the beginning counter.
 * @return Returns 1 if the counter is greater than the beginning counter, otherwise returns 0.
 */
int verifyCounter(int counter, char *message) {
    if (counter > BEGIN_COUNTER) {
        return 1;
    } else {
        puts(message);
        return 0;
    }
}

/**
 * @brief Displays a formatted header with the specified title.
 *
 * This function prints a formatted header with a specified title.
 *
 * @param title The title to be displayed in the header.
 */
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

/**
 * @brief Gets a date from the user and stores it in the specified variables.
 *
 * This function prompts the user to enter a day, month, and year, and stores the values in the provided variables.
 *
 * @param day Pointer to the variable to store the day.
 * @param month Pointer to the variable to store the month.
 * @param year Pointer to the variable to store the year.
 * @param msg The message to be displayed before getting the date.
 */
void getDate(int *day, int *month, int *year, char *msg) {
    puts(msg);
    *day = getInt(MIN_DAY,MAX_DAY,MSG_INSERT_DAY);
    *month = getInt(MIN_MONTH,MAX_MONTH,MSG_INSERT_MONTH);
    *year = getInt(MIN_YEAR,MAX_YEAR,MSG_INSERT_YEAR);
}

/**
 * @brief Frees the memory allocated for users, equipments, and categories.
 *
 * This function frees the memory allocated for the Users, Equipments, and Categories structures.
 *
 * @param users The Users structure to be freed.
 * @param equipments The Equipments structure to be freed.
 * @param categories The Categories structure to be freed.
 */
void freeMemory(Users users, Equipments equipments, Categories categories) {
    free(users.users);
    free(categories.categories);
    for (int i = BEGIN_COUNTER; i < equipments.counterEquipment; i++) {
        free(equipments.equipments[i].maintenanceHistory);
    }
    free(equipments.equipments);
}

