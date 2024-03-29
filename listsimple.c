#include "listsimple.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Funciones de listas en horariosz
void initializeScheduleList(ScheduleList* list) {
    list->head = NULL;
}

void addSchedule(ScheduleList* list, const char* className, const char* startTime, const char* endTime, const char* professor, const char* group) {
    Schedule* newSchedule = (Schedule*)malloc(sizeof(Schedule));
    if (!newSchedule) {
        fprintf(stderr, "Error: No se pudo asignar memoria :c\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newSchedule->className, className);
    strcpy(newSchedule->startTime, startTime);
    strcpy(newSchedule->endTime, endTime);
    strcpy(newSchedule->professor, professor);
    strcpy(newSchedule->group, group);
    newSchedule->next = list->head;

    list->head = newSchedule;
    printf("\nDatos agregados exitosamente");
}

void modifySchedule(ScheduleList* list, const char* className, const char* group) {
    char newClassName[50], newStartTime[6], newEndTime[6], newProfessor[50], newGroup[6];
    Schedule* current = list->head;

    while (current != NULL) {
        if (strcmp(current->className, className) == 0 && strcmp(current->group, group) == 0) {
            printf("Ingrese el nuevo nombre de la clase: ");
            scanf(" %[^\n]", newClassName);
            printf("Ingrese la nueva hora de inicio (HH:MM): ");
            scanf(" %[^\n]", newStartTime);
            printf("Ingrese la nueva hora de fin (HH:MM): ");
            scanf(" %[^\n]", newEndTime);
            printf("Ingrese el nuevo nombre del profesor: ");
            scanf(" %[^\n]", newProfessor);
            printf("Ingrese el nuevo número del grupo (2CVX): ");
            scanf(" %[^\n]", newGroup);
            strcpy(current->className, newClassName);
            strcpy(current->startTime, newStartTime);
            strcpy(current->endTime, newEndTime);
            strcpy(current->professor, newProfessor);
            strcpy(current->group, newGroup);
            printf("El horario se ha modificado exitosamente :)\n");
            return;
        }

        current = current->next;
    }

    printf("No se encontró el horario para modificar.\n");
}

void deleteSchedule(ScheduleList* list, const char* className, const char* group) {
    Schedule* current = list->head;
    Schedule* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->className, className) == 0 && strcmp(current->group, group) == 0) {
            if (prev == NULL) {
                list->head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }

        prev = current;
        current = current->next;
    }

    printf("No se encontró el horario para eliminar.\n");
}

void displaySchedules(ScheduleList* list) {
    Schedule* current = list->head;

    printf("\n+-------------------------------------------------------------------+\n");
    printf("| Clase               | Inicio   | Fin      | Profesor    | Grupo   |\n");
    printf("+---------------------+----------+----------+-------------+---------+\n");

    while (current != NULL) {
        printf("| %-19s | %-8s | %-8s | %-11s | %-7s |\n", current->className, current->startTime, current->endTime, current->professor, current->group);
        current = current->next;
    }

    printf("+-------------------------------------------------------------------+\n");
}

void addUser(User* users, const char* username, const char* password, const char* fullName, const char* userType) {
    strcpy(users->username, username);
    strcpy(users->password, password);
    strcpy(users->fullName, fullName);
    strcpy(users->userType, userType);
}

int authenticateUser(User* users, const char* username, const char* password, char* userType) {
    if (strcmp(users->username, username) == 0 && strcmp(users->password, password) == 0) {
        strcpy(userType, users->userType);
        return 1; // Autenticación exitosa
    }

    return 0; // Autenticación fallida
}


Schedule* findSchedule(ScheduleList* list, const char* className) {
    Schedule* current = list->head;
    while (current != NULL) {
        if (strcmp(current->className, className) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int hasOverlap(ScheduleList* studentSchedule, Schedule* newSchedule) {
    Schedule* current = studentSchedule->head;
    while (current != NULL) {
        if (strcmp(current->startTime, newSchedule->startTime) == 0) {
            return 1; // Traslape encontrado
        }
        current = current->next;
    }
    return 0; //tengo que corregir la lógica de esta función que no está funcionando
}

int hasOverlapShedule(ScheduleList* adminSchedule, const char* className, const char* startTime, const char* group) {
    Schedule* current = adminSchedule->head;

    while (current != NULL) {
        if (strcmp(current->className, className) == 0 &&
            strcmp(current->startTime, startTime) == 0 &&
            strcmp(current->group, group) == 0) {
            return 1; 
        }
        current = current->next;
    }

    return 0; 
}

void addCourseToStudentSchedule(ScheduleList* courseOffering, 

ScheduleList* studentSchedule) {
    char selectedClassName[50];
    printf("\nIngrese el nombre de la clase que desea agregar a su horario: ");
    scanf(" %[^\n]", selectedClassName);

    // Find the selected course in the offering
    Schedule* selectedSchedule = findSchedule(courseOffering, selectedClassName);

    if (selectedSchedule != NULL) {
        // Check for overlap with other already selected courses
        if (!hasOverlap(studentSchedule, selectedSchedule)) {
            // Add the course to the student's schedule
            addSchedule(studentSchedule, selectedSchedule->className, selectedSchedule->startTime, selectedSchedule->endTime, selectedSchedule->professor, selectedSchedule->group);
            printf("\nClase agregada Exitosamente.\n");
        } else {
            printf("\nError: La clase seleccionada traslapa con otra clase en su horario\n");
        }
    } else {
        printf("\nError: Clase no encontrada en la oferta.\n");
    }
}

//----------------------------------------------------------
void showMenu(){
    printf("\nMenu de Administrador:\n");
    printf("1. Agregar un horario\n");
    printf("2. Modificar un horario\n");
    printf("3. Eliminar un horario\n");
    printf("4. Consultar horarios\n");
    printf("5. Cerrar sesión y salir\n");
}

void clearScreen() {
    // Sistema operativo específico
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void showMenuStudent(){
    printf("\nMenu de Estudiante:\n");
    printf("1. Armar horario de clases\n");
    printf("2. Mostrar horario\n");
    printf("3. Eliminar una materia del horario\n");
    printf("4. Cerrar sesión y salir.\n");
}

void loadInitialSchedules(ScheduleList* list) {
    char classNames[][50] = {"ALGEBRA LINEAL", "CALCULO APLICADO", "ALGORITMOS", "ECONOMIA", "MECANICA"};
    char startTimes[][6] = {"18:30", "15:00", "16:30", "20:00", "18:30"};
    char endTimes[][6] = {"20:00", "16:30", "18:00", "21:30", "20:00"};
    char professors[][50] = {"Rald", "Juan", "Marina", "Derek", "Rosa"};
    char group[][6] = {"2CV5", "2CV3", "2CV1", "2CV4", "2CV2"};
    
    // Agregar horarios a la lista
    for (int i = 0; i < 5; i++) {
        // Asumo que tienes una función addSchedule definida
        addSchedule(list, classNames[i], startTimes[i], endTimes[i], professors[i], group[i]);
    }
}
