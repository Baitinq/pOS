#ifndef _PRINTF_INTERNAL_H_
#define _PRINTF_INTERNAL_H_

#include <stdarg.h>
#include <string.h>
#include <math.h>

/* FROM SERENITYOS */

static constexpr const char* printf_hex_digits_lower = "0123456789abcdef";
static constexpr const char* printf_hex_digits_upper = "0123456789ABCDEF";

template<typename PutChFunc, typename T>
inline int print_hex(PutChFunc putch, char*& bufptr, T number, bool upper_case, bool alternate_form, bool left_pad, bool zero_pad, uint8_t field_width)
{
    int ret = 0;

    int digits = 0;
    for (T n = number; n > 0; n >>= 4)
        ++digits;
    if (digits == 0)
        digits = 1;

    if (left_pad) {
        int stop_at = field_width - digits;
        if (alternate_form)
            stop_at -= 2;

        while (ret < stop_at) {
            putch(bufptr, ' ');
            ++ret;
        }
    }

    if (alternate_form) {
        putch(bufptr, '0');
        putch(bufptr, 'x');
        ret += 2;
        field_width += 2;
    }

    if (zero_pad) {
        while (ret < field_width - digits) {
            putch(bufptr, '0');
            ++ret;
        }
    }

    if (number == 0) {
        putch(bufptr, '0');
        ++ret;
    } else {
        uint8_t shift_count = digits * 4;
        while (shift_count) {
            shift_count -= 4;
            putch(bufptr,
                upper_case
                    ? printf_hex_digits_upper[(number >> shift_count) & 0x0f]
                    : printf_hex_digits_lower[(number >> shift_count) & 0x0f]);
            ++ret;
        }
    }

    return ret;
}

template<typename PutChFunc>
inline int print_number(PutChFunc putch, char*& bufptr, uint32_t number, bool left_pad, bool zero_pad, uint32_t field_width)
{
    uint32_t divisor = 1000000000;
    char ch;
    char padding = 1;
    char buf[16];
    char* p = buf;

    for (;;) {
        ch = '0' + (number / divisor);
        number %= divisor;
        if (ch != '0')
            padding = 0;
        if (!padding || divisor == 1)
            *(p++) = ch;
        if (divisor == 1)
            break;
        divisor /= 10;
    }

    size_t numlen = p - buf;
    if (!field_width || field_width < numlen)
        field_width = numlen;
    if (!left_pad) {
        for (unsigned i = 0; i < field_width - numlen; ++i) {
            putch(bufptr, zero_pad ? '0' : ' ');
        }
    }
    for (unsigned i = 0; i < numlen; ++i) {
        putch(bufptr, buf[i]);
    }
    if (left_pad) {
        for (unsigned i = 0; i < field_width - numlen; ++i) {
            putch(bufptr, ' ');
        }
    }

    return field_width;
}

template<typename PutChFunc>
inline int print_uint64_t(PutChFunc putch, char*& bufptr, uint64_t number, bool left_pad, bool zero_pad, uint32_t field_width)
{
    uint64_t divisor = 10000000000000000000LLU;
    char ch;
    char padding = 1;
    char buf[16];
    char* p = buf;

    for (;;) {
        ch = '0' + (number / divisor);
        number %= divisor;
        if (ch != '0')
            padding = 0;
        if (!padding || divisor == 1)
            *(p++) = ch;
        if (divisor == 1)
            break;
        divisor /= 10;
    }

    size_t numlen = p - buf;
    if (!field_width || field_width < numlen)
        field_width = numlen;
    if (!left_pad) {
        for (unsigned i = 0; i < field_width - numlen; ++i) {
            putch(bufptr, zero_pad ? '0' : ' ');
        }
    }
    for (unsigned i = 0; i < numlen; ++i) {
        putch(bufptr, buf[i]);
    }
    if (left_pad) {
        for (unsigned i = 0; i < field_width - numlen; ++i) {
            putch(bufptr, ' ');
        }
    }

    return field_width;
}

