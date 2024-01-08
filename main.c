#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Agregamos los usuarios que estarán durante la ejecución del programa
    User adminUser;
    addUser(&adminUser, "admin", "adminpass", "Administrator", "Admin");

    User studentUser;
    addUser(&studentUser, "student", "studentpass", "Student Name", "Student");

    ScheduleList group1, group2, group3, group4, group5, studentSchedule;
    // inicializamos la estructura que conendrán los 5 grupos de datos
    initializeScheduleList(&group1);
    initializeScheduleList(&group2);
    initializeScheduleList(&group3);
    initializeScheduleList(&group4);
    initializeScheduleList(&group5);
    initializeScheduleList(&studentSchedule);

    // En esta parte del código lo que haré es añadir automáticamente los horarios con arrays dinámicos

    while (1) {
        char username[20], password[20], userType[20];
        //Pedimos usuario y contraseña
        printf("Ingrese su nombre de usuario: ");
        scanf("%s", username);
        printf("Ingrese su contraseña: ");
        scanf("%s", password);

        clearScreen();

        // si es correcto el nombre de usuario y la contraseña entonces accederá a la parte del menú 
        if (authenticateUser(&adminUser, username, password, userType)) {
            while (1) {
                int choice;
                showMenu();
                printf("Seleccione una opción: ");
                scanf("%d", &choice);
                clearScreen();
                switch (choice) {
                    //Agregar un horario
                    case 1: {
                        char className[50], startTime[6], endTime[6], professor[50];
                        printf("Ingrese el nombre de la clase: ");
                        scanf(" %[^\n]", className);  // %[^...] para leer hasta el salto de línea
                        printf("Ingrese la hora de inicio (HH:MM): ");
                        scanf(" %5s", startTime);
                        printf("Ingrese la hora de fin (HH:MM): ");
                        scanf(" %5s", endTime);
                        printf("Ingrese el nombre del profesor: ");
                        scanf(" %[^\n]", professor);

                        // Lógica para agregar horario
                        addSchedule(&group1, className, startTime, endTime, professor);
                        clearScreen();
                        break;
                    }
                    //Modificar horario
                    case 2: {
                        char oldClassName[50], oldStartTime[6];

                        printf("Ingrese el nombre de la clase que desea modificar: ");
                        scanf(" %[^\n]", oldClassName);
                        printf("Ingrese la hora de inicio del horario que desea modificar (HH:MM): ");
                        scanf(" %[^\n]", oldStartTime);

                        clearScreen();
                        printf("Digite los nuevos datos \n\n");

                        // Lógica para modificar horario
                        modifySchedule(&group1, oldClassName, oldStartTime);

                        clearScreen();
                        break;
                    }
                    case 3: {
                        char className[50], startTime[6];
                        printf("Ingrese el nombre de la clase que desea eliminar: ");
                        scanf("%s", className);
                        printf("Ingrese la hora de inicio del horario que desea eliminar (HH:MM): ");
                        scanf("%s", startTime);

                        // Lógica para eliminar horario
                        deleteSchedule(&group1, className, startTime);
                        clearScreen();
                        break;
                    }
                    case 4:
                        // Lógica para mostrar horarios
                        displaySchedules(&group1);
                        break;
                    case 5:
                        // Salir del menú de administrador
                        fflush(stdout);
                        clearScreen();
                        break;
                    default:
                        printf("Opción no válida. Inténtelo de nuevo.\n");
                }

                // Salir del bucle del menú del administrador y volver a solicitar credenciales
                if (choice == 5) {
                    break;
                }
            }
        } 
        else if (authenticateUser(&studentUser, username, password, userType)) {
            while (1) {
                showMenuStudent();
                int choice;
                printf("Seleccione una opción: ");
                scanf("%d", &choice);

                switch (choice) {
                    case 1: 
                        clearScreen();
                        printf("Oferta de Horarios Disponibles:\n");
                        displaySchedules(&group1);  // Muestra la oferta de horarios
                        addCourseToStudentSchedule(&group1, &studentSchedule);
                        break;
                    case 2:
                        // Salir del menú de estudiante
                        clearScreen();
                        displaySchedules(&studentSchedule); 
                        break;
                    case 3:
                        char classNam[50], startTim[6];
                        printf("Ingrese el nombre de la clase que desea eliminar: ");
                        scanf("%s", classNam);
                        printf("Ingrese la hora de inicio del horario que desea eliminar (HH:MM): ");
                        scanf("%s", startTim);
                    
                        // Lógica para eliminar horario
                        deleteSchedule(&studentSchedule, classNam, startTim);
                        clearScreen();
                        break;
                    case 4:
                        // Cierra la sedsión
                        clearScreen();
                        break;
                    default:
                        printf("Opción no válida. Inténtelo de nuevo.\n");
                }
                if (choice == 2) {
                    break;
                }
            }
        } else {
            printf("Credenciales incorrectas. Saliendo del programa.\n");
            break;
        }
    }

    return 0;
}