gdt_start:
  gdt_null:
  dq 0

  gdt_code:
  dw 0FFFFh
  dw 0

  db 0
  db 10011010b
  db 11001111b
  db 0

  gdt_data:
  dw 0FFFFh
  dw 0

  db 0
  db 10010010b
  db 11001111b
  db 0

  gdt_end:

  gdt:
   dw gdt_end - gdt_start - 1
   dd gdt_start

load_GDT:
    cli
    lgdt [gdt]
    sti
    ret