template<typename PutChFunc>
inline int print_double(PutChFunc putch, char*& bufptr, double number, bool left_pad, bool zero_pad, uint32_t field_width, uint32_t fraction_length = 6)
{
    int length = 0;

    if (number < 0) {
        putch(bufptr, '-');
        length++;
        number = 0 - number;
    }

    length = print_uint64_t(putch, bufptr, (int64_t)number, left_pad, zero_pad, field_width);
    putch(bufptr, '.');
    length++;
    double fraction = number - (int64_t)number;

    for (uint32_t i = 0; i < fraction_length; ++i)
        fraction = fraction * 10;

    return length + print_uint64_t(putch, bufptr, (int64_t)fraction, false, true, fraction_length);
}

template<typename PutChFunc>
inline int print_int64_t(PutChFunc putch, char*& bufptr, int64_t number, bool left_pad, bool zero_pad, uint32_t field_width)
{
    if (number < 0) {
        putch(bufptr, '-');
        return print_uint64_t(putch, bufptr, 0 - number, left_pad, zero_pad, field_width) + 1;
    }
    return print_uint64_t(putch, bufptr, number, left_pad, zero_pad, field_width);
}

template<typename PutChFunc>
inline int print_octal_number(PutChFunc putch, char*& bufptr, uint32_t number, bool left_pad, bool zero_pad, uint32_t field_width)
{
    uint32_t divisor = 134217728;
    char ch;
    char padding = 1;
    char buf[32];
    char* p = buf;

    for (;;) {
        ch = '0' + (number / divisor);
        number %= divisor;
        if (ch != '0')
            padding = 0;
        if (!padding || divisor == 1)
            *(p++) = ch;
        if (divisor == 1)
            break;
        divisor /= 8;
    }

    size_t numlen = p - buf;
    if (!field_width || field_width < numlen)
        field_width = numlen;
    if (!left_pad) {
        for (unsigned i = 0; i < field_width - numlen; ++i) {
            putch(bufptr, zero_pad ? '0' : ' ');
        }
    }
    for (unsigned i = 0; i < numlen; ++i) {
        putch(bufptr, buf[i]);
    }
    if (left_pad) {
        for (unsigned i = 0; i < field_width - numlen; ++i) {
            putch(bufptr, ' ');
        }
    }

    return field_width;
}

template<typename PutChFunc>
inline int print_string(PutChFunc putch, char*& bufptr, const char* str, size_t len, bool left_pad, size_t field_width, bool dot)
{
    if (!dot && (!field_width || field_width < len))
        field_width = len;
    size_t pad_amount = field_width > len ? field_width - len : 0;

    if (!left_pad) {
        for (size_t i = 0; i < pad_amount; ++i)
            putch(bufptr, ' ');
    }
    for (int i = 0; i < min(len, field_width); ++i) {
        putch(bufptr, str[i]);
    }
    if (left_pad) {
        for (size_t i = 0; i < pad_amount; ++i)
            putch(bufptr, ' ');
    }
    return field_width;
}

template<typename PutChFunc>
inline int print_signed_number(PutChFunc putch, char*& bufptr, int number, bool left_pad, bool zero_pad, uint32_t field_width, bool always_sign)
{
    if (number < 0) {
        putch(bufptr, '-');
        return print_number(putch, bufptr, 0 - number, left_pad, zero_pad, field_width) + 1;
    }
    if (always_sign)
        putch(bufptr, '+');
    return print_number(putch, bufptr, number, left_pad, zero_pad, field_width);
}

