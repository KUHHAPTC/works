/*
Реализация приложения для гарантированного уничтожения конфиденциальной информации путем затирания данных, реализованы
собственная функция и алгоритм Dod 5220.22M  - национальный стандарт Минобороны США
*/

#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <new>

#pragma comment (lib, "Advapi32.lib")

struct Node
{
    char filename[MAX_PATH];
    struct Node *next;
    struct Node *prev;
};

int dod(char *filename);
int mine(char *filename);
void err(struct Node *Now, struct Node *p, int a);

int main() {
    char q;
    int choice, amount, Err;
    struct Node *Top = NULL;
    struct Node *p = NULL;
    struct Node *Now = NULL;

    Top = new(std::nothrow) Node;
    if(Top == NULL)
    {
        printf("Error of memory allocation for Top");
        return 1;
    }
    p = new(std::nothrow) Node;
    if(p == NULL)
    {
        printf("Error of memory allocation for p");
        return 2;
    }
    Now = new(std::nothrow) Node;
    if(Now == NULL)
    {
        printf("Error of memory allocation for Now#1");
        return 3;
    }

    Err = printf("How you gonna delete your files?\nIf you wanna use DOD.VerseC enter 1, if you wanna use my function enter 2\n");
    if(Err < 0)
    {
        printf("Error of printf#1\n");
        return 4;
    }

    Err = scanf("%d", &choice);
    if(Err != 1)
    {
        printf("Error of scanf#1\n");
        return 5;
    }

    if(choice == 1)
    {
        Err = printf("Okay\n");
        if(Err < 0)
        {
            printf("Error of printf#2\n");
            return 6;
        }
    }
    else if (choice == 2)
    {
        Err = printf("That`s a good choice\n");
        if(Err < 0)
        {
            printf("Error of printf#3\n");
            return 7;
        }
    }
    else
    {
        Err = printf("I told you to enter 1 or 2! That`s over! Next time read more attentively\n");
        if(Err < 0)
        {
             printf("Error of printf#4\n");
             return 8;
        }
        return 9;
    }

    Err = printf("Enter how much files you wanna delete\n");
    if(Err < 0)
    {
        printf("Error of printf#5\n");
        return 10;
    }

    Err = scanf("%d", &amount);
    if(Err != 1)
    {
        printf("Error of scanf#2\n");
        return 11;
    }
    if(amount < 1)
    {
        printf("Enter natural number!");
        return 12;
    }

    Err = printf("Enter the path of file: ");
    if(Err < 0)
    {
        printf("Error of printf#6\n");
        return 13;
    }

    Err = scanf("%s", Now->filename);
    if(Err != 1)
    {
        printf("Error of scanf#3\n");
        return 14;
    }

    Top = Now;
    p = Now;

    for(int i = 0; i < amount - 1; i++)
    {
        Now = Now->next;
        Now = new(std::nothrow) Node;
        if(Now == NULL)
        {
            printf("Error of memory allocation for Now#2");
            err(Now, p, i);
            return 15;
        }
        Err = printf("Enter the path of file: ");
        if(Err < 0)
        {
            printf("Error of printf#7\n");
            err(Now, p, i);
            return 16;
        }
        Err = scanf("%s", Now->filename);
        if(Err != 1)
        {
            printf("Error of scanf#4\n");
            err(Now, p, i);
            return 17;
        }
        Now->prev = p;
        p->next = Now;
        p = Now;
    }

    Now->next = Top;
    Now = Top;

    Err = printf("Are you sure, that you gonna delete it? If you are, write y\n");
    if(Err < 0)
    {
        printf("Error of printf#8\n");
        err(Now, p, amount);
        return 18;
    }

    Err = scanf("\n%c", &q);
    if(q != 'y')
    {
        printf("It is a good idea, not to do it\n");
        err(Now, p, amount);
        return 19;
    }
    if(Err != 1)
    {
        printf("Error of scanf#5\n");
        err(Now, p, amount);
        return 20;
    }

    for(int i = 0; i < amount; i++)
    {
        switch(choice)
        {
            case 1:
            Err = dod(Now->filename);
            if(Err != 0)
            {
                printf("File wasn`t deleted, probably it doesn`t exist!\n");
                err(Now, p, amount);
                return 21;
            }
            Err = printf("File #%d is successfully deleted\n", i + 1);
            if(Err < 0)
            {
                printf("Error of printf#9\n");
                err(Now, p, amount);
                return 22;
            }
            Now = Now->next;
            break;
            case 2:
            Err = mine(Now->filename);
            if(Err != 0)
            {
                printf("File wasn`t deleted, probably it doesn`t exist!\n");
                err(Now, p, amount);
                return 23;
            }
            Err = printf("File #%d is successfully deleted\n", i + 1);
            if(Err < 0)
            {
                printf("Error of printf#10\n");
                err(Now, p, amount);
                return 24;
            }
            Now = Now->next;
            break;
        }
    }

    Now = Top;

    for(int i = 0; i < amount; i++)
    {
    Err = remove(Now->filename);
    if(Err != 0)
    {
        printf("Error of remove");
        err(Now, p, amount);
        return 25;
    }
    Now = Now->next;
    }

    for(int i = 0; i < amount; i++)
    {
        p = Now->next;
        delete Now;
        Now = p;
    }

    Err = printf("Successful clean and delete of the files\n");
    if(Err < 0)
    {
        printf("Error of printf#11\n");
        return 26;
    }

getchar();
getchar();

    return 0;
}

