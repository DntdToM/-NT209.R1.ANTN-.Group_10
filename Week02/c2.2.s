.section .data
    newline: .byte 10
    noti: .string "Enter a number (2-digit): "
    len_noti = . - noti - 1

    noti1: .string "Reminder: "
    len_noti1 = . - noti1 - 1

.section .bss
    .lcomm input, 3
    .lcomm res, 1
    .lcomm sum, 4

.section .text
    .globl _start

_start:
    movl $0, sum
    movl $0, %ecx

.L1:
    cmpl $4, %ecx 
    jge .Done

    pushl %ecx

    // in dong bao nhap
    movl $4, %eax
    movl $1, %ebx
    movl $noti, %ecx
    movl $len_noti, %edx
    int $0x80

    // nhap so
    movl $3, %eax
    movl $0, %ebx
    movl $input, %ecx
    movl $3, %edx
    int $0x80

    // chuyen chuoi thanh so va cong vao sum
    // sao chep so 1 byte sang 4 byte, 'z' = chen so 0 o dau
    movzbl input, %eax
    subb $'0', %al
    imull $10, %eax
    movzbl input+1, %ebx
    subb $'0', %bl
    addl %ebx, %eax

    addl %eax, sum

    popl %ecx
    incl %ecx
    jmp .L1

.Done:
    // chia sum cho 8 lay phan du (%edx)
    movl sum, %eax
    xorl %edx, %edx
    movl $8, %ecx
    divl %ecx

    // chuyen phan du sang ky tu
    addb $'0', %dl 
    movb %dl, res

    // xuat
    movl $4, %eax
    movl $1, %ebx
    movl $noti1, %ecx
    movl $len_noti1, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    movl $res, %ecx
    movl $1, %edx
    int $0x80

    // ket thuc
    movl $4, %eax
    movl $1, %ebx
    movl $newline, %ecx
    movl $1, %edx
    int $0x80

    movl $1, %eax
    int $0x80

// as --32 -o c2.2.o c2.2.s | ld -m elf_i386 -o c2.2 c2.2.o