template<typename PutChFunc>
inline int printf_internal(PutChFunc putch, char* buffer, const char*& fmt, va_list ap)
{
    const char* p;

    int ret = 0;
    char* bufptr = buffer;

    for (p = fmt; *p; ++p) {
        bool left_pad = false;
        bool zero_pad = false;
        bool dot = false;
        unsigned field_width = 0;
        unsigned fraction_length = 0;
        unsigned long_qualifiers = 0;
        bool size_qualifier = false;
        (void)size_qualifier;
        bool alternate_form = 0;
        bool always_sign = false;
        if (*p == '%' && *(p + 1)) {
        one_more:
            ++p;
            if (*p == '.') {
                dot = true;
                if (*(p + 1))
                    goto one_more;
            }
            if (*p == '-') {
                left_pad = true;
                if (*(p + 1))
                    goto one_more;
            }
            if (*p == '+') {
                always_sign = true;
                if (*(p + 1))
                    goto one_more;
            }
            if (!zero_pad && !field_width && *p == '0') {
                zero_pad = true;
                if (*(p + 1))
                    goto one_more;
            }
            if (*p >= '0' && *p <= '9') {
                if (!dot) {
                    field_width *= 10;
                    field_width += *p - '0';
                    if (*(p + 1))
                        goto one_more;
                } else {
                    fraction_length *= 10;
                    fraction_length += *p - '0';
                    if (*(p + 1))
                        goto one_more;
                }
            }
            if (*p == '*') {
                field_width = va_arg(ap, int);
                if (*(p + 1))
                    goto one_more;
            }
            if (*p == 'l') {
                ++long_qualifiers;
                if (*(p + 1))
                    goto one_more;
            }
            if (*p == 'z') {
                size_qualifier = true;
                if (*(p + 1))
                    goto one_more;
            }
            if (*p == '#') {
                alternate_form = true;
                if (*(p + 1))
                    goto one_more;
            }
            switch (*p) {
            case 's': {
                const char* sp = va_arg(ap, const char*);
                if (!sp)
                    sp = "(null)";
                ret += print_string(putch, bufptr, sp, strlen(sp), left_pad, field_width, dot);
            } break;

            case 'd':
            case 'i':
                if (long_qualifiers >= 2)
                    ret += print_int64_t(putch, bufptr, va_arg(ap, int64_t), left_pad, zero_pad, field_width);
                else
                    ret += print_signed_number(putch, bufptr, va_arg(ap, int), left_pad, zero_pad, field_width, always_sign);
                break;

            case 'u':
                if (long_qualifiers >= 2)
                    ret += print_uint64_t(putch, bufptr, va_arg(ap, uint64_t), left_pad, zero_pad, field_width);
                else
                    ret += print_number(putch, bufptr, va_arg(ap, uint32_t), left_pad, zero_pad, field_width);
                break;

            case 'Q':
                ret += print_uint64_t(putch, bufptr, va_arg(ap, uint64_t), left_pad, zero_pad, field_width);
                break;

            case 'q':
                ret += print_hex(putch, bufptr, va_arg(ap, uint64_t), false, false, left_pad, zero_pad, 16);
                break;

            case 'o':
                if (alternate_form) {
                    putch(bufptr, '0');
                    ++ret;
                }
                ret += print_octal_number(putch, bufptr, va_arg(ap, uint32_t), left_pad, zero_pad, field_width);
                break;

            case 'X':
            case 'x':
                ret += print_hex(putch, bufptr, va_arg(ap, uint32_t), *p == 'X', alternate_form, left_pad, zero_pad, field_width);
                break;

            case 'w':
                ret += print_hex(putch, bufptr, va_arg(ap, int), false, alternate_form, false, true, 4);
                break;

            case 'b':
                ret += print_hex(putch, bufptr, va_arg(ap, int), false, alternate_form, false, true, 2);
                break;

            case 'c': {
                char c = va_arg(ap, int);
                ret += print_string(putch, bufptr, &c, 1, left_pad, field_width, dot);
            } break;

            case '%':
                putch(bufptr, '%');
                ++ret;
                break;

            case 'P':
            case 'p':
                ret += print_hex(putch, bufptr, va_arg(ap, uint32_t), *p == 'P', true, false, true, 8);
                break;

            case 'n':
                *va_arg(ap, int*) = ret;
                break;
            }
        } else {
            putch(bufptr, *p);
            ++ret;
        }
    }
    return ret;
}

#endif
