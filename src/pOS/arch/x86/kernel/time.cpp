#include <kernel/time.h>

static constexpr const char* months[12] = {
    "January",
    "Febuary",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};

static constexpr const char* days[7] = {
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday"
};

timedate Time::get_date(void)
{
    return RTC::get_date();
}

uint8_t Time::get_second(void)
{
    return Time::get_date().second;
}

uint8_t Time::get_minute(void)
{
    return Time::get_date().minute;
}

uint8_t Time::get_hour(void)
{
    return Time::get_date().hour;
}

uint8_t Time::get_day(void)
{
    return Time::get_date().day;
}

uint8_t Time::get_month(void)
{
    return Time::get_date().month;
}

uint8_t Time::get_year(void)
{
    return Time::get_date().year;
}

uint8_t Time::get_century(void)
{
    return Time::get_date().century;
}

uint8_t Time::get_millennium(void)
{
    return Time::get_date().millennia;
}

const char* Time::get_day_string(void)
{
    return days[0]; //TODO
}

const char* Time::get_day_string(int day)
{
    return days[day - 1];
}

const char* Time::get_month_string(void)
{
    return months[get_month() - 1];
}

const char* Time::get_month_string(int month)
{
    return months[month - 1];
}

const char* Time::get_weekday(void)
{
    timedate date = RTC::get_date();
    UNUSED_VARIABLE(date);
    return days[0]; //TODO
}

const char* Time::get_weekday(timedate date)
{
    UNUSED_VARIABLE(date);
    return days[0]; //TODO
}

const char* Time::get_date_formatted(void)
{
    //HH:MM:SS
    static char buf[9]; //temp as we dont have mem alloc
    itoa(get_hour(), buf, 2);
    if(strlen(buf) == 1)
    {
        buf[1] = buf[0];
        buf[0] = '0';
    }
    buf[2] = ':';
    itoa(get_minute(), buf + 3, 2);
    if(strlen(buf) == 4)
    {
        buf[4] = buf[3];
        buf[3] = '0';
    }
    buf[5] = ':';
    itoa(get_second(), buf + 6, 2);
    if(strlen(buf) == 7)
    {
        buf[7] = buf[6];
        buf[6] = '0';
    }

    buf[8] = '\0';

    return buf;
}
