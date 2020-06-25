#include <string.h>
#include <stdio.h>
#include <kernel/shell/cmd.h>

#include <kernel/debug.h>

int CMD_MANAGER::execute(char* cmd)
{
    //char* arg = strtok(cmd, " ");

    dbgprintf("cmd: %s\n", cmd);

    switch(str2int(cmd))
    {
        case str2int("clear"):
        case str2int("cls"):
        case str2int("c"):
             return CMD_Clear().execute(cmd);

        case str2int("date"):
        case str2int("time"):
            return CMD_Date().execute(cmd);

        case str2int("halt"):
        case str2int("hlt"):
            return CMD_Halt().execute(cmd);

        case str2int("shutdown"):
            return CMD_Shutdown().execute(cmd);

        case str2int("reboot"):
            return CMD_Reboot().execute(cmd);

        case str2int("test"):
        case str2int("t"):
            return CMD_Test().execute(cmd);
    }

    printf("Unknown cmd: %s\n", cmd);
    return -1;
}
