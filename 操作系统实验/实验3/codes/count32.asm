; Disassembly of file: count32.o
; Mon May 11 19:20:56 2020
; Mode: 32 bits
; Syntax: YASM/NASM
; Instruction set: 80386


global ccount: function
global count: function


SECTION .text   align=1 execute                         ; section number 1, code

ccount: ; Function begin
        push    ebp                                     ; 0000 _ 55
        mov     ebp, esp                                ; 0001 _ 89. E5
        sub     esp, 16                                 ; 0003 _ 83. EC, 10
; Note: Length-changing prefix causes delay on Intel processors
        mov     word [ebp-2H], 0                        ; 0006 _ 66: C7. 45, FE, 0000
        jmp     ?_002                                   ; 000C _ EB, 09

?_001:  mov     ax, word [ebp-2H]                       ; 000E _ 66: 8B. 45, FE
        inc     eax                                     ; 0012 _ 40
        mov     word [ebp-2H], ax                       ; 0013 _ 66: 89. 45, FE
?_002:  movsx   edx, word [ebp-2H]                      ; 0017 _ 0F BF. 55, FE
        mov     eax, dword [ebp+8H]                     ; 001B _ 8B. 45, 08
        add     eax, edx                                ; 001E _ 01. D0
        mov     al, byte [eax]                          ; 0020 _ 8A. 00
        test    al, al                                  ; 0022 _ 84. C0
        jnz     ?_001                                   ; 0024 _ 75, E8
        mov     ax, word [ebp-2H]                       ; 0026 _ 66: 8B. 45, FE
        leave                                           ; 002A _ C9
        ret                                             ; 002B _ C3
; ccount End of function

count:  ; Function begin
        push    ebp                                     ; 002C _ 55
        mov     ebp, esp                                ; 002D _ 89. E5
        sub     esp, 16                                 ; 002F _ 83. EC, 10
        push    dword [ebp+8H]                          ; 0032 _ FF. 75, 08
        call    ccount                                  ; 0035 _ E8, FFFFFFFC(rel)
        add     esp, 4                                  ; 003A _ 83. C4, 04
        cwde                                            ; 003D _ 98
        mov     dword [ebp-8H], eax                     ; 003E _ 89. 45, F8
        mov     eax, dword [ebp-8H]                     ; 0041 _ 8B. 45, F8
        inc     eax                                     ; 0044 _ 40
        mov     dword [ebp-4H], eax                     ; 0045 _ 89. 45, FC
        mov     eax, dword [ebp-4H]                     ; 0048 _ 8B. 45, FC
        leave                                           ; 004B _ C9
        ret                                             ; 004C _ C3
; count End of function


SECTION .data   align=1 noexecute                       ; section number 2, data


SECTION .bss    align=1 noexecute                       ; section number 3, bss


SECTION .eh_frame align=4 noexecute                     ; section number 4, const

        db 14H, 00H, 00H, 00H, 00H, 00H, 00H, 00H       ; 0000 _ ........
        db 01H, 7AH, 52H, 00H, 01H, 7CH, 08H, 01H       ; 0008 _ .zR..|..
        db 1BH, 0CH, 04H, 04H, 88H, 01H, 00H, 00H       ; 0010 _ ........
        db 1CH, 00H, 00H, 00H, 1CH, 00H, 00H, 00H       ; 0018 _ ........
        dd ccount-$-20H                                 ; 0020 _ 00000000 (rel)
        dd 0000002CH, 080E4100H                         ; 0024 _ 44 135151872 
        dd 0D420285H, 0CC56805H                         ; 002C _ 222429829 214263813 
        dd 00000404H, 0000001CH                         ; 0034 _ 1028 28 
        dd 0000003CH                                    ; 003C _ 60 
        dd ccount-$-14H                                 ; 0040 _ 0000002C (rel)
        dd 00000021H, 080E4100H                         ; 0044 _ 33 135151872 
        dd 0D420285H, 0CC55D05H                         ; 004C _ 222429829 214260997 
        dd 00000404H                                    ; 0054 _ 1028 


