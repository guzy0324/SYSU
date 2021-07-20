BITS 16
extern count
extern uint2str
global _start
_start:
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov ss, ax
    call _cls
    push dword _str
    call dword count
    add sp, 4
    mov [_str_len], eax
_print_uint:
    push dword _str_len_str
    push dword eax
    call dword uint2str
    add sp, 8
    push dword _str_len_str
    call dword count
    add sp, 4
_print_str_len:
    mov	bp, _str_len_str   ; BP=当前串的偏移地址
    mov	cl, al             ; CX = 串长
    mov	ax, 1301h          ; AH = 13h（功能号）、AL = 01h（光标置于尾）
    mov	bx, 0007h          ; 页号为0(BH = 0) 黑底白字(BL = 07h)
    mov dh, 0              ; 行号 = 0
    mov	dl, 0              ; 列号=0
    int	10h                ; BIOS的10h功能：显示一行字符
_print_str:
    mov	bp, _str           ; BP=当前串的偏移地址
    mov	cl, byte[_str_len] ; CX = 串长
    mov	ax, 1301h          ; AH = 13h（功能号）、AL = 01h（光标置于尾）
    mov	bx, 0007h          ; 页号为0(BH = 0) 黑底白字(BL = 07h)
    mov dh, 1              ; 行号 = 0
    mov	dl, 0              ; 列号=0
    int	10h                ; BIOS的10h功能：显示一行字符
_end:
    ; jmp $
    mov ah,1
    int 16h
    jz _end
    call _cls
    ret
_cls:
    mov ax, 3
    int 10h
    ret
_str:
    db '18308045_gzy', 0
_str_len:
    dd 0
_str_len_str:
    times 11 db 0