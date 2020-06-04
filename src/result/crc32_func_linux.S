# uint32_t crc32_8(uint32_t crc_iv, const void *p_data, size_t count)
# crc_iv is in %rdi
# p_data is in %rsi
# count is in %rdx
# output crc is in %rax
# temporary register is %rcx
.global crc32_8
.section .text
crc32_8:
	mov %rdi, %rax
	mov $0x0000000000000001, %rcx
crc32_8_start:
	test %rdx, %rdx
	jz crc32_8_end
	crc32b (%rsi), %rax
	add %rcx, %rsi
	dec %rdx
	jmp crc32_8_start
crc32_8_end:
	ret
