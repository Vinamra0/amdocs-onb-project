#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int id;
    char name[30];
    char designation[50];
    int salary;
};

void addEmployee() {
    struct Employee newEmployee;
    printf("Enter Employee ID: ");
    scanf("%d", &newEmployee.id);

    printf("Enter Employee Name: ");
    scanf("%s", newEmployee.name);

    printf("Enter Employee Designation: ");
    scanf("%s", newEmployee.designation);

    printf("Enter Employee Salary: ");
    scanf("%d", &newEmployee.salary);

    FILE *file = fopen("employee_data.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file,"%d %s %s %d\n", newEmployee.id, newEmployee.name, newEmployee.designation, newEmployee.salary);
    printf("Employee added successfully!\n");
    fclose(file);
}

void listEmployees() {
    FILE *file = fopen("employee_data.txt", "r");
    if (file == NULL) {
        printf("No Employee details available.\n");
        return;
    }
    struct Employee emp;
    while (fscanf(file, "%d %s %s %d", &emp.id, emp.name, emp.designation, &emp.salary) != EOF) {
        printf("Employee ID: %d, Name: %s, Designation: %s, Salary: %d\n", emp.id, emp.name, emp.designation, emp.salary);
    }
    fclose(file);
}

void deleteEmployee(int _id) {
    FILE *file = fopen("employee_data.txt", "r");
    if (file == NULL) {
        printf("No employee available.\n");
        return;
    }
    FILE *tempFile = fopen("temp.txt", "w");
    struct Employee emp;
    while (fscanf(file, "%d %s %s %d", &emp.id, emp.name, emp.designation, &emp.salary) != EOF) {
        if (emp.id != _id) {
            fprintf(tempFile, "%d %s %s %d\n", emp.id, emp.name, emp.designation, emp.salary);
        }
    }
    fclose(file);
    fclose(tempFile);
    remove("employee_data.txt");
    rename("temp.txt", "employee_data.txt");
    printf("Employee deleted successfully!\n");
}

void updateEmployee(int _id) {
    FILE *file = fopen("employee_data.txt", "r");
    if (file == NULL) {
        printf("No employee available.\n");
        return;
    }
    FILE *tempFile = fopen("temp.txt", "w");
    struct Employee emp;
    while (fscanf(file, "%d %s %s %d", &emp.id, emp.name, emp.designation, &emp.salary) != EOF) {
        if (emp.id == _id) {
            printf("Enter new Employee Name: ");
            scanf("%s", emp.name);

            printf("Enter new Employee Designation: ");
            scanf("%s", emp.designation);

            printf("Enter new Employee Salary: ");
            scanf("%d", &emp.salary);
        }
        fprintf(tempFile, "%d %s %s %d\n", emp.id, emp.name, emp.designation, emp.salary);
    }
    fclose(file);
    fclose(tempFile);
    remove("employee_data.txt");
    rename("temp.txt", "employee_data.txt");
    printf("Employee details updated successfully!\n");
}

int main() {
    int choice, id;
    while (1) {
        printf("\nEmployee Management System\n");
        printf("1. Add Employee\n");
        printf("2. Delete Employee\n");
        printf("3. Update Employee Details\n");
        printf("4. List Employees\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                printf("Enter Employee ID to delete: ");
                scanf("%d", &id);
                deleteEmployee(id);
                break;
            case 3:
                printf("Enter Employee ID to update: ");
                scanf("%d", &id);
                updateEmployee(id);
                break;
            case 4:
                listEmployees();
                break;
            case 5:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Please enter a valid option.\n");
        }
    }

    return 0;
}
