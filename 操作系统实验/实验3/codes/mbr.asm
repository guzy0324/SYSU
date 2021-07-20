org 0x7c00
_start:
    mov ax, cs
    mov ds, ax
    mov ss, ax
    mov ax, 0x800
    mov es, ax             ; es:bx
    mov cl, 2              ; 扇区号
    mov al, 11             ; 扇区数
    mov bx, 0x100          ; 偏移地址; 存放数据的内存偏移地址
    mov ah, 2              ; 功能号
    mov dl, 0              ; 驱动器号 ; 软盘为0，硬盘和U盘为80H
    mov dh, 0              ; 磁头号 ; 起始编号为0
    mov ch, 0              ; 柱面号 ; 起始编号为0
    int 13H                ; 调用读磁盘BIOS的13h功能
    call dword 0x800:0x100 ; 0x8100
    mov ax, cs             ; 恢复段地址
    mov ds, ax
    mov es, ax             ; 设置段地址（不能直接mov es,段地址）
    ret
times 510-($-$$) db 0
db 0x55
db 0xaa