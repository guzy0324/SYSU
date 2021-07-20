short ccount(char *str)
{
    short n = 0;
    for (; str[n] != '\0'; n++)
        ;
    return n;
}
short count(char *str)
{
    int a = ccount(str);
    int b = a + 1;
    return b;
}