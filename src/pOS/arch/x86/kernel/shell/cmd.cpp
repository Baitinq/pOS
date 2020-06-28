#include <string.h>
#include <stdio.h>
#include <kernel/shell/cmd.h>

#include <kernel/debug.h>

int CMD_MANAGER::execute(char* cmd)
{
    dbgprintf("cmd: %s\n", cmd);

    char* args = strtok(cmd, " ");

    switch(str2int(args))
    {
        case str2int("clear"):
        case str2int("cls"):
        case str2int("c"):
             return CMD_Clear().execute();

        case str2int("date"):
        case str2int("time"):
            return CMD_Date().execute();

        case str2int("halt"):
        case str2int("hlt"):
            return CMD_Halt().execute();

        case str2int("shutdown"):
            return CMD_Shutdown().execute();

        case str2int("reboot"):
            return CMD_Reboot().execute();

        case str2int("test"):
        case str2int("t"):
            return CMD_Test().execute();
    }

    printf("Unknown cmd: %s\n", args);
    return -1;
}
