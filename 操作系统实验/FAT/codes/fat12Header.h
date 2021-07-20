struct Fat12Header
{
    char BS_OEMName[8];
    unsigned char BPB_BytsPerSec[2];
    unsigned char BPB_SecPerClus;
    unsigned char BPB_RsvdSecCnt[2];
    unsigned char BPB_NumFATs;
    unsigned char BPB_RootEntCnt[2];
    unsigned char BPB_TotSec16[2];
    unsigned char BPB_Media;
    unsigned char BPB_FATSz16[2];
    unsigned char BPB_SecPerTrk[2];
    unsigned char BPB_NumHeads[2];
    unsigned char BPB_HiddSec[4];
    unsigned char BPB_TotSec32[4];
    unsigned char BS_DrvNum;
    unsigned char BS_Reservedl;
    unsigned char BS_BootSig;
    unsigned char BS_VolID[4];
    char BS_VolLab[11];
    char BS_FileSysType[8];
};
int check(unsigned char mbr[], unsigned char fat1[], unsigned char fat2[])
{
    struct Fat12Header *p = (struct Fat12Header *)(mbr + 3);
    if ((*(unsigned short *)(p->BPB_BytsPerSec)) != 512)
    {
        return 0;
    }
    if (p->BPB_SecPerClus != 1)
    {
        return 0;
    }
    if ((*(unsigned short *)(p->BPB_RsvdSecCnt)) != 1)
    {
        return 0;
    }
    if (p->BPB_NumFATs != 2)
    {
        return 0;
    }
    if ((*(unsigned short *)(p->BPB_RootEntCnt)) != 224)
    {
        return 0;
    }
    if ((*(unsigned short *)(p->BPB_TotSec16)) != 2880)
    {
        return 0;
    }
    if ((*(unsigned short *)(p->BPB_FATSz16)) != 9)
    {
        return 0;
    }
    const char *FileSysType = "FAT12   ";
    for (int i = 0; i < 8; i++)
    {
        if (p->BS_FileSysType[i] != FileSysType[i])
        {
            return 0;
        }
    }
    if (fat1[0] != 0xf0 || fat1[1] != 0xff || fat1[2] != 0xff)
    {
        return 0;
    }
    for (int i = 0; i < 4608; i++)
    {
        if (fat1[i] != fat2[i])
        {
            return 0;
        }
    }
    return 1;
}