#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>

// Structure to hold information about domestic students
typedef struct {
    char first_name[50];
    char last_name[50];
    char month_birth[10];
    int date_birth;
    int year_birth;
    float gpa;
    char status;
} DomesticStudent;

// Structure to hold additional information about international students
typedef struct {
    int toefl;
} InternationalStudent;

// A generic student structure for both domestic and international students
typedef struct {
    DomesticStudent student;
    union {
        InternationalStudent int_student;
    };
} Student;

int read_students(const char *filename, Student students[], int max_count);
int compare_student(Student *a, Student *b);
void merge_sort(Student student[], int left, int right);
void write_to_file(const char *filename, const Student *student, int count, int option);
#endif