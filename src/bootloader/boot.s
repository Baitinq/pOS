; Multiboot header
MBALIGN  equ  1 << 0
MEMINFO  equ  1 << 1
FLAGS    equ  MBALIGN | MEMINFO
MAGIC    equ  0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)
 
section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM
 
; Setup stack
section .bss
align 16
stack_bottom:
resb 16384 ; 16 KiB
stack_top:
 
section .text
global _start:function (_start.end - _start)
_start:
	; Initialize stack
	mov esp, stack_top
 
	extern kmain
	call kmain
 
	cli
.inf:	hlt
	jmp .inf
.end:

%include "utils/isrs.s"
%include "utils/irq.s"
