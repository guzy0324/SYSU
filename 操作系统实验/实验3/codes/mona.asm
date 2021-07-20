BITS 16
extern main
global _start
global _put
global _move
global _get
global _cls
global _callf
_start:
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov ss, ax
    push dword ebp
    call dword main
    pop dword ebp
    ret
_put:
    mov	al, byte[esp+4]  ; 字符=第一个参数
    mov	bx, 0007h        ; 页号为0(BH = 0) 黑底白字(BL = 07h)
    mov cx, 1            ; 重复次数
    mov ah, 9            ; 功能号
    int 10h              ; 打印字符
    ret
_move:
    mov dl, byte[esp+4]  ; x
    mov dh, byte[esp+8]  ; y
    mov bh, 0            ; 显示页码
    mov ah, 2            ; 功能号
    int 10h              ; 移动光标
    ret
_get:
    mov ah, 0
    int 16h
    ret
_cls:
    mov ax, 3
    int 10h
    ret
_callf:
    mov ax, 0xb00
    mov es, ax           ; es:bx
    mov cl, byte[esp+4]  ; 扇区号
    mov ch, byte[esp+8]  ; 柱面号 ; 起始编号为0
    mov dh, byte[esp+12] ; 磁头号 ; 起始编号为0
    mov al, byte[esp+16] ; 扇区数
    mov bx, 0x100        ; 偏移地址; 存放数据的内存偏移地址
    mov ah, 2            ; 功能号
    mov dl, 0            ; 驱动器号 ; 软盘为0，硬盘和U盘为80H
    int 13H              ; 调用读磁盘BIOS的13h功能
    call 0xb00:0x100     ; 0xb100
    mov ax, cs           ; 恢复段地址
    mov ds, ax
    mov es, ax           ; 设置段地址（不能直接mov es,段地址）
    ret