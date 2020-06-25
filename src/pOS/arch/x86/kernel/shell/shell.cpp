#include <kernel/shell/shell.h>

char Shell::prefix[10];

void signal_handler(Signal_Type signal)
{
    switch(signal)
    {
        case ESC_SIG:
            break;
        case LEFT_ARROW_SIG:
            TTY::tty_cursor_move(-1, 0);
            break;
        case RIGHT_ARROW_SIG:
            TTY::tty_cursor_move(+1, 0);
            break;
        case UP_ARROW_SIG:
            /* TODO: implement history */
            break;
        case DOWN_ARROW_SIG:
            break;
        case KILL_SIG:
            break;
    }
}

int Shell::init(void)
{
    Shell::set_prefix("pOS# ");
    Signals::register_recieve(signal_handler);
    return run();
}

int Shell::run(void)
{
    char c;
    int indx = 0;
    char cmd[20];        /* Mem management */
    printf("pOS# ");
    while((c = getc()) && c != EOF)
    {
        putc(c);

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
