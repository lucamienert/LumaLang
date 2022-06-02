.data
i: .int 0
i_str: .ascii "0"
i_str_len = .- i_str
text1: .ascii "Hello world"
text1_len = .- text1
.bss
.text
.global _start
_start:
call main
mov %eax, %ebx
mov $1, %eax
int $0x80

.global test
test:
mov $4, %eax
mov $1, %ebx
mov $param_str , %ecx
mov $param_str_len, %edx
int $0x80
ret
.global main
main:
call test
mov $4, %eax
mov $1, %ebx
mov $text1, %ecx
mov $text1_len, %edx
int $0x80
mov $0, %eax
ret
