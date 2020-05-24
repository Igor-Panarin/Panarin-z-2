#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <float.h>

#include "student.h"

#define MAX_PRINT 10

void print_student_ptr (student *student_ptr, int n, FILE *output_stream);
void clear (student *student_ptr, int j);

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

void clear (student *student_ptr, int j)
{
  int i = 0;
  for (i = 0; i <= j; i++)
    {
      student_ptr[i].Group = 0;
      student_ptr[i].Rating = 0;
      student_ptr[i].Name[0] = '\0';
    }
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

  double max_rating = 0;

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

  for (i = 0; i < n; i++, j++)
    {
      student_ptr[j].Group = 0;
      student_ptr[j].Rating = 0;

      if (fgets (temp_str, LEN, input_stream))
        {
          if (temp_str[0] != '\n' && temp_str[0] != '\0' && temp_str[0] != ' ')
            {
              sscanf (temp_str, "%s %d %lf",
                      student_ptr[j].Name,
                      &student_ptr[j].Group,
                      &student_ptr[j].Rating);

              if (i == 0)
                {
                  max_rating = student_ptr[j].Rating;
                }
              else
                {
                  if (max_rating < student_ptr[j].Rating)
                    {
                      clear (student_ptr, j);
                      j = 0;

                      sscanf (temp_str, "%s %d %lf",
                              student_ptr[j].Name,
                              &student_ptr[j].Group,
                              &student_ptr[j].Rating);

                      max_rating = student_ptr[j].Rating;
                    }
                  else if (max_rating > student_ptr[j].Rating)
                    {
                      student_ptr[j].Group = 0;
                      student_ptr[j].Rating = 0;
                      student_ptr[j].Name[0] = '\0';
                      j--;
                    }

                }
            }
          else
            {
              i--;
              j--;
            }
        }
      else
        {
          fclose (input_stream);
          free (student_ptr);
          return 1;
        }
    }


  if (!(output_stream = fopen (output_filename, "w")))
    {
      fclose (input_stream);
      free (student_ptr);
      return 1;
    }

  print_student_ptr (student_ptr, j, stdout);
  print_student_ptr (student_ptr, j, output_stream);

  fclose (input_stream);
  fclose (output_stream);
  free (student_ptr);
  return 0;
}
