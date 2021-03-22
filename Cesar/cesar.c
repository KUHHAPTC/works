/*
Реализация алгоритма шифра Цезаря на С
*/

#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

int main()
{
  int n, Err;

  Err = printf("1 to encrypt code, 2 to decrypt code\n");
  if (Err < 0)
  {
    printf("printf error#1!");
    return 1;
  }

  Err = scanf("%d", &n);
  if (Err != 1)
  {
    printf("scanf error#1!");
    return 2;
  }

  switch (n)
  {
  case 1:
    Err = encoder();
    if (Err != 0)
    {
      printf("Error of encryption!");
      return 3;
    }
    Err = getchar();
    if (Err == EOF)
      return 4;

    Err = getchar();
    if (Err == EOF)
      return 5;
    break;
  case 2:
    Err = decryptor();
    if (Err != 0)
    {
      printf("Error of decryption!");
      return 6;
    }
    Err = getchar();
    if (Err == EOF)
      return 7;
    Err = getchar();
    if (Err == EOF)
      return 8;
    break;
  default:
    Err = printf("Wrong value. You should choose 1 or 2!!!!");
    if (Err < 0)
    {
      printf("printf error#2!");
      return 9;
    }
    break;
  }

  return 0;
}

int encoder()
{
  int Err;
  FILE *input, *output;
  char filename[2][64];
  char t;
  int Key, c;

  Err = printf("1st arg is file which you gonna encrypt, 2nd is encrypted file name, 3rd is KEY\n");
  if (Err < 0)
  {
    printf("printf error#3!");
    return 1;
  }

  Err = printf("Choose the KEY from -26 to 26\n");
  if (Err < 0)
  {
    printf("printf error#4!");
    return 2;
  }

  Err = scanf("%64s%64s%d", filename[0], filename[1], &Key);
  if (Err != 3)
  {
    printf("scanf error#2!");
    return 3;
  }

  if (Key > 26 || Key < -26)
  {
    printf("Error of key!");
    return 4;
  }

  input = fopen(filename[0], "r");
  if (input == NULL)
  {
    printf("fopen error#1(Such file doesn`t exist)!\n");
    return 5;
  }

  output = fopen(filename[1], "w");
  if (output == NULL)
  {
    printf("fopen error#2!\n");
    return 6;
  }

  while ((c = fgetc(input)) != EOF)
  {
    if (isalpha(c))
    {
      t = islower(c) ? 'a' : 'A';
      c = (c - t + Key + 26) % 26 + t;
    }
    Err = fputc(c, output);
    if (Err == EOF)
    {
      printf("fputc error#1!");
      return 7;
    }
  }

  Err = fclose(input);
  if (Err != 0)
  {
    printf("fclose error#1!");
    return 8;
  }

  Err = fclose(output);
  if (Err != 0)
  {
    printf("fclose error#2!");
    return 9;
  }
  Err = printf("Successful encryption\n");
  if (Err < 0)
  {
    printf("printf error#5!");
    return 10;
  }

  return 0;
}

int decryptor()
{
  FILE *input, *output;
  int c, Max, t;
  int Counter[26];
  int Key, Err;
  char filename[2][64];

  for (int i = 0; i < 26; i++)
    Counter[i] = 0;

  Err = printf("1st arg is encrypted file, 2nd - name of file where you gonna decrypt it\n");
  if (Err < 0)
  {
    printf("printf error#6!");
    return 1;
  }

  Err = scanf("%64s%64s", filename[0], filename[1]);
  if (Err != 2)
  {
    printf("scanf error#3!");
    return 2;
  }

  Max = 0;

  input = fopen(filename[0], "r");
  if (input == NULL)
  {
    printf("fopen error#3!(Such file doesn`t exist)\n");
    return 3;
  }

  output = fopen(filename[1], "w");
  if (output == NULL)
  {
    printf("fopen error#4!\n");
    return 4;
  }

  while ((c = fgetc(input)) != EOF)
  {
    if (isalpha(c))
    {
      Counter[tolower(c) - 'a']++;
      if (Counter[tolower(c) - 'a'] > Counter[Max])
        Max = tolower(c) - 'a';
    }
  }

  Key = Max + 'a' - 'e';

  Err = fseek(input, 0, SEEK_SET);
  if (Err != 0)
  {
    printf("fseek error!");
    return 5;
  }

  while ((c = fgetc(input)) != EOF)
  {
    if (isalpha(c))
    {
      t = islower(c) ? 'a' : 'A';
      c = (c - t - Key + 26) % 26 + t;
    }
    Err = fputc(c, output);
    if (Err == EOF)
    {
      printf("fputc error#2!");
      return 6;
    }
  }

  Err = fclose(input);
  if (Err != 0)
  {
    printf("fclose error#3!");
    return 7;
  }

  Err = fclose(output);
  if (Err != 0)
  {
    printf("fclose error#4!");
    return 8;
  }

  Err = printf("Successful decryption\n");
  if (Err < 0)
  {
    printf("printf error#7!");
    return 9;
  }

  return 0;
}
