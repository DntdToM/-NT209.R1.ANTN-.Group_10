.section .data
    nhap: .string "Nhap nam sinh (4 ky tu): "
    l_nhap = . - nhap - 1

    yes: .string "Thuoc Doan TN"
    l_yes = . - yes - 1

    no: .string "Khong thuoc Doan TN"
    l_no = . - no - 1

    tuoi: .string "Tuoi: "
    l_tuoi = . - tuoi - 1

    newline: .byte 10

.section .bss
    .lcomm input, 5
    .lcomm res, 2

.section .text
    .globl _start

_start:
    // in "Nhap"
    movl $4, %eax
    movl $1, %ebx
    movl $nhap, %ecx
    movl $l_nhap, %edx
    int $0x80

    // Nhap so 
    movl $3, %eax
    movl $0, %ebx
    movl $input, %ecx
    movl $5, %edx
    int $0x80

    // chuyen chuoi 4 ky tu thanh nam sinh
    movzbl input, %eax
    subb $'0', %al
    imull $1000, %eax
    movzbl input+1, %ebx
    subb $'0', %bl
    imull $100, %ebx
    addl %ebx, %eax
    movzbl input+2, %ebx
    subb $'0', %bl
    imull $10, %ebx
    addl %ebx, %eax
    movzbl input+3, %ebx
    subb $'0', %bl
    addl %ebx, %eax

    // tinh tuoi = 2026 - nam sinh
    movl $2026, %ecx
    subl %eax, %ecx

    // tach 2 chu so cua tuoi de in
    movl %ecx, %eax
    xorl %edx, %edx
    movl $10, %ebx
    divl %ebx

    addb $'0', %al
    addb $'0', %dl 

    movb %al, res
    movb %dl, res+1

    // kiem tra do tuoi Doan TN (16 <= tuoi <= 30)
    cmpl $16, %ecx
    jl .No
    cmpl $30, %ecx
    jg .No
    movl $4, %eax
    movl $1, %ebx
    movl $yes, %ecx
    movl $l_yes, %edx
    int $0x80
    jmp .Done

    .No:
    movl $4, %eax
    movl $1, %ebx
    movl $no, %ecx
    movl $l_no, %edx
    int $0x80

    .Done:
    // in xuong dong va in tuoi
    movl $4, %eax
    movl $1, %ebx
    movl $newline, %ecx
    movl $1, %edx
    int $0x80

    movl $4, %eax
    movl $1, %ebx
    movl $tuoi, %ecx
    movl $l_tuoi, %edx
    int $0x80   

    movl $4, %eax
    movl $1, %ebx
    movl $res, %ecx
    movl $2, %edx
    int $0x80

    // Ket thuc
    movl $4, %eax
    movl $1, %ebx
    movl $newline, %ecx
    movl $1, %edx
    int $0x80

    movl $1, %eax
    int $0x80

// as --32 -o c2.5.o c2.5.s | ld -m elf_i386 -o c2.5 c2.5.o
