__asm__(".code16gcc\n");
#define NULL ((void *)0)
#define null 0
#define NDSPSZ 256
#define LEFT 0x4b
#define RIGHT 0x4d
#define UP 0x48
#define DOWN 0x50
#define DEFAULT_X 0
#define DEFUALT_Y 0
#define CMDSZ 8
#define PROGSZ 8
struct ahch
{
    char ch;
    unsigned char ah;
};
extern void _put(char ch);
extern void _move(int x, int y);
extern unsigned short _get();
extern void _cls();
extern void _callf(int cl, int ch, int dh, int len);
int header, cursor, cursor_x, cursor_y;
void int2str(int n, char *s)
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
        s[n++] = stk[--top];
    }
    s[n] = 0;
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
        _put(str[i]);
        cursor_x += 1;
        _move(cursor_x, cursor_y);
    }
}
struct node
{
    char ch;
    int next;
    int last;
};
struct node ndsp[NDSPSZ];
int new_node(char c, int cursor)
{
    int neo = ndsp[null].next;
    if (neo == null)
    {
        return null;
    }
    ndsp[null].next = ndsp[neo].next;
    ndsp[neo].ch = c;
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
    if (header == cursor)
    {
        header = neo;
    }
    return neo;
}
void delete_node(int nd)
{
    if (header == nd)
    {
        header = ndsp[nd].next;
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
void dump_node(char buf[])
{
    int i = 0;
    while (ndsp[header].ch != 0)
    {
        if (ndsp[header].ch >= 'a' && ndsp[header].ch <= 'z')
        {
            ndsp[header].ch += 'A' - 'a';
        }
        else if (ndsp[header].ch == '\t')
        {
            ndsp[header].ch = ' ';
        }
        buf[i] = ndsp[header].ch;
        delete_node(header);
        if (buf[i] == ' ')
        {
            while (header != null && (ndsp[header].ch == ' ' || ndsp[header].ch == '\t'))
            {
                delete_node(header);
            }
        }
        i++;
    }
    buf[i] = 0;
}
void read()
{
    cursor = header;
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
                if (ndsp[cursor].last != null)
                {
                    cursor = ndsp[cursor].last;
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
                if (ndsp[cursor].next != null)
                {
                    cursor = ndsp[cursor].next;
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
                cursor = header;
                cursor_x = DEFAULT_X;
                _move(cursor_x, cursor_y);
            }
            else if (ax.ah == DOWN)
            {
                for (; ndsp[cursor].ch != 0; cursor = ndsp[cursor].next)
                {
                    cursor_x++;
                }
                _move(cursor_x, cursor_y);
            }
        }
        else if (ax.ch == '\b')
        {
            if (ndsp[cursor].last != null)
            {
                delete_node(ndsp[cursor].last);
                cursor_x--;
                int temp_x = cursor_x;
                _move(cursor_x, cursor_y);
                for (int temp = cursor; temp != null; temp = ndsp[temp].next)
                {
                    _put(ndsp[temp].ch);
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
            int temp = new_node(ax.ch, cursor);
            if (temp != null)
            {
                int temp_x = cursor_x;
                for (; ndsp[temp].ch != 0; temp = ndsp[temp].next)
                {
                    _put(ndsp[temp].ch);
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
int init(int *header_ptr)
{
    _cls();
    int i = 0;
    for (; i < NDSPSZ - 1; i++)
    {
        ndsp[i].next = i + 1;
    }
    ndsp[i].next = null;
    *header_ptr = new_node(0, null);
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
    return *header_ptr;
}
int main()
{
    if (init(&header) == null)
    {
        print("Space used up!");
        //put('\a');
        _get();
        return -1;
    }
    char buf[NDSPSZ];
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
    return 0;
}