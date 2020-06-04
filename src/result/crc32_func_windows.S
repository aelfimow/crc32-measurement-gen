# uint32_t crc32_8(uint32_t crc_iv, const void *p_data, size_t count)
# crc_iv is in %rcx
# p_data is in %rdx
# count is in %r8
# output crc is in %rax
# temporary register is %r9
.global crc32_8
.section .text
crc32_8:
	mov %rcx, %rax
	mov $0x0000000000000001, %r9
crc32_8_start:
	test %r8, %r8
	jz crc32_8_end
	crc32b (%rdx), %eax
	add %r9, %rdx
	dec %r8
	jmp crc32_8_start
crc32_8_end:
	ret
# uint32_t crc32_16(uint32_t crc_iv, const void *p_data, size_t count)
# crc_iv is in %rcx
# p_data is in %rdx
# count is in %r8
# output crc is in %rax
# temporary register is %r9
.global crc32_16
.section .text
crc32_16:
	mov %rcx, %rax
	mov $0x0000000000000002, %r9
crc32_16_start:
	test %r8, %r8
	jz crc32_16_end
	crc32w (%rdx), %eax
	add %r9, %rdx
	dec %r8
	jmp crc32_16_start
crc32_16_end:
	ret
# uint32_t crc32_32(uint32_t crc_iv, const void *p_data, size_t count)
# crc_iv is in %rcx
# p_data is in %rdx
# count is in %r8
# output crc is in %rax
# temporary register is %r9
.global crc32_32
.section .text
crc32_32:
	mov %rcx, %rax
	mov $0x0000000000000004, %r9
crc32_32_start:
	test %r8, %r8
	jz crc32_32_end
	crc32l (%rdx), %eax
	add %r9, %rdx
	dec %r8
	jmp crc32_32_start
crc32_32_end:
	ret
# uint32_t crc32_64(uint32_t crc_iv, const void *p_data, size_t count)
# crc_iv is in %rcx
# p_data is in %rdx
# count is in %r8
# output crc is in %rax
# temporary register is %r9
.global crc32_64
.section .text
crc32_64:
	mov %rcx, %rax
	mov $0x0000000000000008, %r9
crc32_64_start:
	test %r8, %r8
	jz crc32_64_end
	crc32q (%rdx), %rax
	add %r9, %rdx
	dec %r8
	jmp crc32_64_start
crc32_64_end:
	ret
