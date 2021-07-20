BITS 16
extern main
;extern lyheader
;extern new_layer
extern lyfnheader
extern new_layfun
extern clock_hotwheel
extern clock_time
extern ouch_color
extern clock_ouch
extern clock
extern display_str
global _start
global _put
global _move
global _get
global _cls
global _memb
global _call
global _callf
global _display
global _get_time
global _time
global _clock_hotwheel
global _clock_time
global _clock_ouch
global _set_int
global _clock
global _int_20h
global _int_21h
global _int_22h
_start:
    push dword ebp
    mov ax, cs
    mov ds, ax
    mov cx, ss
    mov ss, ax
    mov ebp, esp
    mov esp, 0xffff
    push word cx
    push dword ebp
    call dword main
    mov cx, word[esp+4]
    pop dword esp
    mov ss, cx
    pop dword ebp
    retf
_put:
    mov	al, byte[esp+4]       ; 字符=第一个参数
    mov dx, bx
    mov	bx, 0007h             ; 页号为0(BH = 0) 黑底白字(BL = 07h)
    mov cx, 1                 ; 重复次数
    mov ah, 9                 ; 功能号
    int 10h                   ; 打印字符
    mov bx, dx
    o32 ret
_move:
    mov dl, byte[esp+4]       ; x
    mov dh, byte[esp+8]       ; y
    mov ch, bh
    mov bh, 0                 ; 显示页码
    mov ah, 2                 ; 功能号
    int 10h                   ; 移动光标
    mov bh, ch
    o32 ret
_get:
    mov ah, 1
    int 16h
    jz _get
    mov ah, 0
    int 16h
    o32 ret
_cls:
    mov ax, 3
    int 10h
    o32 ret
_memb:
    mov ax, word [esp + 4]
    mov es, ax
    mov eax, dword [esp + 8]
    mov al, byte [es:eax]
    o32 ret
_call:
    mov ax, word [esp + 4]    ; ker-stack: ker-ret-addr/user-cs/user-ip/arg
    mov dx, word [esp + 8]
    mov ecx, dword [esp + 12]
    push dword ebp            ; ker-stack: ebp/ker-ret-addr/user-cs/user-ip/arg
    push dword ebx            ; ker-stack: ebx/ebp/ker-ret-addr/user-cs/user-ip/arg 
    mov bx, sp
    mov ss, ax
    mov sp, 0xefff            ; user-stack: ，ker-stack: ebx/ebp/ker-ret-addr/user-cs/user-ip/arg
    push word bx              ; user-stack: ker-sp
    push dword ecx            ; user-stack: arg/ker-sp
    push word 0x800           ; user-stack: ker-cs/arg/ker-sp
    push word _call_ret       ; user-stack: ker-next-ip/ker-cs/arg/ker-sp
    push word ax              ; user-stack: user-cs/ker-next-ip/ker-cs/arg/ker-sp
    push word dx              ; user-stack: user-ip/user-cs/ker-next-ip/ker-cs/arg/ker-sp
    mov ds, ax
    retf                      ; user-stack: ker-next-ip/ker-cs/arg/ker-sp
_call_ret:                    ; user-stack: arg/ker-sp（在用户程序retf后），返回值：eax
    add sp, 4                 ; user-stack: ker-sp，返回值：eax
    pop word sp
    mov bx, cs
    mov ds, bx
    mov ss, bx                ; ker-stack: ebx/ebp/ker-ret-addr/user-cs/user-ip，user-stack:，返回值：eax
    pop dword ebx             ; ker-stack: ebp/ker-ret-addr/user-cs/user-ip，user-stack:，返回值：eax
    pop dword ebp             ; ker-stack: ker-ret-addr/user-cs/user-ip，返回值：eax
    o32 ret                   ; ker-stack: user-cs/user-ip，返回值：eax
