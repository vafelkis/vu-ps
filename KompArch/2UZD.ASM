.model tiny
.code
org 100h

start:
    mov si, 81h             ; Command line tail starts at offset 81h
    mov cl, [80h]           ; Get total length of command line tail
    xor ch, ch

    cmp cx, 0               ; Check if length is 0
    je no_args

; Step 1: Skip leading space characters (0x20) and carriage returns (0x0D)
skip_spaces:
    mov al, [si]
    cmp al, 20h             ; Is it a space?
    jne check_cr
    inc si
    loop skip_spaces

check_cr:
    cmp al, 0Dh             ; Is it a carriage return (end of line)?

print_args:
    mov dl, [si]
    cmp dl, 0Dh             ; Stop printing when reaching CR (0x0D)
    je finish

    mov ah, 02h             ; DOS character output function
    int 21h

    inc si
    loop print_args
    jmp finish

finish:
    mov ax, 4C00h           ; Exit program
    int 21h

msg db 'No arguments provided!$'

end start