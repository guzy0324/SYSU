__asm__(".code16gcc\n");
#define NULL ((void *)0)
#define null 0
#define CHSPSZ 256
#define LEFT 0x4b
#define RIGHT 0x4d
#define UP 0x48
#define DOWN 0x50
struct ahch
{
    char ch;
    unsigned char ah;
};
unsigned short _get();
__asm__(
    "_get:\n"
    "    mov  $0x1, %ah\n"
    "    int  $0x16\n"
    "    jz   _get\n"
    "    mov  $0x0, %ah\n"
    "    int  $0x16\n"
    "    ret\n");
void _cls();
__asm__(
    "_cls:\n"
    "    mov  $0x3, %ax\n"
    "    int  $0x10\n"
    "    ret\n");
void _display(char ch, int x, int y, int color);
__asm__(
    "_display:\n"
    "    mov  12(%esp), %eax\n"
    "    mov  $0x50, %ecx\n"
    "    mul  %ecx\n"
    "    add  8(%esp), %eax\n"
    "    mov  $0x2, %ecx\n"
    "    mul  %ecx\n"
    "    mov  %eax, %ecx\n"
    "    mov  $0xb800, %ax\n"
    "    mov  %ax, %gs\n"
    "    mov  16(%esp), %ah\n"
    "    mov  4(%esp), %al\n"
    "    mov  %ax, %gs:(%ecx)\n"
    "    ret\n");
void _move(int x, int y);
__asm__(
    "_move:\n"
    "    mov  4(%esp), %dl\n"
    "    mov  8(%esp), %dh\n"
    "    mov  %bh, %ch\n"
    "    mov  $0x0, %bh\n"
    "    mov  $0x2, %ah\n"
    "    int  $0x10\n"
    "    mov  %ch, %bh\n"
    "    ret\n");
unsigned _get_cs();
__asm__(
    "_get_cs:\n"
    "    mov  $0, %eax\n"
    "    mov  %cs, %ax\n"
    "    ret\n");
