#ifndef _REG_H_
#define _REG_H_

#include <stdio.h>

struct regs
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;
};



class REG
{
public:
    static void print_regs(regs * r)
    {
        Debug::set_serial_debug(true);

        printf("gs: %i\n", r->gs);
        printf("fs: %i\n", r->fs);
        printf("es: %i\n", r->es);
        printf("ds: %i\n\n", r->ds);

        printf("edi: %i\n", r->edi);
        printf("esi: %i\n", r->esi);
        printf("ebp: %i\n", r->ebp);
        printf("esp: %i\n", r->esp);
        printf("ebx: %i\n", r->ebx);
        printf("edx: %i\n", r->edx);
        printf("ecx: %i\n", r->ecx);
        printf("eax: %i\n\n", r->eax);

        printf("int_no: %i\n", r->int_no);
        printf("err_code: %i\n\n", r->err_code);

        printf("eip: %i\n", r->eip);
        printf("cs: %i\n", r->cs);
        printf("eflags: %i\n", r->eflags);
        printf("useresp: %i\n", r->useresp);
        printf("ss: %i\n", r->ss);
    }
};

#endif
