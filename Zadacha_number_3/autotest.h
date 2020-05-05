#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define STRING_SIZE 512

int set_row_elemets (int *rows_element, int n, FILE *input_stream);
int set_matrix (int **matrix, int *rows_element, int n, FILE *input_stream);
void print_matrix (int **matrix, int *rows_element, int n, FILE *output_stream);
int function (int **matrix, int *rows_element, int n);

void AutoTest_change (void);
void AutoTest_not_change (void);
