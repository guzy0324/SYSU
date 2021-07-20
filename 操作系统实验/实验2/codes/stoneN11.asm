    ; 程序源代码（stoneN11.asm）
    ; 本程序在文本方式显示器上从左边射出学号姓名,以45度向右下运动，撞到边框后反射,如此类推.
    ; 谷正阳 2020/4
    ; NASM汇编格式
    Lt equ 0                ; direction: left
    Rt equ 1                ; direction: right
    Up equ 0                ; direction: Up
    Dn equ 1                ; direction: Down
    delay equ 50000         ; 计时器延迟计数,用于控制画框的速度
    ddelay equ 580          ; 计时器延迟计数,用于控制画框的速度
    cmax equ 100            ; 输出最大字符数
                            ; .386
    left equ 39             ; 左边界
    right equ 80            ; 右边界
    top equ 12              ; 上边界
    bottom equ 25           ; 下边界
                            ; org 07c00h           ; 程序加载到100h，可用于生成COM/7c00H引导扇区程序
                            ; ASSUME cs:code,ds:code
                            ; code SEGMENT
    org 100h

Cls:
    mov ah,6
    mov al,0
    mov cx,0
    mov dx,0xffff
    int 10h                 ; cls

start:
    ; xor ax,ax		       ; AX = 0   程序加载到0000：100h才能正确执行
    mov cl,0
    mov dx,string
    mov ax,cs
    mov es,ax               ; ES = 0
    mov ds,ax               ; DS = CS
    mov es,ax               ; ES = CS
    mov ax,0B800h           ; 文本窗口显存起始地址
    mov es,ax               ; GS = B800h
loop1:
    dec word[count]         ; 递减计数变量
    jnz loop1               ; >0：跳转;
    mov word[count],delay
    dec word[dcount]        ; 递减计数变量
    jnz loop1
    mov word[count],delay
    mov word[dcount],ddelay
    cmp byte[ccount], 0
    jz end
    dec byte[ccount]
drx:
    cmp byte[dirx],Rt
    jz  rt                  ; if dirx == Rt goto rt
lt:
    dec word[x]             ; else x--
    cmp word[x],left
    jnz dry                 ; if x != left goto dry
    add word[x],2           ; else x += 2
    mov byte[dirx],Rt       ; dirx = Rt
    jmp dry                 ; goto dry
rt:
    inc word[x]             ; x++
    cmp word[x],right
    jnz dry                 ; if x != right goto dry
    sub word[x],2           ; else x -= 2
    mov byte[dirx],Lt       ; dirx = Lt
dry:
    cmp byte[diry],Dn
    jz  dn                  ; if diry == Dn goto dn
up:
    dec word[y]             ; else y--
    cmp word[y],top
    jnz show                ; if y != top goto show
    add word[y],2           ; else y += 2
    mov byte[diry],Dn       ; diry = Dn
    jmp show                ; goto show
dn:
    inc word[y]             ; y++
    cmp word[y],bottom
    jnz show                ; if y != bottom goto show
    mov byte[diry],Up       ; diry = Up
    sub word[y],2           ; else y -= 2

show:
    xor ax,ax               ; 计算显存地址
    mov ax,word[y]
    mov bx,80
    mul bx                  ; ax = 80 * y
    add ax,word[x]          ; ax = 80 * y + x
    mov bx,2
    mul bx                  ; ax = 2 * (80 * y + x)
    mov bx,ax               ; bx = 2 * (80 * y + x)
    mov ah,cl               ; 0000：黑底、1111：亮白字（默认值为07h）
    mov dx,bx               ; dx = bx
    mov bx,cx               ; bx = cl
    mov al,[string+bx]      ; AL = 显示字符值（默认值为20h=空格符）
    mov bx,dx               ; bx = dx
    add cl,1                ; cl += 1
    cmp cl, 13
    je a                    ; if cl == 13: cl = 0

nxt:
    mov [es:bx],ax          ; 显示字符的ASCII码值
    jmp loop1

a:
    mov cl,0
    jmp nxt

end:
    ; jmp $                ; 停止画框，无限循环
    retf

datadef:
    count dw delay
    dcount dw ddelay
    dirx db Rt
    diry db Dn              ; 向右下运动
    x    dw 0 + left
    y    dw 0 + top         ; 初始位置
    string db ' 18308045_gzy',0
    ccount db cmax
    ; code ENDS
    ; END start
times 510-($-$$) db 0
db 0x55,0xaa