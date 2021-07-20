#include "lib.h"
extern int _clock_wallpaper(int n);
extern int _new_layfun(unsigned cs, int (*fun)(int n), int n);
extern void _get_time();
extern unsigned char _time[];
struct layinfo wallpaper_info;
char str[CHSPSZ];
int color = 0b11100100;
unsigned clock_wallpaper(int n)
{
    unsigned cs = _get_cs();
    wallpaper_info.is_lay = 1;
    wallpaper_info.lay.ds = cs;
    wallpaper_info.lay.str = str;
    wallpaper_info.lay.x = 35;
    wallpaper_info.lay.y = 12;
    wallpaper_info.lay.color = color;
    n -= 1;
    if (n == 1)
    {
        color = 0;
    }
    else
    {
        color = ~color;
    }
    wallpaper_info.n = n;
    return (cs << 16) + (unsigned)&wallpaper_info;
}
int main()
{
    _cls();
    init();
    float a, b;
    scanf(0, 0, 0x0007, "%f %f", &a, &b);
    a += b;
    printf(0, 1, 0x0007, "%f", &a);
    __asm__(
        "int $0x22\n");
    _get_time();
    printf(20, 12, 0x0007, "20%x %x %x %x:%x:%x", _time[0], _time[1], _time[2], _time[3], _time[4], _time[5]);
    scanf(0, 2, 0x0007, "%s", str);
    _new_layfun(_get_cs(), _clock_wallpaper, 12);
}