#ifndef _CMD_H_
#define _CMD_H_

#define ADD_CMD(name)                       \
    class name : public CMD                 \
    {                                       \
    public:                                 \
        int execute();      \
    };

class CMD_MANAGER
{
public:
    static int execute(char* cmd);
};

class CMD
{
public:
    virtual int execute();
};

/* SHELL CMDS */
ADD_CMD(CMD_Clear);
ADD_CMD(CMD_Shutdown);
ADD_CMD(CMD_Reboot);
ADD_CMD(CMD_Halt);
ADD_CMD(CMD_Date);
ADD_CMD(CMD_Test);

#endif
