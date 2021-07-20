; Disassembly of file: upper32.o
; Thu May 14 21:56:59 2020
; Mode: 32 bits
; Syntax: YASM/NASM
; Instruction set: 80386


global upper: ;function
global Message


SECTION .text   align=1 ;execute                         ; section number 1, code

upper:  ; Function begin
        push    ebp                                     ; 0000 _ 55
        mov     ebp, esp                                ; 0001 _ 89. E5
        sub     esp, 4                                  ; 0003 _ 83. EC, 04
        mov     dword [ebp-4H], 0                       ; 0006 _ C7. 45, FC, 00000000
        jmp     ?_003                                   ; 000D _ EB, 38

?_001:  mov     eax, dword [ebp-4H]                     ; 000F _ 8B. 45, FC
        add     eax, Message                            ; 0012 _ 05, 00000000(d)
        mov     al, byte [eax]                          ; 0017 _ 8A. 00
        cmp     al, 96                                  ; 0019 _ 3C, 60
        jle     ?_002                                   ; 001B _ 7E, 27
        mov     eax, dword [ebp-4H]                     ; 001D _ 8B. 45, FC
        add     eax, Message                            ; 0020 _ 05, 00000000(d)
        mov     al, byte [eax]                          ; 0025 _ 8A. 00
        cmp     al, 122                                 ; 0027 _ 3C, 7A
        jg      ?_002                                   ; 0029 _ 7F, 19
        mov     eax, dword [ebp-4H]                     ; 002B _ 8B. 45, FC
        add     eax, Message                            ; 002E _ 05, 00000000(d)
        mov     al, byte [eax]                          ; 0033 _ 8A. 00
        sub     eax, 32                                 ; 0035 _ 83. E8, 20
        mov     dl, al                                  ; 0038 _ 88. C2
        mov     eax, dword [ebp-4H]                     ; 003A _ 8B. 45, FC
        add     eax, Message                            ; 003D _ 05, 00000000(d)
        mov     byte [eax], dl                          ; 0042 _ 88. 10
?_002:  inc     dword [ebp-4H]                          ; 0044 _ FF. 45, FC
?_003:  mov     eax, dword [ebp-4H]                     ; 0047 _ 8B. 45, FC
        add     eax, Message                            ; 004A _ 05, 00000000(d)
        mov     al, byte [eax]                          ; 004F _ 8A. 00
        test    al, al                                  ; 0051 _ 84. C0
        jnz     ?_001                                   ; 0053 _ 75, BA
        nop                                             ; 0055 _ 90
        leave                                           ; 0056 _ C9
        ret                                             ; 0057 _ C3
; upper End of function


SECTION .data   align=4 ;noexecute                       ; section number 2, data

Message:                                                ; tbyte
        db 41H, 61H, 42H, 62H, 43H, 63H, 44H, 64H       ; 0000 _ AaBbCcDd
        db 45H, 65H                                     ; 0008 _ Ee


SECTION .bss    align=1 ;noexecute                       ; section number 3, bss


SECTION .eh_frame align=4 ;noexecute                     ; section number 4, const

        db 14H, 00H, 00H, 00H, 00H, 00H, 00H, 00H       ; 0000 _ ........
        db 01H, 7AH, 52H, 00H, 01H, 7CH, 08H, 01H       ; 0008 _ .zR..|..
        db 1BH, 0CH, 04H, 04H, 88H, 01H, 00H, 00H       ; 0010 _ ........
        db 1CH, 00H, 00H, 00H, 1CH, 00H, 00H, 00H       ; 0018 _ ........
        dd upper-$-20H                                  ; 0020 _ 00000000 (rel)
        dd 00000058H, 080E4100H                         ; 0024 _ 88 135151872 
        dd 0D420285H, 0C5540205H                        ; 002C _ 222429829 -984350203 
        dd 0004040CH                                    ; 0034 _ 263180 


