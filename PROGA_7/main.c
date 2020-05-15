#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <float.h>

#include "student.h"

#define MAX_PRINT 10

void print_student_ptr (student *student_ptr, int n, FILE *output_stream);
void print_student_ptr (student *student_ptr, int n, FILE *output_stream)
{
  int i = 0;
  for (i = 0; i < n; i++)
    fprintf (output_stream, "%s %d %.0lf\n",
             student_ptr[i].Name,
             student_ptr[i].Group,
             student_ptr[i].Rating);
  return;
}

int main (void)
{
  int i = 0, j = 0;
  int n = 0;
  const char *input_filename = "input.txt";
  const char *output_filename = "output.txt";
  FILE *input_stream = stdin;
  FILE *output_stream = stdout;
  char temp_str[LEN];
  student *student_ptr;
  student *student_ptr_max_rating;

  double max_rating = 0;
  int n_max_rating = 0;

  if (!(input_stream = fopen (input_filename, "r")))
    return 1;

  while (fgets (temp_str, LEN, input_stream))
    if (temp_str[0] != '\n' && temp_str[0] != '\0' && temp_str[0] != ' ')
      n++;

  student_ptr = (student *) malloc (n * sizeof (student));
  if (!student_ptr)
    {
      fclose (input_stream);
      return 1;
    }

  rewind (input_stream);

  for (i = 0; i < n; i++)
    {
      student_ptr[i].Group = 0;
      student_ptr[i].Rating = 0;
      if (fgets (temp_str, LEN, input_stream))
        {
          if (temp_str[0] != '\n' && temp_str[0] != '\0' && temp_str[0] != ' ')
            {
              sscanf (temp_str, "%s %d %lf",
                      student_ptr[i].Name,
                      &student_ptr[i].Group,
                      &student_ptr[i].Rating);

              if (i == 0 || max_rating < student_ptr[i].Rating)
                max_rating = student_ptr[i].Rating;
            }
          else
            i--;
        }
      else
        {
          fclose (input_stream);
          free (student_ptr);
          return 1;
        }
    }

  for (i = 0; i < n; i++)
    if (fabs (student_ptr[i].Rating - max_rating) < DBL_MIN)
      n_max_rating++;

  student_ptr_max_rating = (student *) malloc (n_max_rating * sizeof (student));
  if (!student_ptr)
    {
      fclose (input_stream);
      free (student_ptr);
      return 1;
    }

  for (i = 0, j = 0; i < n && j < n_max_rating; i++)
    {
      if (fabs (student_ptr[i].Rating - max_rating) < DBL_MIN)
        {
          strcpy (student_ptr_max_rating[j].Name, student_ptr[i].Name);
          student_ptr_max_rating[j].Group = 1000;
          student_ptr_max_rating[j].Rating = student_ptr[i].Rating;
          j++;
        }
    }

  if (!(output_stream = fopen (output_filename, "w")))
    {
      fclose (input_stream);
      free (student_ptr);
      free (student_ptr_max_rating);
      return 1;
    }

  print_student_ptr (student_ptr, n, stdout);
  printf ("\nStudents with max rating:\n");
  print_student_ptr (student_ptr_max_rating, n_max_rating, stdout);
  print_student_ptr (student_ptr, n, output_stream);
  fprintf (output_stream, "\nStudents with max rating:\n");
  print_student_ptr (student_ptr_max_rating, n_max_rating, output_stream);

  fclose (input_stream);
  fclose (output_stream);
  free (student_ptr);
  free (student_ptr_max_rating);
  return 0;
}
