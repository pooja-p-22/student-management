// student.c
#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Student *students = NULL;
int student_count = 0;
int max_students = 0;

void addStudent() {
    // Check if the array needs resizing
    if (student_count >= max_students) {
        // If max_students is 0, initialize it to 10; otherwise, double its size
        max_students = (max_students == 0) ? 10 : max_students * 2;
        students = realloc(students, max_students * sizeof(Student));
        if (!students) {
            fprintf(stderr, "Memory allocation failed!\n");
            exit(EXIT_FAILURE);
        }
    }

    // Collect new student details
    Student s;
    printf("Enter ID: ");
    scanf("%d", &s.id);
    printf("Enter Name: ");
    scanf(" %[^\n]s", s.name);
    printf("Enter Age: ");
    scanf("%d", &s.age);
    printf("Enter Course: ");
    scanf(" %[^\n]s", s.course);

    // Add the new student to the array
    students[student_count++] = s;
    printf("Student added successfully!\n");
}

void viewStudents() {
    if (student_count == 0) {
        printf("No students to display!\n");
        return;
    }

    printf("\nID\tName\t\tAge\tCourse\n");
    printf("----------------------------------------\n");
    for (int i = 0; i < student_count; i++) {
        printf("%d\t%s\t\t%d\t%s\n", students[i].id, students[i].name, students[i].age, students[i].course);
    }
}

void searchStudent() {
    int id;
    printf("Enter ID to search: ");
    scanf("%d", &id);

    // Perform a linear search for the student ID in the array
    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            // Print the student's details if a match is found
            printf("\nID: %d\nName: %s\nAge: %d\nCourse: %s\n", students[i].id, students[i].name, students[i].age, students[i].course);
            return;
        }
    }
    // If no match is found, print a message
    printf("Student not found!\n");

    // Optimization Note: For larger datasets, consider using a more efficient search algorithm,
    // such as binary search, by keeping the data sorted or using a hash table for constant-time lookups.
}

void updateStudent() {
    int id;
    printf("Enter ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            printf("Enter new Name: ");
            scanf(" %[^\n]s", students[i].name);
            printf("Enter new Age: ");
            scanf("%d", &students[i].age);
            printf("Enter new Course: ");
            scanf(" %[^\n]s", students[i].course);
            printf("Student updated successfully!\n");
            return;
        }
    }
    printf("Student not found!\n");
}

void deleteStudent() {
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            for (int j = i; j < student_count - 1; j++) {
                students[j] = students[j + 1];
            }
            student_count--;
            printf("Student deleted successfully!\n");
            return;
        }
    }
    printf("Student not found!\n");
}

void saveToFile() {
    FILE *file = fopen("students.dat", "wb");
    if (!file) {
        fprintf(stderr, "Error saving data!\n");
        return;
    }
    fwrite(&student_count, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), student_count, file);
    fclose(file);
}

void loadFromFile() {
    FILE *file = fopen("students.dat", "rb");
    if (!file) {
        return; // No data file found
    }
    fread(&student_count, sizeof(int), 1, file);
    students = malloc(student_count * sizeof(Student));
    if (!students) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    fread(students, sizeof(Student), student_count, file);
    fclose(file);
}
