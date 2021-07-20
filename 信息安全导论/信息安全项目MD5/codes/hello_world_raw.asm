org 0x100
main:
    mov ax, 0x3
    int 0x10
    mov ax, 0x1301
    mov bx, 0x0
loop:
    mov cl, [data1+bx]
    cmp cl, [data2+bx]
    jnz evil
    inc bx
    cmp bx, 0x80
    jz good
    jmp loop
good:
    mov bx, 0x0007
    mov cx, length1
    mov dx, 0x0c21
    mov bp, message1
    jmp end
evil:
    mov bx, 0x0015
    mov cx, length2
    mov dx, 0x0c21
    mov bp, message2
    jmp end
end:
    int 0x10
    int 0x20
message1: db "Hello, world!", 0
length1 equ $-message1
message2: db "I'm evil!!!!!", 0
length2 equ $-message2
times 128-($-$$) db 0x0
data1: times 256-($-$$) db 0x0
data2: times 384-($-$$) db 0x0
