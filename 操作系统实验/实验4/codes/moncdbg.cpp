#include <conio.h>
#include <stdio.h>
#include <windows.h>
#define null 0
#define CHSPSZ 256
#define LEFT 0x4b
#define RIGHT 0x4d
#define UP 0x48
#define DOWN 0x50
#define DEFAULT_X 0
#define DEFUALT_Y 0
#define CMDSZ 8
#define PROGSZ 8
#define LYSPSZ 16
struct ahch
{
    char ch;
    unsigned char ah;
};
int chheader, cursor, cursor_x, cursor_y;
void _put(char ch)
{
    _putch(ch);
}
void _move(int x, int y)
{
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO binfo;
    GetConsoleScreenBufferInfo(hout, &binfo);
    binfo.dwCursorPosition.X = x;
    binfo.dwCursorPosition.Y = y;
    SetConsoleCursorPosition(hout, binfo.dwCursorPosition);
}
unsigned short _get()
{
    return getch();
}
void _cls()
{
    system("cls");
}
void _callf(int cl, int ch, int dh, int len)
{
    printf("%d %d %d %d\n", cl, ch, dh, len);
    _get();
}
void _display(char ch, int x, int y, int color)
{
    _move(x, y);
    _put(ch);
    _move(cursor_x, cursor_y);
}
void _get_time()
{
    return;
}
unsigned char _time[6] = {0x20, 0x5, 0x27, 0x13, 0x22, 0x50};
void _set_int(int cs, void (*inter)(), int index)
{
    return;
}
void _clock()
{
    return;
}
void int2str(int n, char *str)
{
    int top = 0;
    char stk[10];
    while (n != 0)
    {
        stk[top++] = n % 10 + '0';
        n /= 10;
    }
    while (top != 0)
    {
        str[n++] = stk[--top];
    }
    str[n] = 0;
}
void BCD2str(unsigned char BCD, char *str)
{
    str[0] = (BCD >> 4) + '0';
    str[1] = (BCD & 0xf) + '0';
}
void display_str(char *str, int x, int y, int color)
{
    int offset_x = 0, offset_y = 0;
    for (int i = 0; str[i] != 0; i++)
    {
        if (str[i] == '\n')
        {
            offset_x = 0;
            offset_y++;
        }
        else
        {
            _display(str[i], x + offset_x, y + offset_y, color);
            offset_x++;
        }
    }
}
void new_page()
{
    cursor_x = 0;
    cursor_y = 0;
    _move(cursor_x, cursor_y);
    _cls();
}
void print(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '\n')
        {
            cursor_x = 0;
            cursor_y++;
        }
        else
        {
            _put(str[i]);
            cursor_x++;
        }
        _move(cursor_x, cursor_y);
    }
}
struct node
{
    int next;
    int last;
};
int new_node(int cursor, int *header_ptr, struct node ndsp[])
{
    int neo = ndsp[null].next;
    if (neo == null)
    {
        return null;
    }
    ndsp[null].next = ndsp[neo].next;
    ndsp[neo].next = cursor;
    if (cursor != null)
    {
        ndsp[neo].last = ndsp[cursor].last;
        if (ndsp[neo].last != null)
        {
            ndsp[ndsp[neo].last].next = neo;
        }
        ndsp[cursor].last = neo;
    }
    else
    {
        ndsp[neo].last = null;
    }
    if (*header_ptr == cursor)
    {
        *header_ptr = neo;
    }
    return neo;
}
void delete_node(int nd, int *header_ptr, struct node ndsp[])
{
    if (*header_ptr == nd)
    {
        *header_ptr = ndsp[nd].next;
    }
    if (ndsp[nd].next != null)
    {
        ndsp[ndsp[nd].next].last = ndsp[nd].last;
    }
    if (ndsp[nd].last != null)
    {
        ndsp[ndsp[nd].last].next = ndsp[nd].next;
    }
    ndsp[nd].next = ndsp[null].next;
    ndsp[null].next = nd;
}
void init_node(int *header_ptr, struct node ndsp[], int sz)
{
    int i = 0;
    for (; i < sz - 1; i++)
    {
        ndsp[i].next = i + 1;
    }
    ndsp[i].next = null;
    *header_ptr = null;
    *header_ptr = new_node(null, header_ptr, ndsp);
}
char chsp[CHSPSZ];
struct node chndsp[CHSPSZ];
int new_ch(char c, int cursor)
{
    int neo_ch = new_node(cursor, &chheader, chndsp);
    if (neo_ch != null)
    {
        chsp[neo_ch] = c;
    }
    return neo_ch;
}
/*void delete_ch(int nd)
{
    delete_node(nd, &chheader, chndsp);
}*/
void dump_node(char buf[])
{
    int i = 0;
    while (chsp[chheader] != 0)
    {
        if (chsp[chheader] >= 'a' && chsp[chheader] <= 'z')
        {
            chsp[chheader] += 'A' - 'a';
        }
        else if (chsp[chheader] == '\t')
        {
            chsp[chheader] = ' ';
        }
        buf[i] = chsp[chheader];
        delete_node(chheader, &chheader, chndsp);
        if (buf[i] == ' ')
        {
            while (chheader != null && (chsp[chheader] == ' ' || chsp[chheader] == '\t'))
            {
                delete_node(chheader, &chheader, chndsp);
            }
        }
        i++;
    }
    buf[i] = 0;
}
void read()
{
    cursor = chheader;
    cursor_x = DEFAULT_X;
    cursor_y = DEFUALT_Y;
    _move(cursor_x, cursor_y);
    unsigned short temp_ax = _get();
    struct ahch ax = *(struct ahch *)&temp_ax;
    while (ax.ch != '\r')
    {
        if (ax.ch == 0 || ax.ch == -32)
        {
            if (ax.ah == LEFT)
            {
                if (chndsp[cursor].last != null)
                {
                    cursor = chndsp[cursor].last;
                    cursor_x -= 1;
                    _move(cursor_x, cursor_y);
                }
                /*else
                {
                    put('\a');
                }*/
            }
            else if (ax.ah == RIGHT)
            {
                if (chndsp[cursor].next != null)
                {
                    cursor = chndsp[cursor].next;
                    cursor_x += 1;
                    _move(cursor_x, cursor_y);
                }
                /*else
                {
                    put('\a');
                }*/
            }
            else if (ax.ah == UP)
            {
                cursor = chheader;
                cursor_x = DEFAULT_X;
                _move(cursor_x, cursor_y);
            }
            else if (ax.ah == DOWN)
            {
                for (; chsp[cursor] != 0; cursor = chndsp[cursor].next)
                {
                    cursor_x++;
                }
                _move(cursor_x, cursor_y);
            }
        }
        else if (ax.ch == '\b')
        {
            if (chndsp[cursor].last != null)
            {
                delete_node(chndsp[cursor].last, &chheader, chndsp);
                cursor_x--;
                int temp_x = cursor_x;
                _move(cursor_x, cursor_y);
                for (int temp = cursor; temp != null; temp = chndsp[temp].next)
                {
                    _put(chsp[temp]);
                    temp_x++;
                    _move(temp_x, cursor_y);
                }
                _move(cursor_x, cursor_y);
            }
            /*else
            {
                put('\a');
            }*/
        }
        else
        {
            int temp = new_ch(ax.ch, cursor);
            if (temp != null)
            {
                int temp_x = cursor_x;
                for (; chsp[temp] != 0; temp = chndsp[temp].next)
                {
                    _put(chsp[temp]);
                    temp_x++;
                    _move(temp_x, cursor_y);
                }
                cursor_x++;
                _move(cursor_x, cursor_y);
            }
            /*else
            {
                put('\a');
            }*/
        }
        temp_ax = _get();
        ax = *(struct ahch *)&temp_ax;
    }
}
int cmp(char *buf, char *cmd)
{
    unsigned int i = 0;
    for (; buf[i] != 0 && buf[i] == cmd[i]; i++)
        ;
    return buf[i] == cmd[i];
}
struct prog
{
    char *name;
    int stt;
    int len;
} program[PROGSZ];
int progsz;
void vir2phy(int vir, int *clp, int *chp, int *dhp)
{
    *clp = vir % 18 + 1;
    *chp = vir / 18 >> 1;
    *dhp = vir / 18 & 1;
}
void cmd_call(char *para)
{
    char *ptr = para;
    while (1)
    {
        for (; *ptr != 0 && *ptr != ' '; ptr++)
            ;
        if (*ptr != 0)
        {
            *ptr = 0;
            for (int i = 0; i < progsz; i++)
            {
                if (cmp(para, program[i].name))
                {
                    int cl, ch, dh;
                    vir2phy(program[i].stt, &cl, &ch, &dh);
                    _callf(cl, ch, dh, program[i].len);
                    break;
                }
            }
            ptr++;
            para = ptr;
        }
        else
        {
            for (int i = 0; i < progsz; i++)
            {
                if (cmp(para, program[i].name))
                {
                    int cl, ch, dh;
                    vir2phy(program[i].stt, &cl, &ch, &dh);
                    _callf(cl, ch, dh, program[i].len);
                    break;
                }
            }
            break;
        }
    }
}
void cmd_list(char *para)
{
    new_page();
    print("Name");
    cursor_x = 13;
    _move(cursor_x, cursor_y);
    print("Start");
    cursor_x = 20;
    _move(cursor_x, cursor_y);
    print("Size");
    for (int i = 0; i < progsz; i++)
    {
        cursor_y++;
        cursor_x = 0;
        _move(cursor_x, cursor_y);
        print(program[i].name);
        cursor_x = 13;
        _move(cursor_x, cursor_y);
        char temp[11];
        int2str(program[i].stt, temp);
        print(temp);
        cursor_x = 20;
        _move(cursor_x, cursor_y);
        int2str(program[i].len, temp);
        print(temp);
    }
    _get();
}
struct cmd
{
    char *name;
    void (*fun)(char *para);
} command[CMDSZ];
int cmdsz;
int execute(char *buf)
{
    char *ptr = buf;
    for (; *ptr != ' ' && *ptr != 0; ptr++)
        ;
    if (*ptr != 0)
    {
        *ptr = 0;
        ptr++; //有坂数
    }
    for (int i = 0; i < cmdsz; i++)
    {
        if (cmp(buf, command[i].name))
        {
            command[i].fun((char *)ptr);
            return 1;
        }
    }
    return 0;
}
struct layer
{
    char *str;
    int x;
    int y;
    int color;
};
struct layer lysp[LYSPSZ];
struct node lyndsp[LYSPSZ];
int lyheader;
int new_layer(char *str, int x, int y, int color, int cursor)
{
    int neo_layer = new_node(cursor, &lyheader, lyndsp);
    if (neo_layer != null)
    {
        lysp[neo_layer].str = str;
        lysp[neo_layer].x = x;
        lysp[neo_layer].y = y;
        lysp[neo_layer].color = color;
    }
    return neo_layer;
}
/*void delete_layer(int nd)
{
    delete_node(nd, &lyheader, lyndsp);
}*/
struct layfun
{
    void (*fun)(int *n_ptr);
    int n;
};
struct layfun lyfnsp[LYSPSZ];
struct node lyfnndsp[LYSPSZ];
int lyfnheader;
int new_layfun(void (*fun)(int *n_ptr), int n, int cursor)
{
    int neo_layfun = new_node(cursor, &lyfnheader, lyfnndsp);
    if (neo_layfun != null)
    {
        lyfnsp[neo_layfun].fun = fun;
        lyfnsp[neo_layfun].n = n;
    }
    return neo_layfun;
}
/*void delete_layfun(int nd)
{
    delete_node(nd, &lyfnheader, lyfnndsp);
}*/
char HW_arr[] = "/|\\";
void clock_hotwheel(int *n_ptr)
{
    char temp[] = {HW_arr[*n_ptr % 3], 0};
    new_layer(temp, 60, 24, 0b00111111, lyheader);
    *n_ptr -= 1;
    if (*n_ptr % 3 == 0)
    {
        *n_ptr = 3;
    }
}
/*void hotwheel()
{
    new_layfun(clock_hotwheel, 3, lyfnheader);
}*/
char clock_str[20] = "20yy/mm/dd hh:mm:ss";
void clock_time(int *n_ptr)
{
    if (*n_ptr % 2 == 0)
    {
        _get_time();
        char *ptr = clock_str + 2;
        for (int i = 0; i < 6; i++)
        {
            BCD2str(_time[i], ptr);
            ptr += 3;
        }
        new_layer(clock_str, 61, 24, 0b00111101, lyheader);
    }
    *n_ptr -= 1;
    if (*n_ptr % 2 == 0)
    {
        *n_ptr = 2;
    }
}
/*void time()
{
    new_layfun(clock_time, 4, lyfnheader);
}*/
char ouch_str[] = "OUCH!OUCH!";
int ouch_color;
void clock_ouch(int *n_ptr)
{
    new_layer(ouch_str, 35, 12, ouch_color, lyheader);
    *n_ptr -= 1;
    if (*n_ptr == 1)
    {
        ouch_color = 0;
    }
    else
    {
        ouch_color = ~ouch_color;
    }
}
/*void ouch()
{
    ouch_color = 0b11100100;
    new_layfun(clock_ouch, 4, lyfnheader);
}*/
void clock()
{
    for (int ptr = lyfnheader; lyfnsp[ptr].fun != NULL; ptr = lyfnndsp[ptr].next)
    {
        lyfnsp[ptr].fun(&lyfnsp[ptr].n);
        if (lyfnsp[ptr].n == 0)
        {
            delete_node(ptr, &lyfnheader, lyfnndsp);
        }
    }
    while (lysp[lyheader].str != NULL)
    {
        display_str(lysp[lyheader].str, lysp[lyheader].x, lysp[lyheader].y, lysp[lyheader].color);
        delete_node(lyheader, &lyheader, lyndsp);
    }
}
void init()
{
    _cls();
    command[0].name = "CALL";
    command[0].fun = cmd_call;
    command[1].name = "LIST";
    command[1].fun = cmd_list;
    cmdsz = 2;
    program[0].name = "LTUP.COM";
    program[0].stt = 32;
    program[0].len = 1;
    program[1].name = "LTDN.COM";
    program[1].stt = 33;
    program[1].len = 1;
    program[2].name = "RTUP.COM";
    program[2].stt = 34;
    program[2].len = 1;
    program[3].name = "RTDN.COM";
    program[3].stt = 35;
    program[3].len = 1;
    program[4].name = "CAL.COM";
    program[4].stt = 36;
    program[4].len = 12;
    progsz = 5;
    init_node(&chheader, chndsp, CHSPSZ);
    chsp[chheader] = 0;
    init_node(&lyheader, lyndsp, LYSPSZ);
    lysp[lyheader].x = 0;
    lysp[lyheader].y = 0;
    lysp[lyheader].str = NULL;
    lysp[lyheader].color = 0;
    init_node(&lyfnheader, lyfnndsp, LYSPSZ);
    lyfnsp[lyfnheader].fun = NULL;
    lyfnsp[lyfnheader].n = 0;
    //new_layfun(clock_hotwheel, 3, lyfnheader);
    //new_layfun(clock_time, 4, lyfnheader);
    _set_int(0x800, _clock, 8);
    return;
}
int main()
{
    init();
    /*char buf[CHSPSZ];
    do
    {
        new_page();
        read();
        dump_node(buf);
        if (execute(buf) == 0)
        {
            cursor_x = 0;
            cursor_y++;
            _move(cursor_x, cursor_y);
            print("Not a commad!");
            //put('\a');
            _get();
        }
    } while (cmp(buf, "EXIT") == 0);
    _cls();
    return 0;*/
    new_layfun(clock_ouch, 4, lyfnheader);
    for(int i = 0; i < 100; i++)
    {
        clock();
    }
    return 0;
}