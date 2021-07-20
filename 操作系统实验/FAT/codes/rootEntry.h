#include "fatItem.h"
#include "string.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#define SIZE 224
#define Null 0
#define ROOT 1
#define TYPE_DIR 0x10
#define TYPE_NORMAL_FILE 0x20
struct RootEntry
{
    char DIR_Name[11];
    unsigned char DIR_Attr;
    unsigned char parent;
    unsigned char last_sibling;
    unsigned char next_sibling;
    unsigned char last_child;
    unsigned char reserve[6];
    unsigned char DIR_WrtTime[2];
    unsigned char DIR_WrtDate[2];
    unsigned char DIR_FstClus[2];
    unsigned char DIR_FileSize[4];
};
void store_name(char stored_name[], const char name[])
{
    int i, j;
    for (i = 0, j = 0; j < 8; j++)
    {
        if (name[i] && name[i] != '.')
        {
            stored_name[j] = name[i];
            i++;
        }
        else
        {
            stored_name[j] = ' ';
        }
    }
    for (; name[i]; i++)
    {
        if (name[i] == '.')
        {
            i++;
            break;
        }
    }
    for (j = 8; j < 11; j++)
    {
        if (name[i])
        {
            stored_name[j] = name[i];
            i++;
        }
        else
        {
            stored_name[j] = ' ';
        }
    }
}
void print_name(char name[])
{
    int i;
    for (i = 0; i < 8 && name[i] != ' '; i++)
    {
        putchar(name[i]);
    }
    if (name[8] != ' ')
    {
        putchar('.');
    }
    for (i = 8; i < 11 && name[i] != ' '; i++)
    {
        putchar(name[i]);
    }
}
void print_stored_name(char name[])
{
    for (int i = 0; i < 11; i++)
    {
        putchar(name[i]);
    }
}
void store_date_time(unsigned short *date_ptr, unsigned short *time_ptr)
{
    time_t timep;
    time(&timep);
    struct tm *p = localtime(&timep);
    *date_ptr = ((((p->tm_year - 80) << 4) + p->tm_mon) << 5) + p->tm_mday;
    *time_ptr = ((p->tm_hour << 6) + p->tm_min) << 5;
}
void convert_date(int *year, int *month, int *day, unsigned short date)
{
    *day = date % 32;
    date >>= 5;
    *month = date % 16;
    date >>= 4;
    *year = (date + 1980) % 100;
}
void convert_time(int *hour, int *minute, unsigned short time)
{
    time >>= 5;
    *minute = time % 64;
    time >>= 6;
    *hour = time;
}
void init(struct RootEntry space[])
{
    memset(space, 0, SIZE * sizeof(struct RootEntry));
    space[Null].last_child = 2;
    for (int i = 2; i < SIZE; i++)
    {
        space[i].last_child = i + 1;
    }
    store_date_time((unsigned short *)space[ROOT].DIR_WrtDate, (unsigned short *)space[ROOT].DIR_WrtTime);
    store_name(space[ROOT].DIR_Name, "ROOT");
    space[ROOT].DIR_Attr = TYPE_DIR;
}
void assign(unsigned char node, const char name[], unsigned char DIR_Attr, unsigned char parent,
            unsigned char fat1[], unsigned char fat2[], struct RootEntry space[], unsigned short *item_top_p)
{
    store_date_time((unsigned short *)space[node].DIR_WrtDate, (unsigned short *)space[node].DIR_WrtTime);
    store_name(space[node].DIR_Name, name);
    space[node].DIR_Attr = DIR_Attr;
    space[node].parent = parent;
    space[node].last_sibling = space[parent].last_child;
    space[node].next_sibling = Null;
    space[node].last_child = Null;
    space[parent].last_child = node;
    if (space[node].last_sibling != Null)
    {
        space[space[node].last_sibling].next_sibling = node;
    }
    if (DIR_Attr == TYPE_DIR)
    {
        if (*(unsigned short *)space[node].DIR_FstClus)
        {
            modify_next_item(*(unsigned short *)space[node].DIR_FstClus, 0xFFF, fat1, fat2);
            *(unsigned short *)space[node].DIR_FstClus = 0;
        }
    }
    else if (DIR_Attr == TYPE_NORMAL_FILE)
    {
        if (*(unsigned short *)space[node].DIR_FstClus)
        {
            modify_next_item(*(unsigned short *)space[node].DIR_FstClus, 0xFFF, fat1, fat2);
        }
        else
        {
            *(unsigned short *)space[node].DIR_FstClus = item_alloc(fat1, fat2, item_top_p);
        }
    }
    *(unsigned int *)space[node].DIR_FileSize = 0;
}
unsigned char memory_alloc(struct RootEntry space[])
{
    unsigned char node = space[Null].last_child;
    space[Null].last_child = space[space[Null].last_child].last_child;
    return node;
}
int memory_delete(unsigned char node, struct RootEntry space[])
{
    if (space[node].last_child != Null)
    {
        return 0;
    }
    space[node].last_child = space[Null].last_child;
    space[Null].last_child = node;
    if (space[space[node].parent].last_child == node)
    {
        space[space[node].parent].last_child = space[node].last_sibling;
    }
    if (space[node].last_sibling != Null)
    {
        space[space[node].last_sibling].next_sibling = space[node].next_sibling;
    }
    if (space[node].next_sibling != Null)
    {
        space[space[node].next_sibling].last_sibling = space[node].last_sibling;
    }
    return 1;
}
int height(unsigned char cur, struct RootEntry space[])
{
    int h = 0, temp;
    for (unsigned char iter = space[cur].last_child; iter != Null; iter = space[iter].last_sibling)
    {
        temp = height(iter, space);
        h = h > temp ? h : temp;
    }
    if (cur != ROOT)
    {
        h += 1;
    }
    return h;
}
int count_file(unsigned char cur, struct RootEntry space[])
{
    int num = 0;
    for (unsigned char iter = space[cur].last_child; iter != Null; iter = space[iter].last_sibling)
    {
        num += count_file(iter, space);
    }
    if (space[cur].DIR_Attr != TYPE_DIR)
    {
        num += 1;
    }
    return num;
}
void list_dir(unsigned char cur, struct RootEntry space[])
{
    int year, month, day, hour, minute;
    if (cur != ROOT)
    {
        convert_date(&year, &month, &day, *(unsigned short *)space[cur].DIR_WrtDate);
        convert_time(&hour, &minute, *(unsigned short *)space[cur].DIR_WrtTime);
        printf(".           <DIR>\t\t%02d-%02d-%02d   %02d:%02d\n", month, day, year, hour, minute);
        convert_date(&year, &month, &day, *(unsigned short *)space[space[cur].parent].DIR_WrtDate);
        convert_time(&hour, &minute, *(unsigned short *)space[space[cur].parent].DIR_WrtTime);
        printf("..          <DIR>\t\t%02d-%02d-%02d   %02d:%02d\n", month, day, year, hour, minute);
    }
    unsigned char p = space[cur].last_child;
    while (space[p].last_sibling != Null)
    {
        p = space[p].last_sibling;
    }
    for (; p != Null; p = space[p].next_sibling)
    {
        if (space[p].DIR_Attr == TYPE_DIR)
        {
            convert_date(&year, &month, &day, *(unsigned short *)space[p].DIR_WrtDate);
            convert_time(&hour, &minute, *(unsigned short *)space[p].DIR_WrtTime);
            print_stored_name(space[p].DIR_Name);
            printf(" <DIR>\t\t%02d-%02d-%02d   %02d:%02d\n", month, day, year, hour, minute);
        }
        else
        {
            convert_date(&year, &month, &day, *(unsigned short *)space[p].DIR_WrtDate);
            convert_time(&hour, &minute, *(unsigned short *)space[p].DIR_WrtTime);
            print_stored_name(space[p].DIR_Name);
            printf("      \t%d\t%02d-%02d-%02d   %02d:%02d\n", *(unsigned int *)space[p].DIR_FileSize, month, day, year, hour, minute);
        }
    }
}
int height_stack[100];
int height_top = 0;
void dfs(unsigned char cur, struct RootEntry space[], int height)
{
    int i, j;
    for (i = 0, j = 0; i < height_top; i++)
    {
        for (; j < height_stack[i] - 1; j++)
        {
            printf("    ");
        }
        printf("|   ");
        j++;
    }
    for (; j < height - 1; j++)
    {
        printf("    ");
    }
    if (height)
    {
        puts("|");
    }
    for (i = 0, j = 0; i < height_top; i++)
    {
        for (; j < height_stack[i] - 1; j++)
        {
            printf("    ");
        }
        printf("|   ");
        j++;
    }
    for (; j < height - 1; j++)
    {
        printf("    ");
    }
    if (height)
    {
        printf("+---");
    }
    print_name(space[cur].DIR_Name);
    putchar('\n');
    if (space[cur].last_child != Null)
    {
        if (height && space[cur].last_sibling != Null)
        {
            height_stack[height_top++] = height;
        }
        dfs(space[cur].last_child, space, height + 1);
        if (height && space[cur].last_sibling != Null)
        {
            height_top--;
        }
    }
    if (height)
    {
        if (space[cur].last_sibling != Null)
        {
            dfs(space[cur].last_sibling, space, height);
        }
    }
}
void delete_tree(unsigned char cur, struct RootEntry space[])
{
    for (unsigned char iter = space[cur].last_child; iter != Null; iter = space[iter].last_sibling)
    {
        delete_tree(iter, space);
    }
    if (space[space[cur].parent].last_child == cur)
    {
        space[space[cur].parent].last_child = space[cur].last_sibling;
    }
    if (space[cur].last_sibling != Null)
    {
        space[space[cur].last_sibling].next_sibling = space[cur].next_sibling;
    }
    if (space[cur].next_sibling != Null)
    {
        space[space[cur].next_sibling].last_sibling = space[cur].last_sibling;
    }
    memory_delete(cur, space);
}
int name_cmp(char *name1, char *name2)
{
    int i;
    for (i = 0; i < 11; i++)
    {
        if (name1[i] < name2[i])
        {
            return -1;
        }
        if (name1[i] > name2[i])
        {
            return 1;
        }
    }
    return 0;
}
void quick_sort(unsigned char a[], unsigned char left, unsigned char right, struct RootEntry space[])
{
    unsigned char pivot = a[left], p1 = left, p2 = right;
    while (p1 < p2)
    {
        while (p1 < p2 && name_cmp(space[a[p2]].DIR_Name, space[pivot].DIR_Name) >= 0)
        {
            p2--;
        }
        if (p1 < p2)
        {
            a[p1] = a[p2];
        }
        while (p1 < p2 && name_cmp(space[a[p1]].DIR_Name, space[pivot].DIR_Name) < 0)
        {
            p1++;
        }
        if (p1 < p2)
        {
            a[p2] = a[p1];
        }
    }
    a[p1] = pivot;
    if (left < p1 - 1)
    {
        quick_sort(a, left, p1 - 1, space);
    }
    if (p1 + 1 < right)
    {
        quick_sort(a, p1 + 1, right, space);
    }
}
int isomorphy(unsigned char cur1, unsigned char cur2, struct RootEntry space1[], struct RootEntry space2[])
{
    unsigned char p, cnt1, cnt2, a1[224], a2[224];
    for (p = space1[cur1].last_child, cnt1 = 0; p != Null; p = space1[p].last_sibling)
    {
        a1[cnt1++] = p;
    }
    for (p = space2[cur2].last_child, cnt2 = 0; p != Null; p = space2[p].last_sibling)
    {
        a2[cnt2++] = p;
    }
    if (cnt1 != cnt2)
    {
        return 0;
    }
    if (cnt1 == 0)
    {
        return 1;
    }
    quick_sort(a1, 0, cnt1 - 1, space1);
    quick_sort(a2, 0, cnt2 - 1, space2);
    for (p = 0; p < cnt1; p++)
    {
        if (name_cmp(space1[a1[p]].DIR_Name, space2[a2[p]].DIR_Name))
        {
            return 0;
        }
        if (!isomorphy(a1[p], a2[p], space1, space2))
        {
            return 0;
        }
    }
    return 1;
}
void print_path_recursion(unsigned char cur, struct RootEntry space[])
{
    if (cur == ROOT)
    {
        printf("A:");
        return;
    }
    print_path_recursion(space[cur].parent, space);
    putchar('\\');
    print_name(space[cur].DIR_Name);
}
void print_path(unsigned char cur, struct RootEntry space[])
{
    if (cur == ROOT)
    {
        printf("A:");
        putchar('\\');
        return;
    }
    print_path_recursion(cur, space);
}
unsigned char locate(char path[], unsigned char cur, struct RootEntry space[])
{
    unsigned char p = cur;
    int i = 0, j, k;
    if (path[0] == 'A' && path[1] == ':')
    {
        p = ROOT;
        i = 2;
        if (path[2] == '\\')
        {
            i = 3;
        }
    }
    else if (path[0] == '\\')
    {
        i = 1;
    }
    while (p != Null && path[i] && path[i] != ' ')
    {
        if (path[i] == '.')
        {
            if (path[i + 1] == '.' && (!path[i + 2] || path[i + 2] == ' ' || path[i + 2] == '\\'))
            {
                p = space[p].parent;
                i += 2;
                if (path[i] == '\\')
                {
                    i += 1;
                }
                continue;
            }
            else if (!path[i + 1] || path[i + 1] == ' ' || path[i + 1] == '\\')
            {
                i += 1;
                if (path[i] == '\\')
                {
                    i += 1;
                }
                continue;
            }
        }
        for (p = space[p].last_child; p != Null; p = space[p].last_sibling)
        {
            for (j = 0; path[i + j] && path[i + j] != ' ' && path[i + j] != '\\' && path[i + j] != '.'; j++)
            {
                if (space[p].DIR_Name[j] != path[i + j])
                {
                    break;
                }
            }
            if (j > 8)
            {
                return Null;
            }
            if (j < 8 && space[p].DIR_Name[j] != ' ')
            {
                continue;
            }
            if (path[i + j] == '.')
            {
                for (j++, k = 8; path[i + j] && path[i + j] != ' ' && path[i + j] != '\\'; j++, k++)
                {
                    if (space[p].DIR_Name[k] != path[i + j])
                    {
                        break;
                    }
                }
                if (space[p].DIR_Name[k] != ' ')
                {
                    continue;
                }
            }
            else if (space[p].DIR_Name[8] != ' ')
            {
                continue;
            }
            if (!path[i + j] || path[i + j] == ' ')
            {
                i += j;
                break;
            }
            if (path[i + j] == '\\')
            {
                i += j + 1;
                break;
            }
        }
    }
    return p;
}
void demo(unsigned char fat1[], unsigned char fat2[], struct RootEntry space1[], unsigned short *item_top_p)
{
    init(space1);
    memset(fat1, 0, 4608);
    memset(fat2, 0, 4608);
    fat1[0] = 0xf0;
    fat1[1] = 0xff;
    fat1[2] = 0xff;
    fat2[0] = 0xf0;
    fat2[1] = 0xff;
    fat2[2] = 0xff;
    /*unsigned char IO1 = memory_alloc(space1);
    assign(IO1, "IO.SYS", 0x27, ROOT, fat1, fat2, space1, item_top_p);
    unsigned char MSDOS1 = memory_alloc(space1);
    assign(MSDOS1, "MSDOS.SYS", 0x27, ROOT, fat1, fat2, space1, item_top_p);
    unsigned char COMMAND1 = memory_alloc(space1);
    assign(COMMAND1, "COMMAND.COM", 0x20, ROOT, fat1, fat2, space1, item_top_p);
    unsigned char DRVSPACE1 = memory_alloc(space1);
    assign(DRVSPACE1, "DRVSPACE.BIN", 0x27, ROOT, fat1, fat2, space1, item_top_p);*/
    unsigned char USER1 = memory_alloc(space1);
    assign(USER1, "USER", TYPE_DIR, ROOT, fat1, fat2, space1, item_top_p);
    unsigned char JOIN1 = memory_alloc(space1);
    assign(JOIN1, "JOIN", TYPE_DIR, USER1, fat1, fat2, space1, item_top_p);
    unsigned char JACK1 = memory_alloc(space1);
    assign(JACK1, "JACK", TYPE_DIR, USER1, fat1, fat2, space1, item_top_p);
    unsigned char LUCY1 = memory_alloc(space1);
    assign(LUCY1, "LUCY", TYPE_DIR, USER1, fat1, fat2, space1, item_top_p);
    unsigned char MUSIC1 = memory_alloc(space1);
    assign(MUSIC1, "MUSIC", TYPE_DIR, JOIN1, fat1, fat2, space1, item_top_p);
    unsigned char PICTURE1 = memory_alloc(space1);
    assign(PICTURE1, "PICTURE", TYPE_DIR, JOIN1, fat1, fat2, space1, item_top_p);
    unsigned char BOOK1 = memory_alloc(space1);
    assign(BOOK1, "BOOK", TYPE_DIR, JOIN1, fat1, fat2, space1, item_top_p);
    /*unsigned char HOULAI1 = memory_alloc(space1);
    assign(HOULAI1, "HOULAI.TXT", 0x20, MUSIC1, fat1, fat2, space1, item_top_p);
    init(space2);
    unsigned char COMMAND2 = memory_alloc(space2);
    assign(COMMAND2, "COMMAND.COM", 0x20, ROOT, fat1, fat2, space2, item_top_p);
    unsigned char IO2 = memory_alloc(space2);
    assign(IO2, "IO.SYS", 0x27, ROOT, fat1, fat2, space2, item_top_p);
    unsigned char MSDOS2 = memory_alloc(space2);
    assign(MSDOS2, "MSDOS.SYS", 0x27, ROOT, fat1, fat2, space2, item_top_p);
    unsigned char USER2 = memory_alloc(space2);
    assign(USER2, "USER", TYPE_DIR, ROOT, fat1, fat2, space2, item_top_p);
    unsigned char JACK2 = memory_alloc(space2);
    assign(JACK2, "JACK", TYPE_DIR, USER2, fat1, fat2, space2, item_top_p);
    unsigned char JOIN2 = memory_alloc(space2);
    assign(JOIN2, "JOIN", TYPE_DIR, USER2, fat1, fat2, space2, item_top_p);
    unsigned char LUCY2 = memory_alloc(space2);
    assign(LUCY2, "LUCY", TYPE_DIR, USER2, fat1, fat2, space2, item_top_p);
    unsigned char MUSIC2 = memory_alloc(space2);
    assign(MUSIC2, "MUSIC", TYPE_DIR, JOIN2, fat1, fat2, space2, item_top_p);
    unsigned char BOOK2 = memory_alloc(space2);
    assign(BOOK2, "BOOK", TYPE_DIR, JOIN2, fat1, fat2, space2, item_top_p);
    unsigned char PICTURE2 = memory_alloc(space2);
    assign(PICTURE2, "PICTURE", TYPE_DIR, JOIN2, fat1, fat2, space2, item_top_p);
    unsigned char HOULAI2 = memory_alloc(space2);
    assign(HOULAI2, "HOULAI.TXT", 0x20, MUSIC2, fat1, fat2, space2, item_top_p);
    unsigned char DRVSPACE2 = memory_alloc(space2);
    assign(DRVSPACE2, "DRVSPACE.BIN", 0x27, ROOT, fat1, fat2, space2, item_top_p);
    puts("space1: ");
    dfs(ROOT, space1, 0);
    puts("space2: ");
    dfs(ROOT, space2, 0);
    printf("h:\t%d\n", height(ROOT, space1, item_top_p));
    printf("file:\t%d\n", count_file(ROOT, space1, item_top_p));
    printf("isomorphy:\t%d\n", isomorphy(ROOT, ROOT, space1, space2));
    delete_tree(JOIN1, space1, item_top_p);
    puts("space1: ");
    dfs(ROOT, space1, 0);
    puts("space2: ");
    dfs(ROOT, space2, 0);
    printf("h:\t%d\n", height(ROOT, space1, item_top_p));
    printf("file:\t%d\n", count_file(ROOT, space1, item_top_p));
    printf("isomorphy:\t%d\n", isomorphy(ROOT, ROOT, space1, space2));*/
}