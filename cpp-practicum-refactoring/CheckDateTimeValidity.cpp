#include <array>
#include <stdexcept>
#include <string>

using namespace std;

// Константы сообщений об ошибках
const string ERRORS[] = {
    "year is too small", "year is too big", "month is too small",
    "month is too big", "day is too small", "day is too big",
    "hour is too small", "hour is too big", "minute is too small",
    "minute is too big", "second is too small", "second is too big"
};

struct DateTime {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

static void CheckDateTimeValidity(const DateTime& dt) {
    if (dt.year < 1 || dt.year > 9999) {
        throw domain_error(dt.year < 1 ? ERRORS[0] : ERRORS[1]);
    }

    if (dt.month < 1 || dt.month > 12) {
        throw domain_error(dt.month < 1 ? ERRORS[2] : ERRORS[3]);
    }

    const bool is_leap_year = (dt.year % 4 == 0) && (dt.year % 100 != 0 || dt.year % 400 == 0);
    const array<int, 12> month_lengths = { 31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (dt.day < 1 || dt.day > month_lengths[dt.month - 1]) {
        throw domain_error(dt.day < 1 ? ERRORS[4] : ERRORS[5]);
    }

    if (dt.hour < 0 || dt.hour > 23) {
        throw domain_error(dt.hour < 0 ? ERRORS[6] : ERRORS[7]);
    }

    if (dt.minute < 0 || dt.minute > 59) {
        throw domain_error(dt.minute < 0 ? ERRORS[8] : ERRORS[9]);
    }

    if (dt.second < 0 || dt.second > 59) {
        throw domain_error(dt.second < 0 ? ERRORS[10] : ERRORS[11]);
    }
}