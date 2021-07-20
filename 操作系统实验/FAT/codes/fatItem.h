void modify_next_item(unsigned short p, unsigned short nxtp, unsigned char fat1[], unsigned char fat2[])
{
    if (!p % 2)
    {
        *(unsigned short *)(fat1 + (unsigned short)(p * 1.5)) &= 0xF000;
        *(unsigned short *)(fat1 + (unsigned short)(p * 1.5)) |= nxtp;
        *(unsigned short *)(fat2 + (unsigned short)(p * 1.5)) &= 0xF000;
        *(unsigned short *)(fat2 + (unsigned short)(p * 1.5)) |= nxtp;
    }
    else
    {
        *(unsigned short *)(fat1 + (unsigned short)(p * 1.5)) &= 0x000F;
        *(unsigned short *)(fat1 + (unsigned short)(p * 1.5)) |= nxtp << 4;
        *(unsigned short *)(fat2 + (unsigned short)(p * 1.5)) &= 0x000F;
        *(unsigned short *)(fat2 + (unsigned short)(p * 1.5)) |= nxtp << 4;
    }
}
unsigned short next_item(unsigned short p, unsigned char fat[])
{
    if (!p % 2)
    {
        return *(unsigned short *)(fat + (unsigned short)(p * 1.5)) & 0x0FFF;
    }
    else
    {
        return *(unsigned short *)(fat + (unsigned short)(p * 1.5)) >> 4;
    }
}
unsigned short item_alloc(unsigned char fat1[], unsigned char fat2[], unsigned short *item_top_p)
{
    unsigned short p;
    if (*item_top_p != 0xFFF)
    {
        p = *item_top_p;
        *item_top_p = next_item(*item_top_p, fat1);
        modify_next_item(p, 0xFFF, fat1, fat2);
    }
    else
    {
        for (p = 2; p < 2849 && next_item(p, fat1); p++)
            ;
        if (p == 2849)
        {
            return 0xFFF;
        }
        modify_next_item(p, 0xFFF, fat1, fat2);
    }
    return p;
}
void item_delete(unsigned short DIR_FstClus, unsigned char fat1[], unsigned char fat2[], unsigned short *item_top_p)
{
    unsigned short p = DIR_FstClus, nxtp;
    p = next_item(DIR_FstClus, fat1);
    if (p == 0xFFF)
    {
        return;
    }
    nxtp = next_item(p, fat1);
    while (nxtp != 0xFFF)
    {
        p = nxtp;
        nxtp = next_item(nxtp, fat1);
    }
    modify_next_item(p, *item_top_p, fat1, fat2);
    *item_top_p = next_item(DIR_FstClus, fat1);
}