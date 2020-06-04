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
	crc32b (%rsi), %eax
	add %rcx, %rsi
	dec %rdx
	jmp crc32_8_start
crc32_8_end:
	ret
# uint32_t crc32_16(uint32_t crc_iv, const void *p_data, size_t count)
# crc_iv is in %rdi
# p_data is in %rsi
# count is in %rdx
# output crc is in %rax
# temporary register is %rcx
.global crc32_16
.section .text
crc32_16:
	mov %rdi, %rax
	mov $0x0000000000000002, %rcx
crc32_16_start:
	test %rdx, %rdx
	jz crc32_16_end
	crc32w (%rsi), %eax
	add %rcx, %rsi
	dec %rdx
	jmp crc32_16_start
crc32_16_end:
	ret
# uint32_t crc32_32(uint32_t crc_iv, const void *p_data, size_t count)
# crc_iv is in %rdi
# p_data is in %rsi
# count is in %rdx
# output crc is in %rax
# temporary register is %rcx
.global crc32_32
.section .text
crc32_32:
	mov %rdi, %rax
	mov $0x0000000000000004, %rcx
crc32_32_start:
	test %rdx, %rdx
	jz crc32_32_end
	crc32l (%rsi), %eax
	add %rcx, %rsi
	dec %rdx
	jmp crc32_32_start
crc32_32_end:
	ret
# uint32_t crc32_64(uint32_t crc_iv, const void *p_data, size_t count)
# crc_iv is in %rdi
# p_data is in %rsi
# count is in %rdx
# output crc is in %rax
# temporary register is %rcx
.global crc32_64
.section .text
crc32_64:
	mov %rdi, %rax
	mov $0x0000000000000008, %rcx
crc32_64_start:
	test %rdx, %rdx
	jz crc32_64_end
	crc32q (%rsi), %rax
	add %rcx, %rsi
	dec %rdx
	jmp crc32_64_start
crc32_64_end:
	ret
