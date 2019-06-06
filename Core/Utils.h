#pragma once

#include <string>

namespace HellGateBot
{
    struct SimpleDate
    {
        int day;
        int month;
        int year;

        SimpleDate() = default;
        SimpleDate(int _day, int _month, int _year);
        bool operator ==(const SimpleDate &right);
    };

    struct SimpleTime
    {
        int hours;
        int minutes;

        SimpleTime() = default;
        SimpleTime(int _hours, int _minutes);
        bool operator <=(const SimpleTime &right);
    };

    std::string replace(std::string source, std::string pattern, std::string with);

    class HellGateException : public std::exception
    {
    public:
        HellGateException(std::string _message);
        const char*	what();
    private:
        std::string message;
    };

    void log(std::string message);
}
