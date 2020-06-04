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
	crc32b (%rdx), %rax
	add %r9, %rdx
	dec %r8
	jmp crc32_8_start
crc32_8_end:
	ret
