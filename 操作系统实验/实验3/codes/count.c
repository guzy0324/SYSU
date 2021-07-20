int count(char *str)
{
    int n = 0;
    for (; str[n] != '\0'; n++)
        ;
    return n;
}
void uint2str(int n, char *str)
{
    unsigned char st[11];
    int len = 0;
    while (n > 0)
    {
        st[len++] = n % 10;
        n /= 10;
    }
    for (; n < len; n++)
    {
        str[n] = st[len - n - 1] + '0';
    }
    str[len] = '\0';
}