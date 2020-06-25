#include <kernel/shell/shell.h>

char Shell::prefix[10];
static int indx = 0;
static char cmd[20];        /* Mem management */

void signal_handler(Signal_Type signal)
{
    switch(signal)
    {
        case ESC_SIG:
            break;
        case LEFT_ARROW_SIG:
            if(indx - 1 >= 0)
            {
                TTY::tty_cursor_move(-1, 0);
                indx--;
            }
            break;
        case RIGHT_ARROW_SIG:
            TTY::tty_cursor_move(+1, 0);
            if(cmd[indx] == 0)
                cmd[indx] = ' ';
            indx++;
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
    Shell::set_prefix(SHELL_PREFIX);
    Signals::register_recieve(signal_handler);
    return run();
}

int Shell::run(void)
{
    char c;
    int return_code = 0;
    printf("%s ", Shell::prefix);
    while((c = getc()) && c != EOF)
    {
        putc(c);

        if(c == '\b')
        {
            cmd[indx] = c;
        }
        else if(c == '\n')
        {
            indx = 0;

            return_code = CMD_MANAGER::execute(cmd);

            char retstr[5];
            sprintf(retstr, "(%d)", return_code);
            if(!return_code)
                retstr[0] = '\0';

            printf("%s%s ", retstr, Shell::prefix);
            memset(cmd, 0, 20);
        }
        else
        {
            cmd[indx++] = c;
        }
    }

    ASSERT(c == EOF);
    return 0;
}

void Shell::set_prefix(const char* new_prefix)
{
    strncpy(prefix, new_prefix, sizeof(prefix));
}
