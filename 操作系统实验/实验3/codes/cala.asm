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
    mov bx, ss
    mov ss, ax
    mov eax, esp
    push word bx
    push dword eax
    push dword ebp
    call dword main
    pop dword ebp
    mov bx, word[esp+4]
    pop dword esp
    mov ss, bx
    retf
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
    mov ah, 1
    int 16h
    jz _get
    mov ah, 0
    int 16h
    ret
_cls:
    mov ax, 3
    int 10h
    ret