BITS 16
extern main
extern clock_wallpaper
global _start
global _clock_wallpaper
global _new_layfun
global _get_time
global _time
_start:
    call dword main
    retf
_clock_wallpaper:
    mov eax, dword [esp + 4]
    push dword eax
    call dword clock_wallpaper
    add esp, 4
    retf
_new_layfun:
    mov ax, word [esp + 4]
    mov es, ax
    mov edx, ebx
    mov ebx, dword [esp + 8]
    mov ecx, dword [esp + 12]
    mov ah, 63h
    int 21h
    mov ebx, edx
    o32 ret
_get_time:
    mov ah, 2ah
    int 21h
    mov byte [_year], cl
    mov byte [_month], dh
    mov byte [_day], dl
    mov ah, 2ch
    int 21h
    mov byte [_hour], ch
    mov byte [_minute], cl
    mov byte [_second], dh
    o32 ret
_time:
    _year db 0
    _month db 0
    _day db 0
    _hour db 0
    _minute db 0
    _second db 0