# uint32_t crc32_8(uint32_t crc, const void *p_data, size_t count)
# crc is in %rcx
# p_data is in %rdx
# count is in %r8
.global crc32_8
.section .text
crc32_8:
	crc32b (%rdx), %rax
	ret
