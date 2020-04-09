#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "autotest.h"

#define STRING_SIZE 512
#define EPS 1e-16

int main (void)
{
  double time = 0;
  const char *input_filename = "data.dat";
  const char *output_filename = "data.res";
  FILE *input_stream = stdin;
  FILE *output_stream = stdout;
  int n = 0, temp = 0;
  double average = 0;
  char string_temp[STRING_SIZE];
  char temp_ch;

  if (!(input_stream = fopen (input_filename, "r")))
    {
      return 1;
    }

  // Вычисления кол-ва строк
  while (fgets (string_temp, STRING_SIZE, input_stream))
    {
      if (string_temp[0] != '\n' && string_temp[0] != '\0')
        {
          n++;
        }
    }

  int rows_element[n];
  rewind (input_stream);

  // Вычисление размера строк
  for (int i = 0; i < n; i++)
    {
      rows_element[i] = 0;
      while (fscanf (input_stream, "%d", &temp) == 1)
        {
          rows_element[i]++;
          if (fscanf (input_stream, "%c", &temp_ch) != 1)
            {
              return 2;
            }
          if (temp_ch == '\n' || temp_ch == '\0')
            {
              break;
            }
        }
    }

  // Выделение памяти под массив
  int **matrix;
  matrix = (int **) malloc (n * sizeof(int *));
  if (!matrix)
    {
      return 3;
    }
  for (int i = 0; i < n; i++)
    {
      *(matrix + i) = (int *) malloc (rows_element[i] * sizeof(int));
      if (!*(matrix + i))
        {
          return 4;
        }
    }

  rewind (input_stream);

  // Запись данных в массив
  for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < rows_element[i]; j++)
        {
          if (fscanf (input_stream, "%d", *(matrix + i) + j) != 1)
            {
              return 5;
            }
        }
    }

  // Печать массива
  printf ("Matrix:\n");
  for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < rows_element[i]; j++)
        {
          printf ("%d ", *(*(matrix + i) + j));
        }
      printf ("\n");
    }

  // Основная функция
  time = clock();
  for (int i = 0; i < n; i++)
    {
      average = 0;
      for (int j = 0; j < rows_element[i]; j++)
        {
          average += *(*(matrix + i) + j);
        }
      if (rows_element[i] != 0)
        average /= rows_element[i];
      for (int j = 0; j < rows_element[i]; j++)
        {
          if (fabs ((double)*(*(matrix + i) + j) - average) < EPS)
            {
              free (*(matrix + i));
              *(matrix + i) = 0;
              break;
            }
        }
    }
  time = (clock() - time) / CLOCKS_PER_SEC;

  if (!(output_stream = fopen (output_filename, "w")))
    {
      return 6;
    }

  // Печать массива
  printf ("New matrix:\n");
  for (int i = 0; i < n; i++)
    {
      if (*(matrix + i))
        {
          for (int j = 0; j < rows_element[i]; j++)
            {
              printf ("%d ", *(*(matrix + i) + j));
              fprintf (output_stream, "%d ", *(*(matrix + i) + j));
            }
          printf ("\n");
          fprintf (output_stream, "\n");
        }
    }

  printf ("Time: %2.2lf\n", time);
  AutoTest (1);

  // Освобождение памяти и закрытие потока
  fclose (input_stream);
  fclose (output_stream);
  for (int i = 0; i < n; i++)
    {
      if (*(matrix + i))
        {
          free(*(matrix + i));
        }
    }
  free (matrix);
  return 0;
}
