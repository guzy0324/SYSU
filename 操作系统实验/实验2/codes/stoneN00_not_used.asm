     ; 程序源代码（stone.asm）
     ; 本程序在文本方式显示器上从左边射出学号姓名,以45度向右下运动，撞到边框后反射,如此类推.
     ; 谷正阳 2020/4
     ; NASM汇编格式
     Dn_Rt equ 1         ; D-Down,U-Up,R-right,L-Left
     Up_Rt equ 2
     Up_Lt equ 3
     Dn_Lt equ 4
     delay equ 50000     ; 计时器延迟计数,用于控制画框的速度
     ddelay equ 580      ; 计时器延迟计数,用于控制画框的速度
                         ; .386
     left	equ -1         ; 左边界
     right	equ	40       ; 右边界
     top	equ	-1         ; 上边界
     bottom	equ	13       ; 下边界
     org 07c00h          ; 程序加载到100h，可用于生成COM/7c00H引导扇区程序
                         ; ASSUME cs:code,ds:code
                         ; code SEGMENT
start:
    ; xor ax,ax					; AX = 0   程序加载到0000：100h才能正确执行
    mov cl,0
    mov dx,string
    mov ax,cs
    mov es,ax            ; ES = 0
    mov ds,ax            ; DS = CS
    mov es,ax            ; ES = CS
    mov ax,0B800h        ; 文本窗口显存起始地址
    mov es,ax            ; GS = B800h
loop1:
    dec word[count]      ; 递减计数变量
    jnz loop1            ; >0：跳转;
    mov word[count],delay
    dec word[dcount]     ; 递减计数变量
    jnz loop1
    mov word[count],delay
    mov word[dcount],ddelay

    mov al,1             ; 类似switch(rdul) case 1 case 2 case 3 case 4
    cmp al,byte[rdul]
    jz  DnRt
      mov al,2
      cmp al,byte[rdul]
    jz  UpRt
      mov al,3
      cmp al,byte[rdul]
    jz  UpLt
      mov al,4
      cmp al,byte[rdul]
    jz  DnLt
      jmp $

DnRt:
    inc word[x]
    inc word[y]
    mov bx,word[x]
    mov ax,right
    sub ax,bx
      jz  dr2ur          ; if x == right: x = right - 2, rudl = Up_Rt
    mov bx,word[y]
    mov ax,bottom
    sub ax,bx
      jz  dr2dl          ; if y == bottom: y = bottom - 2, rudl = Dn_Lt
    jmp show
dr2ur:
      sub word[x],2
      mov byte[rdul],Dn_Lt
      jmp show
dr2dl:
      sub word[y],2
      mov byte[rdul],Up_Rt
      jmp show

UpRt:
    inc word[x]
    dec word[y]
    mov bx,word[x]
    mov ax,right
    sub ax,bx
      jz  ur2ul
    mov bx,word[y]
    mov ax,top
    sub ax,bx
      jz  ur2dr
    jmp show
ur2ul:
      sub word[x],2
      mov byte[rdul],Up_Lt
      jmp show
ur2dr:
      add word[y],2
      mov byte[rdul],Dn_Rt
      jmp show

UpLt:
    dec word[x]
    dec word[y]
    mov bx,word[x]
    mov ax,left
    sub ax,bx
      jz  ul2dl
    mov bx,word[y]
    mov ax,top
    sub ax,bx
      jz  ul2ur
    jmp show
ul2dl:
      add word[x],2
      mov byte[rdul],Up_Rt
      jmp show
ul2ur:
      add word[y],2
      mov byte[rdul],Dn_Lt
      jmp show

DnLt:
    dec word[x]
    inc word[y]
    mov bx,word[x]
    mov ax,left
    sub ax,bx
      jz  dl2dr
    mov bx,word[y]
    mov ax,bottom
    sub ax,bx
      jz  dl2ul
    jmp show
dl2dr:
      add word[x],2
      mov byte[rdul],Dn_Rt
      jmp show
dl2ul:
      sub word[y],2
      mov byte[rdul],Up_Lt
      jmp show

show:
      xor ax,ax          ; 计算显存地址
      mov ax,word[y]
    mov bx,80
    mul bx               ; ax = 80 * y
    add ax,word[x]       ; ax = 80 * y + x
    mov bx,2
    mul bx               ; ax = 2 * (80 * y + x)
    mov bx,ax            ; bx = 2 * (80 * y + x)
    mov ah,cl            ; 0000：黑底、1111：亮白字（默认值为07h）
    mov dx,bx            ; dx = bx
    mov bx,cx            ; bx = cl
    mov al,[string+bx]   ; AL = 显示字符值（默认值为20h=空格符）
    mov bx,dx            ; bx = dx
    add cl,1             ; cl += 1
    cmp cl, 13
    je a                 ; if cl == 13: cl = 0

nxt:
    mov [es:bx],ax       ; 显示字符的ASCII码值
    jmp loop1

a:
    mov cl,0
    jmp nxt

end:
    jmp $                ; 停止画框，无限循环

datadef:
    count dw delay
    dcount dw ddelay
    rdul db Dn_Rt        ; 向右下运动
    x    dw 0 + left
    y    dw 0 + top      ; 初始位置
    string db ' 18308045_gzy',0
    ; code ENDS
    ; END start
times 510-($-$$) db 0
db 0x55,0xaa