#include "ramFDD.h"
#include <string.h>
unsigned char ramFDD144[1474560];
unsigned char ram2[1474560];
int main()
{
    init_ramFDD144(ramFDD144, "../18308045PC/dossys.img");
    FILE *fp;
    init_ramFDD144(ram2, "../18308045PC/fdd144.img");
    fp = fopen("../18308045PC/hh.img", "wb");
    for (int i = 0; i < 512; i++)
    {
        ram2[i] = ramFDD144[i];
    }
    fwrite(ram2, 1, 1474560, fp);
    fclose(fp);
}
