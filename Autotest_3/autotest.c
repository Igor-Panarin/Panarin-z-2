#include "autotest.h"

void AutoTest_change (void)
{
  int **matrix;
  int *rows_element;
  int n = 0;
  int i = 0;
  int j = 0;
  int temp = 0;
  FILE *input_stream = stdin;
  char string_temp[STRING_SIZE];
  const char *input_filename = "data.res";

  int matrix_res[6][4] = {
    { 7, 8, 9 },
    { 10, 11 },
    { 11, 12, 33, 44 },
    { 0, 0, 0 },
    { 4, 4 },
    { 5, 1 }
  };

  // открытие файла
  if (!(input_stream = fopen (input_filename, "r")))
    return;

  // запись кол-ва элементов в файле
  while (fgets (string_temp, STRING_SIZE, input_stream))
    if (string_temp[0] != '\n' && string_temp[0] != '\0')
      n++;

  // выделение памяти для массива кол-ва элементов в строке
  rows_element = (int *) malloc (n * sizeof(int));
  if (!rows_element)
    {
      fclose (input_stream);
      return;
    }

  // запись кол-ва элементов в строке
  rewind (input_stream);
  if (set_row_elemets (rows_element, n, input_stream))
    {
      fclose (input_stream);
      free (rows_element);
      return;
    }

  // выделение памяти под весь файл
  matrix = (int **) malloc (n * sizeof(int *));
  if (!matrix)
    {
      fclose (input_stream);
      free (rows_element);
      return;
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
          return;
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
      return;
    }

  for (i = 0; i < n; i++)
    {
      if (*(matrix + i))
        {
          for (j = 0; j < rows_element[i]; j++)
            if (*(*(matrix + i) + j) != *(*(matrix_res + i + temp) + j))
              {
                printf ("Autotest failed!\n");
                fclose (input_stream);
                for (i = 0; i < n; i++)
                  if (*(matrix + i))
                    free(*(matrix + i));
                free (matrix);
                free (rows_element);
                return;
              }
        }
      else
        temp--;
    }

  printf ("Autotest passed!\n");
  fclose (input_stream);
  for (i = 0; i < n; i++)
    if (*(matrix + i))
      free(*(matrix + i));
  free (matrix);
  free (rows_element);
  return;
}

void AutoTest_not_change (void)
{
  int **matrix;
  int *rows_element;
  int n = 0;
  int i = 0;
  int j = 0;
  int temp = 0;
  FILE *input_stream = stdin;
  char string_temp[STRING_SIZE];
  const char *input_filename = "data.res";

  int matrix_res[7][6] = {
    { 1, 2, 3, 4, 5, 1},
    { 7, 8, 9, 1 },
    { 10, 11 },
    { 11, 12, 33, 44 },
    { 0, 0, 0, 1 },
    { 4, 4, 1 },
    { 5, 1 }
  };

  // открытие файла
  if (!(input_stream = fopen (input_filename, "r")))
    return;

  // запись кол-ва элементов в файле
  while (fgets (string_temp, STRING_SIZE, input_stream))
    if (string_temp[0] != '\n' && string_temp[0] != '\0')
      n++;

  // выделение памяти для массива кол-ва элементов в строке
  rows_element = (int *) malloc (n * sizeof(int));
  if (!rows_element)
    {
      fclose (input_stream);
      return;
    }

  // запись кол-ва элементов в строке
  rewind (input_stream);
  if (set_row_elemets (rows_element, n, input_stream))
    {
      fclose (input_stream);
      free (rows_element);
      return;
    }

  // выделение памяти под весь файл
  matrix = (int **) malloc (n * sizeof(int *));
  if (!matrix)
    {
      fclose (input_stream);
      free (rows_element);
      return;
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
          return;
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
      return;
    }

  for (i = 0; i < n; i++)
    {
      if (*(matrix + i))
        {
          for (j = 0; j < rows_element[i]; j++)
            if (*(*(matrix + i) + j) != *(*(matrix_res + i + temp) + j))
              {
                printf ("Autotest failed!\n");
                fclose (input_stream);
                for (i = 0; i < n; i++)
                  if (*(matrix + i))
                    free(*(matrix + i));
                free (matrix);
                free (rows_element);
                return;
              }
        }
      else
        temp--;
    }

  printf ("Autotest passed!\n");
  fclose (input_stream);
  for (i = 0; i < n; i++)
    if (*(matrix + i))
      free(*(matrix + i));
  free (matrix);
  free (rows_element);
  return;
}
