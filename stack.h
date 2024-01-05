#ifndef STACK_H
#define STACK_H

typedef struct Schedule{
    char className[50];
    char startTime[6];
    char endTime[6];
    char professor[50];
    struct Schedule* next;
} Schedule;

typedef struct {
    Schedule* head;
} ScheduleList;

typedef struct User {
    char username[20];
    char password[20];
    char fullName[50];
    char userType[20];
} User;
// Funciiones usando listas simples para la operación del programa
void initializeScheduleList(ScheduleList* list);
void addSchedule(ScheduleList* list, const char* className, const char* startTime, const char* endTime, const char* professor);
void modifySchedule(ScheduleList* list, const char* className, const char* startTime);
void deleteSchedule(ScheduleList* list, const char* className, const char* startTime);
void displaySchedules(ScheduleList* list);
Schedule* findSchedule(ScheduleList* list, const char* className);
int hasOverlap(ScheduleList* studentSchedule, Schedule* newSchedule);

// Funciones de autenticacion de usuarios y añadir usuarios
void addUser(User* users, const char* username, const char* password, const char* fullName, const char* userType);
int authenticateUser(User* users, const char* username, const char* password, char* userType);

// Funciones complementarias
void showMenu();
void clearScreen();
void showMenuStudent();

#endif
