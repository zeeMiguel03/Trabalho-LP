#ifndef TRABALHO_LP_GERAL_H
#define TRABALHO_LP_GERAL_H

#define INVALID_VALOR "Valor invalid!"

void cleanInputBuffer();
int getInt(int minValor, int maxValor, char *message);
void readString(char *string, unsigned int max, char *message);
int verifyCounter(int counter, char *message);
void header(char *txt);

#endif
