// student.h
#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

typedef struct {
    int id;
    char name[50];
    int age;
    char course[30];
} Student;

extern Student *students;
extern int student_count;
extern int max_students;

void addStudent();
void viewStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void saveToFile();
void loadFromFile();

#endif // STUDENT_H