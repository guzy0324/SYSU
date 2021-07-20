struct RootEntry
{
    char DIR_Name[11];
    unsigned char DIR_Attr;
    unsigned char reserve[10];
    unsigned short DIR_WrtTime;
    unsigned short DIR_WrtDate;
    unsigned short DIR_FstClus;
    unsigned int DIR_FileSize;
};