org 0x7c00
_start:
    push dword ebp
    mov ax, cs
    mov ds, ax
    mov bx, ss
    mov ss, ax
    mov ebp, esp
    mov esp, 0xffff
    push word bx
    push dword ebp
    mov ax, 0x800
    mov es, ax             ; es:bx
    mov cl, 2              ; 扇区号
    mov al, 15             ; 扇区数
    mov bx, 0x100          ; 偏移地址; 存放数据的内存偏移地址
    mov ah, 2              ; 功能号
    mov dl, 0              ; 驱动器号 ; 软盘为0，硬盘和U盘为80H
    mov dh, 0              ; 磁头号 ; 起始编号为0
    mov ch, 0              ; 柱面号 ; 起始编号为0
    int 13H                ; 调用读磁盘BIOS的13h功能
    call dword 0x800:0x100 ; 0x8100
    mov bx, word[esp+4]
    pop dword esp
    mov ss, bx
    pop dword ebp
    retf
times 510-($-$$) db 0
db 0x55
db 0xaa