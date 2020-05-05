#include "autotest.h"

void AutoTest_change (void)
{
  int **matrix;
  int *rows_element;
  int n = 7;
  int i = 0;
  int j = 0;
  int temp = 0;

  int matrix_input[7][5] = {
    { 1, 2, 3, 4, 5 },
    { 7, 8, 9 },
    { 10, 11 },
    { 11, 12, 33, 44 },
    { 0, 0, 0 },
    { 4, 4 },
    { 5, 1 }
  };

  int matrix_res[6][4] = {
    { 7, 8, 9 },
    { 10, 11 },
    { 11, 12, 33, 44 },
    { 0, 0, 0 },
    { 4, 4 },
    { 5, 1 }
  };

  rows_element = (int *) malloc (n * sizeof(int));
  if (!rows_element)
    {
      printf ("Not enough memory!\n");
      return;
    }

  rows_element[0] = 5;
  rows_element[1] = 3;
  rows_element[2] = 2;
  rows_element[3] = 4;
  rows_element[4] = 3;
  rows_element[5] = 2;
  rows_element[6] = 2;

  // выделение памяти под весь файл
  matrix = (int **) malloc (n * sizeof(int *));
  if (!matrix)
    {
      free (rows_element);
      printf ("Not enough memory!\n");
      return;
    }

  for (i = 0; i < n; i++)
    {
      *(matrix + i) = (int *) malloc (rows_element[i] * sizeof(int));
      if (!*(matrix + i))
        {
          for (j = 0; j < i; j++)
            if (*(matrix + j))
              free(*(matrix + j));
          free (matrix);
          free (rows_element);
          printf ("Not enough memory!\n");
          return;
        }
    }

  for (i = 0; i < n; i++)
    for (j = 0; j < rows_element[i]; j++)
      *(*(matrix + i) + j) = *(*(matrix_input + i) + j);

  function (matrix, rows_element, n);

  for (i = 0; i < n; i++)
    {
      if (*(matrix + i))
        {
          for (j = 0; j < rows_element[i]; j++)
            if (*(*(matrix + i) + j) != *(*(matrix_res + i + temp) + j))
              {
                printf ("Autotest failed!\n");
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
  int n = 7;
  int i = 0;
  int j = 0;
  int temp = 0;

  int matrix_input[7][6] = {
    { 1, 2, 3, 4, 5, 1 },
    { 7, 8, 9, 1 },
    { 10, 11 },
    { 11, 12, 33, 44 },
    { 0, 0, 0, 1 },
    { 4, 4, 1 },
    { 5, 1 }
  };

  int matrix_res[7][6] = {
    { 1, 2, 3, 4, 5, 1 },
    { 7, 8, 9, 1 },
    { 10, 11 },
    { 11, 12, 33, 44 },
    { 0, 0, 0, 1 },
    { 4, 4, 1 },
    { 5, 1 }
  };

  rows_element = (int *) malloc (n * sizeof(int));
  if (!rows_element)
    {
      printf ("Not enough memory!\n");
      return;
    }

  rows_element[0] = 6;
  rows_element[1] = 4;
  rows_element[2] = 2;
  rows_element[3] = 4;
  rows_element[4] = 4;
  rows_element[5] = 3;
  rows_element[6] = 2;

  // выделение памяти под весь файл
  matrix = (int **) malloc (n * sizeof(int *));
  if (!matrix)
    {
      free (rows_element);
      printf ("Not enough memory!\n");
      return;
    }

  for (i = 0; i < n; i++)
    {
      *(matrix + i) = (int *) malloc (rows_element[i] * sizeof(int));
      if (!*(matrix + i))
        {
          for (j = 0; j < i; j++)
            if (*(matrix + j))
              free(*(matrix + j));
          free (matrix);
          free (rows_element);
          printf ("Not enough memory!\n");
          return;
        }
    }

  for (i = 0; i < n; i++)
    for (j = 0; j < rows_element[i]; j++)
      *(*(matrix + i) + j) = *(*(matrix_input + i) + j);

  function (matrix, rows_element, n);

  for (i = 0; i < n; i++)
    {
      if (*(matrix + i))
        {
          for (j = 0; j < rows_element[i]; j++)
            if (*(*(matrix + i) + j) != *(*(matrix_res + i + temp) + j))
              {
                printf ("Autotest failed!\n");
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

  printf ("\nAutotest passed!\n");
  for (i = 0; i < n; i++)
    if (*(matrix + i))
      free(*(matrix + i));
  free (matrix);
  free (rows_element);
  return;
}
