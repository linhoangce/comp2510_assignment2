//
// Created by linho on 2024-11-14.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

// Read students information into a Student array
int read_students(const char *file_name,
                  Student students[],
                  int max_count) {

    FILE *file = fopen(file_name, "r");

    if(!file) {
        printf("Error: file does not exist");
        return 0;
    }

    int count = 0;
    char line[256];     // Store information about student on each line

    while(count < max_count &&
            fgets(line, sizeof(line), file)) {
        int fields_count = sscanf(line, "%s %s %[^-]-%d-%d %f %c %d",
                                  students[count].student.first_name,
                                  students[count].student.last_name,
                                  students[count].student.month_birth,
                                  &students[count].student.date_birth,
                                  &students[count].student.year_birth,
                                  &students[count].student.gpa,
                                  &students[count].student.status,
                                  &students[count].int_student.toefl);

        // Check for valid number domestic student fields
        if (fields_count == 7) {
            if (students[count].student.status != 'D') {    // Check for valid status field
                printf("Error : Invalid File Format [Domestic Student].\n");
                return 0;
            }

            count++;
        } else if (fields_count == 8) {     // Check for valid number of international student fields
            if (students[count].student.status != 'I') {        // Check for valid international status
                printf("Error: Wrong format [International Student].\n");
                return 0;
            }

            count++;
        } else {
            printf("Error in read_students: Invalid Format\n");
            return 0;
        }
    }

    fclose(file);
    return count;
}

int getMonthIndex(const char *months[], const char * month) {
    for(int i = 0; i < 12; i++) {
        if(strcmp(month, months[i]) == 0) {
            return i;
        }
    }

    return -1;
}

