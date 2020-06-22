#include <kernel/rtc.h>

int RTC::get_update_in_progress_flag(void)
{
      System::outb(CMOS_PORT, 0x0A);
      return (System::inb(CMOS_DATA) & 0x80);
}

uint8_t RTC::read_cmos(uint8_t registr)
{
    uint8_t result;
    System::outb(CMOS_PORT, registr);
    do
        result = System::inb(CMOS_DATA);
    while(RTC::get_update_in_progress_flag());

    System::outb(CMOS_PORT, 0x0B);
    if(!(System::inb(CMOS_DATA) & 0x04)) //to binary
        result = (result & 0x0F) + ((result/ 16) * 10);

    return result;
}

timedate RTC::get_date(void)
{
    return timedate {
                    RTC::read_cmos(CMOS_READ_SECOND),
                    RTC::read_cmos(CMOS_READ_MINUTE),
                    RTC::read_cmos(CMOS_READ_HOUR),
                    RTC::read_cmos(CMOS_READ_DAY),
                    RTC::read_cmos(CMOS_READ_MONTH),
                    RTC::read_cmos(CMOS_READ_YEAR),
                    CURRENT_CENTURY,
                    CURRENT_MILLENNIUM
                };
}