_callf:
    xor ax, ax                ; AX = 0
    mov es, ax                ; ES = 0
    mov eax, dword[es:36]     ; 设置中断向量的偏移地址
    mov ax, 0xb00
    mov es, ax                ; es:bx
    mov cl, byte[esp+4]       ; 扇区号
    mov ch, byte[esp+8]       ; 柱面号 ; 起始编号为0
    mov dh, byte[esp+12]      ; 磁头号 ; 起始编号为0
    mov al, byte[esp+16]      ; 扇区数
    push dword ebx
    mov bx, 0x100             ; 偏移地址; 存放数据的内存偏移地址
    mov ah, 2                 ; 功能号
    mov dl, 0                 ; 驱动器号 ; 软盘为0，硬盘和U盘为80H
    int 13H                   ; 调用读磁盘BIOS的13h功能
    push dword ebp
    mov ax, 0xb00
    mov ds, ax
    mov word [0], 0x20cd
    mov word [0x2e], sp
    mov word [0x30], ss
    mov sp, 0xffff
    mov ss, ax
    push word 0xb00
    push word 0x0
    jmp 0xb00:0x100           ; 0xb100
_after_user_ret:
    pop dword ebp
    pop dword ebx
    o32 ret
_display:
    mov eax, dword[esp+12]
    mov ecx, 80
    mul ecx
    add eax, dword[esp+8]
    mov ecx, 2
    mul ecx
    mov ecx, eax
    mov	ax, 0B800h            ; 文本窗口显存起始地址
    mov	gs, ax                ; GS = B800h
    mov ah, byte[esp+16]      ; 0000：黑底、1111：亮白字（默认值为07h）
    mov al, byte[esp+4]       ; AL = 显示字符值（默认值为20h=空格符）
    mov [gs:ecx], ax          ; 屏幕第 x 行, 第 y 列
    o32 ret
_get_time:
    mov al, 0                 ; Get seconds (00 to 59)
    out 0x70, al
    in al, 0x71
    mov byte[_second], al

    mov al, 0x02              ; Get minutes (00 to 59)
    out 0x70, al
    in al, 0x71
    mov byte[_minute], al

    mov al, 0x04              ; Get hours (see notes)
    out 0x70, al
    in al, 0x71
    mov byte[_hour], al

    mov al, 0x07              ; Get day of month (01 to 31)
    out 0x70, al
    in al, 0x71
    mov byte[_day], al

    mov al, 0x08              ; Get month (01 to 12)
    out 0x70, al
    in al, 0x71
    mov byte[_month], al

    mov al, 0x09              ; Get year (00 to 99)
    out 0x70, al
    in al, 0x71
    mov byte[_year], al
    o32 ret
_clock_hotwheel:
    mov eax, dword [esp + 4]
    push dword eax
    call dword clock_hotwheel
    add esp, 4
    retf
_clock_time:
    mov eax, dword [esp + 4]
    push dword eax
    call dword clock_time
    add esp, 4
    retf
_clock_ouch:
    mov eax, dword [esp + 4]
    push dword eax
    call dword clock_ouch
    add esp, 4
    retf
_save:
    push word ds
    push word cs
    pop word ds
    pop word [_ds]
    pop dword [_ret_addr]
    pop word [_ip]
    pop word [_cs]
    pop word [_flags]
    mov word [_es], es
    mov word [_ss], ss
    mov word [_fs], fs
    mov word [_gs], gs
    mov dword [_ax], eax
    mov dword [_bx], ebx
    mov dword [_cx], ecx
    mov dword [_dx], edx
    mov dword [_sp], esp
    mov dword [_bp], ebp
    mov dword [_si], esi
    mov dword [_di], edi
    mov ax, cs
    mov ss, ax
    mov esp, 0x100
    push dword [_ret_addr]
    mov eax, dword[_ax]
    o32 ret
_restart:
    pop dword [_ret_addr]
    mov eax, dword [_ax]
    mov ebx, dword [_bx]
    mov ecx, dword [_cx]
    mov edx, dword [_dx]
    mov esp, dword [_sp]
    mov ebp, dword [_bp]
    mov esi, dword [_si]
    mov edi, dword [_di]
    mov es, word [_es]
    mov ss, word [_ss]
    mov fs, word [_fs]
    mov gs, word [_gs]
    push word [_flags]
    push word [_cs]
    push word [_ip]
    push dword [_ret_addr]
    mov ds, word [_ds]
    o32 ret