int compare_students(const Student *a, const Student *b) {
    const char *MONTH[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    int cmp;

    if(a->student.year_birth != b->student.year_birth) {
        return a->student.year_birth - b->student.year_birth;
    }

    cmp = strcmp(a->student.month_birth, b->student.month_birth);

    if(cmp != 0) {
        int monthAIndex = getMonthIndex(MONTH, a->student.month_birth);
        int monthBIndex = getMonthIndex(MONTH, b->student.month_birth);

        if(monthAIndex == -1 || monthBIndex == -1) {
            printf("Error: Month of birth is not valid.");
            return 0;
        }

        return monthAIndex - monthBIndex;
    }

    if(a->student.date_birth != b->student.date_birth) {
        return a->student.date_birth - b->student.date_birth;
    }

    cmp = strcmp(a->student.last_name, b->student.last_name);

    if(cmp != 0) {
        return cmp;
    }

    cmp = strcmp(a->student.first_name, b->student.first_name);

    if(cmp != 0) {
        return cmp;
    }

    if(a->student.gpa != b->student.gpa) {
        return a->student.gpa - b->student.gpa;
    }

    if(a->student.status == 'I' && b->student.status == 'I') {
        cmp = a->int_student.toefl - b->int_student.toefl;

        if(cmp != 0) {
            return cmp;
        }
    }
    return a->student.status - b->student.status;
}

void merge(Student students[], int left, int mid, int right) {
    int n1 = mid - left + 1;    // size of the left half array
    int n2 = right - mid;       // size of the right half array

    // Allocate memory for temporary arrays
    Student *L = (Student *) malloc(n1 * sizeof(Student));
    Student *R = (Student *) malloc(n2 * sizeof(Student));

    if(L == NULL) {
        printf("Memory allocation for L array failed!");
        return;
    }

    if(R == NULL) {
        printf("Memory allocation for R array failed!");
        return;
    }

    // Copy date into the temporary arrays
    for(int i = 0; i < n1; i++) {
        L[i] = students[left + i];
    }

    for(int i = 0; i < n2; i++) {
        R[i] = students[mid + 1 + i];
    }

    // Merge the two halves back into the original array
    int i = 0;
    int j = 0;
    int k = left;

    while(i < n1 && j < n2) {
        if(compare_students(&L[i], &R[j]) <= 0) {
            students[k++] = L[i++];
        } else {
            students[k++] = R[j++];
        }
    }

    // Copying remaining elements from the left half
    while(i < n1) {
        students[k++] = L[i++];
    }

    // Copying remaining elements from the right half
    while(j < n2) {
        students[k++] = R[j++];
    }

    // Free allocated memory
    free(L);
    free(R);

}

void merge_sort(Student students[], int left, int right) {
    if(left < right) {
        int mid = left + (right - left) / 2;    // Calculate the mid point
        merge_sort(students, left, mid);    // Sort the left half

        // printf("LEFT\n");
        // for(int i = 0; i < mid; i++) {
        //     if(students[i].student.status == 'D') {
        //         printf("%s %s %s-%d-%d %.3f %c\n",
        //                         students[i].student.first_name,
        //                         students[i].student.last_name,
        //                         students[i].student.month_birth,
        //                         students[i].student.date_birth,
        //                         students[i].student.year_birth,
        //                         students[i].student.gpa,
        //                         students[i].student.status);
        //     }
        //
        //     if(students[i].student.status == 'I') {
        //         printf("%s %s %s-%d-%d %.3f %c %d\n",
        //                         students[i].student.first_name,
        //                         students[i].student.last_name,
        //                         students[i].student.month_birth,
        //                         students[i].student.date_birth,
        //                         students[i].student.year_birth,
        //                         students[i].student.gpa,
        //                         students[i].student.status,
        //                         students[i].int_student.toefl);
        //     }
        // }
        merge_sort(students, mid + 1, right); // Sort the right half
        // printf("RIGHT\n");
        // for(int i = 0; i < right; i++) {
        //     if(students[i].student.status == 'D') {
        //         printf("%s %s %s-%d-%d %.3f %c\n",
        //                         students[i].student.first_name,
        //                         students[i].student.last_name,
        //                         students[i].student.month_birth,
        //                         students[i].student.date_birth,
        //                         students[i].student.year_birth,
        //                         students[i].student.gpa,
        //                         students[i].student.status);
        //     }
        //
        //     if(students[i].student.status == 'I') {
        //         printf("%s %s %s-%d-%d %.3f %c %d\n",
        //                         students[i].student.first_name,
        //                         students[i].student.last_name,
        //                         students[i].student.month_birth,
        //                         students[i].student.date_birth,
        //                         students[i].student.year_birth,
        //                         students[i].student.gpa,
        //                         students[i].student.status,
        //                         students[i].int_student.toefl);
        //     }
        // }
        merge(students, left, mid, right);          // Merge the sorted halves
    }
}

// Write the student information into the output file
void write_to_file(const char *filename,
                    const Student students[],
                    int count,
                    int option)
{
    FILE *file = fopen(filename, "w");

    if(!file) {
        printf("Error: Could not open file.\n");
        return;
    }

    // Loop through each student and filer based on the selected option
    for(int i = 0; i < count; i++) {
        // Write based on each option selected
        switch(option) {
            case 1:
                if(students[i].student.status == 'D') {
                    fprintf(file, "%s %s %s-%d-%d %.3f %c\n",
                                    students[i].student.first_name,
                                    students[i].student.last_name,
                                    students[i].student.month_birth,
                                    students[i].student.date_birth,
                                    students[i].student.year_birth,
                                    students[i].student.gpa,
                                    students[i].student.status);
                }
                break;
            case 2:
                if(students[i].student.status == 'I') {
                    fprintf(file, "%s %s %s-%d-%d %.3f %c %d\n",
                                    students[i].student.first_name,
                                    students[i].student.last_name,
                                    students[i].student.month_birth,
                                    students[i].student.date_birth,
                                    students[i].student.year_birth,
                                    students[i].student.gpa,
                                    students[i].student.status,
                                    students[i].int_student.toefl);
                }
                break;

            case 3:
                if(students[i].student.status == 'D') {
                    fprintf(file, "%s %s %s-%d-%d %.3f %c\n",
                                    students[i].student.first_name,
                                    students[i].student.last_name,
                                    students[i].student.month_birth,
                                    students[i].student.date_birth,
                                    students[i].student.year_birth,
                                    students[i].student.gpa,
                                    students[i].student.status);
                }

                if(students[i].student.status == 'I') {
                    fprintf(file, "%s %s %s-%d-%d %.3f %c %d\n",
                                    students[i].student.first_name,
                                    students[i].student.last_name,
                                    students[i].student.month_birth,
                                    students[i].student.date_birth,
                                    students[i].student.year_birth,
                                    students[i].student.gpa,
                                    students[i].student.status,
                                    students[i].int_student.toefl);
                }

                break;
            default:
                fprintf(file,"Error: Invalid Option!");
                exit(1);
         }
    }

    fclose(file);
}

