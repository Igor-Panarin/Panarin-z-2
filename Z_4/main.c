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

  int i = 0;
  int j = 0;

  if (!(input_stream = fopen (input_filename, "r")))
    {
      return 1;
    }

  while (fgets (string_temp, STRING_SIZE, input_stream))
    {
      if (string_temp[0] != '\n' && string_temp[0] != '\0')
        {
          n++;
        }
    }

  int *rows_element;
  rows_element = (int *) malloc (n * sizeof(int));
  rewind (input_stream);

  for (i = 0; i < n; i++)
    {
      rows_element[i] = 0;
      while (fscanf (input_stream, "%d", &temp) == 1)
        {
          rows_element[i]++;
          if (fscanf (input_stream, "%c", &temp_ch) != 1)
            {
              fclose (input_stream);
              free (rows_element);
              return 2;
            }
          if (temp_ch == '\n' || temp_ch == '\0')
            {
              break;
            }
        }
    }

  int **matrix;
  matrix = (int **) malloc (n * sizeof(int *));
  if (!matrix)
    {
      return 3;
    }
  for (i = 0; i < n; i++)
    {
      *(matrix + i) = (int *) malloc (rows_element[i] * sizeof(int));
      if (!*(matrix + i))
        {
          fclose (input_stream);
          for (j = 0; j < i; j++)
            {
              if (*(matrix + j))
                {
                  free(*(matrix + j));
                }
            }
          free (matrix);
          free (rows_element);
          return 4;
        }
    }

  rewind (input_stream);

  for (i = 0; i < n; i++)
    {
      for (j = 0; j < rows_element[i]; j++)
        {
          if (fscanf (input_stream, "%d", *(matrix + i) + j) != 1)
            {
              fclose (input_stream);
              for (i = 0; i < n; i++)
                {
                  if (*(matrix + i))
                    {
                      free(*(matrix + i));
                    }
                }
              free (matrix);
              free (rows_element);
              return 5;
            }
        }
    }

  printf ("Matrix:\n");
  for (i = 0; i < n; i++)
    {
      for (j = 0; j < rows_element[i]; j++)
        {
          printf ("%d ", *(*(matrix + i) + j));
        }
      printf ("\n");
    }

  time = clock();
  for (i = 0; i < n; i++)
    {
      average = 0;
      for (j = 0; j < rows_element[i]; j++)
        {
          average += *(*(matrix + i) + j);
        }
      if (rows_element[i] != 0)
        average /= rows_element[i];
      for (j = 0; j < rows_element[i]; j++)
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
      fclose (input_stream);
      for (i = 0; i < n; i++)
        {
          if (*(matrix + i))
            {
              free(*(matrix + i));
            }
        }
      free (matrix);
      free (rows_element);
      return 6;
    }

  printf ("New matrix:\n");
  for (i = 0; i < n; i++)
    {
      if (*(matrix + i))
        {
          for (j = 0; j < rows_element[i]; j++)
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

  fclose (input_stream);
  fclose (output_stream);
  for (i = 0; i < n; i++)
    {
      if (*(matrix + i))
        {
          free(*(matrix + i));
        }
    }
  free (matrix);
  free (rows_element);
  return 0;
}