_set_int:
    cli
    xor ax, ax                ; AX = 0
    mov es, ax                ; ES = 0
    mov ax, word[esp+8]
    mov ecx, dword[esp+12]
    shl ecx, 2
    mov word[es:ecx], ax      ; 设置中断向量的偏移地址
    mov ax, word[esp+4]
    mov word[es:ecx+2], ax    ; 设置中断向量的段地址
    sti
    o32 ret
_clock:
    call dword _save
    dec dword[_count]         ; 递减计数变量
    jnz _clock_end            ; >0：跳转
    call dword clock
    mov dword[_count], _delay ; 重置计数变量=初值delay
_clock_end:
    mov al, 20h               ; AL = EOI
    out 20h, al               ; 发送EOI到主8529A
    out 0A0h, al              ; 发送EOI到从8529A
    call dword _restart
    iret                      ; 从中断返回
_ouch:
    call dword _save
    in al, 60h
    pushf
    pushf
    pop ax
    and ah, 0b11111100
    push ax
    popf
    call _int_9_cs:_int_9_ip
    cmp dword[_press], 0
    jz _ouch_end
    mov dword[ouch_color], 0b11100100
    push dword [lyfnheader]
    push dword 4
    push dword _clock_ouch
    push dword 0x800
    call dword new_layfun
    add esp, 16
_ouch_end:
    xor dword[_press], 0xffff
    mov al, 20h               ; AL = EOI
    out 20h, al               ; 发送EOI到主8529A
    out 0A0h, al              ; 发送EOI到从8529A
    call dword _restart
    iret                      ; 从中断返回
_int_20h:
    add sp, 4
    pop word bx
    mov sp, word [0x2e]
    mov ss, word [0x30]
    mov ax, 0x800
    mov ds, ax
    push bx
    push 0x800
    push word _after_user_ret
    iret
_int_21h:
    call dword _save
    cmp ah, 0x2a
    jz _int_21h_2ah
    cmp ah, 0x2c
    jz _int_21h_2ch
    cmp ah, 0x63
    jz _int_21h_63h
;    cmp ah, 0x64
;    jz _int_21h_64h
_int_21h_2ah:
    mov ch, 0
    mov cl, byte [_year]
    mov dh, byte [_month]
    mov dl, byte [_day]
    mov byte [_cx], cl
    mov word [_dx], dx
    jmp _int_21h_end
_int_21h_2ch:
    mov ch, byte [_hour]
    mov cl, byte [_minute]
    mov dh, byte [_second]
    mov dl, 0
    mov word [_cx], cx
    mov word [_dx], dx
    jmp _int_21h_end
_int_21h_63h:
    push dword [lyfnheader]
    push dword ecx
    push dword ebx
    push word 0
    push word es
    call dword new_layfun
    add esp, 16
    mov dword [_ax], eax
    jmp _int_21h_end
;_int_21h_64h:
;    mov esp, 0xefff
;    push dword [lyheader]
;    push word 0
;    push word dx
;    push word 0
;    sub esp, 1
;    mov byte [esp], 0
;    sub esp, 1
;    mov byte [esp], cl
;    push word 0
;    sub esp, 1
;    mov byte[esp], 0
;    sub esp, 1
;    mov byte [esp], ch
;    push dword ebx
;    push word 0
;    push word es
;    call dword new_layer
;    add esp, 24
;    mov dword [_ax], eax
;    jmp _int_21h_end
_int_21h_end:
    call dword _restart
    iret
_int_22h:
    call dword _save
    push dword 0007h
    push dword 24
    push dword 0
    push dword _int_22h_str
    call dword display_str
    add esp, 16
    call dword _restart
    iret
_data_define:
    _count dd _delay          ; 计时器计数变量，初值=delay
    _press dd 0
_time:
    _year db 0
    _month db 0
    _day db 0
    _hour db 0
    _minute db 0
    _second db 0
_register:
    _ax dd 0
    _bx dd 0
    _cx dd 0
    _dx dd 0
    _sp dd 0
    _bp dd 0
    _si dd 0
    _di dd 0
    _ip dw 0
    _flags dw 0
    _es dw 0
    _cs dw 0
    _ss dw 0
    _ds dw 0
    _fs dw 0
    _gs dw 0
_ret_addr: dd 0
_int_22h_str: db 'int 22h', 0
_delay equ 4
_int_9_cs equ 0xf000
_int_9_ip equ 0xe987