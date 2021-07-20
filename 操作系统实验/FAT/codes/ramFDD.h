#include <stdio.h>
void init_ramFDD144(unsigned char *ramFDD144, const char *path)
{
    FILE *fp = fopen(path, "rb");
    fread(ramFDD144, 1, 1474560, fp);
    fclose(fp);
} /*
void read_ramFDD_Block(unsigned char *ramFDD_Block, const unsigned char *ramFDD144, size_t offset)
{
    ramFDD144 += offset * 512;
    for (offset = 0; offset < 512; offset++)
    {
        ramFDD_Block[offset] = ramFDD144[offset];
    }
}
void write_ramFDD_Block(const unsigned char *ramFDD_Block, unsigned char *ramFDD144, size_t offset)
{
    ramFDD144 += offset * 512;
    for (offset = 0; offset < 512; offset++)
    {
        ramFDD144[offset] = ramFDD_Block[offset];
    }
}*/
void write_ramFDD144(unsigned char *ramFDD144, const char *path)
{
    FILE *fp = fopen(path, "wb");
    fwrite(ramFDD144, 1, 1474560, fp);
    fclose(fp);
}