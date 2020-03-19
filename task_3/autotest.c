#include "autotest.h"

void AutoTest (int result)
{
  if (result == RESULT)
    {
      printf ("Autotest passed!\n");
    }
  else
    {
      printf ("Autotest failed!\n");
    }
  return;
}
