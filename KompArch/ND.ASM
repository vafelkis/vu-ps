.model small
.stack 100h

.data
    msg_prompt  db 'Type something and press Enter: $'
    msg_result  db 13, 10, 'Result: $'
    buffer      db 100 dup(0)

.code
main proc
    mov ax, @data
    mov ds, ax

    mov dx, offset msg_prompt
    mov ah, 09h
    int 21h

    mov si, offset buffer
    mov di, 0

read_loop:
    mov ah, 01h
    int 21h

    cmp al, 13
    je print_result

    mov [si], al
    inc si
    inc di
    jmp read_loop

print_result:
    mov dx, offset msg_result
    mov ah, 09h
    int 21h

    cmp di, 0
    je exit_program

    mov si, offset buffer
    mov bx, di

process_chars:
    push bx
    mov bl, [si]

    mov cx, 8
bit_loop:
    shl bl, 1
    jc print_one

    mov dl, '0'
    jmp display_bit

print_one:
    mov dl, '1'

display_bit:
    mov ah, 02h
    int 21h
    loop bit_loop

    mov dl, ' '
    mov ah, 02h
    int 21h

    inc si
    pop bx
    dec bx
    jnz process_chars

exit_program:
    mov ax, 4C00h
    int 21h
main endp
end main