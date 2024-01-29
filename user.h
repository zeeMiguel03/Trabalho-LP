#ifndef TRABALHO_LP_USER_H
#define TRABALHO_LP_USER_H

#define MAX_NAME_USER 30
#define MAX_ACRONYM_USER 5
#define MAX_FUNCTION_USER 20

#define MSG_GET_USER_NAME "Insert user name: "
#define MSG_GET_USER_ACRONYM "Insert user acronym:"
#define MSG_GET_USER_FUNCTION "Insert user function: "
#define MSG_NEW_USER_NAME "Insert user new name:"
#define MSG_NEW_USER_ACRONYM "Insert user new acronym:"
#define MSG_NEW_USER_FUNCTION "Insert user new function:"

#define MSG_NO_USERS "No users yet!"
#define MSG_USER_NOT_FOUND "User not founded!"
#define MSG_USER_HAVE_EQUIPMENT "You cannot delete this user! \nYou want to inactive the user? \n1 - Yes\n2 - No\n0 - Leave"

#define MSG_SEARCH_USER "Search the user by the number:"

#define MENU_MODIFY_USER "\n1 - Modify Name\n2 - Modify Acronym\n3 - Modify Function\n4 - Modify State\n0 - Leave\nChoose: "

#define FILE_USER "fileUser.bin"

typedef enum {ACTIVE = 1, INACTIVE} stateUser;

typedef struct {
    char name[MAX_NAME_USER];
    char acronym[MAX_ACRONYM_USER];
    char functionUser[MAX_FUNCTION_USER];
    int codIdentify, numberEquipments;
    stateUser state;
} User;

typedef struct {
    int counterUsers, maxUsers;
    User *users;
} Users;

void bootUsers(Users *users);
void saveUsers(Users *users);
void relocateUsers(Users *users);
int searchUser(Users users, int number);
void insertUser(Users *users);
void modifyUser(Users *users);
void deleteUser(Users *users);


#endif
