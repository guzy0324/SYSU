__asm__(".code16gcc\n");
#define NULL ((void *)0)
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
#define PCBSPSZ 10
#define READY 0
#define RUNNING 1
#define BLOCKED 2
struct ahch
{
    char ch;
    unsigned char ah;
};
struct reg
{
    unsigned int ax;
    unsigned int bx;
    unsigned int cx;
    unsigned int dx;
    unsigned int sp;
    unsigned int bp;
    unsigned int si;
    unsigned int di;
    unsigned int ip;
    unsigned int flags;
    unsigned int es;
    unsigned int cs;
    unsigned int ss;
    unsigned int ds;
    unsigned int fs;
    unsigned int gs;
};
void reg_cpy(struct reg* reg1, struct reg* reg2)
{
    unsigned int *p1 = (unsigned int *)reg1;
    unsigned int *p2 = (unsigned int *)reg2;
    for (int i = 0; i < 16; i++)
    {
        p1[i] = p2[i];
    }
}
void reg_swap(struct reg* reg1, struct reg* reg2)
{
    unsigned int *p1 = (unsigned int *)reg1;
    unsigned int *p2 = (unsigned int *)reg2;
    for (int i = 0; i < 16; i++)
    {
        p1[i] += p2[i];
        p2[i] = p1[i] - p2[i];
        p1[i] -= p2[i];
    }
}
struct reg regs;
extern void _put(char ch);
extern void _move(int x, int y);
extern unsigned short _get();
extern void _cls();
extern unsigned char _memb(unsigned ds, unsigned char *ptr);
extern void _stack_cpy(unsigned ss1, unsigned sp1, unsigned ss2, unsigned sp2, unsigned top);
extern unsigned _call(unsigned cs, unsigned (*fun)(unsigned arg), unsigned arg);
extern void _load(int cl, int ch, int dh, int len, int es);
extern void _callf();
extern void _display(char ch, int x, int y, int color);
extern void _get_time();
extern unsigned char _time[6];
extern void _cmd_sync(char *para);
extern int _clock_hotwheel(int n);
extern int _clock_time(int n);
extern int _clock_ouch(int n);
extern void _set_int(int cs, void (*inter)(), int index);
extern void _clock();
extern void _int_20h();
extern void _int_21h();
extern void _int_22h();
int chheader, cursor, cursor_x, cursor_y;
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
void display_str(unsigned ds, char *str, int x, int y, int color)
{
    int offset_x = 0, offset_y = 0;
    int i = 0;
    char ch = _memb(ds, (unsigned char *)str);
    while (ch != 0)
    {
        if (ch == '\n')
        {
            offset_x = 0;
            offset_y++;
        }
        else
        {
            _display(ch, x + offset_x, y + offset_y, color);
            offset_x++;
        }
        i++;
        ch = _memb(ds, (unsigned char *)str + i);
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
                    _load(cl, ch, dh, program[i].len, 0x1000);
                    _callf();
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
                    _load(cl, ch, dh, program[i].len, 0x1000);
                    _callf();
                    break;
                }
            }
            break;
        }
    }
}
struct PCB
{
    struct reg pregs;
    int pid;
    char pname[10];
    char pstate;
    int fpid;
};
struct PCB pcbsp[PCBSPSZ];
struct node pcbndsp[PCBSPSZ];
int pcbheader, cur_pcb = 1;
int new_pcb(char *pname, int cursor)
{
    int neo_pcb = new_node(cursor, &pcbheader, pcbndsp);
    if (neo_pcb != null)
    {
        int cs = 0x1000 * (neo_pcb - 1);
        pcbsp[neo_pcb].pregs.ax = 0;
        pcbsp[neo_pcb].pregs.bx = 0;
        pcbsp[neo_pcb].pregs.cx = 0;
        pcbsp[neo_pcb].pregs.dx = 0;
        pcbsp[neo_pcb].pregs.sp = 0xfffb;
        pcbsp[neo_pcb].pregs.bp = 0;
        pcbsp[neo_pcb].pregs.si = 0;
        pcbsp[neo_pcb].pregs.di = 0;
        pcbsp[neo_pcb].pregs.ip = 100;
        pcbsp[neo_pcb].pregs.flags = 512;
        pcbsp[neo_pcb].pregs.es = 0;
        pcbsp[neo_pcb].pregs.cs = cs;
        pcbsp[neo_pcb].pregs.ss = cs;
        pcbsp[neo_pcb].pregs.ds = cs;
        pcbsp[neo_pcb].pregs.fs = 0;
        pcbsp[neo_pcb].pregs.gs = 0;
        pcbsp[neo_pcb].pid = neo_pcb;
        for (int i = 0; i < 10 && pname[i] != 0; i++)
        {
            pcbsp[neo_pcb].pname[i] = pname[i];
        }
        pcbsp[neo_pcb].pstate = READY;
        pcbsp[neo_pcb].fpid = cur_pcb;
    }
    return neo_pcb;
}
int blockheader;
void block()
{
    int cur_pcb_temp = cur_pcb;
    pcbsp[cur_pcb].pstate = BLOCKED;
    reg_swap(&pcbsp[cur_pcb].pregs, &regs);
    cur_pcb = pcbndsp[cur_pcb].next;
    if (pcbsp[cur_pcb].pid == 0)
    {
        cur_pcb = pcbheader;
    }
    reg_swap(&pcbsp[cur_pcb].pregs, &regs);
    pcbsp[cur_pcb].pstate = RUNNING;
    if (cur_pcb_temp == pcbheader)
    {
        pcbheader = pcbndsp[cur_pcb_temp].next;
    }
    else
    {
        pcbndsp[pcbndsp[cur_pcb_temp].last].next = pcbndsp[cur_pcb_temp].next;
    }
    pcbndsp[cur_pcb_temp].next = blockheader;
    pcbndsp[pcbndsp[cur_pcb_temp].next].last = pcbndsp[cur_pcb_temp].last;
    pcbndsp[cur_pcb_temp].last = null;
    if (blockheader != null)
    {
        pcbndsp[blockheader].last = cur_pcb_temp;
    }
    blockheader = cur_pcb_temp;
}
void wakeup(int pid)
{
    if (pid == blockheader)
    {
        blockheader = pcbndsp[pid].next;
    }
    else
    {
        pcbndsp[pcbndsp[pid].last].next = pcbndsp[pid].next;
    }
    pcbndsp[pid].next = pcbndsp[cur_pcb].next;
    pcbndsp[cur_pcb].next = pid;
    if (pcbndsp[pid].next != null)
    {
        pcbndsp[pcbndsp[pid].next].last = pid;
    }
    pcbndsp[pid].last = cur_pcb;
    pcbsp[pid].pstate = READY;
}
void sync_ret()
{
    pcbsp[cur_pcb].pstate = READY;
    reg_swap(&pcbsp[cur_pcb].pregs, &regs);
    cur_pcb = pcbndsp[cur_pcb].next;
    delete_node(pcbndsp[cur_pcb].last, &pcbheader, pcbndsp);
    if (pcbsp[cur_pcb].pid == 0)
    {
        cur_pcb = pcbheader;
    }
    if (pcbsp[cur_pcb].pid != 0)
    {
        reg_swap(&pcbsp[cur_pcb].pregs, &regs);
        pcbsp[cur_pcb].pstate = RUNNING;
    }
    else
    {
        _cls();
    }
}
void fork()
{
    int pid = new_pcb("Thread", cur_pcb);
    if (pid == null)
    {
        regs.ax = -1;
        return;
    }
    reg_cpy(&pcbsp[pid].pregs, &regs);
    pcbsp[pid].pregs.ax = 0;
    pcbsp[pid].pregs.ss = 0x1000 * (pid - 1);
    _stack_cpy(pcbsp[pid].pregs.ss, pcbsp[pid].pregs.sp, regs.ss, regs.sp, 0xffff);
    regs.ax = pid;
}
void exit()
{
    if (pcbsp[pcbsp[cur_pcb].fpid].pstate == BLOCKED)
    {
        wakeup(pcbsp[cur_pcb].fpid);
    }
    sync_ret();
}
void cmd_sync(char *para)
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
                    int pid = new_pcb(program[i].name, pcbheader);
                    _load(cl, ch, dh, program[i].len, 0x1000 * (pid - 1));
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
                    int pid = new_pcb(program[i].name, pcbheader);
                    _load(cl, ch, dh, program[i].len, 0x1000 * (pid - 1));
                    break;
                }
            }
            break;
        }
    }
    cur_pcb = null;
}
void schedule()
{
    if (cur_pcb == null)
    {
        cur_pcb = pcbheader;
        if (pcbsp[cur_pcb].pid != 0)
        {
            reg_swap(&pcbsp[cur_pcb].pregs, &regs);
            pcbsp[cur_pcb].pstate = RUNNING;
        }
    }
    else if (pcbsp[cur_pcb].pid != 0)
    {
        pcbsp[cur_pcb].pstate = READY;
        reg_swap(&pcbsp[cur_pcb].pregs, &regs);
        cur_pcb = pcbndsp[cur_pcb].next;
        if (pcbsp[cur_pcb].pid == 0)
        {
            cur_pcb = pcbheader;
        }
        reg_swap(&pcbsp[cur_pcb].pregs, &regs);
        pcbsp[cur_pcb].pstate = RUNNING;
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
        ptr++;
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
    unsigned ds;
    char *str;
    int x;
    int y;
    int color;
};
struct layer lysp[LYSPSZ];
struct node lyndsp[LYSPSZ];
int lyheader;
int new_layer(unsigned ds, char *str, int x, int y, int color, int cursor)
{
    int neo_layer = new_node(cursor, &lyheader, lyndsp);
    if (neo_layer != null)
    {
        lysp[neo_layer].ds = ds;
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
struct layfun lyfnsp[LYSPSZ];
struct node lyfnndsp[LYSPSZ];
int lyfnheader;
int new_layfun(unsigned cs, int (*fun)(int n), int n, int cursor)
{
    int neo_layfun = new_node(cursor, &lyfnheader, lyfnndsp);
    if (neo_layfun != null)
    {
        lyfnsp[neo_layfun].cs = cs;
        lyfnsp[neo_layfun].fun = fun;
        lyfnsp[neo_layfun].n = n;
    }
    return neo_layfun;
}
/*void delete_layfun(int nd)
{
    delete_node(nd, &lyfnheader, lyfnndsp);
}*/
struct layinfo hotwheel_info;
char hotwheel_arr[] = "/|\\";
char hotwheel_str[] = {0, 0};
unsigned clock_hotwheel(int n)
{
    hotwheel_str[0] = hotwheel_arr[n % 3];
    hotwheel_info.is_lay = 1;
    hotwheel_info.lay.ds = 0x800;
    hotwheel_info.lay.str = hotwheel_str;
    hotwheel_info.lay.x = 60;
    hotwheel_info.lay.y = 24;
    hotwheel_info.lay.color = 0b00111111;
    n -= 1;
    if (n % 3 == 0)
    {
        n = 3;
    }
    hotwheel_info.n = n;
    return (0x800 << 16) + (unsigned)&hotwheel_info;
}
/*void hotwheel()
{
    new_layfun(clock_hotwheel, 3, lyfnheader);
}*/
struct layinfo time_info;
char time_str[20] = "20yy/mm/dd hh:mm:ss";
unsigned clock_time(int n)
{
    time_info.is_lay = 0;
    if (n % 2 == 0)
    {
        _get_time();
        char *ptr = time_str + 2;
        for (int i = 0; i < 6; i++)
        {
            BCD2str(_time[i], ptr);
            ptr += 3;
        }
        time_info.is_lay = 1;
        time_info.lay.ds = 0x800;
        time_info.lay.str = time_str;
        time_info.lay.x = 61;
        time_info.lay.y = 24;
        time_info.lay.color = 0b00111101;
    }
    n -= 1;
    if (n % 2 == 0)
    {
        n = 2;
    }
    time_info.n = n;
    return (0x800 << 16) + (unsigned)&time_info;
}
/*void time()
{
    new_layfun(clock_time, 4, lyfnheader);
}*/
struct layinfo ouch_info;
char ouch_str[] = "OUCH!OUCH!";
int ouch_color;
int clock_ouch(int n)
{
    ouch_info.is_lay = 1;
    ouch_info.lay.ds = 0x800;
    ouch_info.lay.str = ouch_str;
    ouch_info.lay.x = 35;
    ouch_info.lay.y = 12;
    ouch_info.lay.color = ouch_color;
    new_layer(0x800, ouch_str, 35, 12, ouch_color, lyheader);
    n -= 1;
    if (n == 1)
    {
        ouch_color = 0;
    }
    else
    {
        ouch_color = ~ouch_color;
    }
    return (0x800 << 16) + (unsigned)&ouch_info;
}
/*void ouch()
{
    ouch_color = 0b11100100;
    new_layfun(clock_ouch, 4, lyfnheader);
}*/
struct layinfo layer_info;
void clock()
{
    for (int ptr = lyfnheader; lyfnsp[ptr].cs != 0 || lyfnsp[ptr].fun != NULL; ptr = lyfnndsp[ptr].next)
    {
        unsigned info_ptr = _call(lyfnsp[ptr].cs, (unsigned (*)(unsigned))lyfnsp[ptr].fun, lyfnsp[ptr].n);
        unsigned ds = info_ptr >> 16;
        unsigned char *addr = (unsigned char *)(info_ptr - (ds << 16));
        for (int i = 0; i < sizeof(struct layinfo); i++)
        {
            *((unsigned char *)&layer_info + i) = _memb(ds, addr + i);
        }
        lyfnsp[ptr].n = layer_info.n;
        if (layer_info.is_lay != 0)
        {
            new_layer(layer_info.lay.ds, layer_info.lay.str, layer_info.lay.x, layer_info.lay.y, layer_info.lay.color, lyheader);
        }
        if (lyfnsp[ptr].n == 0)
        {
            delete_node(ptr, &lyfnheader, lyfnndsp);
        }
    }
    while (lysp[lyheader].str != NULL)
    {
        display_str(lysp[lyheader].ds, lysp[lyheader].str, lysp[lyheader].x, lysp[lyheader].y, lysp[lyheader].color);
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
    command[2].name = "SYNC";
    command[2].fun = _cmd_sync;
    cmdsz = 3;
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
    program[5].name = "COUNT.COM";
    program[5].stt = 48;
    program[5].len = 13;
    progsz = 6;
    init_node(&chheader, chndsp, CHSPSZ);
    chsp[chheader] = 0;
    init_node(&lyheader, lyndsp, LYSPSZ);
    lysp[lyheader].x = 0;
    lysp[lyheader].y = 0;
    lysp[lyheader].str = NULL;
    lysp[lyheader].color = 0;
    init_node(&lyfnheader, lyfnndsp, LYSPSZ);
    lyfnsp[lyfnheader].cs = 0;
    lyfnsp[lyfnheader].fun = NULL;
    lyfnsp[lyfnheader].n = 0;
    new_layfun(0x800, _clock_hotwheel, 3, lyfnheader);
    new_layfun(0x800, _clock_time, 4, lyfnheader);
    init_node(&pcbheader, pcbndsp, PCBSPSZ);
    pcbsp[pcbheader].pid = 0;
    blockheader = null;
    _set_int(0x800, _clock, 8);
    _set_int(0x800, _int_20h, 0x20);
    _set_int(0x800, _int_21h, 0x21);
    _set_int(0x800, _int_22h, 0x22);
}
int main()
{
    init();
    char buf[CHSPSZ];
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