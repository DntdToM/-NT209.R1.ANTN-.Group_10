.section .data
    entX: .string "Enter x: "
    l_entX = . - entX - 1

    entY: .string "Enter y: "
    l_entY = . - entY - 1

    dp: .string "Count 10x: "
    l_dp = . - dp - 1

    newline: .byte 10

    cnt: .long 0

.section .bss
    .lcomm input, 3
    .lcomm st, 4
    .lcomm en, 4

.section .text
    .globl _start

_start:
    // nhap x
    movl $4, %eax
    movl $1, %ebx
    movl $entX, %ecx
    movl $l_entX, %edx
    int $0x80

    movl $3, %eax
    movl $0, %ebx
    movl $input, %ecx
    movl $3, %edx
    int $0x80

    // chuyen chuoi x thanh so
    movzbl input, %eax
    subb $'0', %al
    imull $10, %eax
    movzbl input+1, %ebx
    subb $'0', %bl
    addl %ebx, %eax

    movl %eax, st

    // nhap y
    movl $4, %eax
    movl $1, %ebx
    movl $entY, %ecx
    movl $l_entY, %edx
    int $0x80

    movl $3, %eax
    movl $0, %ebx
    movl $input, %ecx
    movl $3, %edx
    int $0x80

    // chuyen chuoi y thanh so
    movzbl input, %eax
    subb $'0', %al
    imull $10, %eax
    movzbl input+1, %ebx
    subb $'0', %bl
    addl %ebx, %eax

    movl %eax, en

    // while (st <= en), out <=> st > en
    movl st, %ecx

    .L: 
        cmpl %ecx, en
        jl .Done

        pushl %ecx

        // kiem tra chia het cho 10
        movl %ecx, %eax
        xorl %edx, %edx
        movl $10, %ecx
        divl %ecx # phan du = %edx

        popl %ecx
        incl %ecx

        cmpl $0, %edx
        jne .L

        incl cnt 
        jmp .L

    .Done:
        // chuyen cnt thanh ky tu
        addl $'0', cnt

        // in ket qua
        movl $4, %eax
        movl $1, %ebx
        movl $dp, %ecx
        movl $l_dp, %edx
        int $0x80

        movl $4, %eax
        movl $1, %ebx
        movl $cnt, %ecx
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

// as --32 -o c2.4.o c2.4.s | ld -m elf_i386 -o c2.4 c2.4.o
