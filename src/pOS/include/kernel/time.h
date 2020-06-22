#ifndef _TIME_H_
#define _TIME_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct timedate
{
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    uint8_t year;
    uint8_t century;
    uint8_t millennia;
};

#include <kernel/rtc.h>

class Time
{
public:
    static timedate get_date(void);
    static uint8_t get_second(void);
    static uint8_t get_minute(void);
    static uint8_t get_hour(void);
    static uint8_t get_day(void);
    static uint8_t get_month(void);
    static uint8_t get_year(void);
    static uint8_t get_century(void);
    static uint8_t get_millennium(void);
    static const char* get_day_string(void);
    static const char* get_day_string(int day);
    static const char* get_month_string(void);
    static const char* get_month_string(int month);
    static const char* get_weekday(void);
    static const char* get_weekday(timedate date);
    static const char* get_date_formatted(void);
};

#endif
