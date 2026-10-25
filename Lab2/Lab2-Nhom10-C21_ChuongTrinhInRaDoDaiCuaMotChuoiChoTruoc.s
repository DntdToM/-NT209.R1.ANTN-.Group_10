.section .data
msg: .string "Coc Coc"
len: .int (. - msg - 1 + 48)

.section .text
    .global _start

_start:
    # Khoi lenh xuat ket qua bien len ra man hinh
    movl $4, %eax
    movl $1, %ebx
    movl $len, %ecx
    movl $1, %edx
    int $0x80

    movl $1, %eax
    int $0x80    
