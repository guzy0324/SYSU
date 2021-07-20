#include "lib.h"
char str[80] = "129djwqhdsajd128dw9i39ie93i8494urjoiew98kdkd";
int LetterNr = 0;
float LetterNrF = 0.0;
int main()
{
    _cls();
    init();
    /*for (int i = 0; str[i] != '\0'; i++)
    {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
        {
            LetterNr++;
        }
    }
    printf(0, 0, 7, "Number of letters = %d", LetterNr);*/
    int pid = _fork();
    if (pid == -1)
    {
        printf(0, 0, 7, "Error in fork!");
    }
    if (pid)
    {
        _block();
        printf(0, 0, 7, "Number of letters = %d", LetterNr);
    }
    else
    {
        for (int i = 0; str[i] != '\0'; i++)
        {
            if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
            {
                LetterNr++;
            }
        }
        _exit();
    }
    _get();
}