#ifndef _RTC_H_
#define _RTC_H_

#include <stdint.h>
#include <kernel/time.h>
#include <kernel/system.h>

#define CMOS_PORT 0x70
#define CMOS_DATA 0x71

#define CMOS_READ_SECOND 0x00
#define CMOS_READ_MINUTE 0x02
#define CMOS_READ_HOUR 0x04
#define CMOS_READ_DAY 0x07
#define CMOS_READ_MONTH 0x08
#define CMOS_READ_YEAR 0x09

#define CURRENT_CENTURY 21
#define CURRENT_MILLENNIUM 3

class RTC
{
public:
    static timedate get_date(void);
private:
    static int get_update_in_progress_flag(void);
    static uint8_t read_cmos(uint8_t registr);
};

#endif
