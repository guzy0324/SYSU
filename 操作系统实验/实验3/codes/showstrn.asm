BITS 16
extern upper
extern Message
global _start
_start:
    mov ax,cs
    mov ds,ax
    mov es,ax
    mov ss,ax
    call dword upper
    mov bp,Message
    mov ax,ds
    mov es,ax
    mov cx,10
    mov ax,1301h
    mov bx,0007h
    mov dh,10
    mov dl,10
    int 10h
_end:
    jmp $