int chheader, cursor, cursor_x, cursor_y;
int top;
char stk[32];
void int2str(int n, char *str, int base)
{
    int i = 0;
    if (n == 0)
    {
        str[i++] = '0';
        goto int2str_ret;
    }
    else if (n < 0)
    {
        str[i++] = '-';
        n = -n;
    }
    top = 0;
    while (n != 0)
    {
        stk[top] = n % base;
        if (stk[top] >= 10)
        {
            stk[top] += 'a' - 10;
        }
        else
        {
            stk[top] += '0';
        }
        n /= base;
        top++;
    }
    while (top != 0)
    {
        str[i++] = stk[--top];
    }
int2str_ret:
    str[i] = 0;
}
void float2str(float fn, char *s)
{
    int i = 0;
    if (fn < 0)
    {
        fn = -fn;
        s[i++] = '-';
    }
    top = 0;
    int n = (int)fn;
    if (n == 0)
    {
        s[i++] = '0';
    }
    while (n != 0)
    {
        stk[top++] = n % 10 + '0';
        n /= 10;
    }
    while (top != 0)
    {
        s[i++] = stk[--top];
    }
    float t = fn - (float)(int)fn;
    s[i++] = '.';
    int j = i + 4;
    while (i < j)
    {
        t *= 10;
        s[i++] = (int)t + '0';
        t = t - (int)t;
    }
    s[i] = 0;
}
void strcpy(char *dest, char *src)
{
    int i = 0;
    while (src[i] != 0)
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = 0;
}
float str2num(char *s, int *i_ptr)
{
    if (s[*i_ptr] >= '0' && s[*i_ptr] <= '9')
    {
        float num = s[*i_ptr] - '0';
        int exponent = 0;
        while (s[*i_ptr + 1] >= '0' && s[*i_ptr + 1] <= '9')
        {
            num = num * 10 + s[++*i_ptr] - '0';
        }
        if (s[*i_ptr + 1] == '.')
        {
            (*i_ptr)++;
            while (s[*i_ptr + 1] >= '0' && s[*i_ptr + 1] <= '9')
            {
                num = num * 10 + s[++*i_ptr] - '0';
                exponent++;
            }
        }
        while (exponent > 0)
        {
            num /= 10;
            exponent--;
        }
        return num;
    }
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
void putch(char ch, int init_x, int init_y, int color)
{
    if (ch == '\n')
    {
        cursor_x = init_x;
        cursor_y++;
    }
    else if (ch == '\t')
    {
        if (cursor_x >= 76)
        {
            cursor_x = init_x + cursor_x - 76;
            cursor_y++;
        }
    }
    else
    {
        _display(ch, cursor_x, cursor_y, color);
        if (cursor_x == 79)
        {
            cursor_x = init_x;
            if (cursor_y == 24)
            {
                cursor_y = init_y;
            }
            else
            {
                cursor_y++;
            }
        }
        else
        {
            cursor_x++;
        }
    }
}
void puts(char *str, int init_x, int init_y, int color)
{
    for (int i = 0; str[i] != 0; i++)
    {
        putch(str[i], init_x, init_y, color);
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
    new_node(null, header_ptr, ndsp);
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
void dump_node(char buf[])
{
    int i = 0;
    while (chsp[chheader] != 0)
    {
        buf[i++] = chsp[chheader];
        delete_node(chheader, &chheader, chndsp);
    }
    buf[i] = 0;
}
void read(char *buf, int x, int y, int color)
{
    cursor = chheader;
    cursor_x = x;
    cursor_y = y;
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
            }
            else if (ax.ah == RIGHT)
            {
                if (chndsp[cursor].next != null)
                {
                    cursor = chndsp[cursor].next;
                    cursor_x += 1;
                    _move(cursor_x, cursor_y);
                }
            }
            else if (ax.ah == UP)
            {
                cursor = chheader;
                cursor_x = x;
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
                    _display(chsp[temp], temp_x, cursor_y, color);
                    temp_x++;
                    _move(temp_x, cursor_y);
                }
				_move(cursor_x, cursor_y);
            }
        }
        else
        {
            int temp = new_ch(ax.ch, cursor);
            if (temp != null)
            {
                int temp_x = cursor_x;
                for (; chsp[temp] != 0; temp = chndsp[temp].next)
                {
                    _display(chsp[temp], temp_x, cursor_y, color);
                    temp_x++;
					_move(temp_x, cursor_y);
                }
                cursor_x++;
				_move(cursor_x, cursor_y);
            }
        }
        temp_ax = _get();
        ax = *(struct ahch *)&temp_ax;
    }
    dump_node(buf);
}
void init()
{
    init_node(&chheader, chndsp, CHSPSZ);
    chsp[chheader] = 0;
}
char buf[CHSPSZ];
void printf(int x, int y, int color, const char *fmt, ...)
{
    int offset = 1;
    cursor_x = x;
    cursor_y = y;
    for (int i = 0; fmt[i] != 0; i++)
    {
        if (fmt[i] == '%')
        {
            i++;
            switch (fmt[i])
            {
            case 0:
                return;
            case '%':
                putch('%', x, y, color);
                break;
            case 'c':
                putch(*(char *)(&fmt + offset), x, y, color);
                offset++;
                break;
            case 's':
                puts(*(char **)(&fmt + offset), x, y, color);
                offset++;
                break;
            case 'b':
                int2str(*(int *)(&fmt + offset), buf, 2);
                puts(buf, x, y, color);
                offset++;
                break;
            case 'o':
                int2str(*(int *)(&fmt + offset), buf, 8);
                puts(buf, x, y, color);
                offset++;
                break;
            case 'd':
                int2str(*(int *)(&fmt + offset), buf, 10);
                puts(buf, x, y, color);
                offset++;
                break;
            case 'x':
                int2str(*(int *)(&fmt + offset), buf, 16);
                puts(buf, x, y, color);
                offset++;
                break;
            case 'f':
                float2str(**(float **)(&fmt + offset), buf);
                puts(buf, x, y, color);
                offset++;
                break;
            }
        }
        else
        {
            putch(fmt[i], x, y, color);
        }
    }
}
void scanf(int x, int y, int color, const char *fmt, ...)
{
    int offset = 1;
    read(buf, x, y, color);
    for (int i = 0, j = 0; fmt[i] != 0 && j < CHSPSZ && buf[j] != 0; i++, j++)
    {
        if (fmt[i] == '%')
        {
            i++;
            switch (fmt[i])
            {
            case 0:
                return;
            case '%':
                if (buf[j] != '%')
                {
                    return;
                }
                break;
            case 'c':
                **(char **)(&fmt + offset) = buf[j];
                offset++;
                break;
            case 's':
                strcpy(*(char **)(&fmt + offset), buf + j);
                return;
                break;
            case 'd':
                **(int **)(&fmt + offset) = str2num(buf, &j);
                offset++;
                break;
            case 'f':
                **(float **)(&fmt + offset) = str2num(buf, &j);
                offset++;
                break;
            default:
                return;
            }
        }
        else
        {
            if (fmt[i] != buf[j])
            {
                return;
            }
        }
    }
}
struct layer
{
    unsigned ds;
    char *str;
    int x;
    int y;
    int color;
};
struct layinfo
{
    int n;
    int is_lay;
    struct layer lay;
};
struct layfun
{
    unsigned cs;
    int (*fun)(int n);
    int n;
};
int _new_layfun(unsigned cs, int (*fun)(int n), int n);
__asm__(
    "_new_layfun:\n"
    "    mov  4(%esp), %eax\n"
    "    mov  %ax, %es\n"
    "    mov  %ebx, %edx\n"
    "    mov  8(%esp), %ebx\n"
    "    mov  12(%esp), %ecx\n"
    "    mov  $0x63, %ah\n"
    "    int  $0x21\n"
    "    mov  %edx, %ebx\n"
    "    ret\n");
int _fork();
__asm__(
    "_fork:\n"
    "    mov  %ebx, %edx\n"
    "    mov  $0x64, %ah\n"
    "    int  $0x21\n"
    "    mov  %edx, %ebx\n"
    "    ret\n");
void _exit();
__asm__(
    "_exit:\n"
    "    mov  %ebx, %edx\n"
    "    mov  $0x65, %ah\n"
    "    int  $0x21\n"
    "    mov  %edx, %ebx\n"
    "    ret\n");
void _block();
__asm__(
    "_block:\n"
    "    mov  %ebx, %edx\n"
    "    mov  $0x66, %ah\n"
    "    int  $0x21\n"
    "    mov  %edx, %ebx\n"
    "    ret\n");
void _wakeup(int pid);
__asm__(
    "_wakeup:\n"
    "    mov  %ebx, %edx\n"
    "    mov  4(%esp), %ebx\n"
    "    mov  $0x67, %ah\n"
    "    int  $0x21\n"
    "    mov  %edx, %ebx\n"
    "    ret\n");