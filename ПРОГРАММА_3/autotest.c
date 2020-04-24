#include "autotest.h"

void AutoTest_change (int **matrix, int *rows_element, int n)
{
  int i = 0;
  int j = 0;
  int temp = 0;

  int matrix_res[6][11] = {
    { 7, 8, 9 },
    { 10, 11 },
    { 111, 123, 333, 444, 5555, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    { 4, 4 },
    { 5, 1 }
  };


  for (i = 0; i < n; i++)
    {
      if (*(matrix + i))
        {
          for (j = 0; j < rows_element[i]; j++)
            if (*(*(matrix + i) + j) != *(*(matrix_res + i + temp) + j))
              {
                printf ("Autotest failed!\n");
                return;
              }
        }
      else
        temp--;
    }

  printf ("Autotest passed!\n");
  return;
}

void AutoTest_not_change (int **matrix, int *rows_element, int n)
{
  int i = 0;
  int j = 0;
  int temp = 0;

  int matrix_res[7][12] = {
    { 1, 2, 3, 4, 5, 1},
    { 7, 8, 9, 1 },
    { 10, 11 },
    { 111, 123, 333, 444, 5555, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    { 4, 4, 1},
    { 5, 1 }
  };

  for (i = 0; i < n; i++)
    {
      if (*(matrix + i))
        {
          for (j = 0; j < rows_element[i]; j++)
            if (*(*(matrix + i) + j) != *(*(matrix_res + i + temp) + j))
              {
                printf ("Autotest failed!\n");
                return;
              }
        }
      else
        temp--;
    }

  printf ("Autotest passed!\n");
  return;
}
