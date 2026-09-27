.MODEL small
.STACK 100

.DATA
 msg db 'labas, pasauli!', 0Dh, 0Ah, '$'

 .CODE
start:
 mov ax, @DATA
 mov ds, ax

 mov ah, 9
 mov dx, offset msg
 int 21h

 mov ax, 4C00h
end start
