.section .data
    noti: .string "Enter a year (4-digits): "
    noti_len: .int (. - noti - 1)

    noti1: .string "Nam nhuan\n"
    noti1_len: .int (. - noti1 - 1)

    noti2: .string "Khong phai nam nhuan\n"
    noti2_len: .int (. - noti2 - 1)

    noti3: .string "Nam nhuan ke tiep: "
    noti3_len: .int (. - noti3 - 1)

    noti4_adv: .string "10000\n"
    noti4_len: .int (. - noti4_adv -1)

.section .bss
    .lcomm str, 8
    .lcomm n, 4
    .lcomm i, 4

.section .text
    .global _start

_start:
    movl $0, n       # n = 0
    movl $0, i       # i = 0

    # In thong bao nhap
    movl $4, %eax
    movl $1, %ebx
    movl $noti, %ecx
    movl noti_len, %edx
    int $0x80

    # Nhap so nam 4-digit
    movl $3, %eax
    movl $0, %ebx
    movl $str, %ecx
    movl $5, %edx
    int $0x80

    # Logic luu so vao bien n (string -> int)
    movzbl str, %eax
    subl $48, %eax
    imull $1000, %eax
    addl %eax, n
    
    movzbl str+1, %eax
    subl $48, %eax
    imull $100, %eax
    addl %eax, n

    movzbl str+2, %eax
    subl $48, %eax
    imull $10, %eax
    addl %eax, n

    movzbl str+3, %eax
    subl $48, %eax
    addl %eax, n

.Loop:
    # i = 0, i <= 10, i++
    # Kiem tra nam (n + i) co phai nam nhuan khong
    movl n, %eax
    addl i, %eax
    movl %eax, %ebx     # Luu ban sao cua (n + i) vao %ebx

    # 1. Kiem tra chia het cho 4
    andl $3, %eax
    cmpl $0, %eax
    jne .False          # Khong chia het cho 4 -> Khong phai nam nhuan

    # 2. Kiem tra chia het cho 100 (tuc la chia het cho 25 vi da chia het cho 4)
    movl %ebx, %eax
    xorl %edx, %edx
    movl $25, %ecx
    divl %ecx
    cmpl $0, %edx
    jne .True           # Khong chia het cho 25 -> La nam nhuan

    # 3. Neu chia het cho 100, phai chia het cho 400 (tuc %eax sau khi chia 25 phai chia het cho 16)
    andl $15, %eax
    cmpl $0, %eax
    je .True            # Chia het cho 16 (tuc chia het cho 400) -> La nam nhuan
    jmp .False          # Chia het cho 100 nhung khong chia het cho 400 -> Khong phai nam nhuan

.False:
    cmpl $0, i
    jne .Loop_condition
    
    # In ra chuoi "Khong phai nam nhuan"
    movl $4, %eax
    movl $1, %ebx
    movl $noti2, %ecx
    movl noti2_len, %edx
    int $0x80

    jmp .Loop_condition

.True:
    cmpl $0, i
    jne .Adv_noti

    # In ra chuoi "Nam nhuan"
    movl $4, %eax
    movl $1, %ebx
    movl $noti1, %ecx
    movl noti1_len, %edx
    int $0x80

    jmp .Loop_condition

.Loop_condition:
    incl i
    cmpl $10, i         # 2 nam nhuan lien tiep cach nhau khong qua 8 nam
    jle .Loop

.Adv_noti:
    # In ra chuoi "Nam nhuan ke tiep: "
    movl $4, %eax
    movl $1, %ebx
    movl $noti3, %ecx
    movl noti3_len, %edx
    int $0x80

    cmpl $9996, n       # Re nhanh cho truong hop dac biet
    jge .In10000

    # Tinh va chuyen (n + i) thanh chuoi 4-digit
    movl n, %eax
    addl i, %eax
    movl $str+3, %edi
    movl $10, %ecx

.convert_to_string:
    xorl %edx, %edx
    divl %ecx
    addl $48, %edx
    movb %dl, (%edi)
    decl %edi
    cmpl $str, %edi
    jge .convert_to_string

    # Them ky tu xuong dong vao cuoi chuoi str+4
    movb $10, str+4

    # In ra nam nhuan ke tiep
    movl $4, %eax
    movl $1, %ebx
    movl $str, %ecx
    movl $5, %edx
    int $0x80
    jmp .Exit

.In10000:
    movl $4, %eax
    movl $1, %ebx
    movl $noti4_adv, %ecx
    movl noti4_len, %edx
    int $0x80

.Exit:
    # Thoat chuong trinh
    movl $1, %eax
    xorl %ebx, %ebx
    int $0x80
