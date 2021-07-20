#include "fat12Header.h"
#include "file.h"
#include "ramFDD.h"
#include <conio.h>
#define ESC 0x1b
#define LEFT 75
#define UP 72
#define RIGHT 77
#define DOWN 80
void read_command(char command[], char parameter[])
{
    int i;
    char ch;
    while ((ch = getchar()) == ' ')
        ;
    for (i = 0; ch != ' '; i++)
    {
        if (ch == '\n')
        {
            command[i] = '\0';
            parameter[0] = '\0';
            return;
        }
        if (ch >= 'a' && ch <= 'z')
        {
            command[i] = ch - 'a' + 'A';
        }
        else
        {
            command[i] = ch;
        }
        ch = getchar();
    }
    command[i] = '\0';
    while ((ch = getchar()) == ' ')
        ;
    for (i = 0; ch != '\n'; i++)
    {
        if (ch == ' ')
        {
            parameter[i++] = ' ';
            while ((ch = getchar()) == ' ')
                ;
        }
        if (ch >= 'a' && ch <= 'z')
        {
            parameter[i] = ch - 'a' + 'A';
        }
        else
        {
            parameter[i] = ch;
        }
        ch = getchar();
    }
    parameter[i] = '\0';
}
int is_command(const char command1[], const char command2[])
{
    int i;
    for (i = 0; command1[i]; i++)
    {
        if (command1[i] != command2[i])
        {
            return 0;
        }
    }
    return command2[i] == 0;
}
char *split(char path[])
{
    int i;
    for (i = 0; path[i]; i++)
        ;
    for (; path[i] != '\\'; i--)
    {
        if (!i)
        {
            return NULL;
        }
    }
    path[i] = '\0';
    return path + i + 1;
}
int check_name(char *name)
{
    int i;
    for (i = 0; name[i]; i++)
    {
        if (name[i] == '.')
        {
            i++;
            continue;
        }
        if (!((name[i] >= '0' && name[i] <= '9') || (name[i] >= 'A' && name[i] <= 'Z')))
        {
            return 0;
        }
    }
    return 1;
}
void execute_command(char command[], char parameter[], unsigned char *cur_ptr,
                     unsigned char mbr[], unsigned char fat1[], unsigned char fat2[], struct RootEntry space[], unsigned char data[],
                     struct ActiveFile active_list[], struct OpenFile open_list[], unsigned short *item_top_p)
{
    if (is_command(command, "CHECK"))
    {
        if (check(mbr, fat1, fat2))
        {
            puts("Legal");
        }
        else
        {
            puts("Illegal");
        }
    }
    else if (is_command(command, "DIR"))
    {
        unsigned char temp = locate(parameter, *cur_ptr, space);
        if (temp == Null)
        {
            puts("File not found");
        }
        else
        {
            list_dir(temp, space);
        }
    }
    else if (is_command(command, "CD"))
    {
        unsigned char cur = *cur_ptr;
        if (parameter[0] != '>')
        {
            unsigned char temp = locate(parameter, *cur_ptr, space);
            if (temp == Null || space[temp].DIR_Attr != TYPE_DIR)
            {
                puts("Invalid directory");
            }
            else
            {
                *cur_ptr = temp;
            }
            while (*parameter != ' ')
            {
                parameter++;
            }
            parameter++;
        }
        if (parameter[0] == '>' && parameter[1] == ' ')
        {
            char *file_name = split(parameter + 2);
            unsigned char temp;
            if (file_name != NULL)
            {
                temp = locate(parameter + 2, cur, space);
                if (temp == Null || space[temp].DIR_Attr != TYPE_DIR)
                {
                    puts("Invalid path");
                    return;
                }
            }
            else
            {
                file_name = parameter + 2;
                temp = cur;
            }
            if (!check_name(file_name))
            {
                puts("Invalid file name");
                return;
            }
            if (locate(file_name, temp, space) != Null)
            {
                puts("File already exists");
                return;
            }
            unsigned char file;
            if ((file = memory_alloc(space)) == Null)
            {
                puts("Space used up");
            }
            else
            {
                assign(file, file_name, TYPE_NORMAL_FILE, temp, fat1, fat2, space, item_top_p);
            }
        }
    }
    else if (is_command(command, "TREE"))
    {
        unsigned char temp = locate(parameter, *cur_ptr, space);
        if (temp == Null)
        {
            puts("File not found");
        }
        else
        {
            dfs(temp, space, 0);
        }
    }
    else if (is_command(command, "MD"))
    {
        char *file_name = split(parameter);
        unsigned char temp;
        if (file_name != NULL)
        {
            temp = locate(parameter, *cur_ptr, space);
            if (temp == Null || space[temp].DIR_Attr != TYPE_DIR)
            {
                puts("Invalid path");
                return;
            }
        }
        else
        {
            file_name = parameter;
            temp = *cur_ptr;
        }
        if (!check_name(file_name))
        {
            puts("Invalid directory name");
            return;
        }
        if (locate(file_name, temp, space) != Null)
        {
            puts("Directory already exists");
            return;
        }
        unsigned char file;
        if ((file = memory_alloc(space)) == Null)
        {
            puts("Space used up");
        }
        else
        {
            assign(file, file_name, TYPE_DIR, temp, fat1, fat2, space, item_top_p);
        }
    }
    else if (is_command(command, "RD"))
    {
        unsigned char temp = locate(parameter, *cur_ptr, space);
        if (temp == Null)
        {
            puts("Invalid path");
        }
        else
        {
            if (space[temp].DIR_Attr != TYPE_DIR)
            {
                puts("Not directory");
            }
            else if (!memory_delete(temp, space))
            {
                puts("Directory not empty");
            }
        }
    }
    else if (is_command(command, "DEL"))
    {
        unsigned char temp = locate(parameter, *cur_ptr, space);
        if (temp == Null)
        {
            puts("Invalid path");
        }
        else
        {
            if (space[temp].DIR_Attr == TYPE_DIR)
            {
                while (1)
                {
                    puts("All files in directory will be deleted!");
                    puts("Are you sure (Y/N)?");
                    char ch = getchar();
                    while (getchar() != '\n')
                        ;
                    if (ch == 'Y' || ch == 'y')
                    {
                        unsigned char p;
                        for (p = space[temp].last_child; p != Null; p = space[p].last_sibling)
                        {
                            if (space[p].DIR_Attr != TYPE_DIR)
                            {
                                break;
                            }
                        }
                        if (p == Null)
                        {
                            puts("File not found");
                            break;
                        }
                        memory_delete(p, space);
                        item_delete(*(unsigned short *)space[p].DIR_FstClus, fat1, fat2, item_top_p);
                        for (; p != Null; p = space[p].last_sibling)
                        {
                            if (space[p].DIR_Attr != TYPE_DIR)
                            {
                                memory_delete(p, space);
                                item_delete(*(unsigned short *)space[p].DIR_FstClus, fat1, fat2, item_top_p);
                            }
                        }
                        break;
                    }
                    else if (ch == 'N' || ch == 'n')
                    {
                        break;
                    }
                }
            }
            else
            {
                item_delete(*(unsigned short *)space[temp].DIR_FstClus, fat1, fat2, item_top_p);
                memory_delete(temp, space);
            }
        }
    }
    else if (is_command(command, "REN"))
    {
        unsigned char temp = locate(parameter, *cur_ptr, space);
        if (temp == Null)
        {
            puts("File not found");
            return;
        }
        while (*parameter != ' ')
        {
            parameter++;
        }
        parameter++;
        if (!check_name(parameter))
        {
            puts("Invalid file name");
            return;
        }
        store_name(space[temp].DIR_Name, parameter);
    }
    else if (is_command(command, "EDIT"))
    {
        unsigned char temp = locate(parameter, *cur_ptr, space);
        if (temp == Null)
        {
            puts("File not found");
            return;
        }
        if (space[temp].DIR_Attr != TYPE_NORMAL_FILE)
        {
            puts("Not file");
            return;
        }
        struct OpenFile *fp;
        if ((fp = file_open(temp, 'w', active_list, open_list, fat1, space, data)) == NULL)
        {
            puts("Too much files opend");
            return;
        }
        system("cls");
        file_read(fp, -1, NULL);
        char ch;
        while (1)
        {
            ch = getch();
            if (!ch || ch == -32)
            {
                ch = getch();
                if (ch == LEFT)
                {
                    if (!seek(fp, -1, fp->posi))
                    {
                        putchar('\a');
                    }
                }
                else if (ch == RIGHT)
                {
                    if (!seek(fp, 1, fp->posi))
                    {
                        putchar('\a');
                    }
                }
            }
            else if (ch == '\r')
            {
                insert(fp, '\n');
            }
            else if (ch == ESC)
            {
                system("cls");
                break;
            }
            else if (ch == '\b')
            {
                erase(fp);
            }
            else
            {
                insert(fp, ch);
            }
            system("cls");
            file_read(fp, -1, NULL);
        }
        if (!file_close(fp, fat1, fat2, data, item_top_p))
        {
            puts("Fail saving, space used up");
        }
    }
    else if (is_command(command, "MOVE"))
    {
        unsigned char temp = locate(parameter, *cur_ptr, space);
        if (temp == Null)
        {
            puts("File not found");
            return;
        }
        while (*parameter != ' ')
        {
            parameter++;
        }
        parameter++;
        unsigned char temp2 = locate(parameter, *cur_ptr, space);
        if (space[temp2].DIR_Attr != TYPE_DIR)
        {
            puts("Not directory");
            return;
        }
        if (space[space[temp].parent].last_child == temp)
        {
            space[space[temp].parent].last_child = space[temp].last_sibling;
        }
        if (space[temp].last_sibling != Null)
        {
            space[space[temp].last_sibling].next_sibling = space[temp].next_sibling;
        }
        if (space[temp].next_sibling != Null)
        {
            space[space[temp].next_sibling].last_sibling = space[temp].last_sibling;
        }
        space[temp].parent = temp2;
        space[temp].last_sibling = space[temp2].last_child;
        space[temp].next_sibling = Null;
        space[temp2].last_child = temp;
        if (space[temp].last_sibling != Null)
        {
            space[space[temp].last_sibling].next_sibling = temp;
        }
    }
    else if (is_command(command, "FILECPY"))
    {
        unsigned char temp = locate(parameter, *cur_ptr, space);
        if (temp == Null)
        {
            puts("File not found");
            return;
        }
        if (space[temp].DIR_Attr != TYPE_NORMAL_FILE)
        {
            puts("Not file");
        }
        while (*parameter != ' ')
        {
            parameter++;
        }
        parameter++;
        unsigned char temp2 = locate(parameter, *cur_ptr, space);
        struct OpenFile *fp1, *fp2;
        if (temp2 == Null)
        {
            puts("File not found");
            return;
        }
        if (space[temp2].DIR_Attr != TYPE_NORMAL_FILE)
        {
            puts("Not file");
        }
        fp2 = file_open(temp, 'r', active_list, open_list, fat1, space, data);
        fp1 = file_open(temp2, 'w', active_list, open_list, fat1, space, data);
        copy(fp1, fp2);
        file_close(fp1, fat1, fat2, data, item_top_p);
        file_close(fp2, fat1, fat2, data, item_top_p);
    }
    else if (is_command(command, "FILECAT"))
    {
        unsigned char temp = locate(parameter, *cur_ptr, space);
        if (temp == Null)
        {
            puts("File not found");
            return;
        }
        if (space[temp].DIR_Attr != TYPE_NORMAL_FILE)
        {
            puts("Not file");
        }
        while (*parameter != ' ')
        {
            parameter++;
        }
        parameter++;
        unsigned char temp2 = locate(parameter, *cur_ptr, space);
        struct OpenFile *fp1, *fp2;
        if (temp2 == Null)
        {
            puts("File not found");
            return;
        }
        if (space[temp2].DIR_Attr != TYPE_NORMAL_FILE)
        {
            puts("Not file");
        }
        fp2 = file_open(temp, 'r', active_list, open_list, fat1, space, data);
        fp1 = file_open(temp2, 'w', active_list, open_list, fat1, space, data);
        seek(fp1, *(int *)fp1->af->dir->DIR_FileSize, fp1->posi);
        copy(fp1, fp2);
        file_close(fp1, fat1, fat2, data, item_top_p);
        file_close(fp2, fat1, fat2, data, item_top_p);
    }
    else if (is_command(command, "DEMO"))
    {
        demo(fat1, fat2, space, item_top_p);
    }
    else
    {
        puts("Bad command or file name");
    }
}