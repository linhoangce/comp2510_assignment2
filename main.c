#include <stdio.h>
#include <stdlib.h>
#include "student.h"

int main(int argc, char *argv[])
{
    if(argc != 4) {
        printf("Usage: %s <input_file> <output_file> <option>\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    const char *output_file = argv[2];
    int option = atoi(argv[3]);

    if(option < 1 || option > 3) {
        printf("Error: Option must be between 1 and 3.\n");
        return 1;
    }

    Student students[100];

    int student_count = read_students(input_file, students, 100);

    if(student_count == 0) {
        FILE *file = fopen(output_file, "w");

        if(!output_file) {
            printf("Error opening file!");
            return 1;
        }

        fprintf(file, "Error: Invalid format!\n");
        printf("Error: No students found in the input file!");
        return 1;
    }

    printf("Student Count: %d\n\n", student_count);
    merge_sort(students, 0, student_count - 1);
    write_to_file(output_file, students, student_count, option);
    printf("Data successfully written to %s\n", output_file);

    return 0;
}
