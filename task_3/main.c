#include "search.h"
#include "autotest.h"

int main (void)
{
  int result;
  double time;
  const char *SInputFile = "data.dat";
  char word[STRING_SIZE];
  word[0] = '\0';


  time = clock();
  result = search (SInputFile, word);
  time = (clock() - time) / CLOCKS_PER_SEC;

  if (result <= 0)
    {
      switch (result)
        {
        case 0:
          printf ("Cannot find word.\n");
          return 0;
        case -1:
          printf ("Cannot open file \"%s\".\n", SInputFile);
          return 0;
        case -2:
          printf ("Error read from file \"%s\".\n", SInputFile);
          return 0;
        default:
          printf ("Error in function \"search\".\n");
          return 0;
        }
    }

  printf ("Answer: \"%s\"\n", word);
  printf ("Time: %2.2lf\n", time);
  AutoTest (1);
  return 0;
}
