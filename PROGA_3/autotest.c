#include "autotest.h"

void AutoTest (int number_of_delete_row, int result)
{
  if (number_of_delete_row == result)
    printf ("Autotest passed!\n");
  else
    printf ("Autotest failed!\n");
  return;
}
