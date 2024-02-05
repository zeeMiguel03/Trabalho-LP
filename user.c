#include "user.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "geral.h"
#include "listings.h"

/**
 * @brief Initialize or load user data from the file.
 *
 * This function checks if the user file exists. If it does, it loads user data from the file.
 * If the file does not exist, it creates a new file and initializes the Users structure.
 *
 * @param users Pointer to the Users structure to be initialized or loaded.
 */
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

/**
 * @brief Save user data to the file.
 *
 * This function saves user data, including the counter of users, the maximum number of users,
 * and the array of users, to the user file.
 *
 * @param users Pointer to the Users structure containing user information to be saved.
 */
void saveUsers(Users *users) {
    FILE *file = fopen(FILE_USER, "wb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fwrite(&users->counterUsers, sizeof(int), 1, file);
    fwrite(&users->maxUsers, sizeof(int), 1, file);
    fwrite(users->users, sizeof(User), users->counterUsers, file);
    fclose(file);
}

/**
 * @brief Relocate memory for the Users structure if necessary.
 *
 * This function checks if the maximum number of users has been reached.
 * If so, it reallocates memory to accommodate more users by doubling the capacity.
 *
 * @param users Pointer to the Users structure whose memory may need to be relocated.
 */
void relocateUsers(Users *users) {
    if (users->maxUsers == users->counterUsers) {
        User *pUser = realloc(users->users, sizeof(User) * (users->maxUsers * 2));
        if (pUser == NULL) {
            puts("Error relocating memory");
            return;
        }

        users->users = pUser;
        users->maxUsers *= 2;
    }
}

/**
 * @brief Search for a user in the Users structure by code identification number.
 *
 * This function searches for a user with the specified code identification number
 * in the given Users structure. If the user is found, it returns the index of the user;
 * otherwise, it returns -1 and prints an error message.
 *
 * @param users The Users structure containing user information.
 * @param number The code identification number of the user to search for.
 * @return The index of the user if found; otherwise, -1.
 */
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

/**
 * @brief Inserts a new user into the Users structure.
 *
 * This function inserts a new user into the Users structure, prompting the user
 * for information such as name, acronym, and function. It initializes other user properties
 * like code identification, the number of equipments, and the initial state.
 *
 * @param users Pointer to the Users structure containing user information.
 */
void insertUser(Users *users) {
    relocateUsers(users);

    readString(users->users[users->counterUsers].name, MAX_NAME_USER, MSG_GET_USER_NAME);
    readString(users->users[users->counterUsers].acronym, MAX_ACRONYM_USER, MSG_GET_USER_ACRONYM);
    readString(users->users[users->counterUsers].functionUser, MAX_FUNCTION_USER, MSG_GET_USER_FUNCTION);

    users->users[users->counterUsers].codIdentify = verifyNumberUser(users, users->counterUsers);
    users->users[users->counterUsers].numberEquipments = 0;
    users->users[users->counterUsers].state = ACTIVE;

    users->counterUsers++;
    saveUsers(users);
}

/**
 * @brief Modifies user information in the Users structure.
 *
 * This function allows the modification of various aspects of a user's information,
 * such as name, acronym, function, and state.
 *
 * @param users Pointer to the Users structure containing user information.
 */
void modifyUser(Users *users) {
    int number, index, option;
    int verify = verifyCounter(users->counterUsers, MSG_NO_USERS);
    char newName[MAX_NAME_USER], newFunction[MAX_FUNCTION_USER], newAcronym[MAX_ACRONYM_USER];

    if (verify == 1) {
        listUsers(*users);
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
                        modifyStateUser(users, index);
                        break;
                    case 0:
                        break;
                }
            } while (option != 0);
        }
    }
}

/**
 * @brief Deletes a user from the Users structure.
 *
 * This function allows the deletion of a user from the Users structure.
 * It prompts the user to choose a user to delete, checks if the user has any equipment,
 * and performs the deletion if conditions are met.
 *
 * @param users Pointer to the Users structure containing user information.
 */
void deleteUser(Users *users) {
    int number, index, i, option;
    if (verifyCounter(users->counterUsers, MSG_NO_USERS) == 1) {
        listUsers(*users);
        number = getInt(1, users->counterUsers, MSG_SEARCH_USER);
        index = searchUser(*users, number);
        if (index != -1) {
            if (users->users[index].numberEquipments == 0) {
                for (i = index; i < users->counterUsers - 1; i++) {
                    users->users[i] = users->users[i + 1];
                }
                users->counterUsers --;
                saveUsers(users);
            } else {
                puts(MSG_USER_HAVE_EQUIPMENT);
                option = getInt(0, 1, CHOOSE_INACTIVE);
                if (option == 1) {
                    modifyStateUser(users,index);
                }
                return;
            }
        }
    }
}

/**
 * @brief Toggle the state of a user between ACTIVE and INACTIVE.
 *
 * This function modifies the state of a user in the given Users structure.
 * If the user's current state is ACTIVE, it will be changed to INACTIVE, and vice versa.
 *
 * @param users Pointer to the Users structure containing user information.
 * @param numberUser Index of the user in the users array to be modified.
 */
void modifyStateUser(Users *users, int numberUser) {
    if (users->users[numberUser].state == ACTIVE) {
        users->users[numberUser].state = INACTIVE;
    } else {
        users->users[numberUser].state = ACTIVE;
    }
}

int isNumberInUseUser(Users *users, int number) {
    for (int i = BEGIN_COUNTER; i < users->counterUsers; i++) {
        if (users->users[i].codIdentify == number) {
            return 1;
        }
    }
    return 0;
}

int verifyNumberUser(Users *users, int number) {
    if (isNumberInUseUser(users, number) == 1) {
        do {
            number += 1;
        } while (isNumberInUseUser(users, number) == 1);
        return number;
    } else {
        return number;
    }
}




