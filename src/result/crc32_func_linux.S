# uint32_t crc32_8(uint32_t crc, const void *p_data, size_t count)
# crc is in %rdi
# p_data is in %rsi
# count is in %rdx
.global crc32_8
.section .text
crc32_8:
	crc32b (%rsi), %rax
	ret
