; 程序源代码（myos1.asm）
org  7c00h
; org  100h
; org 0h

; BIOS将把引导扇区加载到0:7C00h处，并开始执行
OffSetOfUserPrg1 equ 8100h
LEFT equ 0x4b00
RIGHT equ 0x4d00
UP equ 0x4800
DOWN equ 0x5000
Cls:
    mov ah,6
    mov al,0
    mov cx,0
    mov dx,0xffff
    int 10h                      ; cls

Start:
    mov ax, 0
    mov ss, ax
    mov sp, 0x7c00
    mov	ax, cs                   ; 置其他段寄存器值与CS相同
    mov	ds, ax                   ; 数据段
    mov	ax, ds                   ; ES:BP = 串地址
    mov	bp, ProgramInfo          ; BP=当前串的偏移地址
    mov	es, ax                   ; 置ES=DS
    mov	ax, 1301h                ; AH = 13h（功能号）、AL = 01h（光标置于尾）
    mov	bx, 0007h                ; 页号为0(BH = 0) 黑底白字(BL = 07h)
    mov dh, 0                    ; 行号 = 0

Form:
    cmp dh, [TotalNum]
    jz Inst
    mov	dl, 5                    ; 列号=5
    mov	cx, 1                    ; CX = 1
    int	10h                      ; BIOS的10h功能：显示一行字符

    inc bp
    mov	dl, 10                   ; 列号=10
    mov	cx, 1                    ; CX = 1
    int	10h                      ; BIOS的10h功能：显示一行字符
    inc bp
    inc dh
    jmp Form

Inst:
    mov	bp, Message              ; BP=当前串的偏移地址
    mov	dl, 0                    ; 列号=0
    mov	cx, MessageLength        ; CX = 串长
    int	10h                      ; BIOS的10h功能：显示一行字符

    mov si, Order                ; 数组中光标位置
    mov dl, MessageLength        ; 光标位置
    mov di, Order
    add di, [Len]

Dump:
    cmp si, di
    jz Input
    mov al,byte[si]
    mov ah,9                     ; 功能号
    mov cx,1                     ; 重复次数
    int 10h                      ; 打印字符
    inc si
    inc dx
    mov ah, 2
    ; mov bh,0
    int 10h                      ; 移动光标
    jmp Dump

Input:
    mov ah,0
    int 16h
    cmp al,0x0d                  ; '/r'
    jz Load

    cmp al,0x08                  ; '/b'
    jz BackSpace

    cmp ax,LEFT
    jz Left
    cmp ax,RIGHT
    jz Right
    cmp ax,UP
    jz Up
    cmp ax,DOWN
    jz Down

    mov di,ProgramInfo
Defau:
    cmp di,TotalNum
    jz Input
    cmp al,byte[di]
    jz ValidProgram
    add di,2
    jmp Defau

BackSpace:
    cmp si, Order
    jz Input                     ; 如果到最左，则无效
    push dx
    push si
    mov di,Order
    add di,[Len]                 ; di=数组尾
Erase:
    mov al, byte[si]
    dec si
    dec dx
    mov ah, 2
    ; mov bh,0
    int 10h                      ; 移动光标
    mov byte[si],al
    mov ah,9                     ; 功能号
    mov cx,1                     ; 重复次数
    int 10h                      ; 打印字符

    add si, 2
    add dx, 2
    mov ah, 2
    ; mov bh,0
    int 10h                      ; 移动光标
    cmp di, si
    jns Erase
BackSpaceReturn:
    dec	word[Len]
    pop si
    pop dx                       ; BackSpace后接着Left
Left:
    cmp si, Order
    jz Input                     ; 如果到最左，则无效
    dec si
    dec dx                       ; 行号dh，列号dl
    mov ah, 2
    ; mov bh,0
    int 10h                      ; 左移一位光标
    jmp Input
ValidProgram:
    push dx
    push si                      ; 暂存
    mov di,Order
    inc word[Len]
    add di,[Len]                 ; di=数组尾
Insert:
    cmp si,di
    jz InsertReturn
    mov cl, byte[si]
    push cx
    mov [si],al
    mov ah,9                     ; 功能号
    mov cx,1                     ; 重复次数
    int 10h                      ; 打印字符

    pop ax
    inc si
    inc dx
    mov ah,2
    ; mov bh,0
    int 10h                      ; 移动光标

    jmp Insert
InsertReturn:
    pop si
    pop dx                       ; Insert后接着Right
Right:
    mov di,Order
    add di,[Len]                 ; di=数组尾
    cmp si,di
    jz Input                     ; 如果到最右，则无效
    inc si
    inc dx                       ; 行号dh，列号dl
    mov ah, 2
    ; mov bh,0
    int 10h                      ; 右移一位光标
    jmp Input

Up:
    mov si, Order
    mov dl, MessageLength        ; 列号dl
    mov ah, 2
    ; mov bh,0
    int 10h                      ; 左移至头光标
    jmp Input
Down:
    mov si, Order
    add si, [Len]
    mov dl, MessageLength
    add dx, [Len]                ; 行号dh，列号dl
    mov ah, 2
    ; mov bh,0
    int 10h                      ; 右移至尾光标
    jmp Input

Load:
    mov si, Order
    mov di, Order
    add di, [Len]

LoadnEx:
    ; 读软盘或硬盘上的若干物理扇区到内存的ES:BX处：
    cmp si, di
    jz Cls                       ; 执行完成，从头开始

    mov cl,byte[si]              ; 起始扇区号 ; 起始编号为1
    mov bx,ProgramInfo
MapLoop:
    cmp cl,byte[bx]
    jz SetSec
    add bx,2                     ; 前面有效输入的原则，已经保证了一定可以找到
    jmp MapLoop

SetSec:
    mov cl,byte[bx+1]
    sub cl,'0'

    mov ax,cs                    ; 段地址 ; 存放数据的内存基地址
    mov es,ax                    ; 设置段地址（不能直接mov es,段地址）
    mov bx, OffSetOfUserPrg1     ; 偏移地址; 存放数据的内存偏移地址
    mov ah,2                     ; 功能号
    mov al,1                     ; 扇区数
    mov dl,0                     ; 驱动器号 ; 软盘为0，硬盘和U盘为80H
    mov dh,0                     ; 磁头号 ; 起始编号为0
    mov ch,0                     ; 柱面号 ; 起始编号为0

    int 13H                      ; 调用读磁盘BIOS的13h功能
                                 ; 用户程序a.com已加载到指定内存区域中
    call 800h:100h
    mov ax, 0
    mov ds,ax
    mov es,ax                    ; 设置段地址（不能直接mov es,段地址）
    inc si
    jmp LoadnEx

ProgramInfo:
    db 'G'
    db '2'
    db 'U'
    db '3'
    db 'Z'
    db '4'
    db 'Y'
    db '5'
TotalNum:
    db ($-ProgramInfo) / 2
Message:
    db 'Input an order and hit Enter: '
MessageLength  equ ($-Message)
Len:
    dw 0
Order:
    times 510-($-$$) db 0
    db 0x55,0xaa

