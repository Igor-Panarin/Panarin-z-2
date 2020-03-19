#include "search.h"

int search (const char *SInputFile, char *word)
{
  FILE *InputFile = stdin;
  int flag = 1;
  int max_word_size = 0;
  char string_temp[STRING_SIZE];
  char word_temp[STRING_SIZE];

  if (!(InputFile = fopen (SInputFile, "r")))
    {
      return -1;
    }

  while (fgets (string_temp, STRING_SIZE, InputFile))
    {
//      printf ("%s", string_temp);
      for (int i = 0; i < STRING_SIZE && string_temp[i] != '\0'; i++)
        {
          if (string_temp[i] == '"')
            {
              flag = 1;
              for (int j = i + 1, k = 0; j < STRING_SIZE; j++, k++)
                {
                  word_temp[k] = string_temp[j];
                  if (word_temp[k] != '"' && (word_temp[k] > 'A' + 26 || word_temp[k] < 'A'))
                    {
                      flag = 0;
                    }
                  if (word_temp[k] == '"')
                    {
                      word_temp[k] = '\0';
                      if (flag == 1 && word_temp[k - 1] == 'A' &&
                          max_word_size < (int) strlen (word_temp))
                        {
                          strcpy (word, word_temp);
                          max_word_size = strlen (word_temp);
                        }
                      i = j + 1;
                      break;
                    }
                }
            }
        }
//      printf ("Answer: %s\n", word);
    }

  fclose (InputFile);
  return max_word_size;
}
