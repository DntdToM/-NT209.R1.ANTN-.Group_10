.section .data
  prompt: .ascii "Enter some text: "
  prompt_len = . - prompt        # Automatically calculate the length of the prompt
  number: .int 65
.section .bss
  buffer: .space 256              # Reserve 256 bytes of uninitialized memory for the input

.section .text
  .global _start

_start:
  # 1. Print the prompt (sys_write)
  movl $4, %eax                  # System call 4 (sys_write)
  movl $1, %ebx                  # File descriptor 1 (stdout)
  movl $prompt, %ecx             # Pointer to the prompt string
  movl $prompt_len, %edx         # Length of the prompt
  int $0x80                      # Trigger interrupt

  # enter the string 
  movl $3, %eax                  # System call 3 (sys_read)
  movl $0, %ebx                  # File descriptor 0 (stdin)
  movl $buffer, %ecx             # Pointer to our reserved memory buffer
  movl $256, %edx                  # Maximum number of bytes to read
  int $0x80                      # Trigger interrupt

  movl %eax, %esi # get the string size for later process 
  subl $1, %esi # remove the count for enter              
  

  # enter the number 
  movl $3, %eax
  movl $number, %ecx 
  movl $0, %ebx
  movl $1, %edx 
  int $0x80 
  
  # get the real number 
  subl $48,number 



# idea: First, we load the variable to the register. Then we access the bytes, character by character 
# ý tưởng cần làm  nâng cao 2: Size đã có nhập vào, comp cái biến đấy với ecx !
# Có các case  với các ky tu: neu la A-Z thi jump 
#
#
#     if less than 65:
#       stay 
#     if great than 122:
#       stay 
#
#
#     if great than 96: 
#         process a
#     if lower than 90
#        process A


  movl $0, %ecx 

  loop:

  cmpl %esi, %ecx
  je end
  
  movl $0, %ebx 
  movb buffer(,%ecx ,1) , %bl    # lấy character 

  # lớn hơn 122 
  cmpl $122, %ebx  
  
  jg  no 
   

  # nhở hơn 41 
  cmpl $65, %ebx 

  jl no


  cmpl  $97, %ebx 
  jge processa

  cmpl $90, %ebx
  jle processA


  # if reaching here means they are betwwen 90 and 97
  jmp no 

  processA:
  # this part is for  A-Z
   subb $65, %bl     

   addb number, %bl 
   mov $0, %eax
   mov %bl, %al 


   mov $0, %edx
   mov $26, %ebx 
   divl %ebx  

   addl $65, %edx


  # add the  character back !
  movb %dl, buffer(,%ecx ,1) 


  jmp no 

  
   # THis part is for a-z 
  processa:


   subb $97, %bl 

   addb number, %bl 
   mov $0, %eax
   mov %bl, %al 


   mov $0, %edx
   mov $26, %ebx 
   divl %ebx  

   addl $97, %edx

  # add the  character back !
  movb %dl, buffer(,%ecx ,1) 

  no:

  addl $1,%ecx 

  jmp loop 
  
  end:

 
  # 3. Print the modified string!
  movl $4, %eax                  # System call 4 (32-bit sys_write)
  movl $1, %ebx                  # File descriptor 1 (stdout)
  movl $buffer, %ecx             # Pointer to the start of the buffer
  movl %esi, %edx                  # Print 5 bytes (the whole string)
  int $0x80





  # 4. Exit gracefully (sys_exit)
  movl $1, %eax                  # System call 1 (sys_exit)
  movl $0, %ebx                  # Exit status 0
  int $0x80                      # Trigger interrupt
