#include <kernel/shell/shell.h>

char Shell::prefix[10];

int Shell::init(void)
{
    Shell::set_prefix("pOS# ");
    return run();
}

int Shell::run(void)
{
    char c;
    char cmd[20];        /* Mem management */
    int indx = 0;
    printf("pOS# ");
    while((c = getc()) && c != EOF)
    {
        putc(c);
        /* TODO: Handle signals */
        if(c == '\b')
            indx--;
        else if(c == '\n')
        {
            cmd[indx] = '\0';
            indx = 0;

            CMD_MANAGER::execute(cmd);

            printf(Shell::prefix);
        }
        else
            cmd[indx++] = c;
    }

    ASSERT(c == EOF);
    return 0;
}

void Shell::set_prefix(const char* new_prefix)
{
    strncpy(prefix, new_prefix, sizeof(prefix));
}
