#include "rootEntry.h"
#include <stdlib.h>
#define MAX_ACTIVE_FILE 100
#define MAX_OPEN_FILE 10
#define READ 0
#define WRITE 1
#define CURSOR '~'
struct FileBuffer
{
    char value;
    struct FileBuffer *next;
    struct FileBuffer *last;
};
struct ActiveFile
{
    struct RootEntry *dir;
    unsigned char uid;
    int share_counter;
    struct FileBuffer *fb;
};
struct OpenFile
{
    struct FileBuffer *posi;
    int read_or_write;
    struct ActiveFile *af;
};
struct OpenFile *file_open(unsigned char uid, char opt, struct ActiveFile active_list[], struct OpenFile open_list[], unsigned char fat[], struct RootEntry space[], unsigned char data[])
{
    int i, j, k = -1;
    for (i = 0; i < MAX_OPEN_FILE && open_list[i].af != NULL; i++)
        ;
    if (i == MAX_OPEN_FILE)
    {
        return NULL;
    }
    for (j = 0; j < MAX_ACTIVE_FILE && active_list[j].uid != Null; j++)
    {
        if (uid == active_list[i].uid)
        {
            break;
        }
        if (k == -1 && !active_list[j].share_counter)
        {
            k = j;
        }
    }
    if (j == MAX_ACTIVE_FILE && k == -1)
    {
        return NULL;
    }
    if (uid == active_list[j].uid && active_list[j].share_counter)
    {
        active_list[j].share_counter++;
    }
    else
    {
        if (k != -1)
        {
            j = k;
        }
        active_list[j].dir = (struct RootEntry *)space + uid;
        active_list[j].uid = uid;
        active_list[j].share_counter = 1;
        unsigned int sz = 0;
        struct FileBuffer *p = NULL;
        unsigned short clus = *(unsigned short *)active_list[j].dir->DIR_FstClus;
        int flag = 1;
        while (clus != 0xFFF)
        {
            int offset = (clus - 2) * 512;
            for (; sz < *(unsigned int *)active_list[j].dir->DIR_FileSize && (flag || sz % 512); sz++, offset++)
            {
                flag = 0;
                struct FileBuffer *node = (struct FileBuffer *)malloc(sizeof(struct FileBuffer));
                node->last = p;
                if (p == NULL)
                {
                    active_list[j].fb = node;
                    p = active_list[j].fb;
                }
                else
                {
                    p->next = node;
                    p = p->next;
                }
                p->value = data[offset];
            }
            if (sz == *(unsigned int *)active_list[j].dir->DIR_FileSize)
            {
                break;
            }
            clus = next_item(clus, fat);
            flag = 1;
        }
        if (p == NULL)
        {
            struct FileBuffer *node = (struct FileBuffer *)malloc(sizeof(struct FileBuffer));
            node->last = p;
            active_list[j].fb = node;
            p = active_list[j].fb;
            p->value = '\0';
            p->next = NULL;
        }
        else
        {
            struct FileBuffer *node = (struct FileBuffer *)malloc(sizeof(struct FileBuffer));
            node->last = p;
            p->next = node;
            p = p->next;
            p->value = '\0';
            p->next = NULL;
        }
    }
    open_list[i].posi = active_list[j].fb;
    if (opt == 'w')
    {
        open_list[i].read_or_write = WRITE;
    }
    else
    {
        open_list[i].read_or_write = READ;
    }
    open_list[i].af = active_list + j;
    return open_list + i;
}
int file_close(struct OpenFile *fp, unsigned char fat1[], unsigned char fat2[], unsigned char data[], unsigned short *item_top_p)
{
    fp->af->share_counter--;
    if (!fp->af->share_counter)
    {
        unsigned int sz = 0;
        struct FileBuffer *p = fp->af->fb;
        unsigned short clus = *(unsigned short *)fp->af->dir->DIR_FstClus;
        int offset = (clus - 2) * 512;
        if (p->next != NULL)
        {
            while (p->next->next != NULL)
            {
                data[offset] = p->value;
                p = p->next;
                free(p->last);
                offset++;
                sz++;
                if (!sz % 512)
                {
                    clus = next_item(clus, fat1);
                    if (clus == 0xFFF)
                    {
                        clus = item_alloc(fat1, fat2, item_top_p);
                        if (clus == 0xFFF)
                        {
                            return 0;
                        }
                    }
                    offset = (clus - 2) * 512;
                }
            }
            free(p->next);
            data[offset] = p->value;
            sz++;
        }
        free(p);
        if (next_item(clus, fat1) != 0xFFF)
        {
            item_delete(clus, fat1, fat2, item_top_p);
            modify_next_item(clus, 0xFFF, fat1, fat2);
        }
        *(unsigned int *)fp->af->dir->DIR_FileSize = sz;
    }
    fp->af = NULL;
    return 1;
}
int file_read(struct OpenFile *fp, int sz, struct FileBuffer *posi)
{
    struct FileBuffer *p;
    if (posi != NULL)
    {
        p = posi;
    }
    else
    {
        p = fp->af->fb;
    }
    int i;
    for (i = 0; (sz == -1 || (sz != -1 && i < sz)) && p != NULL; i++, p = p->next)
    {
        if (posi == NULL && p == fp->posi)
        {
            putchar(CURSOR);
            if (p->value == '\n')
            {
                putchar('\n');
            }
        }
        else
        {
            putchar(p->value);
        }
    }
    return i;
}
/*int file_write(struct OpenFile *fp, unsigned char buf[])
{
    if (fp->read_or_write != WRITE)
    {
        return -1;
    }
    int i = 0;
    struct FileBuffer *p;
    for (p = fp->posi;; buf++, p = p->next, i++)
    {
        p->value = *buf;
        if (p->next == NULL && *buf)
        {
            p->next = (struct FileBuffer *)malloc(sizeof(struct FileBuffer));
            p->next->last = p;
            p->next->next = NULL;
        }
        if (!*buf)
        {
            break;
        }
    }
    if (p != NULL)
    {
        p->last->next = NULL;
        while (p->next != NULL)
        {
            p = p->next;
            free(p->last);
        }
        free(p);
    }
    return i;
}*/
int seek(struct OpenFile *fp, int offset, struct FileBuffer *start)
{
    struct FileBuffer *posi = start;
    while (offset > 0)
    {
        if (posi->next == NULL)
        {
            return 0;
        }
        posi = posi->next;
        offset--;
    }
    while (offset < 0)
    {
        if (posi->last == NULL)
        {
            return 0;
        }
        posi = posi->last;
        offset++;
    }
    fp->posi = posi;
    return 1;
}
int insert(struct OpenFile *fp, unsigned char ch)
{
    if (fp->read_or_write != WRITE)
    {
        return 0;
    }
    if (fp->posi->last == NULL)
    {
        fp->af->fb = (struct FileBuffer *)malloc(sizeof(struct FileBuffer));
        fp->af->fb->last = NULL;
        fp->posi->last = fp->af->fb;
    }
    else
    {
        fp->posi->last->next = (struct FileBuffer *)malloc(sizeof(struct FileBuffer));
        fp->posi->last->next->last = fp->posi->last;
        fp->posi->last = fp->posi->last->next;
    }
    fp->posi->last->next = fp->posi;
    fp->posi->last->value = ch;
    return 1;
}
int erase(struct OpenFile *fp)
{
    if (fp->read_or_write != WRITE)
    {
        return 0;
    }
    if (fp->posi->last != NULL)
    {
        if (fp->posi->last->last != NULL)
        {
            fp->posi->last = fp->posi->last->last;
            free(fp->posi->last->next);
            fp->posi->last->next = fp->posi;
        }
        else
        {
            fp->posi->last = NULL;
            free(fp->af->fb);
            fp->af->fb = fp->posi;
        }
    }
    return 1;
}
int copy(struct OpenFile *fp1, struct OpenFile *fp2)
{
    if (fp1->read_or_write != WRITE)
    {
        return -1;
    }
    int i = 0;
    struct FileBuffer *p1 = fp1->posi, *p2 = fp2->posi;
    for (; p2 != NULL; p1 = p1->next, p2 = p2->next, i++)
    {
        p1->value = p2->value;
        if (p1->next == NULL && p2->next != NULL)
        {
            p1->next = (struct FileBuffer *)malloc(sizeof(struct FileBuffer));
            p1->next->last = p1;
            p1->next->next = NULL;
        }
    }
    if (p1 != NULL)
    {
        p1->last->next = NULL;
        while (p1->next != NULL)
        {
            p1 = p1->next;
            free(p1->last);
        }
        free(p1);
    }
    return i;
}