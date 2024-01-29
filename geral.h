#ifndef TRABALHO_LP_GERAL_H
#define TRABALHO_LP_GERAL_H
#define INVALID_VALOR "Valor invalid!"

#include "user.h"
#include "equipments.h"

#define MSG_INSERT_DAY "Insert day:"
#define MSG_INSERT_MONTH "Insert month:"
#define MSG_INSERT_YEAR "Insert year:"

void cleanInputBuffer();
int getInt(int minValor, int maxValor, char *message);
void readString(char *string, unsigned int max, char *message);
int verifyCounter(int counter, char *message);
void header(char *txt);
void getDate(int *day, int *month, int *year, char *msg);
void freeMemory(Users users, Equipments equipments, Categories categories);

#endif
