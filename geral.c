#include "geral.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

/**
 * @brief Clears the input buffer.
 */
void cleanInputBuffer() {
    char ch;
    while ((ch = getchar() != '\n' && ch != EOF));
}

/**
 * @brief Gets an integer value within a specific range.
 *
 * @param minValor The minimum allowed value.
 * @param maxValor The maximum allowed value.
 * @param message The message to be displayed to request input.
 * @return The integer value entered by the user within the specified range.
 */
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
//ss//
/**
 * @brief Reads a string from the standard input, removing the newline character if present.
 *
 * @param string Pointer to the string where to store the input.
 * @param max The maximum length of the string.
 * @param message The message to be displayed to request input.
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
 * @brief Verifies if the counter is greater than zero.
 *
 * @param counter The value of the counter to be checked.
 * @param message The message to be displayed if the counter is not greater than zero.
 * @return Returns 1 if the counter is greater than zero, 0 otherwise.
 */
int verifyCounter(int counter, char *message) {
    if (counter > 1) {
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
    printf("                         %s\n", title);
}

void getDate(int day, int month, int year, char *msg) {
    puts(msg);
    day = getInt(1,31,MSG_INSERT_DAY);
    month = getInt(1,12,MSG_INSERT_MONTH);
    year = getInt(1900,2024,MSG_INSERT_YEAR);
}