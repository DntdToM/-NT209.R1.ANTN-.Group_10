.section .data
noti: .string "Enter a number (2-digit): "
noti_len: .int (. - noti - 1)

noti1: .string "Reminder: "
len_noti1: .int (. - noti1 - 1)

newline: .string "\n"

.section .bss
    .lcomm str, 4
    .lcomm res, 4
    .lcomm cnt, 1

.section .text
    .global _start

_start:
    movl $0, res
    movb $4, cnt

L1:
    cmpb $0, cnt
    jle End
    decb cnt

    # In thong bao
    movl $4, %eax
    movl $1, %ebx
    movl $noti, %ecx
    movl noti_len, %edx
    int $0x80

    # Nhap so 2-digit
    movl $3, %eax
    movl $0, %ebx
    movl $str, %ecx
    movl $3, %edx
    int $0x80

    # Logic cong 2 so vao bien res
    movzbl str, %eax
    addl %eax, %eax
    movzbl str+1, %ebx
    addl %ebx, %eax
    addl %eax, res

    jmp L1

End:
    # Chia du cho 8
    andl $7, res
    addl $48, res

    # In ra chuoi Reminder:
    movl $4, %eax
    movl $1, %ebx
    movl $noti1, %ecx
    movl $len_noti1, %edx
    int $0x80

    # In ra ket qua
    movl $4, %eax
    movl $1, %ebx
    movl $res, %ecx
    movl $1, %edx
    int $0x80

    # Them ki tu xuong dong
    movl $4, %eax
    movl $1, %ebx
    movl $newline, %ecx
    movl $1, %edx
    int $0x80

    movl $1, %eax
    xorl %ebx, %ebx
    int $0x80
