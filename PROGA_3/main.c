#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <float.h>
#include "autotest.h"

#define STRING_SIZE 512

int set_row_elemets (int *rows_element, int n, FILE *input_stream);
int set_matrix (int **matrix, int *rows_element, int n, FILE *input_stream);
void print_matrix (int **matrix, int *rows_element, int n, FILE *output_stream);
int function (int **matrix, int *rows_element, int n);

int set_row_elemets (int *rows_element, int n, FILE *input_stream)
{
  int i = 0;
  int temp = 0;
  char temp_ch;
  for (i = 0; i < n; i++)
    {
      rows_element[i] = 0;
      while (fscanf (input_stream, "%d", &temp) == 1)
        {
          rows_element[i]++;
          if (fscanf (input_stream, "%c", &temp_ch) != 1)
            return 1;
          if (temp_ch == '\n' || temp_ch == '\0')
            break;
        }
    }
  return 0;
}

int set_matrix (int **matrix, int *rows_element, int n, FILE *input_stream)
{
  int i = 0;
  int j = 0;
  for (i = 0; i < n; i++)
    for (j = 0; j < rows_element[i]; j++)
      if (fscanf (input_stream, "%d", *(matrix + i) + j) != 1)
        return 1;
  return 0;
}

void print_matrix (int **matrix, int *rows_element, int n, FILE *output_stream)
{
  int i = 0;
  int j = 0;
  printf ("Matrix:\n");
  for (i = 0; i < n; i++)
    {
      if (*(matrix + i) + j)
        {
          for (j = 0; j < rows_element[i]; j++)
            fprintf (output_stream, "%d ", *(*(matrix + i) + j));
          fprintf (output_stream, "\n");
        }
    }
  fprintf (output_stream, "\n");
  return;
}

int function (int **matrix, int *rows_element, int n)
{
  int i = 0;
  int j = 0;
  int flag = 0;
  double average = 0;
  int number_of_delete_row = -1;
  for (i = 0; i < n; i++)
    {
      if (flag)
        break;
      average = 0;
      for (j = 0; j < rows_element[i]; j++)
        average += *(*(matrix + i) + j);
      if (rows_element[i] != 0)
        average /= rows_element[i];
      for (j = 0; j < rows_element[i]; j++)
        {
          if (fabs ((double)*(*(matrix + i) + j) - average) < DBL_MIN)
            {
              free (*(matrix + i));
              *(matrix + i) = 0;
              flag = 1;
              number_of_delete_row = i;
              break;
            }
        }
    }
  return number_of_delete_row;
}

int main (void)
{
  // используемые переменные
  int i = 0;
  int j = 0;
  int n = 0;
  double time = 0;
  const char *input_filename = "data.dat";
  const char *output_filename = "data.res";
  FILE *input_stream = stdin;
  FILE *output_stream = stdout;
  char string_temp[STRING_SIZE];
  int number_of_delete_row = 0;
  int *rows_element;
  int **matrix;

  // ответ, номер строки которая должна удалиться
  int result = 0;

  // открытие файла
  if (!(input_stream = fopen (input_filename, "r")))
    return 1;

  // запись кол-ва элементов в файле
  while (fgets (string_temp, STRING_SIZE, input_stream))
    if (string_temp[0] != '\n' && string_temp[0] != '\0')
      n++;

  // выделение памяти для массива кол-ва элементов в строке
  rows_element = (int *) malloc (n * sizeof(int));
  if (!rows_element)
    {
      fclose (input_stream);
      return 1;
    }

  // запись кол-ва элементов в строке
  rewind (input_stream);
  if (set_row_elemets (rows_element, n, input_stream))
    {
      fclose (input_stream);
      free (rows_element);
      return 1;
    }

  // выделение памяти под весь файл
  matrix = (int **) malloc (n * sizeof(int *));
  if (!matrix)
    {
      fclose (input_stream);
      free (rows_element);
      return 1;
    }
  for (i = 0; i < n; i++)
    {
      *(matrix + i) = (int *) malloc (rows_element[i] * sizeof(int));
      if (!*(matrix + i))
        {
          fclose (input_stream);
          for (j = 0; j < i; j++)
            if (*(matrix + j))
              free(*(matrix + j));
          free (matrix);
          free (rows_element);
          return 1;
        }
    }

  // запись файла в массив
  rewind (input_stream);
  if (set_matrix (matrix, rows_element, n, input_stream))
    {
      fclose (input_stream);
      for (j = 0; j < n; j++)
        if (*(matrix + j))
          free(*(matrix + j));
      free (matrix);
      free (rows_element);
      return 1;
    }

  // печать матрицы на экран
  print_matrix (matrix, rows_element, n, stdout);

  // основная функция программы
  time = clock();
  number_of_delete_row = function (matrix, rows_element, n);
  time = (clock() - time) / CLOCKS_PER_SEC;

  // открытие файла
  if (!(output_stream = fopen (output_filename, "w")))
    {
      fclose (input_stream);
      for (i = 0; i < n; i++)
        if (*(matrix + i))
          free(*(matrix + i));
      free (matrix);
      free (rows_element);
      return 1;
    }

  // печать матрицы на экран
  print_matrix (matrix, rows_element, n, stdout);
  // печать матрицы в файл
  print_matrix (matrix, rows_element, n, output_stream);

  printf ("Time: %2.2lf\n", time);
  AutoTest (number_of_delete_row, result);

  fclose (input_stream);
  fclose (output_stream);
  for (i = 0; i < n; i++)
    if (*(matrix + i))
      free(*(matrix + i));
  free (matrix);
  free (rows_element);
  return 0;
}