int mine(char *filename) {

    FILE *output;
    int Err = 0, size = 0, numb = 0, passes = 0;
    char j;
    HCRYPTPROV hProv = NULL;
    HCRYPTPROV *phProv = &hProv;
    BYTE *pbBuffer;
    BOOL retval;

    if(filename == NULL)
    {
        printf("Wrong path of file");
        return 1;
    }

    output = fopen(filename, "r+");
    if(output == NULL)
    {
        printf("Error of fopen\n");
        return 2;
    }

    Err = fseek(output, 0, SEEK_END);
    if(Err != 0)
    {
        printf("Error of fseek#1\n");
        return 3;
    }

    Err = size = ftell(output);
    if(Err == -1L)
    {
        printf("Error of ftell\n");
        return 4;
    }

    Err = fseek(output, 0, SEEK_SET);
    if(Err != 0)
    {
        printf("Error of fseek#2\n");
        return 5;
    }

    Err = printf("How much passes you want?\n");
    if(Err < 0)
    {
        printf("Error of printf#12\n");
        return 6;
    }

    Err = scanf("%d", &passes);
    if(Err != 1)
    {
        printf("Error of scanf#6\n");
        return 7;
    }

    pbBuffer = new(std::nothrow) BYTE[size];
    if (pbBuffer == NULL)
    {
        printf("Error of memory allocation");
        return 8;
    }

    retval = CryptAcquireContext(phProv, 0, 0, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
    if (retval != 0)
    {
        Err = CryptGenRandom(hProv, size, pbBuffer);
        if(Err == 0)
            {
                printf("Error of CryptGenRandom\n");
                 return 9;
            }
    }
    else
    {
        printf("Error of CryptAcquireContext");
        return 10;
    }

    if (CryptReleaseContext(hProv, 0) == 0)
    {
        printf("Error of CryptReleaseContext");
        return 11;
    }

    for(j = 0; j < passes; j++)
    {
        Err = printf("Symbol %d is ", j + 1);
        if(Err < 0)
        {
            printf("Error of printf#13\n");
            return 12;
        }

        Err = scanf("\n%d", &numb);
        if(Err != 1)
        {
            printf("Error of scanf#7\n");
            return 13;
        }

        if((numb > 0) && (numb < 256))
        {
            for(int i = 0; i < size; i++)
                Err = fwrite(&numb, sizeof(char), 1, output);
                if(Err != 1)
                {
                    printf("Error of fwrite#1\n");
                    return 14;
                }
        }
        else
        {
            for (int k = 0; k < size; k++)
            {
                numb = pbBuffer[k];
                Err = fwrite(&numb, sizeof(char), 1, output);
                if(Err != 1)
                {
                    printf("Error of fwrite#2\n");
                    return 15;
                }
            }
        }
        Err = fseek(output, 0, SEEK_SET);
        if(Err != 0)
        {
            printf("Error of fseek#3\n");
            return 16;
        }
    }

    delete[] pbBuffer;

    Err = fclose(output);
    if(Err != 0)
    {
        printf("Error of fclose");
        return 17;
    }

    return 0;
}

int dod(char *filename) {

    FILE *output;
    int Err = 0;
    int size = 0;
    HCRYPTPROV hProv = NULL;
    HCRYPTPROV *phProv = &hProv;
    BYTE *pbBuffer;
    BOOL retval;
    int temp;

    if(filename == NULL)
    {
        printf("Wrong path");
        return 1;
    }

    output = fopen(filename, "r+");
    if(output == NULL)
    {
        printf("Error of fopen\n");
        return 2;
    }

    Err = fseek(output, 0, SEEK_END);
    if(Err != 0)
    {
        printf("Error of fseek#1\n");
        return 3;
    }

    Err = size = ftell(output);
    if(Err == -1L)
    {
        printf("Error of ftell\n");
        return 4;
    }

    Err = fseek(output, 0, SEEK_SET);
    if(Err != 0)
    {
        printf("Error of fseek#2\n");
        return 5;
    }

    pbBuffer = new(std::nothrow) BYTE[size];
    if (pbBuffer == NULL)
    {
        printf("Error of memory allocation");
        return 6;
    }

    for(char j = 0; j < 2; j++)
    {
        for(int i = 0; i < size; i++)
            Err = fwrite(&j, sizeof(char), 1, output);
        if (Err != 1)
        {
            printf("Error of fwrite#1\n");
            return 7;
        }
        Err = fseek(output, 0, SEEK_SET);
        if(Err != 0)
        {
            printf("Error of fseek#3\n");
            return 8;
        }
    }

    retval = CryptAcquireContext(phProv, 0, 0, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_SILENT);
    if (retval != 0)
    {
        Err = CryptGenRandom(hProv, size, pbBuffer);
        if(Err == 0)
        {
            printf("Error of CryptGenRandom\n");
            return 9;
        }
        for (int k = 0; k < size; k++)
        {
            if (pbBuffer[k] < 128)
            {
                temp = 0;
            }
            else
            {
                temp = 1;
            }
            Err = fwrite(&temp, sizeof(char), 1, output);
            if (Err != 1)
            {
                printf("Error of fwrite#2\n");
                return 10;
            }
        }
    }
    else
    {
        printf("Error of CryptAcquireContext");
        return 11;
    }

    if (CryptReleaseContext(hProv, 0) == 0)
    {
        printf("Error of CryptReleaseContext");
        return 12;
    }

    delete[] pbBuffer;

    Err = fclose(output);
    if(Err != 0)
    {
        printf("Error of fclose\n");
        return 13;
    }

    return 0;
}

void err(struct Node *Now, struct Node *p, int amount) {

    for(int i = 0; i < amount; i++)
    {
        p = Now->next;
        delete Now;
        Now = p;
    }
}

