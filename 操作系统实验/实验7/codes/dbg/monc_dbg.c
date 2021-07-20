#define NULL ((void *)0)
#define null 0
#define PROGSZ 8
#define PCBSPSZ 10
#define READY 0
#define RUNNING 1
#define BLOCKED 2
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
void _stack_cpy(unsigned ss1, unsigned sp1, unsigned ss2, unsigned sp2, unsigned top)
{

}
void _load(int cl, int ch, int dh, int len, int es)
{

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
        //_cls();
    }
}
void ffork()
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
    _stack_cpy(pcbsp[cur_pcb].pregs.ss, pcbsp[cur_pcb].pregs.sp, pcbsp[pid].pregs.ss, pcbsp[pid].pregs.sp, 0xffff);
    regs.ax = pid;
}
void eexit()
{
    if (pcbsp[pcbsp[cur_pcb].fpid].pstate == BLOCKED)
    {
        wakeup(pcbsp[cur_pcb].fpid);
    }
    sync_ret();
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
void init()
{
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
    init_node(&pcbheader, pcbndsp, PCBSPSZ);
    pcbsp[pcbheader].pid = 0;
    blockheader = null;
}
int main()
{
    init();
    cmd_sync("COUNT.COM");
    schedule();
    ffork();
    block();
    eexit();
    schedule();
    return 0;
}