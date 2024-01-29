#include "user.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "geral.h"
//ss////ss//
void bootUsers(Users *users) {
    FILE *file = fopen(FILE_USER, "rb");
    if (file == NULL) {
        file = fopen(FILE_USER, "wb");
        users->counterUsers = 1;
        users->maxUsers = 5;
        users->users = (User *) malloc(sizeof(User) * users->maxUsers);
        fclose(file);
        return;
    }
    fread(&users->counterUsers, sizeof(int), 1, file);
    fread(&users->maxUsers, sizeof(int), 1, file);
    users->users = (User *) malloc(sizeof(User) * users->maxUsers);
    fread(users->users, sizeof(User), users->counterUsers, file);
    fclose(file);
}

void saveUsers(Users *users) {
    FILE *file = fopen(FILE_USER, "wb");
    if (file == NULL) {
        exit(EXIT_FAILURE);
    }
    fwrite(&users->counterUsers, sizeof(int), 1, file);
    fwrite(&users->maxUsers, sizeof(int), 1, file);
    fwrite(users->users, sizeof(User), users->counterUsers, file);
    fclose(file);
}

void relocateUsers(Users *users) {
    if (users->maxUsers == users->counterUsers) {
        User *pUser = realloc(users->users, sizeof(User) * (users->maxUsers * 2));
        if (pUser == NULL) {
            puts("Error relocating memory");
            return;
        } else {
            users->users = pUser;
            users->maxUsers *= users->maxUsers;
        }
    }
}

int searchUser(Users users, int number) {
    int verify = verifyCounter(users.counterUsers, MSG_NO_USERS), i;
    if (verify == 1) {
        for (i = 0; i < users.counterUsers; i++) {
            if (users.users[i].codIdentify == number) {
                return i;
            }
        }
        puts(MSG_USER_NOT_FOUND);
        return -1;
    } else {
        return -1;
    }
}

void insertUser(Users *users) {
    relocateUsers(users);
    readString(users->users[users->counterUsers].name, MAX_NAME_USER, MSG_GET_USER_NAME);
    readString(users->users[users->counterUsers].acronym, MAX_ACRONYM_USER, MSG_GET_USER_ACRONYM);
    readString(users->users[users->counterUsers].functionUser, MAX_FUNCTION_USER, MSG_GET_USER_FUNCTION);
    users->users[users->counterUsers].codIdentify = users->counterUsers;
    users->users[users->counterUsers].numberEquipments = 0;
    users->users[users->counterUsers].state = ACTIVE;
    users->counterUsers++;
    saveUsers(users);
}

void modifyUser(Users *users) {
    int number, index, option;
    int verify = verifyCounter(users->counterUsers, MSG_NO_USERS);
    char newName[MAX_NAME_USER], newFunction[MAX_FUNCTION_USER], newAcronym[MAX_ACRONYM_USER];

    if (verify == 1) {
        number = getInt(1, users->counterUsers, MSG_SEARCH_USER);
        index = searchUser(*users, number);
        if (index != -1) {
            do {
                option = getInt(0, 4, MENU_MODIFY_USER);
                switch (option) {
                    case 1:
                        readString(newName, MAX_NAME_USER, MSG_NEW_USER_NAME);
                        strcpy(users->users[index].name, newName);
                        break;
                    case 2:
                        readString(newAcronym, MAX_ACRONYM_USER, MSG_NEW_USER_ACRONYM);
                        strcpy(users->users[index].acronym, newAcronym);
                        break;
                    case 3:
                        readString(newFunction, MAX_FUNCTION_USER, MSG_NEW_USER_FUNCTION);
                        strcpy(users->users[index].functionUser, newFunction);
                        break;
                    case 4:
                        if (users->users[index].state == ACTIVE) {
                            users->users[index].state = INACTIVE;
                        } else {
                            users->users[index].state = ACTIVE;
                        }
                        break;
                    case 0:
                        break;
                }
            } while (option != 0);
        }
    }
}

void deleteUser(Users *users) {
    int verify = verifyCounter(users->counterUsers, MSG_NO_USERS), number, index, i;
    if (verify == 1) {
        number = getInt(1, users->counterUsers, MSG_SEARCH_USER);
        index = searchUser(*users, number);
        if (index != -1) {
            if (users->users[index].numberEquipments == 0) {
                strcpy(users->users[index].name,"");
                strcpy(users->users[index].functionUser,"");
                strcpy(users->users[index].acronym,"");
                users->users[index].codIdentify = 0;

                for (i = index; i < users->counterUsers - 1; i++) {
                    users->users[i] = users->users[i + 1];
                }
                users->counterUsers --;
                saveUsers(users);
            } else {
                puts(MSG_USER_HAVE_EQUIPMENT);
                return;
            }
        }
    }
}

