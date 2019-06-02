#include "Utils.h"

namespace HellGateBot
{
    std::string replace(std::string source, std::string pattern, std::string with)
    {
        auto beginning = source.find(pattern);
        if (beginning != 0)
        {
            source = source.replace(beginning, pattern.size(), with);
        }

        return source;
    }

    SimpleDate::SimpleDate(int _day, int _month, int _year)
    {
        day = _day;
        month = _month;
        year = _year;
    }

    bool SimpleDate::operator ==(const SimpleDate &right)
    {
        return year == right.year && month == right.month && day == right.day;
    }

    SimpleTime::SimpleTime(int _hours, int _minutes)
    {
        hours = _hours;
        minutes = _minutes;
    }

    bool SimpleTime::operator <(const SimpleTime &right)
    {
        return hours * 60 + minutes < right.hours * 60 + right.minutes;
    }

    HellGateException::HellGateException(std::string _message)
    {
        message = _message;
    }

    const char *HellGateException::what()
    {
        return message.c_str();
    }

}
