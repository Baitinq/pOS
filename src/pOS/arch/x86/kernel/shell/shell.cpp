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
    Shell::set_prefix("pOS#");
    Signals::register_recieve(signal_handler);
    return run();
}

int Shell::run(void)
{
    char c;
    int return_code = 0;
    int indx = 0;
    char cmd[20];        /* Mem management */
    printf("%s ", Shell::prefix);
    while((c = getc()) && c != EOF)
    {
        putc(c);

        if(c == '\b')
            indx--;
        else if(c == '\n')
        {
            cmd[indx] = '\0';
            indx = 0;

            return_code = CMD_MANAGER::execute(cmd);

            char retstr[5];
            sprintf(retstr, "(%d)", return_code);
            if(!return_code)
                retstr[0] = '\0';
            printf("%s%s ", retstr, Shell::prefix);
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
